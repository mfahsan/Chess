#ifndef __ROOK_H__
#define __ROOK_H__

#include "piece.h"

class Rook final : public Piece{
  public:
    Rook(const int& colour);	//ctor
    void increment() override;						//set legal moves for rook
    char getType() override;							//returns the type of rook, i.e. 'R' or 'r'
    ~Rook();															//dtor
};

#endif
