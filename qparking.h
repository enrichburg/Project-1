#ifndef QPARKINGSYSTEM_H
#define QPARKINGSYSTEM_H
#include <string>
#include <vector>
#include "garage.h"
#include "customer.h"

class QParkingSystem {

    private:

        int numberOfGarages;
        int garageCapacity;
        vector<Garage> garages;
        vector<Customer> customers;

    public:

        QParkingSystem();

        bool LoadConfiguration(const string& fileName);

        bool AssignParkingSpace();
        bool RetrieveCar();
        int GetAvailableSpaces() const;
        void WriteOccupancy() const;

};

#endif