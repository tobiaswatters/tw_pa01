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

  // Game logic:
  // Find shared cards
  set<Card> shared;
  for (auto& card : player1) {
    if (player2.count(card)) {
      shared.insert(card);
    }
  }

  set<Card> alice_final = player1; // copy original cards
  set<Card> bob_final = player2; 

  while (!shared.empty()) {
    // Alice's turn
    auto aliceIt = shared.begin();
    cout << "Alice picked matching card " << aliceIt->cardname << endl;
    alice_final.erase(*aliceIt);
    bob_final.erase(*aliceIt);
    shared.erase(aliceIt);

    if (shared.empty()) break;

    // Bob's turn
    auto bobIt = shared.rbegin();
    cout << endl << "Bob picked matching card " << bobIt->cardname << endl;
    alice_final.erase(*bobIt);
    bob_final.erase(*bobIt);
    shared.erase(*bobIt);
}

  
  cout << endl << "Alice's cards:" << endl;
  for (auto& card : alice_final) cout << card.cardname << endl;
  cout << "Bob's cards:" << endl;
  for (auto& card : bob_final) cout << card.cardname << endl;

  return 0;
}
