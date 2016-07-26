#include "grid.h"
#include "ai1.h"
#include "piece.h"
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;
std::vector<char> v;

Ai1::Ai1(const int& colour, Grid *g) : Ai::Ai(colour, g) {}		//ctor

Ai1::~Ai1(){}																									//dtor

void Ai1::move() {																						//move function
  srand(time(NULL));
	std::vector<string> pieces = g->returnPieces(colour);				//get pieces
  
  while (1) { 
  	int random = rand() % pieces.size(); 
  
  	string piecePosn = pieces[random];													//randomly select a piece from pieces
  
  	if (!g->pieceExist(piecePosn)) continue;
  
  	Piece *p = g->getPiece(piecePosn);
  	vector<string> legalMoves = p->getLegalMoves();
  
 	 	int random2 = rand() % legalMoves.size();	
 	 	string newPosn = legalMoves[random2];												//randomly select a legal move

  	if (!g->canMove(piecePosn, newPosn)) continue;							//check if randomlyselected piece can move to a newPosn

  	if (canPromote(piecePosn, newPosn)){											//check if pawn promotionis possible
  		int rand2 = rand() % 4;																		//randomly generate a piece type to promte the pawn to
			char d = p->getType() - 'P';
		
    	if (rand2 == 0) {
    		d += 'Q';
      	g->move(piecePosn, newPosn, d);
    	}
    	else if (rand2 == 1) {
    		d += 'B';
      	g->move(piecePosn, newPosn, d);
    	}
    	else if (rand2 == 2) {
    		d += 'R';
      	g->move(piecePosn, newPosn, d);
    	}
    	else {
    		d += 'N';
      	g->move(piecePosn, newPosn, d);
    	}
   		return;
 		}
   	g->move(piecePosn, newPosn);															//move the piece
   	return;
	}
}
