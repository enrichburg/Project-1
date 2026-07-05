#include "qparking.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stack>

QParkingSystem::QParkingSystem() {

    numberOfGarages = 0;
    garageCapacity = 0;
    interactionsFile = "";

}

static string Trim(const string& value) {

    size_t first = value.find_first_not_of(" \t\r\n");
    size_t last = value.find_last_not_of(" \t\r\n");
    if (first == string::npos || last == string::npos) {
        return "";
    }
    return value.substr(first, last - first + 1);

}

static vector<string> SplitCsvLine(const string& line) {

    vector<string> tokens;
    stringstream ss(line);
    string token;
    while (getline(ss, token, ',')) {
        tokens.push_back(Trim(token));
    }
    return tokens;

}

// Looks up a customer by id; returns their index in the vector, or -1.
int QParkingSystem::FindCustomerIndex(const string& customerId) const {

    for (int i = 0; i < static_cast<int>(customers.size()); ++i) {
        if (customers[i].GetId() == customerId) {
            return i;
        }
    }
    return -1;

}

bool QParkingSystem::LoadConfiguration(const string& fileName) {

    ifstream configFile(fileName);
    if (!configFile.is_open()) {
        return false;
    }

    if (!(configFile >> numberOfGarages >> garageCapacity)) {
        return false;
    }

    string occupancyFile;
    string customerFile;
    string line;
    getline(configFile, line);

    if (!getline(configFile, occupancyFile) || occupancyFile.empty()) {
        return false;
    }
    occupancyFile = Trim(occupancyFile);

    if (!getline(configFile, customerFile) || customerFile.empty()) {
        return false;
    }
    customerFile = Trim(customerFile);

    // Component 2: optional 4th line names the interactions file. A missing or
    // empty line simply means there are no interactions to run (still valid).
    string interactionsLine;
    if (getline(configFile, interactionsLine)) {
        interactionsFile = Trim(interactionsLine);
    }

    garages.clear();
    garages.reserve(numberOfGarages);
    for (int i = 0; i < numberOfGarages; ++i) {
        garages.emplace_back(garageCapacity);
    }

    ifstream occupancyStream(occupancyFile);
    if (!occupancyStream.is_open()) {
        return false;
    }

    int currentRow = 0;
    while (currentRow < garageCapacity && getline(occupancyStream, line)) {
        if (Trim(line).empty()) {
            continue;
        }

        vector<string> rowValues = SplitCsvLine(line);
        if (static_cast<int>(rowValues.size()) != numberOfGarages) {
            return false;
        }

        for (int column = 0; column < numberOfGarages; ++column) {
            garages[column].SetSpace(rowValues[column]);
        }

        ++currentRow;
    }

    if (currentRow != garageCapacity) {
        return false;
    }

    ifstream customerStream(customerFile);
    if (!customerStream.is_open()) {
        return false;
    }

    customers.clear();
    int customerIndex = 1;
    while (getline(customerStream, line)) {
        if (Trim(line).empty()) {
            continue;
        }

        vector<string> fields = SplitCsvLine(line);
        if (fields.size() < 4) {
            return false;
        }

        string id = to_string(customerIndex++);
        customers.emplace_back(id, fields[0], fields[1], fields[2], fields[3], false, -1, -1);
    }

    for (int row = 0; row < garageCapacity; ++row) {
        for (int garageIndex = 0; garageIndex < numberOfGarages; ++garageIndex) {
            string spotValue = garages[garageIndex].GetSpotValue(row);
            if (spotValue != "-1" && spotValue != "R") {
                bool matched = false;
                for (auto& customer : customers) {
                    if (customer.GetId() == spotValue) {
                        customer.SetParkingLocation(garageIndex, row);
                        matched = true;
                        break;
                    }
                }
                if (!matched) {
                    return false;
                }
            }
        }
    }

    return true;
}

// Component 2: read the interactions file and execute each line. A "D" line
// registers a new customer and parks them (C3); a "P" line retrieves a car
// (C4/C5). Parsing is tolerant of spaces around the tokens.
void QParkingSystem::ProcessInteractions() {

    if (interactionsFile.empty()) {
        return;
    }

    ifstream stream(interactionsFile);
    if (!stream.is_open()) {
        cout << "No interactions file to process.\n";
        return;
    }

    cout << "\n--- Processing interactions ---\n";

    string line;
    while (getline(stream, line)) {
        line = Trim(line);
        if (line.empty()) {
            continue;
        }

        // split the command letter from the rest of the line at the first ':'
        size_t colon = line.find(':');
        if (colon == string::npos) {
            continue;
        }
        string command = Trim(line.substr(0, colon));
        string rest = Trim(line.substr(colon + 1));

        if (command == "D") {
            // D: name, phone, time -> new customer drops off a car
            vector<string> fields = SplitCsvLine(rest);
            if (fields.size() < 3) {
                continue;
            }
            // new drop-off customers continue the sequential ids after the roster
            string id = to_string(customers.size() + 1);
            customers.emplace_back(id, fields[0], fields[1], fields[2], "-1", false, -1, -1);
            cout << "Drop-off: customer " << id << " (" << fields[0]
                 << ") arrived at " << fields[2] << "\n";
            AssignParkingSpace(id);
        }
        else if (command == "P") {
            // P: customerID -> customer picks up their car
            string id = Trim(rest);
            cout << "Pick-up: customer " << id << " requested their car\n";
            RetrieveCar(id);
        }
    }

    cout << "--- Interactions complete ---\n";

}

