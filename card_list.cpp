// card_list.cpp
// Author: Tobias Watters
// Implementation of the classes defined in card_list.h

#include "card_list.h"
#include <iostream>

using namespace std;

CardBST::CardBST() {root = nullptr;}

bool CardBST::insert(string cardname) {
    int targetKey = cardToKey(cardname);

    // if tree is empty, insert at root
    if (!root){
        root = new Node(targetKey);
        return true;
    }

    return insert(cardname, root);
}

bool CardBST::insert(string cardname, Node *n) {
    int targetKey = cardToKey(cardname);

    // duplicate keys not allowed
    if (n->info.key == targetKey) {return false;} 
    
    else if (targetKey < n->info.key) {

        // insert as left child if empty
        if (!n->left) {
            n->left = new Node(targetKey);
            n->left->parent = n;
            return true;
        }

        // continue searching left subtree
        return insert(cardname, n->left);
    } 
    
    else {

        // insert as right child if empty
        if (!n->right) {
            n->right = new Node(targetKey);
            n->right->parent = n;
            return true;
        }

        // continue searching right subtree
        return insert(cardname, n->right);
    }
}

Card* CardBST::find(int key) {
    Node* found = find(key, root);

    if (!found) return nullptr;

    return &(found->info);
}

CardBST::Node* CardBST::find(int key, Node* n) {

    // key not found
    if (!n) return nullptr;

    if (n->info.key == key) {return n;}

    // search left subtree
    else if (key < n->info.key) return find(key, n->left);

    // search right subtree
    return find(key, n->right);
}

bool CardBST::erase(int key) {
    Node* n = find(key, root);

    // key does not exist
    if (!n) return false;

    // case 1: no children
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
    
    // case 2: only left child
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
    
    // case 3: only right child
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
    } 
    
    else { // case 4: two children

        // find inorder successor
        Node* successor = n->right;
        while (successor->left) {
            successor = successor->left;
        }

        // copy successor data into current node
        n->info = successor->info;

        // successor can only have right child
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

    // predecessor is max node in left subtree
    if (n->left) {
        predecessor = n->left;

        while (predecessor->right)
            predecessor = predecessor->right;

        return &(predecessor->info);
    } 
    
    // otherwise move up until coming from right child
    else if (n->parent) {
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

    // successor is min node in right subtree
    if (n->right) {
        successor = n->right;

        while (successor->left) 
            successor = successor->left;

        return &(successor->info);
    } 
    
    // otherwise move up until coming from left child
    else if (n->parent) {
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

// dereference operator
Card& CardBST::iterator::operator*() {
    return curr->info;
}

// arrow operator
Card* CardBST::iterator::operator->() {
    return &(curr->info);
}

// Move to in-order successor (next larger)
CardBST::iterator& CardBST::iterator::operator++() {
    if (!curr) return *this;

    if (curr->right) {

        // go right once, then all the way left
        curr = curr->right;

        while (curr->left) curr = curr->left;
    } 
    
    else {

        // move upward until node is a left child
        Node* p = curr->parent;

        while (p && curr == p->right) {
            curr = p;
            p = p->parent;
        }

        // nullptr if already largest element
        curr = p;
    }

    return *this;
}

// Move to in-order predecessor (next smaller)
CardBST::iterator& CardBST::iterator::operator--() {
    if (!curr) return *this;

    if (curr->left) {

        // go left once, then all the way right
        curr = curr->left;

        while (curr->right) curr = curr->right;
    } 
    
    else {

        // move upward until node is a right child
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

// begin = smallest node
CardBST::iterator CardBST::begin() {
    Node* n = root;

    while (n && n->left) n = n->left;

    return iterator(n);
}

// end = nullptr
CardBST::iterator CardBST::end() {
    return iterator(nullptr);
}

// rbegin = largest node
CardBST::iterator CardBST::rbegin() {
    Node* n = root;

    while (n && n->right) n = n->right;

    return iterator(n);
}

// rend = nullptr
CardBST::iterator CardBST::rend() {
    return iterator(nullptr);
}

void playGame(CardBST player1, CardBST player2) {
    
    // store all matching cards
    CardBST shared;

    for (auto it = player1.begin(); it != player1.end(); ++it) {
        if (player2.find((*it).key)) {
            shared.insert((*it).cardname);
        }
    }

    // copies of original trees
    CardBST alice_final = player1;
    CardBST bob_final = player2;
    
    while (!shared.empty()) {

        // Alice removes smallest shared card
        auto aliceIt = shared.begin();

        cout << "Alice picked matching card " << aliceIt->cardname << endl;

        alice_final.erase(aliceIt->key);
        bob_final.erase(aliceIt->key);
        shared.erase(aliceIt->key);

        if (shared.empty()) break;

        // Bob removes largest shared card
        auto bobIt = shared.rbegin();

        cout << "Bob picked matching card " << bobIt->cardname << endl;

        alice_final.erase(bobIt->key);
        bob_final.erase(bobIt->key);
        shared.erase(bobIt->key);
    }

    cout << endl << "Alice's cards:" << endl;

    // print Alice's remaining cards in order
    for (auto it = alice_final.begin(); it != alice_final.end(); ++it) 
        cout << it->cardname << endl;

    cout << endl << "Bob's cards:" << endl;

    // print Bob's remaining cards in order
    for (auto it = bob_final.begin(); it != bob_final.end(); ++it)
        cout << it->cardname << endl;
}