// card_list.cpp
// Author: Tobias Watters
// Implementation of the classes defined in card_list.h

#include "card_list.h"
#include <iostream>

using namespace std;

CardBST::CardBST() {root = nullptr;}

bool CardBST::insert(string cardname) {
    int targetKey = cardToKey(cardname);
    if (!root){
        root = new Node(targetKey);
        return true;
    }
    return insert(cardname, root);
}

bool CardBST::insert(string cardname, Node *n) {
    int targetKey = cardToKey(cardname);

    if (n->info.key == targetKey) {return false;} 
    else if (targetKey < n->info.key) {
        if (!n->left) {
            n->left = new Node(targetKey);
            n->left->parent = n;
            return true;
        }
        return insert(cardname, n->left);
    } else {
        if (!n->right) {
            n->right = new Node(targetKey);
            n->right->parent = n;
            return true;
        }
        return insert(cardname, n->right);
    }
}

Card* CardBST::find(int key) {
    Node* found = find(key, root);

    if (!found) return nullptr;

    return &(found->info);
}

CardBST::Node* CardBST::find(int key, Node* n) {
    if (!n) return nullptr;
    if (n->info.key == key) {return n;}
    else if (key < n->info.key) return find(key, n->left);
    return find(key, n->right);
}

bool CardBST::erase(int key) {
    Node* n = find(key, root);
    if (!n) return false;

    if (!n->left && !n->right) {
        if (n == root) {
            root = nullptr;
        } else if (n->parent->left == n) {
            n->parent->left = nullptr;
        } else {
            n->parent->right = nullptr;
        }
        delete n;
        return true;
    } 
    else if (n->left && !n->right) {
        if (n == root) {
            root = n->left;
            n->left->parent = nullptr;
        } else if (n->parent->left == n) {
            n->parent->left = n->left;
            n->left->parent = n->parent;
        } else {
            n->parent->right = n->left;
            n->left->parent = n->parent;
        }
        delete n;
        return true;
    } 
    else if (n->right && !n->left) {
        if (n == root) {
            root = n->right;
            n->right->parent = nullptr;
        } else if (n->parent->left == n) {
            n->parent->left = n->right;
            n->right->parent = n->parent;
        } else {
            n->parent->right = n->right;
            n->right->parent = n->parent;
        }
        delete n;
        return true;
    } else { // two children
        Node* successor = n->right;
        while (successor->left) {
            successor = successor->left;
        }
        n->info = successor->info;
        Node* child = successor->right;
        if (successor->parent->left == successor)
            successor->parent->left = child;
        else
            successor->parent->right = child;
        if (child)
            child->parent = successor->parent;
        delete successor;
        return true;
    }
}

bool CardBST::empty() {
    if (root == nullptr) return true;
    else return false;
}

Card* CardBST::prevCard(int key) {
    Node* n = find(key, root);
    if (!n) return nullptr;
    Node* predecessor = nullptr;
    if (n->left) {
        predecessor = n->left;
        while (predecessor->right)
            predecessor = predecessor->right;
        return &(predecessor->info);
    } else if (n->parent) {
        predecessor = n;
        while (predecessor->parent) {
            if (predecessor == predecessor->parent->right)
                return &(predecessor->parent->info);
            predecessor = predecessor->parent;
        }   
    }
    return nullptr;
}

Card* CardBST::nextCard(int key) {
    Node* n = find(key, root);
    if (!n) return nullptr;
    Node* successor = nullptr;
    if (n->right) {
        successor = n->right;
        while (successor->left) 
            successor = successor->left;
        return &(successor->info);
    } else if (n->parent) {
        successor = n;
        while (successor->parent) {
            if (successor == successor->parent->left)
                return &(successor->parent->info);
            successor = successor->parent;
        }   
    }
    return nullptr;
}
// iterator constructor
CardBST::iterator::iterator(CardBST::Node* ptr) : curr(ptr) {}

// dereference
Card& CardBST::iterator::operator*() {
    return curr->info;
}

Card* CardBST::iterator::operator->() {
    return &(curr->info);
}

// Move to in-order successor (next larger)
CardBST::iterator& CardBST::iterator::operator++() {
    if (!curr) return *this;

    if (curr->right) {
        // go right then all the way left
        curr = curr->right;
        while (curr->left) curr = curr->left;
    } else {
        // climb up until we came from a left child
        Node* p = curr->parent;
        while (p && curr == p->right) {
            curr = p;
            p = p->parent;
        }
        curr = p; // nullptr if we were at the maximum
    }
    return *this;
}

// Move to in-order predecessor (next smaller)
CardBST::iterator& CardBST::iterator::operator--() {
    if (!curr) return *this;

    if (curr->left) {
        // go left then all the way right
        curr = curr->left;
        while (curr->right) curr = curr->right;
    } else {
        // climb up until we came from a right child
        Node* p = curr->parent;
        while (p && curr == p->left) {
            curr = p;
            p = p->parent;
        }
        curr = p;
    }
    return *this;
}

bool CardBST::iterator::operator==(const iterator& rhs) const {
    return curr == rhs.curr;
}

bool CardBST::iterator::operator!=(const iterator& rhs) const {
    return curr != rhs.curr;
}

// begin: smallest node = go all the way left from root
CardBST::iterator CardBST::begin() {
    Node* n = root;
    while (n && n->left) n = n->left;
    return iterator(n);
}

// end: nullptr (one past the largest)
CardBST::iterator CardBST::end() {
    return iterator(nullptr);
}

// rbegin: largest node = go all the way right from root
CardBST::iterator CardBST::rbegin() {
    Node* n = root;
    while (n && n->right) n = n->right;
    return iterator(n);
}

// rend: nullptr (one past the smallest)
CardBST::iterator CardBST::rend() {
    return iterator(nullptr);
}

void playGame(CardBST player1, CardBST player2) {
    
    // find shared cards
    CardBST shared;
    for (auto it = player1.begin(); it != player1.end(); ++it) {
        if (player2.find((*it).key)) {
            shared.insert((*it).cardname);
        }
    }

    CardBST alice_final = player1; // copy original cards
    CardBST bob_final = player2;
    
    while (!shared.empty()) {
        // Alice's turn
        auto aliceIt = shared.begin();
        cout << "Alice picked matching card " << aliceIt->cardname << endl;
        alice_final.erase(aliceIt->key);
        bob_final.erase(aliceIt->key);
        shared.erase(aliceIt->key);

        if (shared.empty()) break;

        // Bob's turn
        auto bobIt = shared.rbegin();
        cout << "Bob picked matching card " << bobIt->cardname << endl;
        alice_final.erase(bobIt->key);
        bob_final.erase(bobIt->key);
        shared.erase(bobIt->key);
    }

    cout << endl << "Alice's cards:" << endl;
    for (auto it = alice_final.begin(); it != alice_final.end(); ++it) 
        cout << it->cardname << endl;
    cout << endl << "Bob's cards:" << endl;
    for (auto it = bob_final.begin(); it != bob_final.end(); ++it)
        cout << it->cardname << endl;
} 