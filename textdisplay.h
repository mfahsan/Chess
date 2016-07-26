#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
class Piece;

class TextDisplay {
  std::vector<std::vector<char>> theDisplay;	// text display for the grid
  const int gridSize;													// size of the grid
 public:
  TextDisplay();															// ctor
  ~TextDisplay();															// dtor

  void notifyDisplay(const std::string &initial, const std::string &dest, Piece *p);	// notifies theDisplay when a piece move
  void notifyDisplay(Piece *p, const std::string &dest);															// notifies theDisplay when a piece is added
  void notifyDisplay(const std::string &dest);																				// notifies theDisplay when a piece is removed
  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);					//output overload, prints the grid
};

#endif
