// Michael Montella

#include <iostream>
#include <fstream>
#include <sstream>
#include "MovieTree.h"

using namespace std;

MovieTree::MovieTree() {
    root = NULL;
}

MovieTree::~MovieTree() {
    DeleteAll(root);
}

// Delete all
void MovieTree::DeleteAll(MovieNode *node) {
    if (node != NULL) {
        DeleteAll(node->leftChild);
        DeleteAll(node->rightChild);
        cout << "Deleting: " << node->title << endl;
        delete node;
    }
}

// Print Movie inventory
void MovieTree::printMovieInventory() {
    printMovieInventory(root);
}

void MovieTree::printMovieInventory(MovieNode *node) {
    if (node->leftChild != NULL) {
        printMovieInventory(node->leftChild);
    }
    cout << "Movie: " << node->title << " " << node->quantity << endl;
    if (node->rightChild != NULL) {
        printMovieInventory(node->rightChild);
    }
}

// Add Movie
void MovieTree::addMovieNode(int ranking, string title, int releaseYear, int quantity) {
    MovieNode *temp = new MovieNode;
    MovieNode *parent = NULL;

    temp->parent = NULL;
    temp->leftChild = NULL;
    temp->rightChild = NULL;

    MovieNode *node = new MovieNode(ranking, title, releaseYear, quantity);
    node->parent = NULL;
    node->rightChild = NULL;
    node->leftChild = NULL;

    temp = root;
    bool left = true;
    while(temp != NULL) {
        parent = temp;
        if (node->title.compare(temp->title) < 0) {
            temp = temp->leftChild;
            left = true;
        } else {
            temp = temp->rightChild;
            left = false;
        }
    }

    if (parent == NULL) {
        root = node;
    } else if (left) {
        parent->leftChild = node;
        node->parent = parent;
    } else {
        parent->rightChild = node;
        node->parent = parent;
    }
}

// Find movie
void MovieTree::findMovie(string title) {
    MovieNode *node = new MovieNode;
    node = root;
    bool exists = false;
    while (node != NULL) {
        if (title != node->title) {
            if (title.compare(node->title) < 0) {
                node = node->leftChild;
            } else {
                node = node->rightChild;
            }
        } else {
            exists = true;
            break;
        }
    }

    if (exists) {
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << node->ranking << endl;
        cout << "Title:" << node->title << endl;
        cout << "Year:" << node->year << endl;
        cout << "Quantity:" << node->quantity << endl;
    } else {
        cout << "Movie not found." << endl;
    }
}

// Rent movie
void MovieTree::rentMovie(string title) {
    MovieNode *node = new MovieNode;
    node = root;
    bool exists = false;
    while(node != NULL) {
        if (title != node->title) {
            if (title.compare(node->title) < 0) {
                node = node->leftChild;
            } else {
                node = node->rightChild;
            }
        } else {
            exists = true;
            break;
        }
    }

    if (exists) {
        cout << "Movie has been rented." << endl;
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << node->ranking << endl;
        cout << "Title:" << node->title << endl;
        cout << "Year:" << node->year << endl;
        cout << "Quantity:" << node->quantity - 1 << endl;

        node->quantity -= 1;

        if (node->quantity == 0) {
            deleteMovieNode(node->title);
        }
    } else {
        cout << "Movie not found." << endl;
    }
}

// Count movies
int MovieTree::countMovieNodes() {
    int totalMovies = 0;
    countMovieNodes(root, &totalMovies);
    cout << "Tree contains: " << totalMovies << " movies." << endl;
    return totalMovies;
}

void MovieTree::countMovieNodes(MovieNode *node, int *num) {
    if (node->leftChild != NULL) {
        countMovieNodes(node->leftChild, num);
    }
    *num = *num + 1;
    if (node->rightChild != NULL) {
        countMovieNodes(node->rightChild, num);
    }
}

// Delete movie
void MovieTree::deleteMovieNode(string title) {
    MovieNode *node = new MovieNode;

    node = root;
    while (node != NULL) {
        if (title != node->title) {
            if (title.compare(node->title) < 0) {
                node = node->leftChild;
            } else {
                node = node->rightChild;
            }
        } else {
            break;
        }
    }

    if (node->leftChild == NULL && node->rightChild == NULL) {
        // No children
        if (node->title.compare(node->parent->title) < 0) {
            node->parent->leftChild = NULL;
        } else {
            node->parent->rightChild = NULL;
        }
    } else if (node->leftChild != NULL && node->rightChild != NULL) {
        // 2 children
        MovieNode *temp = node->rightChild;

        if (temp->leftChild != NULL) {
            while (temp != NULL) {
                temp = temp->leftChild;
            }
        } else if (temp->rightChild != NULL) {
            temp = temp->rightChild;
        }

        if (node->parent->leftChild->title == node->title) {
            // node is left child
            node->parent->leftChild = temp;
            temp->parent = node->parent;
            temp->leftChild = node->leftChild;
            if (temp->rightChild != NULL) {
                temp->rightChild->parent = temp;
            }
        } else {
            // node is right child
            node->parent->rightChild = temp;
            temp->parent = node->parent;
        }
    } else {
        // 1 child
        if (node->leftChild == NULL) {
            node->rightChild->parent = node->parent;
            if (node->parent->rightChild == node) {
                node->parent->rightChild = node->rightChild;
            } else {
                node->parent->leftChild = node->rightChild;
            }
        } else if (node->rightChild == NULL) {
            node->leftChild->parent = node->parent;
            if (node->parent->rightChild == node) {
                node->parent->rightChild = node->leftChild;
            } else {
                node->parent->leftChild = node->leftChild;
            }
        }
    }
    delete node;
}
