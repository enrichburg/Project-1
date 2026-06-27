#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>
using namespace std;

class Customer {

    private:
    
        string id;
        string name;
        string phone;
        string arrivalTime;
        string departureTime;
        bool isParked;
        int garageIndex;
        int spotIndex;

    public:

        Customer();
        Customer(const string& id, const string& name, const string& phone, const string& arrivalTime, const string& departureTime, bool isParked, int garageIndex, int spotIndex);

        void SetDepartureTime(const string& departureTime);
        void SetParkingLocation(int garageIndex, int spotIndex);
        void ClearParkingLocation();

        string GetId() const;
        string GetName() const;
        string GetPhone() const;
        string GetArrivalTime() const;
        string GetDepartureTime() const;
        bool IsParked() const;
        int GetGarageIndex() const;
        int GetSpotIndex() const;

};

#endif