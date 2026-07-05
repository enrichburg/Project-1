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
        string interactionsFile;
        vector<Garage> garages;
        vector<Customer> customers;

        int FindCustomerIndex(const string& customerId) const;

    public:

        QParkingSystem();

        bool LoadConfiguration(const string& fileName);

        void ProcessInteractions();
        bool AssignParkingSpace(const string& customerId);
        bool LocateCar(const string& customerId, int& garageIndex, int& spotIndex) const;
        bool RetrieveCar(const string& customerId);
        int GetAvailableSpaces() const;
        void PrintStatus() const;
        void WriteOccupancy() const;

};

#endif