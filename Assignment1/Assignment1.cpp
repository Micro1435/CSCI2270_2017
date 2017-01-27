// Michael Montella
// Assignment 1
// 1 22 17

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//Struct for each item
struct Items {
    string type;
    int status;
    int price;
};

int loopCounter = 0;    // Counts loops
int fileCounter = 0;    // Counts times it reads file
int shiftCounter = 0;   // Counts times array shifts
int lineCounter = 0;    // Counts lines for array

bool first = true;

Items matchArray[100];  // Array of matched Items
int counter2 = 0;       // Counter for matchArray


void deleteItem(Items *array, int index, int *length) {

    // Shifts all objects in array
    for (int i = index; i < *length - 1; i++) {
        array[i].type = array[i + 1].type;
        array[i].status = array[i + 1].status;
        array[i].price = array[i + 1].price;

        shiftCounter++;
    }

    *length -= 1;

}

// Function to search through array
void searchItems (string filename, Items *arr) {
    ifstream inFile;
    inFile.open(filename);
    string data;

    if (inFile.good()) {    // Checks to make sure opening file worked correctly
        while(getline(inFile, data, '\n')) {    // Loops through each line in file
            fileCounter++;  // Iterate loop counter
            stringstream ss(data);
            string newData;
            string newType;
            int newStatus;
            int newPrice;
            getline(ss, newData, ',');
            newType = newData;

            getline(ss, newData, ',');
            if(newData == " for sale") {
                newStatus = 0;  // Item is marked for sale
            } else {
                newStatus = 1;  // Item is marked wanted
            }

            getline(ss, newData, ',');
            newPrice = stoi(newData);   // Makes newPrice int of newData

            if (fileCounter == 1) {     // Adds first item into array so loop works correctly
                arr[lineCounter].type = newType;
                arr[lineCounter].status = newStatus;
                arr[lineCounter].price = newPrice;
            }

            for(int i = 0; i < lineCounter; i++) {
                loopCounter++;
                if (newType == arr[i].type && newStatus != arr[i].status) {     // Checks to see if item matches and status differs

                    if (newStatus == 1 && newPrice >= arr[i].price) {
                        matchArray[counter2].type = arr[i].type;
                        matchArray[counter2].price = arr[i].price;
                        counter2++;

                        deleteItem(arr, i, &lineCounter);    // Removes item from array

                        lineCounter -= 1;
                        break;
                    } else if (newStatus == 0 && newPrice <= arr[i].price) {
                        matchArray[counter2].type = arr[i].type;
                        matchArray[counter2].price = newPrice;
                        counter2++;

                        deleteItem(arr, i, &lineCounter);    // Removes item from array

                        lineCounter -= 1;
                        break;
                    }
                } else {    // Adds to itemArray if it doesn't have a match
                    arr[lineCounter].type = newType;
                    arr[lineCounter].status = newStatus;
                    arr[lineCounter].price = newPrice;
                }
            }
            lineCounter++;
        }
    }
}

void printMatches (Items *arr) {
    for(int i = 0; i < counter2; i++) {
        cout << matchArray[i].type << " " << matchArray[i].price << endl;
    }
}

void printBoard (Items *arr) {
    cout << "#" << endl;
    for (int i = 0; i < lineCounter; i++ ) {
        if (arr[i].type != "") {
            if(arr[i].status == 0) {
                cout << arr[i].type << ", for sale, " << arr[i].price <<  endl;
            } else {
                cout << arr[i].type << ", wanted, " << arr[i].price << endl;
            }
        }
    }
}

int main (int argc, char* argv[]) {
    Items itemArray[100];
    string name;
    getline(cin, name);
    searchItems(name, itemArray);
    printMatches(matchArray);
    printBoard(itemArray);

    cout << "#" << endl;
    cout << "file read:" << fileCounter << endl;
    cout << "search array:" << loopCounter << endl;
    cout << "shift array:" << shiftCounter << endl;

    return 0;
}
