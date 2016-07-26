#ifndef __QUEEN_H__
#define __QUEEN_H__

#include "piece.h"

class Queen final : public Piece{
  public:
    Queen(const int& colour);	//ctor
    void increment() override;							//set legal moves for queen
    char getType() override;								//returns the type of queen, i.e. 'Q' or 'q'
    ~Queen();																//dtor
};

#endif
