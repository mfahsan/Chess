#include "bishop.h"
#include "piece.h"
#include <iostream>

using namespace std;

Bishop::Bishop(const int& colour) : Piece::Piece(colour, 3){}

void Bishop::increment(){
	int vec[4][2] = {{1, 1}, {1,-1}, {-1, 1}, {-1, -1}};	//movement vectors for bishop
	legalMoves.clear();
	for(int i = 0; i < 4; i++){														//find all legel moves for each position vector
		Piece::legalDestLong(vec[i]);
	}
}

char Bishop::getType(){
	if(colour == WHITE) return 'B';
	return 'b';
}

Bishop::~Bishop(){}
