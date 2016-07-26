#include "pawn.h"
#include "piece.h"

Pawn::Pawn(const int& colour) : Piece::Piece(colour, 1){}

void Pawn::increment(){
	if(colour == WHITE){
		int vec[4][2] = {{0, 1}, {1, 1}, {-1, 1}, {0, 2}};				//position vectors for a white pawn
		legalMoves.clear();
		for(int i = 0; i < 3; i++){																//get normal movement legal moves
			Piece::legalDestShort(vec[i]);
		}
  	if(position[1] == '2'){																		//get extra legal move at initial position
    	Piece::legalDestShort(vec[3]);
  	}
  }
  else if(colour == BLACK){
		int vec[4][2] = {{0, -1}, {-1, -1}, {1, -1}, {0, -2}};		//position vectors for a black pawn
		legalMoves.clear();
		for(int i = 0; i < 3; i++){																//get normal movement legal moves
			Piece::legalDestShort(vec[i]);
		}
  	if(position[1] == '7'){																		//get extra legal move at initial position
    	Piece::legalDestShort(vec[3]);
  	}
  }
}

char Pawn::getType(){
	if(colour == WHITE) return 'P';
	return 'p';
}

Pawn::~Pawn(){}
