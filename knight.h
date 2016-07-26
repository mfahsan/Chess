#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "piece.h"

class Knight final : public Piece{
  public:
    Knight(const int& colour);	//ctor
    void increment() override;							//set the legal moves for a Knight at position
    char getType() override;								//returns the type of Knight, i.e. 'n' or 'N'
    ~Knight();															//dtor
};

#endif
