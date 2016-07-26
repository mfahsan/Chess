#include "grid.h"
#include "ai2.h"
#include "piece.h"
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

Ai2::Ai2(const int& colour, Grid* g) : Ai::Ai(colour, g) {}			//ctor

Ai2::~Ai2(){}		//dtor

bool Ai2::canCapture (const string &initial, const string &dest) {						//returns true if piece at initial can capture piece at dest
  if (!g->getPiece(dest)) return false; 
  return g->canMove(initial, dest); 
}

bool Ai2::contains(const string& position, std::vector<string> positions) {		//returns true if positions has position in it
  for (int i = 0; i < positions.size(); i++) {
  	if (position == positions[i]) return true;
  }
 	return false;
}

void Ai2::move() {																							//generates a move for AI level 2
	std::vector<string> piecesConsidered; 
  srand(time(NULL));

  std::vector<string> pieces = g->returnPieces(colour);					//get AI pieces
  
  while (1) { 																										//checks if any piece can capture
  	if (piecesConsidered.size() == pieces.size()) break;					//break from the loop if all pieces have been considered

  	int random = rand() % pieces.size(); 													//generate a random number
  
  	string piecePosn = pieces[random];														//get a position from pieces with random
  
  	if(contains(piecePosn, piecesConsidered)) continue; 					//check if piece has been considered before
  
  	Piece *p = g->getPiece(piecePosn);														//get the piece at piecePosn
  	std::vector<string> legalMoves = p->getLegalMoves();					//get legal moves of p

  	for (int i = 0; i < legalMoves.size(); i++) {									//Iterate through all the legal moves of p to determine if p can capture
 			string newPosn = legalMoves[i];
  		if (!canCapture(piecePosn, newPosn)) continue;							//contiune if piece cannot make a capturing move
    	else {
    		if (canPromote(piecePosn, newPosn))  {										//check for pawn promotion
    			int rand2 = rand() % 4;																	//randomly generate a piece type to promote the pawn to
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
		piecesConsidered.push_back(piecePosn);												//add to pieces considered so as to not check the same piece twice
	}

	piecesConsidered.clear();																				//clear all pieces considered

	while (1) { 																										//checks if any piece can putthe opposite king under Check
		if (piecesConsidered.size() == pieces.size()) break;					//break from the loop if all pieces have been considered
  	int random = rand() % pieces.size(); 													//generate a random number
  	
  	string piecePosn = pieces[random];														//get a position from pieces with random
  
  	if (contains(piecePosn, piecesConsidered)) continue; 					//check if piece has been considered before
  
  	Piece *p = g->getPiece(piecePosn);														//get the piece at piecePosn
  	std::vector<string> legalMoves = p->getLegalMoves();					//get legal moves of p

  	for (int i = 0; i < legalMoves.size(); i++) {									//Iterate through all the legal moves of p to determine if p can capture
  	  string newPosn = legalMoves[i];
  	  if (!attackCheck(piecePosn, newPosn)) continue;							//check if Checking the opposite king is possible
  	  else {
  	  	if (canPromote(piecePosn, newPosn))  {										//check for pawn promotion
  	  		int rand2 = rand() % 4;																	//randomly generate a type to promote to
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
				
				g->move(piecePosn, newPosn);															//move piece
     	 return;
   		}
		}
		piecesConsidered.push_back(piecePosn);												//add to piece to considered
	}

	while (1) { 																										//randomly moves a piece
	  int random = rand() % pieces.size(); 													//generate a random number
	  
	  string piecePosn = pieces[random];														//get a random piece
	  
	  Piece *p = g->getPiece(piecePosn);														//get piece at piecePosn
	  vector<string> legalMoves = p->getLegalMoves();								//get legal moves of p
	  
	  int random2 = rand() % legalMoves.size();											//get a random legal move
	  string newPosn = legalMoves[random2];
	
	  if (!g->canMove(piecePosn, newPosn)) continue;								//check if move can be made
	  
	  if (canPromote(piecePosn, newPosn))  {												//check for pawn promotion
    	int rand2 = rand() % 4;
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
    g->move(piecePosn, newPosn);																	//move the 
    return;
	}
}
