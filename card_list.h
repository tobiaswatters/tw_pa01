// card_list.h
// Author: Tobias Watters
// All class declarations related to defining a BST that represents a player's hand
#include "card.h"

#ifndef CARD_LIST_H
#define CARD_LIST_H

class CardBST {
    private:
        struct Node {
            Card info;
            Node *left, *right, *parent;
            Node(int key) : info(Card(key)), left(0), right(0), parent(0) { }
        };
        Node* root;
        bool insert(string cardname, Node *n); 
        Node* find(int key, Node* n);

    public:
        class iterator {
            public:
                iterator(CardBST::Node* ptr = nullptr);

                Card& operator*();
                Card* operator->();

                iterator& operator++(); // next card
                iterator& operator--(); // previous card

                bool operator==(const iterator& rhs) const;
                bool operator!=(const iterator& rhs) const;

            private:
                Node* curr;
        };

        // forward iteration
        iterator begin(); // smallest card
        iterator end();   // nullptr

        // reverse iteration
        iterator rbegin(); // largest card
        iterator rend();

        CardBST();
        bool insert(string cardname);
        Card* find(int key);
        bool erase(int key);
        bool empty();
        Card* nextCard(int key);
        Card* prevCard(int key);
};

void playGame(CardBST player1, CardBST player2);



#endif
