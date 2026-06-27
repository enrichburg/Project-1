#ifndef GARAGE_H
#define GARAGE_H
#include <string>
#include <vector>
using namespace std;

class Garage {

    private:

        vector<string> spaces;
        int freeSpots; // change back into a stack later
        int capacity;

    public:

        Garage();
        explicit Garage(int capacity);
        Garage(int capacity, vector<string> initialSpaces);

        void SetSpace(const string& space);
        bool ParkCustomer();
        bool RemoveCustomer();
        bool IsAvailable() const;
        int GetAvailableCount() const;
        string GetSpotValue(int index) const;
        void PrintLayout() const;
};

#endif