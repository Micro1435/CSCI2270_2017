// Michael Montella

#include <iostream>
#include <fstream>
#include <sstream>
#include "MovieTree.h"

using namespace std;

void printMenu() {
    cout << "======Main Menu======" << endl;
    cout << "1. Find a movie" << endl;
    cout << "2. Rent a movie" << endl;
    cout << "3. Print the inventory" << endl;
    cout << "4. Delete a movie" << endl;
    cout << "5. Count the movies" << endl;
    cout << "6. Quit" << endl;
}

int main(int argc, char *argv[]) {

    MovieTree movieTree;

    int choice = 0;

    ifstream inFile;
    inFile.open(argv[1]);
    if (inFile.good()) {
        string data;
        while (getline(inFile, data)) {
            stringstream ss(data);

            // Movie ranking
            string rank;
            getline(ss, rank, ',');

            // Movie title
            string title;
            getline(ss, title, ',');

            // Release year
            string releaseYear;
            getline(ss, releaseYear, ',');

            // quantity
            string quantity;
            getline(ss, quantity, ',');

            movieTree.addMovieNode(stoi(rank), title, stoi(releaseYear), stoi(quantity));

        }
    }

    while (choice != 6) {
        printMenu();
        cin >> choice;

        if (choice == 1) {
            string title;
            cin.ignore();

            cout << "Enter title:" << endl;
            getline(cin, title);

            movieTree.findMovie(title);
        } else if (choice == 2) {
            string title;
            cin.ignore();

            cout << "Enter title:" << endl;
            getline(cin, title);

            movieTree.rentMovie(title);
        } else if (choice == 3) {
            movieTree.printMovieInventory();
        } else if (choice == 4) {
            string title;
            cin.ignore();

            cout << "Enter title:" << endl;
            getline(cin, title);

            movieTree.deleteMovieNode(title);
        } else if (choice == 5) {
            movieTree.countMovieNodes();
        } else if (choice == 6) {
            cout << "Goodbye!" << endl;
        }
    }

    return 0;
}
