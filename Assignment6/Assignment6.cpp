// Assignment 6
// Michael Montella

#include <iostream>
#include "Queue.h"
#include <sstream>

using namespace std;

void displayMenu() {
    cout << "======Main Menu=====" << endl;
    cout << "1. Enqueue word" << endl;
    cout << "2. Dequeue word" << endl;
    cout << "3. Print queue" << endl;
    cout << "4. Enqueue sentence" << endl;
    cout << "5. Quit" << endl;
}

int main() {
    Queue queue(10);
    int choice = 0;
    while (choice != 5) {
        displayMenu();
        cin >> choice;

        if (choice == 1) {
            cout << "word: ";
            string word;
            cin >> word;
            queue.enqueue(word);
        } else if (choice == 2) {
            queue.dequeue();
        } else if (choice == 3) {
            queue.printQueue();
        } else if (choice == 4) {
            string data;
            cin.ignore();

            cout << "sentence: ";
            getline (cin, data);
            string word;
            stringstream ss(data);
            while (ss >> word) {
                queue.enqueue(word);
            }
        } else {
            cout << "Goodbye!" << endl;
        }
    }

    return 0;
}
