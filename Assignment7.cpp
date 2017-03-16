#include <Iostream>

using namespace std;

void linkedList(char a) {
    if (head == NULL) {
        head = new Node;
        head->key = a;
        head->next = NULL;
    } else {
        Node *temp = new Node;
        temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        Node *add = new Node;
        temp->next = add;
        add->key = a;
    }

}

void RangeSearch(TreeNode *node, char m, char n) {

    if (node == NULL) {
        return;
    }

    if (m < node->key) {
        RangeSearch(node->left, m, n);
    }

    if (m <= node->key && n >= node->key) {
        linkedList(node->key);
    }

    if (n > node->key) {
        RangeSearch(node->right, m, n);
    }
}

int main() {
    return 0;
}
