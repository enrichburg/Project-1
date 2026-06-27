#include <iostream>
#include <string>
#include "garage.h"
#include "qparking.h"

int main() {

    QParkingSystem system;
    string fileName;

    cout << "Enter name of configuration file: ";
    cin >> fileName;

    if (system.LoadConfiguration(fileName)) {
        system.WriteOccupancy();
        cout << "Configuration loaded and output.txt\n";
    }
    else {
        cout << "Failed to load configuration\n";
    }

    return 0;
}