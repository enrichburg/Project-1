#include "garage.h"
#include <iostream>

Garage::Garage() {

    capacity = 0;

}

Garage::Garage(int capacity)

    : spaces(), freeSpots(), capacity(capacity) {
    spaces.reserve(capacity);

}

Garage::Garage(int capacity, vector<string> initialSpaces)

    : spaces(move(initialSpaces)), freeSpots(), capacity(capacity) {
    // push free spots in increasing order so the next spot to fill is on top
    for (int i = 0; i < static_cast<int>(spaces.size()); ++i) {
        if (spaces[i] == "-1") {
            freeSpots.push(i);
        }
    }

}

// Loads one spot value while reading occupancy.csv; "R" cells never enter freeSpots.
void Garage::SetSpace(const string& space) {

    if (static_cast<int>(spaces.size()) < capacity) {
        int index = static_cast<int>(spaces.size());
        spaces.push_back(space);
        if (space == "-1") {
            freeSpots.push(index);
        }
    }

}

// Parks a car in the next open spot; returns the spot index (-1 if full).
int Garage::ParkCustomer(const string& id) {

    if (freeSpots.empty()) {
        return -1;
    }
    int spot = freeSpots.top();
    freeSpots.pop();
    spaces[spot] = id;
    return spot;

}

// Removes the top car of the stack and returns its id ("" if no cars).
string Garage::RemoveCustomer() {

    int top = GetTopOccupiedIndex();
    if (top == -1) {
        return "";
    }
    string removed = spaces[top];
    spaces[top] = "-1";
    freeSpots.push(top);
    return removed;

}

bool Garage::IsAvailable() const { return !freeSpots.empty(); }
int Garage::GetAvailableCount() const { return static_cast<int>(freeSpots.size()); }

// Returns the row index of the topmost car, or -1 if the garage has no cars.
int Garage::GetTopOccupiedIndex() const {

    for (int i = 0; i < static_cast<int>(spaces.size()); ++i) {
        if (spaces[i] != "-1" && spaces[i] != "R") {
            return i;
        }
    }
    return -1;

}

string Garage::GetSpotValue(int index) const {

    if (index < 0 || index >= static_cast<int>(spaces.size())) {
        return "";
    }
    return spaces[index];

}

void Garage::PrintLayout() const {

    for (const auto& space : spaces) {
        cout << space << endl;
    }

}
