#ifndef __AI3_H__
#define __AI3_H__

#include "ai.h"
class Grid;

class Ai3 final : public Ai {
		bool canCapture (const std::string &initial, const std::string &dest);			//returns true if piece at initial can capture piece at dest
		bool contains(const std::string& position, std::vector<std::string> positions);	//returns true if positions contians position
		bool canAvoidCapture(const std::string& initial, const std::string &dest);	//returns true if piece at initial can avoid cpature by
																																								//moving to dest
		std::vector<std::string> returnEndangered();			//returns all the pieces in danger
		bool move(const std::string &initial, const std::string &dest);	//returns true if moving a piece at initial to dest was successful
	public:
		void move();												//generates a valid move
																				//Prefers avoiding capture over capturing and checking the opposition king
		Ai3(const int& colour, Grid *g);		//ctor
		~Ai3();															//dtor
};

#endif
