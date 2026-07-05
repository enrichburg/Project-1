#include <iostream>
#include <string>
#include "garage.h"
#include "qparking.h"

int main(int argc, char* argv[]) {

    QParkingSystem system;
    string fileName;

    // accept the config file name from the command line, else prompt for it
    if (argc > 1) {
        fileName = argv[1];
    }
    else {
        cout << "Enter name of configuration file: ";
        cin >> fileName;
    }

    if (system.LoadConfiguration(fileName)) {
        system.ProcessInteractions();
        system.PrintStatus();
        system.WriteOccupancy();
        cout << "\nFinal occupancy written to output.txt\n";
    }
    else {
        cout << "Failed to load configuration\n";
    }

    return 0;
}