// Component 3: choose a garage for a dropped-off car. Reserved spots are never
// used; the garage with the most free spots wins (ties go to the lowest index)
// so the load stays balanced. Returns false when the lot is full.
bool QParkingSystem::AssignParkingSpace(const string& customerId) {

    int bestGarage = -1;
    int bestCount = 0;
    for (int i = 0; i < numberOfGarages; ++i) {
        int count = garages[i].GetAvailableCount();
        if (count > bestCount) {
            bestCount = count;
            bestGarage = i;
        }
    }

    if (bestGarage == -1) {
        cout << "  lot full: no space available for customer " << customerId << "\n";
        return false;
    }

    int spot = garages[bestGarage].ParkCustomer(customerId);
    int customerIndex = FindCustomerIndex(customerId);
    if (customerIndex != -1) {
        customers[customerIndex].SetParkingLocation(bestGarage, spot);
    }

    cout << "  parked customer " << customerId << " in garage " << bestGarage
         << ", spot " << spot << "\n";
    return true;

}

// Component 4: resolve a customer id to its parked location. Kept small and
// self-contained; all pick-up code routes location lookups through here.
bool QParkingSystem::LocateCar(const string& customerId, int& garageIndex, int& spotIndex) const {

    for (const auto& customer : customers) {
        if (customer.GetId() == customerId && customer.IsParked()) {
            garageIndex = customer.GetGarageIndex();
            spotIndex = customer.GetSpotIndex();
            return true;
        }
    }

    return false;

}

// Component 5: retrieve a customer's car. Cars stacked above the target are
// popped onto a temporary stack, then pushed back so their order is preserved.
bool QParkingSystem::RetrieveCar(const string& customerId) {

    int garageIndex = -1;
    int spotIndex = -1;

    if (!LocateCar(customerId, garageIndex, spotIndex)) {
        cout << "  could not retrieve car for customer " << customerId
             << " (not found or not parked)\n";
        return false;
    }

    // move the cars above the target aside; the reserved spaces are what
    // physically guarantee the valet always has room for this shuffle
    stack<string> movedCars;
    while (garages[garageIndex].GetTopOccupiedIndex() != spotIndex) {
        movedCars.push(garages[garageIndex].RemoveCustomer());
        cout << "  moved car " << movedCars.top() << " aside\n";
    }

    string retrieved = garages[garageIndex].RemoveCustomer();
    int retrievedIndex = FindCustomerIndex(retrieved);
    if (retrievedIndex != -1) {
        customers[retrievedIndex].ClearParkingLocation();
    }
    cout << "  car " << retrieved << " retrieved from garage " << garageIndex << "\n";

    // popping the temporary stack returns the cars in LIFO order, which
    // restores their original stacking order in the garage
    while (!movedCars.empty()) {
        string movedId = movedCars.top();
        movedCars.pop();
        int spot = garages[garageIndex].ParkCustomer(movedId);
        int movedIndex = FindCustomerIndex(movedId);
        if (movedIndex != -1) {
            customers[movedIndex].SetParkingLocation(garageIndex, spot);
        }
        cout << "  returned car " << movedId << " to garage " << garageIndex
             << ", spot " << spot << "\n";
    }

    return true;

}

// Component 6: total free (non-reserved) spots across all garages. Small and
// self-contained (display only) -- it is the sum of each garage's own count.
int QParkingSystem::GetAvailableSpaces() const {

    int totalAvailable = 0;
    for (const auto& garage : garages) {
        totalAvailable += garage.GetAvailableCount();
    }
    return totalAvailable;

}

// Component 6: print the current lot layout plus each garage's available count
// (read straight from the garages) and the overall availability total.
void QParkingSystem::PrintStatus() const {

    cout << "\n--- Parking lot status ---\n";
    for (int row = 0; row < garageCapacity; ++row) {
        for (int column = 0; column < numberOfGarages; ++column) {
            cout << garages[column].GetSpotValue(row);
            if (column < numberOfGarages - 1) {
                cout << "\t";
            }
        }
        cout << "\n";
    }

    for (int i = 0; i < numberOfGarages; ++i) {
        cout << "Garage " << i << " available: " << garages[i].GetAvailableCount() << "\n";
    }
    cout << "Total available spaces: " << GetAvailableSpaces() << "\n";

}

void QParkingSystem::WriteOccupancy() const {

    ofstream output("output.txt");
    if (!output.is_open()) {
        return;
    }

    for (int row = 0; row < garageCapacity; ++row) {
        for (int column = 0; column < numberOfGarages; ++column) {
            output << garages[column].GetSpotValue(row);
            if (column < numberOfGarages - 1) {
                output << ",";
            }
        }
        output << "\n";
    }

}
