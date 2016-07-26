#ifndef __PIECE_H__
#define __PIECE_H__

#include <string>
#include <vector>
#define WHITE 0
#define BLACK 1

class Piece{
	protected:
		const int colour;
		std::vector <std::string> legalMoves;										//vector of all the legal moves for a piece
		std::string position;																		//position of the piece on the grid
		const int rank;																					//rank of a piece. Ranks are as follows:
																														//king = 6, queen = 5, rook = 4, bishop = 3, knight = 2, pawn = 1
		void legalDestLong(const int* vec);											//adds all positions to legalMoves from the current position to the end of the
																														//board in the given direction vector
		void legalDestShort(const int* vec);										//adds all positions to legalMoves from the current position to in the given
																														//direction vector
    bool hasMoved;																					//True if piece has moved before
	public:													
		Piece(const int& colour, const int& rank);	//Ctor
		bool isLegal(const std::string& dest);									//returns true if dest is a legal move
		void setCoords(const std::string &pos);									//set coordinates of piece on the board
		std::string getCoords();																//returns coordinates of the piece on the board
		int getRank();																					//returns rank of the piece
		int getColour();																				//returns the value of colour
		void setHasMoved(bool moved);														//change hasMoved
		bool getHasMoved();																			//returns value of hasMoved
		std::vector<std::string> const &getLegalMoves() const;	//returns the legal moves vector
		virtual char getType() = 0;	
		virtual void increment() = 0;																							
		virtual ~Piece() = 0; 																	//pure virtual dtor
};

#endif
