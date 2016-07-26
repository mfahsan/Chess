#include "grid.h"
#include "ai4.h"
#include "piece.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <ctime>
using namespace std;



Ai4::~Ai4(){}

bool Ai4::canCapture (const string &initial, const string &dest) {
  if (!g->getPiece(dest)) return false;           // checks if there is a piece at dest (capture not possible if there isnt )

   return g->canMove(initial, dest);    // checks of initial can move to dest (canmove and pieceexist means opponents piece can be captured )


}

int Ai4::returnRank(const string &initial, const string &dest) {
  //if (!g->pieceExist(initial)) return 0;
	if (canCapture(initial,dest)) {
    			Piece *p = g->getPiece(dest);     // gets the piece 
    			return p->getRank();            // gets the rank 
    		}   
    	  
     return 0;              // returns 0 if there is no piece at dest 
} 

int Ai4::maxRank(const int& colour) {
	vector<string> move; 
	int rank = 0;
	vector<string> pieces = g->returnPieces(colour);   // gets piece positions 
    
    for (int i =0; i < pieces.size(); i++)  {        // loops through every piece 
    	Piece *p = g->getPiece(pieces[i]); 
    	vector<string> legalMoves = p->getLegalMoves();
    	for (int j = 0; j < legalMoves.size(); j++) {    // loops through the legal moves of piece 
    		if (canCapture(pieces[i],legalMoves[j])) { 
    			Piece *q = g->getPiece(legalMoves[j]);
    			if (q->getRank() > rank) {                 
    			 rank = q->getRank();                        // replaces the rank only if it is greater than the highest previous rank 
    	  }
      }
    
    }
 }
 return rank;        // returns rank after receiving the highest rank
}

Ai4::Ai4(const int& colour, Grid *g) : Ai::Ai(colour, g) {}


bool Ai4::contains(const string& position, vector<string> positions) {
  for (int i = 0; i < positions.size(); i++) {
     if (position == positions[i]) return true;
  }
 return false;
}



void Ai4::move() {
   srand(time(NULL));
   int opColour = g->oppColour(colour);    // gets oppoonents colour 
    

   vector<string> opPieces = g->returnPieces(opColour);
   int state = -6;                  // set to worse than worst possible state, so that it is replaced by the first move

   int cap = 0;
   int avoid = 0;
 
   string initial = "  ";           // initialises two strings, later to be replaced by movements 
   string dest = "  ";   
     
   
   	vector<string> pieces = g->returnPieces(colour);
    
    std::vector<string> piecesConsidered;


    while (1)  {
    	if(pieces.size() == piecesConsidered.size()) break;     // breaks out of the loop if all pieces have been considered 
    	
    	int random = rand() % pieces.size();
    	
    	string piecePosn = pieces[random];              // takes a random piece 
    	
    	Piece *p = g->getPiece(piecePosn);
    	if(contains (piecePosn, piecesConsidered)) continue;      // does the loop again if the piece has already been considered 
    	vector<string> legalMoves = p->getLegalMoves();
    	for (int j = 0; j < legalMoves.size(); j++) {
    		if (!g->canMove(piecePosn, legalMoves[j])) continue;           // does the loop again if the movement is not possible 
    		
        int newcap = returnRank(piecePosn, legalMoves[j]);
    		
        if (attackCheck(piecePosn, legalMoves[j])) {              // gives a preference of putting the king on check 
    			newcap += 1;
    		}
        
        if (canPromote(piecePosn, legalMoves[j])) {             // gives a preference of promoting since pawn changes to queen 
          newcap += 3;   
        }
         
        string condest = legalMoves[j];
        
        int dir = condest[0] - piecePosn[0];

    		Piece *a = g->assumeMove(piecePosn, legalMoves[j]);          // the move has to be assumed to check the max rank of the opponent  
    	    int newavoid = maxRank(opColour);                         // after the move 
    	    g->undoAssume(piecePosn, legalMoves[j],a);                       // undoes the move since move is not finalised 
    	    if ((newcap - newavoid) > state) {                    // replaces the move with previous if it can offer higher state 
    	    	 initial = piecePosn;
    	    	 dest = legalMoves[j];
    	    	 cap = newcap;
    	    	 avoid = newavoid;             
    	    	 state = cap - avoid;
    	    }
    	    else if ((newcap - newavoid) == state) {            // replaces the move if it offers same state but a safer move 
    	       if (newavoid < avoid) {
    	       	initial = piecePosn;
    	    	 	dest = legalMoves[j];
    	    	 	cap = newcap;
    	    	 	avoid = newavoid;
    	    	 	state = cap - avoid;
    	       }
    	    }
    	}
    	piecesConsidered.push_back(piecePosn);             // adds to pieces considered 
    }
     
     

     if (canPromote(initial,dest)) {
      if (colour == BLACK) g->move(initial, dest, 'q');            // adds the extra parameter if promoting is done. Always promotes to queen 
      else g->move(initial, dest, 'Q');                             // calls move and finishes the function 

      return;
   }
    


     g->move(initial, dest);                    // calls move with the final decisions of move
}
