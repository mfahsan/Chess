#include <iostream>
#include <vector>
#include <string>
#include "piece.h"
#include "textdisplay.h"

using namespace std;

TextDisplay::TextDisplay() : gridSize{8} {			//ctor
  for (int r = 0 ; r < gridSize ; ++r) {
		vector<char> Col;
		theDisplay.push_back(Col);
		for (int c = 0 ; c < gridSize ; ++c) {
			if (((r % 2 == 0) && (c % 2 == 0)) || ((r % 2 != 0) && (c % 2 != 0))) {
				theDisplay.at(r).push_back('_');
			}
			else {
				theDisplay.at(r).push_back(' ');
			}
		}
	}
}

TextDisplay::~TextDisplay(){}	//dtor

void TextDisplay::notifyDisplay(const string &initial, const string &dest, Piece *p){		//called when a piece is moved
  int oldR = initial[1] - '1';
	int oldC = initial[0] - 'a';
	if (((oldR % 2 == 0) && (oldC % 2 == 0)) || ((oldR % 2 != 0) && (oldC % 2 != 0))) {
		theDisplay[oldR][oldC] = '_';
	}
	else {
		theDisplay[oldR][oldC] = ' ';
	}
	int newR = dest[1] - '1';
	int newC = dest[0] - 'a';
	theDisplay[newR][newC] = p->getType();
}

void TextDisplay::notifyDisplay(Piece *p, const string &dest){			//called when a piece is added
  int newR = dest[1] - '1';
	int newC = dest[0] - 'a';
	theDisplay[newR][newC] = p->getType();
}

void TextDisplay::notifyDisplay(const string &dest){			//called when a piece is removed
  int oldR = dest[1] - '1';
	int oldC = dest[0] - 'a';
	if (((oldR % 2 == 0) && (oldC % 2 == 0)) || ((oldR % 2 != 0) && (oldC % 2 != 0))) {
		theDisplay[oldR][oldC] = '_';
	}
	else {
		theDisplay[oldR][oldC] = ' ';
	}
}

ostream &operator<<(ostream &out, const TextDisplay &td){	//output overload, prints the grid
  for(int i = td.gridSize; i > 0; i--){
  	out << i << ' '; 
    for(int j = 0; j < td.gridSize; j++){
      out << td.theDisplay[i-1][j];
    }
    out << '\n';
  }
  out << endl;
  out << "  ";
  for(char c = 'a'; c <= 'h'; c++){
  	out << c;
  }
  out << endl;
  return out;
}
