#ifndef __AI4_H__
#define __AI4_H__

#include "ai.h"
class Grid;

class Ai4 : public Ai {
		bool canCapture (const std::string &initial, const std::string &dest);  // returns true if piece at initial can capture at dest 
		int returnRank(const std::string &initial, const std::string &dest);   // returns the rank of the piece at dest 
		int maxRank(const int& colour);                  // returns the max rank that can be captured by the player with colour 
		std::vector<std::string> returnEndangered();       
		bool contains(const std::string& position, std::vector<std::string> positions);  // returns true if position exists in positions   
	public:
		void move();                       // move function 
		Ai4(const int& colour, Grid *g);      // constructor 
		~Ai4();    							// destructor 
}; 

#endif
