#include "grid.h"
#include "ai3.h"
#include "piece.h"
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;

Ai3::Ai3(const int& colour, Grid* g) : Ai::Ai(colour, g) {}	//ctor

Ai3::~Ai3(){}		//dtor

bool Ai3::canCapture (const string &initial, const string &dest) {			//returns true if piece at initial can capture piece at dest
  if (!g->getPiece(dest)) return false; 
  return g->canMove(initial, dest); 
}

bool Ai3::contains(const string& position, vector<string> positions) {	//returns true if positions has position in it
  for (int i = 0; i < positions.size(); i++) {
  	if (position == positions[i]) return true;
  }
 	return false;
}

vector<string> Ai3::returnEndangered() {					//returns pieces that are in danger
	int opColour;
  vector<string> endangered;

	if (colour == 0) opColour = 1;
 	else opColour = 0;

  vector<string> opPieces = g->returnPieces(opColour);
  for (int i = 0; i < opPieces.size();i++) {					//Iterate through opposite pieces
  	Piece *p = g->getPiece(opPieces[i]);
    vector<string> legalMoves = p->getLegalMoves();
    for (int j = 0; j < legalMoves.size(); j++) {			//Iterate through legal moves of p
      if ((!contains(legalMoves[j], endangered)) && canCapture(opPieces[i], legalMoves[j])) endangered.push_back(legalMoves[j]);
    } 
  }
  return endangered;
}

bool Ai3::canAvoidCapture(const string& initial, const string &dest) {	//checks if piece at initial can avoid capture by moving to dest
	int opColour; 

 	if (colour == 0) opColour = 1;
 	else opColour = 0;

 	if(!g->canMove(initial, dest)) return false;					//check if piece at initial can move to dest
 	Piece *q = g->assumeMove(initial, dest);

 	vector<string> opPieces = g->returnPieces(opColour);

 	for (int i = 0; i < opPieces.size(); i++) {						//Iterate through all the oppostion pieces 
  	if (canCapture(opPieces[i],dest)) {
   		g->undoAssume(initial, dest,q);
   		return false;
   	}
 	}
 	g->undoAssume(initial, dest, q);
 	return true;
}

bool Ai3::move(const string &initial, const string &dest) {	//checks for pawn promotion and valid moves
	srand(time(NULL));
  Piece *p = g->getPiece(initial);
  
  if (canPromote(initial, dest))  {				//checks for pawn promotion and randomly generates a type to promote to 
  	int rand2 = rand() % 4;
		char d = p->getType() - 'P';
    if (rand2 == 0) {
    	d += 'Q';
      return g->move(initial, dest, d);
    }
    else if (rand2 == 1) {
    	d += 'B';
      return g->move(initial, dest, d);
    }
    else if (rand2 == 2) {
    	d += 'R';
      return g->move(initial, dest, d);
    }
    else {
    	d += 'N';
      return g->move(initial, dest, d);
    }
  }
  return g->move(initial, dest);  						//move piece at initial to dest
}

