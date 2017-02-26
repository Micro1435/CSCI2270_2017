// Michael Montella
// Assignment 5

#include <iostream>
#include <fstream>
#include <sstream>
#include "CommunicationNetwork.h"

using namespace std;

CommunicationNetwork::CommunicationNetwork() {      // Constructor
}

CommunicationNetwork::~CommunicationNetwork() {     // Destructor
    deleteNetwork();
}

void CommunicationNetwork::addCity(string prevCity, string newCity) {
    // Add new city node after the previous city
    City *city = new City;
    city->cityName = newCity;
    city->next = NULL;
    city->prev = NULL;
    City *current = CommunicationNetwork::head;
    while (current != NULL) {                       // Loop until you find prevCity
        if (prevCity == "First") {
            city->next = current;
            city->prev = NULL;
            current->prev = city;
            CommunicationNetwork::head = city;
            break;
        }
        if (current->cityName == prevCity) {
            city->next = current->next;
            city->prev = current;           // Assign next to current's next
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
                    while (current->next != NULL) {
                        current->message = word;
                        cout << current->cityName << " received " << current->message << endl;
                        current->message = "";
                        current = current->next;
                    }
                    while (current != NULL) {
                        current->message = word;
                        cout << current->cityName << " received " << current->message << endl;
                        current->message = "";
                        current = current->prev;
                    }
                }
            }
        }
    }
}

void CommunicationNetwork::printNetwork() {
    if (CommunicationNetwork::head != NULL) {
        City *current = CommunicationNetwork::head;
        cout << "===CURRENT PATH===" << endl;
        cout << "NULL <- ";

        while (current->next != NULL) {
            cout << current->cityName << " <-> ";
            current = current->next;
        }
        cout << current->cityName << " -> ";
        cout << "NULL" << endl;
        cout << "==================" <<	endl;
    } else {
        cout << "===CURRENT PATH===" << endl;
        cout << "NULL" << endl;
        cout << "==================" <<	endl;
    }
}

void CommunicationNetwork::buildNetwork() {
    string startCities[] = {"Los Angeles", "Phoenix", "Denver", "Dallas", "St. Louis", "Chicago", "Atlanta", "Washington, D.C.", "New York", "Boston"};

    CommunicationNetwork::head = new City;                  // New city pointer
    CommunicationNetwork::head->cityName = startCities[0];   // Assigns to LA
    CommunicationNetwork::head->next = NULL;                 // Assigns next to NULL
    CommunicationNetwork::head->prev = NULL;

    City *current = CommunicationNetwork::head;

    for (int i = 1; i < 10; i++) {
        City *temp = new City;              // New Temporary city
        temp->cityName = startCities[i];     // Assigns name
        temp->next = NULL;                   // Assigns next to NULL
        temp->prev = current;
        current->next = temp;                // Assigns current next to new city
        current = current->next;             // Switches current to new city
    }                                       // Repeat until network is built

    CommunicationNetwork::tail = current;

    printNetwork();
}

void CommunicationNetwork::deleteCity(string delCity) {
    City *current = CommunicationNetwork::head;
    int replaced = 0;

    while (current != NULL) {
        if (delCity == CommunicationNetwork::tail->cityName) {
            current = CommunicationNetwork::tail;
            current->prev->next = NULL;
            delete current;
            replaced = 1;
            break;
        }
        if (current->cityName == delCity) {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            replaced = 1;
            break;
        }
        current = current->next;
    }

    if (replaced == 0) {
        cout << delCity << "not found" << endl;
    }
}

void CommunicationNetwork::deleteNetwork() {
    if (CommunicationNetwork::head != NULL) {
        City *current = CommunicationNetwork::head;
        City *temp = new City;

        while (current != NULL) {
            cout << "deleting " << current->cityName << endl;
            temp = current->next;
            delete(current);
            current = temp;
        }
        CommunicationNetwork::head = NULL;
    }
}
