#include "knight.h"
#include "piece.h"
#include <iostream>

using namespace std;

Knight::Knight(const int& colour) : Piece::Piece(colour, 2){}

void Knight::increment(){
	int vec[8][2] = {{1, 2}, {2, 1}, {-1, 2}, {2, -1},
			             {-2, 1}, {1, -2}, {-1, -2}, {-2, -1}};		//position vectors for a knight
	legalMoves.clear();
	for(int i = 0; i < 8; i++){																//get legal moves for each position vector
		Piece::legalDestShort(vec[i]);
	}
}

char Knight::getType(){
	if(colour == WHITE) return 'N';
	return 'n';
}

Knight::~Knight(){}
