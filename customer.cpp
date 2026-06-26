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