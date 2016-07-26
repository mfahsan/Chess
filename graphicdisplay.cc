#include <iostream>
#include <vector>
#include <string>
#include "piece.h"
#include "window.h"
#include "graphicdisplay.h"

using namespace std;

GraphicDisplay::GraphicDisplay(Xwindow& xw) : length{maxLen/gridSize}, xw{xw}{		//ctor
  for (int r = 0 ; r < gridSize ; ++r) {
		for (int c = 0 ; c < gridSize ; ++c) {
			if (((r % 2 == 0) && (c % 2 == 0)) || ((r % 2 != 0) && (c % 2 != 0))) {			//fill square with Khaki
				xw.fillRectangle(r*length, c*length, length, length);
			}
			else {
				xw.fillRectangle(r*length, c*length, length, length, Xwindow::Brown);			//fill square with Brown
			}
		}
	}
	for (int c = 0 ; c < gridSize ; c++) {
		xw.fillRectangle(c*length, maxLen, length, 20, Xwindow::Orange);						//create column with letters
		string lpos = " ";
		lpos[0] = c + 'a';
		xw.drawString(c*length + 31, maxLen + 10, lpos);
		xw.fillRectangle(maxLen, c*length, 20, length, Xwindow::Orange);						//create row with numbers
		string npos = " ";
		npos[0] = '8' - c;
		xw.drawString(maxLen+5, c*length+31, npos);
	}
	xw.fillRectangle(maxLen, maxLen, 20, 20, Xwindow::Orange);
}

GraphicDisplay::~GraphicDisplay(){}								// dtor

void GraphicDisplay::notifyDisplay(const string &initial, const string &dest, Piece *p){		//called when piece is moved
  int oldR = '8' - initial[1];
	int oldC = initial[0] - 'a';
	if (((oldR % 2 == 0) && (oldC % 2 == 0)) || ((oldR % 2 != 0) && (oldC % 2 != 0))) {
		xw.fillRectangle(oldC*length, oldR*length, length, length);
	}
	else {
		xw.fillRectangle(oldC*length, oldR*length, length, length, Xwindow::Brown);
	}
	int newR = '8' - dest[1] + 1;
	int newC = dest[0] - 'a';
	int colour = p->getColour();
	string piece = " ";
	piece[0] = p->getType();
	xw.drawBigString(newC*length + 20, newR*length - 29, piece, colour);
}

void GraphicDisplay::notifyDisplay(Piece *p, const string &dest){				//called when piece is added
  int newR = '8' - dest[1] + 1;
	int newC = dest[0] - 'a';
	string piece = " ";
	piece[0] = p->getType();
	int colour = p->getColour();
	xw.drawBigString(newC*length + 20, newR*length - 20, piece, colour);
}

void GraphicDisplay::notifyDisplay(const string &dest){									//called when piece is removed
  int oldR = '8' - dest[1];
	int oldC = dest[0] - 'a';
	if (((oldR % 2 == 0) && (oldC % 2 == 0)) || ((oldR % 2 != 0) && (oldC % 2 != 0))) {
		xw.fillRectangle(oldC*length, oldR*length, length, length);
	}
	else {
		xw.fillRectangle(oldC*length, oldR*length, length, length, Xwindow::Brown);
	}
}

