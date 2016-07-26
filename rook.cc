#include "rook.h"
#include "piece.h"

Rook::Rook(const int& colour) : Piece::Piece(colour, 4){}

void Rook::increment(){
	int vec[4][2] = {{0, 1}, {1,0}, {-1, 0}, {0, -1}};	//Position vectors for rook
	legalMoves.clear();		
	for(int i = 0; i < 4; i++){													//set legal moves for rook for every direction vector
		Piece::legalDestLong(vec[i]);
	}
}

char Rook::getType(){
	if(colour == WHITE) return 'R';
	return 'r';
}

Rook::~Rook(){}
