#include "garage.h"
#include <fstream>
#include <iostream>
#include <sstream>

Garage::Garage() {
    capacity = 0;
}

Garage::Garage(int capacity, vector<string> initialSpaces) {
    this->capacity = capacity;
    spaces = initialSpaces;
}

bool Garage::ParkCustomer() { return false; }
bool Garage::RemoveCustomer() { return false; }
bool Garage::IsAvailable() const { return false; }
int Garage::GetCapacity() const { return capacity; }
int Garage::GetAvailableCount() const { return 0; }
string Garage::GetSpotValue() const { return ""; }
void Garage::PrintLayout() const {}
