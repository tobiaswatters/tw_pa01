// card.cpp - used by set and bst implementation
// Author: Tobias Watters
// Implementation of the classes defined in card.h

#include "card.h"

using namespace std;


Card::Card() {key = 102;} // default card is ace of clubs
Card::Card(string suitVal) {
    key = 0; // initialize


    cardname = suitVal;

    if (suitVal[0] == 'c') {
        key = 100;
    } else if (suitVal[0] == 'd') {
        key = 200;
    } else if (suitVal[0] == 's') {
        key = 300;
    } else if (suitVal[0] == 'h') {
        key = 400;
    } else return; // invalid suit

    if (50 <= suitVal[2] && suitVal[2] <= 57) { // value of card is a digit
        key += suitVal[2] - 48; // ASCII logic
    } else if (suitVal[2] == '1') {
        key += 10;
    }
    else if (suitVal[2] == 'j') {
        key += 11;
    } else if (suitVal[2] == 'q') {
        key += 12;
    } else if (suitVal[2] == 'k') {
        key += 13;
    } else if (suitVal[2] == 'a') {
        key += 1;
    } else return; // invalid card value
}

Card::Card(int k) {
    key = k;

    int suit = key / 100;
    int value = key % 100;

    // suit
    if (suit == 1) {
        cardname = "c ";
    } 
    else if (suit == 2) {
        cardname = "d ";
    } 
    else if (suit == 3) {
        cardname = "s ";
    } 
    else if (suit == 4) {
        cardname = "h ";
    } 
    else {
        key = 0;
        cardname = "";
        return;
    }

    // value
    if (2 <= value && value <= 9) {
        cardname += char(value + 48); // ASCII digit
    } 
    else if (value == 1) {
        cardname += 'a';
    } 
    else if (value == 10) {
        cardname += "10";
    } 
    else if (value == 11) {
        cardname += 'j';
    } 
    else if (value == 12) {
        cardname += 'q';
    } 
    else if (value == 13) {
        cardname += 'k';
    } 
    else {
        key = 0;
        cardname = "";
    }
}

bool Card::operator==(const Card& rhs) const {
    return key == rhs.key;
}

bool Card::operator>(const Card& rhs) const {
    return key > rhs.key;
}

bool Card::operator<(const Card& rhs) const {
    return key < rhs.key;
}

int cardToKey(string cardname) {
    int key = 0;

    // suit
    if (cardname[0] == 'c') {
        key = 100;
    } 
    else if (cardname[0] == 'd') {
        key = 200;
    } 
    else if (cardname[0] == 's') {
        key = 300;
    } 
    else if (cardname[0] == 'h') {
        key = 400;
    } 
    else {
        return 0;
    }

    // value
    if (cardname[2] >= '2' && cardname[2] <= '9') {
        key += cardname[2] - '0';
    } 
    else if (cardname[2] == 'a') {
        key += 1;
    } 
    else if (cardname[2] == 'j') {
        key += 11;
    } 
    else if (cardname[2] == 'q') {
        key += 12;
    } 
    else if (cardname[2] == 'k') {
        key += 13;
    } 
    else if (cardname.substr(2) == "10") {
        key += 10;
    } 
    else {
        return 0;
    }

    return key;
}
