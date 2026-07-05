#ifndef GARAGE_H
#define GARAGE_H
#include <string>
#include <vector>
#include <stack>
using namespace std;

class Garage {

    private:

        vector<string> spaces;
        stack<int> freeSpots; // indices of open (non-reserved) spots; top = next spot to fill
        int capacity;

    public:

        Garage();
        explicit Garage(int capacity);
        Garage(int capacity, vector<string> initialSpaces);

        void SetSpace(const string& space);
        int ParkCustomer(const string& id);
        string RemoveCustomer();
        bool IsAvailable() const;
        int GetAvailableCount() const;
        int GetTopOccupiedIndex() const;
        string GetSpotValue(int index) const;
        void PrintLayout() const;
};

#endif
