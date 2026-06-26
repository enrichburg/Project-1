#include "customer.h"

Customer::Customer() {

    id = "NA";
    name = "NA";
    phone = "-1";
    arrivalTime = "-1";
    departureTime = "-1";
    isParked = false;
    garageIndex = -1;
    spotIndex = -1;

}

Customer::Customer(string id, string name, string phone, string arrivalTime, string departureTime, bool isParked, int garageIndex, int spotIndex) {

    this->id = id;
    this->name = name;
    this->phone = phone;
    this->arrivalTime = arrivalTime;
    this->departureTime = departureTime;
    this->isParked = isParked;
    this->garageIndex = garageIndex;
    this->spotIndex = spotIndex;

}

void Customer::SetDepartureTime(string departureTime) {
    this->departureTime = departureTime;
}

void Customer::SetParkingLocation(int garageIndex, int spotIndex) {
    this->garageIndex = garageIndex;
    this->spotIndex = spotIndex;
    isParked = true;
}

void Customer::ClearParkingLocation() {
    garageIndex = -1;
    spotIndex = -1;
    isParked = false;
}

string Customer::GetId() const { return id; }
string Customer::GetName() const { return name; }
string Customer::GetPhone() const { return phone; }
string Customer::GetArrivalTime() const { return arrivalTime; }
string Customer::GetDepartureTime() const { return departureTime; }
bool Customer::IsParked() const { return isParked; }
int Customer::GetGarageIndex() const { return garageIndex; }
int Customer::GetSpotIndex() const { return spotIndex; }