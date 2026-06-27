#include "qparking.h"
#include <fstream>
#include <sstream>

QParkingSystem::QParkingSystem() {

    numberOfGarages = 0;
    garageCapacity = 0;

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

bool QParkingSystem::AssignParkingSpace() { return false; }
bool QParkingSystem::RetrieveCar() { return false; }
int QParkingSystem::GetAvailableSpaces() const { return 0; }

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
