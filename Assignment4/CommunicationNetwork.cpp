// Michael Montella
// Assignment 4

#include <iostream>
#include <fstream>
#include <sstream>
#include "CommunicationNetwork.h"

using namespace std;

CommunicationNetwork::CommunicationNetwork() {      // Constructor
}

CommunicationNetwork::~CommunicationNetwork() {     // Destructor
}

void CommunicationNetwork::addCity(string prevCity, string newCity) {
    // Add new city node after the previous city
    City *city = new City;
    city->cityName = newCity;
    city->next = NULL;
    City *current = CommunicationNetwork::head;
    while (current != NULL) {                       // Loop until you find prevCity
        if (current->cityName == prevCity) {
            city->next = current->next;               // Assign next to current's next
            current->next = city;                    // Assign current next to new city
            break;
        }
        current = current->next;
    }
}

void CommunicationNetwork::transmitMsg(char *filename) {
    // open file
    ifstream inFile;
    inFile.open(filename);
    string data;

    City *current = CommunicationNetwork::head;

    if (current->cityName != "Los Angeles") {
        cout << "Empty List" << endl;
    } else {
        if (inFile.good()) {
            while (getline(inFile, data)) {
                stringstream ss(data);
                string word;
                while (ss >> word) {
                    current = CommunicationNetwork::head;
                    while (current != NULL) {
                        current->message = word;
                        cout << current->cityName << " received " << current->message << endl;
                        current->message = "";
                        current = current->next;
                    }
                }
            }
        }
    }
}

void CommunicationNetwork::printNetwork() {
    City *current = CommunicationNetwork::head;
    cout << "===CURRENT PATH===" << endl;

    while (current != NULL) {
        cout << current->cityName << " -> ";
        current = current->next;
    }
    cout << "NULL" << endl;
    cout	<<	"=================="	<<	endl;
}

void CommunicationNetwork::buildNetwork() {
    string startCities[] = {"Los Angeles", "Phoenix", "Denver", "Dallas", "St. Louis", "Chicago", "Atlanta", "Washington, D.C.", "New York", "Boston"};

    CommunicationNetwork::head = new City;                  // New city pointer
    CommunicationNetwork::head->cityName = startCities[0];   // Assigns to LA
    CommunicationNetwork::head->next = NULL;                 // Assigns next to NULL

    City *current = CommunicationNetwork::head;

    for (int i = 1; i < 10; i++) {
        City *temp = new City;              // New Temporary city
        temp->cityName = startCities[i];     // Assigns name
        temp->next = NULL;                   // Assigns next to NULL
        current->next = temp;                // Assigns current next to new city
        current = current->next;             // Switches current to new city
    }                                       // Repeat until network is built

    CommunicationNetwork::tail = current;

    printNetwork();
}
