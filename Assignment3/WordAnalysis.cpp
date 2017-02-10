// Assignment 3
// Michael Montella

#include "WordAnalysis.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

WordAnalysis::WordAnalysis(int num) {
    words = new word[num];
    wordCount = num;
    index = 0;
    timesDoubled = 0;
}

WordAnalysis::~WordAnalysis() {
    // Destructor
    delete [] words;
}

void WordAnalysis::doubleArrayAndAdd(string newWord) {

    bool match = false;

    if (index == 0) {
        words->w = "";
        words->count = 0;
    }

    // DOUBLE ARRAY
    if (index == wordCount) {
        timesDoubled++;
        wordCount *= 2;
        word *arr2 = new word[wordCount];

        for (int i = 0; i < index; i++) {
            arr2[i] = words[i];
        }

        delete [] words;
        words = arr2;
    }
    // Adds word or increases count
    if (checkIfCommonWord(newWord) == false) {
        for (int i = 0; i <= index; i++) {
            if (newWord == words[i].w) {
                words[i].count++;
                match = false;
                break;
            } else {
                match = true;
            }
        }
        if (match) {
            words[index].w = newWord;
            words[index].count = 1;
            index++;
        }
    }
}

bool WordAnalysis::checkIfCommonWord(string word) {
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

void WordAnalysis::sortData() {
    word temp;
    for (int i = 0; i < index; i++) {
        for (int j = 0; j < index; j++) {
            if (words[j].count < words[j + 1].count) {
                temp = words[j + 1];
                words[j + 1] = words[j];
                words[j] = temp;
            }
        }
    }
}


bool WordAnalysis::readDataFile(char *filename) {
    ifstream inFile;
    inFile.open(filename);
    string data;

    if(inFile.good()) {
        while(getline(inFile, data)) {
            stringstream ss(data, stringstream::in);
            string word;

            while(ss >> word) {
                doubleArrayAndAdd(word);
            }
        }

        return true;
    } else {
        return false;
    }
}

int WordAnalysis::getWordCount() {
    int nonCommon = 0;
    for (int i = 0; i < index; i++) {
        nonCommon = nonCommon + words[i].count;
    }
    return nonCommon;
}

int WordAnalysis::getUniqueWordCount() {
    int count = 0;
    for (int i = 0; i < index; i++) {
        if(words[i].w != "") {
            count++;
        }
    }
    return count;
}

int WordAnalysis::getArrayDoubling() {
    return WordAnalysis::timesDoubled;
}

void WordAnalysis::printCommonWords(int num) {
    sortData();
    for (int i = 0; i < num; i++) {
        cout << words[i].count << " - " << words[i].w << endl;
    }
}
