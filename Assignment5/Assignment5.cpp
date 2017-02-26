// Michael Montella
// Assignment 5

#include <iostream>
#include <fstream>
#include "CommunicationNetwork.h"

using namespace std;

void displayMenu() {
    cout << "======Main Menu======" << endl;
    cout << "1. Build Network" << endl;
    cout << "2. Print Network Path" << endl;
    cout << "3. Transmit Message Coast-To-Coast-To-Coast" << endl;
    cout << "4. Add City" << endl;
	cout << "5. Delete City" << endl;
	cout << "6. Clear Network" << endl;
    cout << "7. Quit" << endl;
}

int main(int argc, char* argv[]) {
    CommunicationNetwork network;
    string cityName;
    string prevCity;
    string delNode;

    char *fileName = argv[1];

    int userChoice = 0;
    while(userChoice != 7) {
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
            cin.ignore();
            cout << "Enter a city name: " << endl;
            getline(cin, delNode);

            network.deleteCity(delNode);
        } else if (userChoice == 6) {
            network.deleteNetwork();
        } else if (userChoice == 7) {
            cout << "Goodbye!" << endl;
        }
    }

    return 0;
}
