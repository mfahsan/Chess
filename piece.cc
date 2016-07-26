#include "piece.h"
#include <iostream>

using namespace std;

Piece::Piece(const int& colour, const int& rank) : colour{colour}, position{"  "}, rank{rank}, hasMoved{false} {}

bool Piece::isLegal(const string& dest){
  for(auto &g : legalMoves){		//Iterate through legal moves
    if(g == dest){
      return true;
    }
  }
  return false;
}

void Piece::legalDestLong(const int* vec){
  string pos = "  ";
  char xpos = position[0];
  char ypos = position[1];
  xpos += vec[0];
  ypos += vec[1];
  while(xpos <= 'h' && xpos >= 'a' && ypos <= '8' && ypos >= '1'){			//add till end of the board
    pos[0] = xpos;
    pos[1] = ypos;
    legalMoves.push_back(pos);
    xpos += vec[0];
 		ypos += vec[1];
  }
}

void Piece::legalDestShort(const int* vec){
  string pos = "  ";
  char xpos = position[0];
  char ypos = position[1];
  xpos += vec[0];
  ypos += vec[1];
  pos[0] = xpos;
  pos[1] = ypos;
  if(xpos <= 'h' && xpos >= 'a' && ypos <= '8' && ypos >= '1') legalMoves.push_back(pos);	//add if xpos and ypos are positions on the board
}

vector<string> const& Piece::getLegalMoves() const { return legalMoves; }
string Piece::getCoords(){ return position; }
int Piece::getColour(){ return colour; } 
int Piece::getRank(){ return rank; }
void Piece::setCoords(const string& pos){ position = pos; }
void Piece::setHasMoved(bool moved){ hasMoved = moved; }
bool Piece::getHasMoved(){ return hasMoved; }

Piece::~Piece() {}												//dtor