void Ai3::move() {			//generate initial nad final position to move to
	vector<string> endangered = returnEndangered();	//get pieces in danger
	vector<string> piecesConsidered;

	srand(time(NULL));

	while (1) {				//piece in danger trying to avoid capture and capture 
		if (piecesConsidered.size() == endangered.size()) break;
	  int random = rand() % endangered.size();
	  string piecePosn = endangered[random];
	  if (contains(piecePosn, piecesConsidered)) continue;
	  Piece *p = g->getPiece(piecePosn); 
	  vector<string> legalMoves = p->getLegalMoves();
		
	  for (int i = 0; i < legalMoves.size(); i++) {
	  	string newPosn = legalMoves[i];
	  	if(canAvoidCapture(piecePosn, newPosn) && canCapture(piecePosn, newPosn)) {
	    	move(piecePosn, newPosn);
	    	return;
      }
  	}
  	piecesConsidered.push_back(piecePosn);
	}
	piecesConsidered.clear();
	while (1) {				//piece in danger trying to avoid capture
    if (piecesConsidered.size() == endangered.size()) break;
    int random = rand() % endangered.size();
    string piecePosn = endangered[random];
    if (contains(piecePosn, piecesConsidered)) continue;
    Piece *p = g->getPiece(piecePosn); 
    vector<string> legalMoves = p->getLegalMoves();

    for (int i = 0; i < legalMoves.size(); i++) {
      string newPosn = legalMoves[i];
      if(canAvoidCapture(piecePosn, newPosn)) {
        move(piecePosn, newPosn);
        return;
      }
    }
    piecesConsidered.push_back(piecePosn);
	}

	piecesConsidered.clear();

	while (1) {   			//piece in danger trying to capture
		if (piecesConsidered.size() == endangered.size()) break;
  	int random = rand() % endangered.size();
  	string piecePosn = endangered[random];
  	if (contains(piecePosn, piecesConsidered)) continue;
  	Piece *p = g->getPiece(piecePosn); 
  	vector<string> legalMoves = p->getLegalMoves();

  	for (int i = 0; i < legalMoves.size(); i++) {
  		string newPosn = legalMoves[i];
  		if (canCapture(piecePosn, newPosn)) {
      	move(piecePosn, newPosn);
    		return;
      }
  	}
  	piecesConsidered.push_back(piecePosn);
	}

	piecesConsidered.clear();

	while (1) {         //random piece trying to avoid capture and capture
	  vector<string> pieces = g->returnPieces(colour);
  	if (piecesConsidered.size() == pieces.size()) break;
  	int random = rand() % pieces.size(); 
  	string piecePosn = pieces[random];
  	if (contains(piecePosn, piecesConsidered)) continue;
  	Piece *p = g->getPiece(piecePosn);
  	vector<string> legalMoves = p->getLegalMoves();

  	for (int i = 0; i < legalMoves.size(); i++) {
    	string newPosn = legalMoves[i];
    	if (canAvoidCapture(piecePosn, newPosn) && canCapture(piecePosn, newPosn)) {
      	move(piecePosn, newPosn);
      	return;
    	}
		}
 		piecesConsidered.push_back(piecePosn);
	}

	piecesConsidered.clear();

	while (1) { 				//random piece truing to capture
  	vector<string> pieces = g->returnPieces(colour);
   	if (piecesConsidered.size() == pieces.size()) break;
  	int random = rand() % pieces.size(); 
  	string piecePosn = pieces[random];
  	if (contains(piecePosn, piecesConsidered)) continue;
  	Piece *p = g->getPiece(piecePosn);
  	vector<string> legalMoves = p->getLegalMoves();
  	
  	for (int i = 0; i < legalMoves.size(); i++) {
  		string newPosn = legalMoves[i];
  		if(canCapture(piecePosn, newPosn)) { 
    		move(piecePosn, newPosn);
    		return;
    	}
		}
 		piecesConsidered.push_back(piecePosn);
	}

	piecesConsidered.clear();

	while (1) {         //random piece trying to put opposition king under check
  	vector<string> pieces = g->returnPieces(colour);
  	if (piecesConsidered.size() == pieces.size()) break;
  	int random = rand() % pieces.size(); 
  	string piecePosn = pieces[random];
		if (contains(piecePosn, piecesConsidered)) continue;
  	Piece *p = g->getPiece(piecePosn);
  	vector<string> legalMoves = p->getLegalMoves();

  	for (int i = 0; i < legalMoves.size(); i++) {
    	string newPosn = legalMoves[i];
    	if (attackCheck(piecePosn, newPosn)) {
      	move(piecePosn, newPosn);
      	return;
    	}
		}
 		piecesConsidered.push_back(piecePosn);
	}

	piecesConsidered.clear();

	while (1) { 			//random piece trying to move
	  vector<string> pieces = g->returnPieces(colour);
  	int random = rand() % pieces.size(); 
  	string piecePosn = pieces[random];
  	if (contains (piecePosn, piecesConsidered)) continue;
  	Piece *p = g->getPiece(piecePosn);
  	vector<string> legalMoves = p->getLegalMoves();
  	
  	for (int i =0; i < legalMoves.size(); i++) {
  		string newPosn = legalMoves[i];
  		if (move(piecePosn, newPosn)) return;
  	}
  	piecesConsidered.push_back(piecePosn);
  }
}
