#ifndef __AI1_H__
#define __AI1_H__

#include "ai.h"
class Grid;

class Ai1 final: public Ai {
	public:
		void move();											//generate a random move
		Ai1(const int& colour, Grid* g);	//ctor
		~Ai1();														//dtor
};

#endif
