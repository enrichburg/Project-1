#ifndef GARAGE_H
#define GARAGE_H

#include <ostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#include "customer.h"

class Garage {

private:
    int capacity;
    vector<string> spaces;
    stack<int> freeSpots;

public:
    Garage();
    Garage(int capacity, vector<string> initialSpaces);

    bool ParkCustomer();
    bool RemoveCustomer();
    bool IsAvailable() const;
    int GetCapacity() const;
    int GetAvailableCount() const;
    string GetSpotValue() const;
    void PrintLayout() const;
};

#endif