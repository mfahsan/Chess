#ifndef __GRID_H__
#define __GRID_H__

#include <iostream>
#include <vector>
#include <string>

#define WHITE 0
#define BLACK 1

class TextDisplay;
class GraphicDisplay;
class Xwindow;
class Piece;
class Ai;

class Grid {
  	std::vector<std::vector<Piece *>> theGrid;			// the actual chess board  
  	std::vector<std::string> history;					// the history of moves
  	std::vector<Piece *> removed;						// pieces captured

  	int gridSize;    									// size of the grid
  	bool checkMate;        							
  	bool staleMate;
  	bool check;
  
  	int player = 0; 									// shows whose turn it is, black or white
  	int numMoves = 0; 									// number of moves played

  	double whiteScore = 0;
  	double blackScore = 0;

  	bool enPossible = false;							// true if the enpassant move can be performed
  	std::string enPassantPos = "  ";					// the position where the pawn can move to for enpassant to work

	bool whiteCheckedBefore = false;
	bool blackCheckedBefore = false;
	
  	bool isCustom;										// true if the board is a custom setup
  
  	TextDisplay *td; 									// textdisplay
  	GraphicDisplay *gd;									// graphics display
  
  	Ai* comp1;											// white Ai
  	Ai* comp2;											// black ai
  
  	std::string getString(int r, int c);														// returns string corresponding to the row and column 
  	void changePlayer();																		// changes the player after every move
  	void win(const int& colour);																// updates the checkMate field
  	void clearGrid();																			// clears the board after every game
  	void initEmpty();																			// initializes an empty chess board
  	void stalemate(const int& colour);															// updates the staleMate field
  	void makeHistory(const std::string& initial,const std::string& dest);						// adds the move made to the history vector
  
  	bool checkObstruct(const std::string &initial, const std::string &dest);					// checks if there is any obstruction between initial and dest
  	bool entailsCheck(const std::string &initial,const std::string &dest); 						// checks if a move made from initial to dest puts the players king under check
  	bool checkCheck(const int& player); 														// checks if players king is under check
  	bool isFriend(const std::string& initial, const std::string& dest);							// checks if the piece at dest is a friend of piece at initial
  	bool validColour(const std::string& initial, const int& colour);							// checks if the piece being moved is of the same colour as the player
  	bool castling(const std::string& initial, const std::string& dest);							// castling move
  	bool castlingCondition(const std::string& initial, const int& dir);							// checks if all the conditions for castling is satisfied
  	bool promote(const std::string& initial ,const std::string& dest, const char& type);		// promoting move
  	bool CheckedBefore(const int& player);														// true if the player has been checked before
  	bool validPos(const std::string& pos);														// checks if pos is a valid position on the board
  	bool enPassant(const std::string& initial, const std::string& dest);						// enpassant move
 
  public:
 
  	Grid();																						// ctor
  	~Grid();																					// dtor
  
  	int oppColour(const int& colour);															// returns the opposite colour of colour
  	double getWhiteScore();																		// returns whites score
  	double getBlackScore();																		// returns blacks score
  
  	void notify(const std::string &initial,const std::string &dest); 							// notifies both the displays when a piece is moved
  	void init(Xwindow& xw); 																	// initializes the board			
  	void addPiece(const char &t, const std::string &dest);										// adds a piece of type t at dest
  	void removePiece(const std::string &dest);													// removes piece from dest
  	void setIsCustom(const bool& custom);														// sets the isCustom field to true or false
  	void setCompLevel1(const int& level);														// sets the level of white ai
  	void setCompLevel2(const int& level);														// sets the level of black ai
  	void setPlayer(const int& colour);															// sets which player moves next
  	void undoAssume(const std::string& initial, const std::string& dest , Piece* captured);		// undoes the assumed moved
  	void updateScore();																			// updates the score
  
  	bool undo();																				// undo the previous move
  	bool canMove(const std::string &initial, const std::string &dest);							// returns true if the piece can move from initial to dest
  	bool move(const std::string& initial, const std::string& dest, const char& type = ' '); 	// moves piece from initial to dest
  	bool checkConditions();																		// checks if the setup conditions are met
  	bool getIsCustom();																			// returns the isCustom field
  	bool getCheckMate();																		// returns the checkmate field 
  	bool getStaleMate();																		// returns the checkmate field
  	bool move();																				// moves the ai
  	bool pieceExist(const std::string &position);												// returns true if a piece exists at position
  	bool getCheck();																			// returns the check field
  
  	std::string getKingPos(const int &player);													// returns the players king position
  	std::string getPlayer();																	// returns the player who moves next
  	Piece* assumeMove(const std::string& initial, const std::string& dest);						// assumes a move from initial to dest and returns a piece pointer from dest
  	Piece* getPiece(const std::string &position);												// returns the piece from position
  	std::vector<std::string> returnPieces(const int& colour);									// returns a vector of all the pieces of colour
  	std::vector<std::string> getHistory();														// returns the history vector
  
  	friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
