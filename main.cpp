// This file should implement the game using a custom implementation of a BST (based on your earlier BST implementation)
#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
#include "card_list.h"
//Do not include set in this file

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

  CardBST player1, player2;

  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    player1.insert(line);
  }
  cardFile1.close();


  while (getline (cardFile2, line) && (line.length() > 0)){
    player2.insert(line);
  }
  cardFile2.close();

  playGame(player1, player2);  
  
  return 0;
}
