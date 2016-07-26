#ifndef __BISHOP_H__
#define __BISHOP_H__

#include "piece.h"

class Bishop final : public Piece{
  public:
    Bishop(const int& colour);	//ctor
    void increment() override;							//set the legal moves for a bishop at position
    char getType() override;								//returns the type of bishop, i.e. 'b' or 'B'
    ~Bishop();															//dtor
};

#endif
