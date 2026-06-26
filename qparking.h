#ifndef QPARKINGSYSTEM_H
#define QPARKINGSYSTEM_H
#include "garage.h"

class QParkingSystem {
private:
    int numberOfGarages;
    int garageCapacity;
    vector<Garage> garages;
    vector<Customer> customers;

public:
    QParkingSystem();

    bool LoadConfiguration();
    bool LoadInitialOccupancy();

    bool AssignParkingSpace();
    bool RetrieveCar();
    int GetAvailableSpaces() const;
    void WriteOccupancy() const;
};

#endif