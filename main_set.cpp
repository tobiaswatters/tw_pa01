// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }

  //declare sets
  set<Card> player1, player2;

  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    player1.insert(Card(line));
  }
  cardFile1.close();


  while (getline (cardFile2, line) && (line.length() > 0)){
    player2.insert(Card(line));
  }
  cardFile2.close();
  /*
  // debugging 1:
  cout << "Alice's ordered cards (bicycle)" << endl;
  for (auto& card : player1) cout << card.cardname << endl;

  cout << "Bob's ordered cards (SF)" << endl;
  for (auto& card : player2) cout << card.cardname << endl;
  */


  // Game logic:
  // Find shared cards
  set<Card> shared;
  for (auto& card : player1) {
    if (player2.count(card)) {
      shared.insert(card);
    }
  }

  /* debugging 2:
  cout << endl << "Shared cards, ordered:" << endl;
  for (auto& card : shared) cout << card.cardname << endl;
  */

  set<Card> alice_final = player1; // copy original cards
  set<Card> bob_final = player2; 

  while (!shared.empty()) {
    // Alice's turn
    auto aliceIt = shared.begin(); // starts with smallest card values
    cout << "Alice picked matching card " << aliceIt->cardname << endl;
    alice_final.erase(*aliceIt);
    bob_final.erase(*aliceIt);
    shared.erase(aliceIt); // delete from shared so bob can't delete too

    if (shared.empty()) break; // check if allice found last shared card, break so bob doesnt try to access empty set. 

    // Bob's turn
    auto bobIt = shared.rbegin(); // starts with largest card value
    cout << "Bob picked matching card " << bobIt->cardname << endl;
    alice_final.erase(*bobIt);
    bob_final.erase(*bobIt);
    shared.erase(*bobIt); // delete from shared so alice cant delte too
}

  // read out final cards. 
  cout << endl << "Alice's cards:" << endl;
  for (auto& card : alice_final) cout << card.cardname << endl;
  cout << endl << "Bob's cards:" << endl;
  for (auto& card : bob_final) cout << card.cardname << endl;

  return 0;
}
