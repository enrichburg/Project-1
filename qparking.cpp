#include "qparking.h"

QParkingSystem::QParkingSystem() {
    numberOfGarages = 0;
    garageCapacity = 0;
}

bool QParkingSystem::LoadConfiguration() { return false; }
bool QParkingSystem::LoadInitialOccupancy() { return false; }
bool QParkingSystem::AssignParkingSpace() { return false; }
bool QParkingSystem::RetrieveCar() { return false; }
int QParkingSystem::GetAvailableSpaces() const { return 0; }
void QParkingSystem::WriteOccupancy() const {}
