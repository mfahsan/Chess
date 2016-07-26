#include "queen.h"
#include "piece.h"

Queen::Queen(const int& colour) : Piece::Piece(colour, 5){}

void Queen::increment(){
	int vec[8][2] = {{1, 1}, {1,-1}, {-1, 1}, {-1, -1},
			 {0, 1}, {1, 0}, {-1, 0}, {0, -1}};							//direction vectors for a queen
	legalMoves.clear();
	for(int i = 0; i < 8; i++){													//set legal moves for each direction vector
		Piece::legalDestLong(vec[i]);
	}

}

char Queen::getType(){
	if(colour == WHITE) return 'Q';
	return 'q';
}

Queen::~Queen(){}
