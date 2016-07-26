#include "ai.h"
#include "grid.h"
#include <string>
#include "piece.h"

using namespace std;

Ai::Ai(const int& colour, Grid* g) : colour{colour}, g{g} {}						//ctor

int Ai::getColour(){ return colour; }																		//returns colour of the AI

bool Ai::attackCheck(const string& initial, const string& dest) {				//checks which piece can put the opposition king under check
  bool underCheck = false;
  if (!g->canMove(initial, dest)) return underCheck;

  Piece *temp = g->assumeMove(initial, dest);														//assume piece at initial move to final
	int opColour = g->oppColour(colour);
  string kingPosn = g->getKingPos(opColour);														//get opposition kings postion
  vector<string> pieces = g->returnPieces(colour);											//get all ai pieces

  for (int i = 0 ; i < pieces.size() ; i++) {					//iterate through all the pieces to see if any piece can put the king under check
  	if ((g->canMove(pieces[i], kingPosn))) {
    	underCheck = true;
    	g->undoAssume(initial, dest,temp);
    	return underCheck;
    }
  }
  g->undoAssume(initial, dest, temp);									//undo the assumed move
  return underCheck;
}

bool Ai::canPromote(const string &initial, const string &dest) {						//return true if pawn promotion is possible
  Piece *p = g->getPiece(initial);

  if ((!(p->getType() == 'p')) && (!(p->getType() == 'P'))) return false;		//if not a pawn return false
  else if (p->getType() == 'P') {																						//if white pawn
    if ((initial[1] != '7') || (dest[1] != '8')) return false;							//check initial position and final position
  }
  else if (p->getType() == 'p') {																						//if black pawn
    if ((initial[1] != '2') || (dest[1] != '1')) return false;							//check initial position and final position
  }
  return true; 
}
