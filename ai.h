#ifndef __AI_H__
#define __AI_H__
#include <string>
class Grid;

class Ai {
	protected:
 		const int colour;				//colour of AI
 		Grid *g;								//grid that the AI acts on
 		bool attackCheck(const std::string& initial, const std::string& dest);	//returns true if moving from initial to final puts the
 																																						//opposition king under check
 		bool canPromote(const std::string& initial, const std::string& dest);		//returns true if pawn promotion is possible
 	public:
 		Ai(const int& colour, Grid* g);			//ctor
  	virtual void move() = 0;
  	int getColour();										//returns colour
  	virtual ~Ai() = default;						//dtor
};

#endif
