//  Assignment2
// Michael Montella
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct Words {
    string word; 
    int wordCount;
};

bool commonCheck(string word){
    int common = 0;

    string theList[50] = {"the", "be", "to", "of", "and", "a", "in", "that", "have", "i", "it", "for", "not", "on", "with", "he", "as", "you", "do", "at", "this", "but", "his", "by", "from", "they", "we", "say", "her", "she", "or", "an", "will", "my", "one", "all", "would", "there", "their", "what", "so", "up", "out", "if", "about", "who", "get", "which", "go", "me"};

    for(int i = 0; i < 50; i++){
        if(theList[i] == word){
            common = 1;
        }
    }

    if (common == 1) {
        return true;       //Common
    } else {
        return false;       //Not Common
    }
}

void sortArray(Words array[], int count, int number) {

    Words newArray;

    for (int i = 0; i < count; i++) {
        for (int i = 0; i < count; i++) {
            if (array[i].wordCount < array[i + 1].wordCount) {
                newArray = array[i + 1];
                array[i + 1] = array[i];
                array[i] = newArray;
            }
        }
    }

}


int main(int argc, char * argv[]) {
    Words * wordArray;

    ifstream inFile;
    inFile.open(argv[1]);
    string data;

    int counter = 0;
    int nonCommonCounter = 0;
    int size = 100;
    int doubleCounter = 0;

    wordArray = new Words[size];

    if(inFile.good()) {

        while (getline(inFile, data)) {

            stringstream ss(data, stringstream::in);
            string word;

            bool match = false;

            while (ss >> word) {
                if (counter == 0) {
                    wordArray->word = "";
                    wordArray->wordCount = 0;
                }

                // ARRAY DOUBLING
                if (counter == size) {      // check if array is full
                    doubleCounter++;
                    size = size * 2;        // Double the size of the array
                    Words * arr2 = new Words[size];     // Create new temp array

                    for (int i = 0; i < size / 2; i++) {
                        arr2[i].word = wordArray[i].word;   // Copy data
                        arr2[i].wordCount = wordArray[i].wordCount;
                    }

                    delete [] wordArray;    // Free up allocated memory

                    wordArray = arr2;   // Change pointer to point at the new array

                    if (commonCheck(word) == false) {
                        nonCommonCounter++;
                        for (int i = 0; i <= counter; i++) {
                            if (word == wordArray[i].word) {    // Checks if the word is in the array
                                wordArray[i].wordCount++;       // If true, increment word count
                                match = false;
                                break;
                            } else {
                                match = true;
                            }
                        }

                        if (match) {                                // If word is not in array
                            wordArray[counter].word = word;         // Add it
                            wordArray[counter].wordCount = 1;       // Increase word count
                            counter++;
                        }
                    }
                } else {
                    if (commonCheck(word) == false) {
                        nonCommonCounter++;
                        for (int i = 0; i <= counter; i++) {
                            if (word == wordArray[i].word) {
                                wordArray[i].wordCount++;
                                match = false;
                                break;
                            } else {
                                match = true;
                            }
                        }

                        if (match) {
                            wordArray[counter].word = word;
                            wordArray[counter].wordCount = 1;
                            counter++;
                        }
                    }
                }
            }


        }
    }

    int number = stoi(argv[2]);
    sortArray(wordArray, counter, number);

    for (int i = 0; i < number; i++) {
        cout << wordArray[i].wordCount << " - " << wordArray[i].word << endl;
    }

    cout << "#" << endl;
    cout << "Array doubled: " << doubleCounter << endl;
    cout << "#" << endl;
    cout << "Unique non-common words: " << counter << endl;
    cout << "#" << endl;
    cout << "Total non-common words: " << nonCommonCounter << endl;
    cout << endl;

    return 0;
}
