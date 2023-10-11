// Kristopher Acuna - 5005035589
// CS302 - 1004
// Had to similate a connect 4 match as seen

#include "LL.h"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
bool gameIsOn = true;
string r = "Red";
string b = "Blue";

// rewrites the input to lower
int getIndex(char userInput) {
  char lowerInput = tolower(userInput);
  int placeOnBoard = lowerInput - 'a';
  return placeOnBoard;
}

bool find4InARow(const LL<bool> &list);
bool columnFound4(LL<bool> board[]) {
  LL<bool> place;
  const int boardSize = 7;
  int i = 0;
  while (i < boardSize) {
    place = board[i];
    if (find4InARow(place))
      return true;
    i++;
  }
  return false;
}

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

int main() {
  cout << endl;
  string space;
  const int boardSize = 7;
  string currentUser = "Red";
  LL<bool> board[boardSize];
  gameIsOn = true;

  for (int i = boardSize - 1; i >= 0; i--) // creates rows
  {
    int j = 0;
    while (j < boardSize) {
      auto checkIt = board[j].end();
      if (i < board[j].size()) {
        int k = 0;
        while (k <= i) {
          checkIt++;
          k++;
        }
        cout << (*checkIt ? " R " : " B ");
        // cout << "check output";
      } else {
        cout << " - ";
      }
      j++;
    }
    cout << endl;
  }

  cout << "\n A"
       << "  "
       << "B"
       << "  "
       << "C"
       << "  "
       << "D"
       << "  "
       << "E"
       << "  "
       << "F"
       << "  "
       << "G"
       << "  " << endl;

  while (gameIsOn) {
    char userInput;
    cout << currentUser << " Player Select a row: ";
    cin >> userInput;
    // go ahead and check for invalid moves and columns
    int placeOnBoard = getIndex(userInput);
    if (placeOnBoard >= boardSize) {
      cout << "Invalid Column\n";
      continue;
    }
    if (placeOnBoard < 0) {
      cout << "Invalid Column\n";
      continue;
    }
    if (board[placeOnBoard].size() >= boardSize) {
      cout << "Invalid Move\n";
      continue;
    }
    // valid move
    board[placeOnBoard].tailInsert(currentUser == "Red");
    // break to exit
    // break;

    // int placeOnBoard = getIndex(userInput);
    cout << endl;
    switch (placeOnBoard) {
    case -1:
      cout << "Invalid Move" << endl;
      break;
    case 7:
      cout << "Invalid Move" << endl;
      break;
    default:
      if (placeOnBoard >= 0 && placeOnBoard < boardSize) {
      }
    }

    for (int i = boardSize - 1; i >= 0; i--) // creates rows
    {
      int j = 0;
      while (j < boardSize) {
        auto checkIt = board[j].end();
        if (i < board[j].size()) {
          int k = 0;
          while (k <= i) {
            checkIt++;
            k++;
          }
          cout << (*checkIt ? " R " : " B ");
        } else {
          cout << " - ";
        }
        j++;
      }
      cout << '\n';
    }

    cout << "\nA"
         << "  "
         << "B"
         << "  "
         << "C"
         << "  "
         << "D"
         << "  "
         << "E"
         << "  "
         << "F"
         << "  "
         << "G"
         << "  " << endl;

    // lets check for ties
    bool filledTheBoard = true;
    cout << endl;
    for (int i = 0; i < boardSize; i++) {
      if (board[i].size() != boardSize) {
        filledTheBoard = false;
        break;
      }
    }
    if (filledTheBoard) {
      cout << "Tie." << endl;
      return 0;
    }

    if (columnFound4(board)) { // check whoever the winner for the board is

      cout << currentUser << " wins !" << endl;
      return 0;
    }

    currentUser =
        (currentUser == r ? b : r); // string to string to switch players
  }

  return 0;
}

bool find4InARow(const LL<bool> &list) {

  if (list.size() < 4 || list.isEmpty())
    return false;
  auto first = list.begin();
  auto second = first;
  ++second;
  auto third = second;
  ++third;
  auto fourth = third;
  ++fourth;
  for (; fourth != list.end(); ++first, ++second, ++third, ++fourth) {
    if (*first == *second && *second == *third && *third == *fourth) {
      return true;
    }
  }
  return false;
}