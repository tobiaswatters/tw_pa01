// card.h
// Author: Your name
// All class declarations related to defining a single card go here
#include <string>

#ifndef CARD_H
#define CARD_H

using namespace std;



class Card {
    /*
    Constructor takes in the string eg 'h 8' and assigns a key
    hundreds place correspond to suit (clubs 100, diamonds 200, spades 300, hearts 400)
    */
    public: 
        int key;
        string cardname;
        Card(); // default card is ace of clubs
        Card(string suitVal);
        Card(int k);
        string keyToStr(int key) const;
        bool operator>(const Card& rhs) const; 
        bool operator<(const Card& rhs) const; 
        bool operator==(const Card& rhs) const;
};

int cardToKey(string cardname);

#endif