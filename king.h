#ifndef __KING_H__
#define __KING_H__

#include "piece.h"

class King final : public Piece{
  public:
    King(const int& colour);	//ctor
    void increment() override;						//set the legal moves for a king at position
    char getType() override;							//returns the type of king, i.e. 'k' or 'K'
    ~King();															//dtor
};

#endif
