#ifndef __AI2_H__
#define __AI2_H__

#include "ai.h"
class Grid;

class Ai2 final : public Ai {
		bool canCapture(const std::string &initial, const std::string &dest);						//returns true if initial can capture at dest
		bool contains(const std::string& position, std::vector<std::string> positions);	//retunrs true if positions contains position
	public:
		void move();											//generate a valid move
																			//Prefers caturing an opponent piece over avoiding capture and checking
		Ai2(const int& colour, Grid *g);	//ctor
		~Ai2();														//dtor
};

#endif
