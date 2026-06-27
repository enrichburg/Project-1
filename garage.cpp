#include "garage.h"
#include <iostream>

Garage::Garage() {

    capacity = 0;
    freeSpots = 0;

}

Garage::Garage(int capacity)

    : spaces(), freeSpots(0), capacity(capacity) {
    spaces.reserve(capacity);

}

Garage::Garage(int capacity, vector<string> initialSpaces)

    : spaces(move(initialSpaces)), freeSpots(0), capacity(capacity) {
    for (const auto& space : spaces) {
        if (space == "-1") {
            ++freeSpots;
        }
    }

}

void Garage::SetSpace(const string& space) {

    if (static_cast<int>(spaces.size()) < capacity) {
        spaces.push_back(space);
        if (space == "-1") {
            ++freeSpots;
        }
    }

}

bool Garage::ParkCustomer() { return false; }
bool Garage::RemoveCustomer() { return false; }
bool Garage::IsAvailable() const { return freeSpots > 0; }
int Garage::GetAvailableCount() const {  return freeSpots; }

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
