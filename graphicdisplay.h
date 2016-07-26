#ifndef __GRAPHICDISPLAY_H__
#define __GRAPHICDISPLAY_H__
#include <iostream>
#include <vector>
class Piece;
class Xwindow;

class GraphicDisplay {
  const int maxLen = 496;			//length of the grid
  const int gridSize = 8;			//size of the grid
  const int length;						//length of a square
  Xwindow xw;
 public:
  GraphicDisplay(Xwindow& xw);			//ctor
  ~GraphicDisplay();								//dtor

  void notifyDisplay(const std::string &initial, const std::string &dest, Piece *p);	//notifies xw when a piece is moved
  void notifyDisplay(Piece *p, const std::string &dest);															//notifies xw when a piece is added
  void notifyDisplay(const std::string &dest);																				//notifies xw when a piece is removed
};

#endif
