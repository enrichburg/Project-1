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
    Customer(string id, string name, string phone, string arrivalTime, string departureTime, bool isParked, int garageIndex, int spotIndex);

    void SetDepartureTime(string departureTime);
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