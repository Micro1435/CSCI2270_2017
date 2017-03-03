// Assignment 6
// Michael Montella

#include <iostream>
#include "Queue.h"

using namespace std;
Queue::Queue(int size) {
    queueSize = size;
    arrayQueue = new string [queueSize];
    queueHead = 0;
    queueTail = 0;
    queueCount = 0;
}

Queue::~Queue() {
    //destructor
}

void Queue::enqueue(string word) {
    if (queueIsFull() != true) {    // Checks to see if queue is full or not
        arrayQueue[queueTail] = word;
        queueCount++;
        if (queueTail == queueSize - 1) {
            queueTail = 0;  //Sets tail to 0 if queue is full
        } else {
            queueTail++;    //Increments queue tail position
        }

        cout << "E: " << word << endl;
        cout << "H: " << queueHead << endl;
        cout << "T: " << queueTail << endl;
    } else {
        cout << "Queue is full." << endl;
    }
}

string Queue::dequeue() {
    string word;
    word = arrayQueue[queueHead];

    if (queueIsEmpty() != true) {   // Checks queue
        arrayQueue[queueHead] = ""; // Sets head to ""
        queueHead++;    // Increments head position
        queueCount--;
        cout << "H: " << queueHead << endl;
        cout << "T: " << queueTail << endl;
        cout << "word: " << word << endl;

    } else {
        cout << "Queue is empty." << endl;
    }

    return word;
}

void Queue::printQueue() {
    if (queueIsEmpty() == true) {
        cout << "Empty" << endl;
    } else {
        int head = queueHead;
        if (head < queueTail) {
            while (head < queueTail) {
                cout << head << ": " << arrayQueue[head] << endl;
                head++;
            }
        } else {
            while (head < queueSize) {
                cout << head << ": " << arrayQueue[head] << endl;
                head++;
            }
            head = 0;
            while (head < queueTail) {
                cout << head <<": " << arrayQueue[head] << endl;
                head++;
            }
        }
    }


}

bool Queue::queueIsFull() {
    if (queueCount == queueSize) {
        return true;
    }
    return false;
}

bool Queue::queueIsEmpty() {
    if (queueCount == 0) {
        return true;
    }
    return false;
}
