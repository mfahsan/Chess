#include "king.h"
#include "piece.h"

King::King(const int& colour) : Piece::Piece(colour, 6){}

void King::increment(){
	int vec[8][2] = {{1, 1}, {1,-1}, {-1, 1}, {-1, -1},			//position vectors for a king
			 {0, 1}, {1, 0}, {-1, 0}, {0, -1}};
	legalMoves.clear();
	for(int i = 0; i < 8; i++){															//get legal moves for each position vector
		Piece::legalDestShort(vec[i]);
	}

}

char King::getType(){
	if(colour == WHITE) return 'K';
	return 'k';
}

King::~King(){}
