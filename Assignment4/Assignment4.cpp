// Michael Montella
// Assignment 4

#include <iostream>
#include <fstream>
#include "CommunicationNetwork.h"

using namespace std;

void displayMenu() {
    cout << "======Main Menu======" << endl;
    cout << "1. Build Network" << endl;
    cout << "2. Print Network Path" << endl;
    cout << "3. Transmit Message Coast-To-Coast" << endl;
    cout << "4. Add City" << endl;
    cout << "5. Quit" << endl;
}

int main(int argc, char* argv[]) {
    CommunicationNetwork network;
    string cityName;
    string prevCity;

    char *fileName = argv[1];

    int userChoice = 0;
    while(userChoice != 5) {
        displayMenu();
        cin >> userChoice;

        if (userChoice == 1) {
            network.buildNetwork();
        } else if (userChoice == 2) {
            network.printNetwork();
        } else if (userChoice == 3) {
            network.transmitMsg(fileName);
        } else if (userChoice == 4) {
            cin.ignore();
            cout << "Enter a city name: " << endl;
            getline(cin, cityName);
            cout << "Enter a previous city name: " << endl;
            getline(cin, prevCity);

            network.addCity(prevCity, cityName);
        } else if (userChoice == 5) {
            cout << "Goodbye!" << endl;
        }
    }

    return 0;
}
