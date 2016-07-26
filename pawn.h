#ifndef __PAWN_H__
#define __PAWN_H__

#include "piece.h"

class Pawn final : public Piece{
  public:
    Pawn(const int& colour);	//ctor
    void increment() override;						//set the legal moves for a pawn at position
    char getType() override;							//returns the type of pawn, i.e. 'p' or 'P'
    ~Pawn();															//dtor
};

#endif
