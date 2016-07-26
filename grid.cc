#include <iostream>
#include "grid.h"
#include "piece.h"
#include "textdisplay.h"
#include "window.h"
#include "graphicdisplay.h"
#include "pawn.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "ai.h"
#include "ai1.h"
#include "ai2.h"
#include "ai3.h"
#include "ai4.h"
#include <string>

using namespace std;

Grid::Grid():gridSize{0}, checkMate{false}, staleMate{false}, check{false}, td{nullptr}, gd{nullptr}, comp1{nullptr}, comp2{nullptr}, player{WHITE} {}

Grid::~Grid() {
	delete comp1;
	delete comp2;
	for (int r = 0 ; r < gridSize ; r++) {
		for (int c = 0 ; c < gridSize ; c++) {
			delete theGrid[r][c];
		}
	}
	for (auto m : removed) {
		delete m;
	}
}

void Grid::setCompLevel1(const int& level){ 
	switch (level){
		case 1:
			comp1 = new Ai1(WHITE, this);
			break;
		case 2:
			comp1 = new Ai2(WHITE, this);
			break;
		case 3:
			comp1 = new Ai3(WHITE, this);
			break;
		case 4:
			comp1 = new Ai4(WHITE, this);
			break;
		default:
			break;
	}
}
void Grid::setCompLevel2(const int& level){
	switch (level){
		case 1:
			comp2 = new Ai1(BLACK, this);
			break;
		case 2:
			comp2 = new Ai2(BLACK, this);
			break;
		case 3:
			comp2 = new Ai3(BLACK, this);
			break;
		case 4:
			comp2 = new Ai4(BLACK, this);
			break;
		default:
			break;
	}
}

void Grid::setIsCustom(const bool& custom){ isCustom = custom; }

bool Grid::getIsCustom(){ return isCustom; }

void Grid::setPlayer(const int& colour){ player = colour; }

string Grid::getPlayer(){
	if (player == 0) {
		return "White";
	}
	else {
		return "Black";
	}
}

bool Grid::getCheckMate(){ return checkMate; }

void Grid::clearGrid() {
	delete td;
	delete comp1;
	delete comp2;
	for(int i = 0; i < gridSize; i++){
		theGrid.at(i).clear();
	}
	gridSize = 0;
	checkMate = false;
	staleMate = false;
	history.clear();
	removed.clear();
	player = WHITE;
	enPossible = false;
	enPassantPos = "  ";
	check = false;
}

void Grid::addPiece(const char &t, const string &dest){
	if(validPos(dest)){
		int r = dest[1] - '1';
		int c = dest[0] - 'a';
		Piece *p;
		switch (t){
			case 'p':
				p = new Pawn(BLACK);
				p->setCoords(dest);
				p->increment();
				theGrid[r][c] = p;
				break;
			case 'P':
				p = new Pawn(WHITE);
				p->setCoords(dest);
				p->increment();
				theGrid[r][c] = p;
				break;	
			case 'k':
				p = new King(BLACK);
				p->setCoords(dest);
				p->increment();
				theGrid[r][c] = p;
				break;
			case 'K':
				p = new King(WHITE);
				p->setCoords(dest);
				p->increment();
				theGrid[r][c] = p;
				break;	
			case 'q':
				p = new Queen(BLACK);
				p->setCoords(dest);
				p->increment();
				theGrid[r][c] = p;
				break;
			case 'Q':
				p = new Queen(WHITE);
				p->setCoords(dest);
				p->increment();
				theGrid[r][c] = p;
				break;
			case 'b':
				p = new Bishop(BLACK);
				p->setCoords(dest);
				p->increment();
				theGrid[r][c] = p;
				break;
			case 'B':
				p = new Bishop(WHITE);
				p->setCoords(dest);
				p->increment();
				theGrid[r][c] = p;
				break;
			case 'n':
				p = new Knight(BLACK);
				p->setCoords(dest);
				p->increment();
				theGrid[r][c] = p;
				break;
			case 'N':
				p = new Knight(WHITE);
				p->setCoords(dest);
				p->increment();
				theGrid[r][c] = p;
				break;
			case 'r':
				p = new Rook(BLACK);
				p->setCoords(dest);
				p->increment();
				theGrid[r][c] = p;
				break;
			case 'R':
				p = new Rook(WHITE);
				p->setCoords(dest);
				p->increment();
				theGrid[r][c] = p;
				break;							
		}
		td->notifyDisplay(p, dest);
		gd->notifyDisplay(p, dest);
	}
}

void Grid::removePiece(const string &dest){
	if(validPos(dest)){
		int r = dest[1] - '1';
		int c = dest[0] - 'a';
		delete theGrid[r][c];
		theGrid[r][c] = nullptr; 
		td->notifyDisplay(dest);
		gd->notifyDisplay(dest);
	}
}

void Grid::initEmpty() {
	for (int r = 0 ; r < 8 ; r++) {
			vector<Piece *> Col;
			theGrid.push_back(Col);
		for (int c = 0 ; c < 8 ; c++) {
			Piece *p = nullptr;
			theGrid.at(r).push_back(p);
		}
	}
}

void Grid::init(Xwindow& xw) {
	clearGrid();
	td = new TextDisplay();
	gd = new GraphicDisplay(xw);
	gridSize = 8;
	initEmpty();

	// filling the grid with Pieces	if its not a custom setup
	if (!isCustom) {
		for (int r = 0 ; r < gridSize ; ++r) {
			for (int c = 0 ; c < gridSize ; ++c) {
				if (r == 0) {									// row 1
					if (c == 0 || c == gridSize - 1) {			
						string pos = getString(r, c);
						addPiece('R', pos);							
					}
					else if (c == 1 || c == gridSize - 2) {		
						string pos = getString(r, c);
						addPiece('N', pos);
					} 
					else if (c == 2 || c == gridSize - 3) {		
						string pos = getString(r, c);
						addPiece('B', pos);	
					}
					else if (c == 3) {
						string pos = getString(r, c);
						addPiece('Q', pos);
					}
					else if (c == 4) {
						string pos = getString(r, c);
						addPiece('K', pos);
					}
				}
				else if (r == 1) {								// row 2
					string pos = getString(r, c);
					addPiece('P', pos);
				}
				else if (r == gridSize - 2) {					// row 7
					string pos = getString(r, c);
					addPiece('p', pos);	
				}
				else if (r == gridSize - 1) {					// row 8
					if (c == 0 || c == gridSize - 1) {			
						string pos = getString(r, c);
						addPiece('r', pos);
					}
					else if (c == 1 || c == gridSize - 2) {		
						string pos = getString(r, c);
						addPiece('n', pos);
					} 
					else if (c == 2 || c == gridSize - 3) {
						string pos = getString(r, c);
						addPiece('b', pos);
					}
					else if (c == 3) {
						string pos = getString(r, c);
						addPiece('q', pos);
					}
					else if (c == 4) {						
						string pos = getString(r, c);
						addPiece('k', pos);		
					}
				}
			}
		}
	}
}
	

ostream &operator<<(ostream &out, const Grid &g) {
  	out << *(g.td);
  	return out;
}

void Grid::changePlayer() {
	if (player == WHITE) {
		player = BLACK;
	}
	else {
		player = WHITE;
	}
}

string Grid::getKingPos(const int &player) {
	for (int r = 0 ; r < gridSize ; r++) {
		for (int c = 0 ; c < gridSize ; c++) {
			string pos = getString(r, c);
			if (!pieceExist(pos)) continue;
			Piece *d = getPiece(pos);
			if ((player == d->getColour()) && (d->getType() == 'K' || d->getType() == 'k')) {
				return d->getCoords();
			}
		}
	}
}

bool Grid::checkConditions() {
	int blackKingCount = 0;
	int whiteKingCount = 0;
	for (int r = 0 ; r < gridSize ; r++) {
		for (int c = 0 ; c < gridSize ; c++) {
			string pos = getString(r, c);
			if (pieceExist(pos)) {
				Piece *p = getPiece(pos);
				if ((r == 0 || r == 7) && (p->getType() == 'p' || p->getType() == 'P')) return false; 		// pawn at either end
				if (p->getType() == 'K') whiteKingCount++;
				if (p->getType() == 'k') blackKingCount++;
 			}
		}
	}
	if (!(blackKingCount == 1 && whiteKingCount == 1)) return false;		// exactly one king of each colour
	if (checkCheck(WHITE)) return false;			// white king under check
	if (checkCheck(BLACK)) return false;			// black king under check
	return true;
}



Piece* Grid::getPiece(const string &position) {
	int r = position[1] - '1';
	int c = position[0] - 'a';

	return theGrid[r][c];
}



bool Grid::pieceExist(const string& str) {
	int r = str[1] - '1';
	int c = str[0] - 'a';

	if (!(theGrid[r][c] == nullptr)) {
		return true;
	}
	return false;
}

bool Grid::checkObstruct(const string& initial, const string& dest){
  	Piece* p = getPiece(initial);
  	if (p->getType() == 'N' || p->getType() == 'n') return false;		// doesn check for knight since it can jump over
  	if(p->getType() == 'P' || p->getType() == 'p'){
  		if(initial[0] - dest[0] == 0){
  		if(pieceExist(dest)) return true;
  		}
  	}
  	string in = initial;
  	int x = dest[0] - initial[0];
  	int y = dest[1] - initial[1];
  	// finding the direction vector
  	int xpos = x/max(abs(x), abs(y));
  	int ypos = y/max(abs(x), abs(y));
  	in[0] += xpos;
  	in[1] += ypos;
  	while(!(in == dest)){
    	if(pieceExist(in)) return true;
    	in[0] += xpos;
    	in[1] += ypos;
  	}
  	return false;
}

bool Grid::move(){
	if(!(comp1 == nullptr) && comp1->getColour() == player){
		comp1->move();
	}
	else if(!(comp2 == nullptr) && comp2->getColour() == player){
		comp2->move();
	}
	return true;
}

bool Grid::canMove(const string &initial, const string & dest) {
 	if (!pieceExist(initial)) return false;
	Piece *p = getPiece(initial);
  	if (pieceExist(dest) && isFriend(initial, dest)) return false;
 	 if (!p->isLegal(dest)) return false;
  	if (p->getType() == 'p' || p->getType() == 'P'){
  		if(initial[0] - dest[0] == 1 || initial[0] - dest[0] == -1){
  			if(!pieceExist(dest)) return false;
  		}
  	}
  
  	if (checkObstruct(initial, dest)) return false;
  
  	if (entailsCheck(initial, dest)) return false;
  	return true;
}


bool Grid::move(const string& initial, const string& dest, const char& type) {
	if(!(validPos(initial) && validPos(dest))) return false;
	if(!pieceExist(initial)) return false;
	if(!validColour(initial, player)) return false;

	// if its a castling move
	if(initial == "e1" || initial == "e8"){
		if(dest[0] - initial[0] == 2 || dest[0] - initial[0] == -2){
			return castling(initial, dest);
		}
	}
  	int ir = initial[1] - '1';
  	int ic = initial[0] - 'a';

  	int fr = dest[1] - '1';
  	int fc = dest[0] - 'a';

  	// if its an enpassant move
  	if ((enPossible == true)
  		&&
  		(theGrid[ir][ic]->getType() == 'p' || theGrid[ir][ic]->getType() == 'P')
  		&&
  		(theGrid[ir][ic]->isLegal(dest))
  		&&
  		(dest == enPassantPos)) return enPassant(initial, dest);

  	if (!canMove(initial, dest)) return false;
  

  	// if its a promoting move
  	if(theGrid[ir][ic]->getType() == 'P' || theGrid[ir][ic]->getType() == 'p'){
  		if(player == WHITE && initial[1] == '7' && dest[1] == '8') return promote(initial, dest, type);
  		else if(player == BLACK && initial[1] == '2' && dest[1] == '1') return promote(initial, dest, type);
  	}


  	// normal move
  	td->notifyDisplay(dest);
  	gd->notifyDisplay(dest);
  	Piece* p = theGrid[fr][fc];
  	removed.push_back(p);

	

  	theGrid[fr][fc] = theGrid[ir][ic];
  	theGrid[ir][ic] = nullptr;
  	theGrid[fr][fc]->setCoords(dest);
  	theGrid[fr][fc]->increment();
  	theGrid[fr][fc]->setHasMoved(true);
  
  	notify(initial, dest);
  
  	makeHistory(initial, dest);
  	changePlayer();
  	// checks if the board is won
  	if(checkCheck(player)){
  		check = true;
  		if(player == WHITE) whiteCheckedBefore = true;
  		else if(player == BLACK) blackCheckedBefore = true;
  		win(player);
  	}
  	else {	// checks for stalemate
  		check = false;
  		stalemate(player);
  		if (staleMate) {
  			whiteScore += 0.5;
  			blackScore += 0.5;
  		}
  	}

  	if (enPossible) {
  		enPossible = false; 
  		enPassantPos = "  ";
 	}

  	if ((ir == 6 || ir == 1) 
  		&& 
  		(fr == 4 || fr == 3)
  		&& 
  		(theGrid[fr][fc]->getType() == 'p' || theGrid[fr][fc]->getType() == 'P')) {
  			enPossible = true;
  			if (theGrid[fr][fc]->getType() == 'p') {
  				int row = fr + 1;
  				int col = fc;
  				enPassantPos = getString(row, col);
  			} else {
  				int row = fr - 1;
  				int col = fc;
  				enPassantPos = getString(row, col);
  			}
  	}
  
  	return true;
}


string Grid::getString(int r, int c) {
	string a = "  ";
	a[0] = c + 'a';
	a[1] = r + '1';

	return a;
}

int Grid::oppColour(const int& colour){
	if (colour == WHITE) {
		return BLACK;
	}
	else {
		return WHITE;
	}
}

bool Grid::checkCheck(const int& player) {
	string kingPos = getKingPos(player);
	int otherColour = oppColour(player);
	for (int r = 0; r < gridSize ; ++r) {
		for (int c = 0 ; c < gridSize ; ++c) {
			string pos = getString(r, c);
			if (pieceExist(pos) 
				&& 
				theGrid[r][c]->getColour() == otherColour
				&&
				theGrid[r][c]->isLegal(kingPos)
				&&
				!checkObstruct(pos, kingPos)) {
				return true;
			}
		}
	}
	return false;
}


bool Grid::entailsCheck(const string &initial, const string &dest) {
	int ir = initial[1] - '1';
  	int ic = initial[0] - 'a';

 	int fr = dest[1] - '1';
  	int fc = dest[0] - 'a';

  	Piece *temp = theGrid[fr][fc];

  	theGrid[fr][fc] = theGrid[ir][ic];
  	theGrid[fr][fc]->setCoords(dest);
  	theGrid[ir][ic] = nullptr;

  	if (checkCheck(theGrid[fr][fc]->getColour())) {
  		theGrid[ir][ic] = theGrid[fr][fc];
  		theGrid[ir][ic]->setCoords(initial);
  		theGrid[fr][fc] = temp;
  		temp = nullptr;
  		return true;
  	}
  	theGrid[ir][ic] = theGrid[fr][fc];
  	theGrid[ir][ic]->setCoords(initial);
  	theGrid[fr][fc] = temp;
  	temp = nullptr;
  	return false;
}

void Grid::notify(const string &initial,const string &dest) {
 	Piece *p = getPiece(dest);
 	td->notifyDisplay(initial, dest, p);
 	gd->notifyDisplay(initial, dest, p);
}




bool Grid::isFriend(const string& initial, const string& dest) {
  	Piece *p = getPiece(initial);
  	Piece *q = getPiece(dest);

  	return (p->getColour() == q->getColour());
}

bool Grid::validColour(const string& initial, const int& colour) {
	Piece *p = getPiece(initial);
	if (p->getColour() == colour) return true;
	return false;
}

void Grid::stalemate(const int& colour) {			// checks if there is any valid move of colour pieces
 	staleMate = true;
  	for (int r = 0; r < gridSize; r++) {
    	for (int c = 0; c < gridSize; c++) { 
      		if (theGrid[r][c] == nullptr) continue;
      		if (theGrid[r][c]->getColour() == colour) {
        		string position = getString(r,c);
        		std::vector<string> str = theGrid[r][c]->getLegalMoves();
        		for (int i =0 ; i < str.size() ; i++) {
           			if (canMove(position,str[i])) staleMate = false;
        		}
      		}
    	}
  	}
}

void Grid::win(const int& colour) {
 	stalemate(colour);
 	if (staleMate) {
 		checkMate = true;
 		changePlayer();
 		if(player == WHITE) whiteScore += 1;
 		else blackScore += 1;
	}
}


bool Grid::promote(const string& initial, const string& dest, const char& type){
	int ixpos = initial[0] - 'a';
	int iypos = initial[1] - '1';
	if(theGrid[iypos][ixpos]->getColour() == WHITE){
		if(!(dest[1] == '8' && (type == 'Q' || type == 'R' || type == 'N' || type == 'B'))) return false;
	}
	else{
		if(!(dest[1] == '1' && (type == 'q' || type == 'r' || type == 'n' || type == 'b'))) return false;
	}

	int ir = initial[1] - '1';
  	int ic = initial[0] - 'a';

 	int fr = dest[1] - '1';
  	int fc = dest[0] - 'a';

	Piece* oppPiece = theGrid[fr][fc];
	removed.push_back(oppPiece);
	theGrid[fr][fc] = nullptr;

	Piece* myPiece = theGrid[ir][ic];
	removed.push_back(myPiece);	
	theGrid[ir][ic] = nullptr;

	td->notifyDisplay(dest);
	gd->notifyDisplay(dest);
	
	td->notifyDisplay(initial);
	gd->notifyDisplay(initial);

	addPiece(type, dest);
	makeHistory(initial, dest);
	changePlayer();
	if(checkCheck(player)){
		check = true;
		win(player);
		if(checkMate){
			if (player == WHITE) {
				blackScore++;
			} 
			else {
				whiteScore++;
			}
		}  
  	}
  	else {
  		check = false;
  		stalemate(player); 
  		if (staleMate){
  			whiteScore += 0.5;
  			blackScore += 0.5;
  		}
  	}
  	if (enPossible) {
  		enPossible = false; 
  		enPassantPos = "  ";
  	}
	return true;
}

bool Grid::castling(const string &initial, const string &dest) {
	if (pieceExist(initial)){
		if (!(getPiece(initial)->getType() == 'k' || getPiece(initial)->getType() == 'K')) return false;
	}
	else return false;
	int dir = dest[0] - initial[0];
	
	string rookPos = "  ";
	if (dir > 0) {
		rookPos[0] = 'h';
		rookPos[1] = initial[1];
	}
	else {
		rookPos[0] = 'a';
		rookPos[1] = initial[1];
	}
	if (pieceExist(rookPos)) {
		if (!(getPiece(rookPos)->getType() == 'r' || getPiece(rookPos)->getType() == 'R')) return false;
	}
	else return false;
	if(!castlingCondition(initial, dir)) return false;
	int r = dest[1] - '1';

	if (dir > 0) {								// castling on the right side
		string rookPos1 = getString(r, 5);
		theGrid[r][6] = theGrid[r][4];
		theGrid[r][6]->setCoords(dest);
		theGrid[r][6]->increment();
		theGrid[r][5] = theGrid[r][7];
		theGrid[r][5]->setCoords(rookPos1);
		theGrid[r][5]->increment();
		theGrid[r][4] = nullptr;
		theGrid[r][7] = nullptr;
		
		notify(initial, dest);
		notify(rookPos, rookPos1);
	}
	else {										// castling on the left side
		string rookPos2 = getString(r, 3);
		theGrid[r][2] = theGrid[r][4];
		theGrid[r][2]->setCoords(dest);
		theGrid[r][2]->increment();
		theGrid[r][3] = theGrid[r][0];
		theGrid[r][3]->setCoords(rookPos2);
		theGrid[r][3]->increment();
		theGrid[r][4] = nullptr;
		theGrid[r][0] = nullptr;
		notify(initial, dest);
		notify(rookPos, rookPos2);
	}
	
	Piece *p = nullptr;
	removed.push_back(p);

	makeHistory(initial, dest);
	changePlayer();
	if(checkCheck(player)){
		check = true;
  		if(player == WHITE) whiteCheckedBefore = true;
  		else if(player == BLACK) blackCheckedBefore = true;
  		win(player); 
  	}
  	else {
  		check = false;
  		stalemate(player);
  		if (staleMate) {
  			whiteScore += 0.5;
  			blackScore += 0.5;
  		}
  	}
  	if (enPossible) {
  		enPossible = false; 
  		enPassantPos = "  ";
  	}
	return true;
}

bool Grid::CheckedBefore(const int& player){
	if(player == WHITE) return whiteCheckedBefore;
	return blackCheckedBefore;
}

bool Grid::castlingCondition(const string &initial,const int& dir) {
	Piece *p = getPiece(initial);
	if (!(p->getHasMoved())
		&&
		!(CheckedBefore(player))) {
		char r = initial[1];
		string pos1 = "  ";
		string pos2 = "  ";
		string pos3 = "  ";
		if (dir > 0) {
			pos1[0] = 'f';
			pos1[1] = r;
			pos2[0] = 'g';
			pos2[1] = r;
			pos3[0] = 'h';
			pos3[1] = r;
		}
		else {
			pos1[0] = 'd';
			pos1[1] = r;
			pos2[0] = 'c';
			pos2[1] = r;
			pos3[0] = 'a';
			pos3[1] = r;
		}
		
		Piece *m = getPiece(pos3);
		if (!pieceExist(pos1) 
			&& 
			!pieceExist(pos2)
			&&
			!entailsCheck(initial, pos1)
			&&
			!entailsCheck(initial, pos2)
			&&
			!(m->getHasMoved())) {
			return true;
		}
	}
	return false;
}



Piece* Grid::assumeMove(const string& initial, const string& dest) {
	int ir = initial[1] - '1';
  	int ic = initial[0] - 'a';

 	int fr = dest[1] - '1';
  	int fc = dest[0] - 'a';

  	Piece *temp = theGrid[fr][fc];

  	theGrid[fr][fc] = theGrid[ir][ic];
  	theGrid[fr][fc]->setCoords(dest);
  	theGrid[fr][fc]->increment();
  	theGrid[ir][ic] = nullptr;
  	return temp;
}

void Grid::undoAssume(const string& initial, const string& dest , Piece* captured) {
	int ir = initial[1] - '1';
  	int ic = initial[0] - 'a';

 	int fr = dest[1] - '1';
  	int fc = dest[0] - 'a';

  	theGrid[ir][ic] = theGrid[fr][fc];
  	theGrid[ir][ic]->setCoords(initial);
  	theGrid[ir][ic]->increment();
  	theGrid[fr][fc] = captured;
  	if (theGrid[fr][fc]) {
  		theGrid[fr][fc]->setCoords(dest);
  		theGrid[fr][fc]->increment();
  	}
 	captured = nullptr;
}

vector<string> Grid::returnPieces(const int& colour) {
	vector<string> p;
	for (int r = 0 ; r < gridSize ; r++) {
		for (int c = 0 ; c < gridSize ; c++) {
			string piece = getString(r, c);
			if (pieceExist(piece)) {
				if (theGrid[r][c]->getColour() == colour){
					p.push_back(piece);
				}
			}
		}
	}
	return p;
} 

bool Grid::getStaleMate(){return staleMate;}

bool Grid::getCheck(){ return check; }

void Grid::updateScore() {
	if (player == WHITE) {
		blackScore++;
	} else {
		whiteScore++;
	}
}

bool Grid::validPos(const string& pos){
	return (pos.length() == 2 && 'a' <= pos[0] && pos[0] <= 'h' && '1' <= pos[1] && pos[1] <= '8');
}

double Grid::getWhiteScore(){return whiteScore;}

double Grid::getBlackScore(){return blackScore;}

void Grid::makeHistory(const string& initial, const string& dest) {
	numMoves++;
  	string histNum = to_string(numMoves);
  	string histResult = histNum + " " + initial + " " + dest;
  	history.push_back(histResult);
}

vector<string> Grid::getHistory(){return history;}

bool Grid::undo(){
	if (numMoves == 0) return false;
	numMoves--;

	string movement = history.back();
	history.pop_back();
	string initial = movement.substr(5,2);
    string dest = movement.substr(2,2);

    int ir = initial[1] - '1';
  	int ic = initial[0] - 'a';

 	int fr = dest[1] - '1';
  	int fc = dest[0] - 'a';

  	Piece* lastPiece = removed.back();
  	removed.pop_back();

    
    //undoes castling
	if(initial == "g1" || initial == "g8" || initial == "c1" || initial == "c8"){
		if((dest[0] - initial[0] == 2 || dest[0] - initial[0] == -2) && (getPiece(initial)->getType() == 'k'  || getPiece(initial)->getType() == 'K')){
			int r = dest[1] - '1';
			if (initial == "g1" || initial == "g8") {
				theGrid[r][4] = theGrid[r][6];
				string kingPosition = getString(r, 4);
				theGrid[r][4]->setCoords(kingPosition);
				theGrid[r][4]->increment();
				theGrid[r][6] = nullptr;

				theGrid[r][7] = theGrid[r][5];
				string rookFinal = getString(r, 7);
				theGrid[r][7]->setCoords(rookFinal);
				theGrid[r][7]->increment();
				theGrid[r][5] = nullptr;

				string rookInitial = getString(r, 5);

				notify(initial, dest);
				notify(rookInitial, rookFinal);
				changePlayer();
				if (checkCheck(theGrid[fr][fc]->getColour())) check = true;
				else check = false;
				return true;
			}
			else if (initial == "c1" || initial == "c8") {
				theGrid[r][4] = theGrid[r][2];
				string kingPosition = getString(r, 4);
				theGrid[r][4]->setCoords(kingPosition);
				theGrid[r][4]->increment();
				theGrid[r][2] = nullptr;

				theGrid[r][0] = theGrid[r][3];
				string rookFinal = getString(r, 0);
				theGrid[r][0]->setCoords(rookFinal);
				theGrid[r][0]->increment();
				theGrid[r][3] = nullptr;

				string rookInitial = getString(r, 3);

				notify(initial, dest);
				notify(rookInitial, rookFinal);	
				changePlayer();
				if (checkCheck(theGrid[fr][fc]->getColour())) check = true;
				else check = false;
				return true;
			}
		}
	}

	//undoes promotion
	if (lastPiece != nullptr) {
		if ((initial[1] == '8' || initial[1] == '1') 
 			&& (dest[1] == '7' || dest[1] == '2') 
 			&& (lastPiece->getType() == 'P' || lastPiece->getType() == 'p')) {
 			
 			removePiece(initial);

 			Piece* secondLastPiece = removed.back();
 			removed.pop_back();

 			theGrid[fr][fc] = lastPiece;
 			theGrid[fr][fc]->setCoords(dest);
 			theGrid[fr][fc]->increment();
 			lastPiece = nullptr;

 			theGrid[ir][ic] = secondLastPiece;
 			if (theGrid[ir][ic] != nullptr){
 				theGrid[ir][ic]->setCoords(initial);
 				theGrid[ir][ic]->increment();
 			}
 			secondLastPiece = nullptr;

 			td->notifyDisplay(theGrid[fr][fc], dest);
 			gd->notifyDisplay(theGrid[fr][fc], dest);

 			if (theGrid[ir][ic] != nullptr) {
 				td->notifyDisplay(theGrid[ir][ic], initial);
 				gd->notifyDisplay(theGrid[ir][ic], initial);
 			} else {
 				td->notifyDisplay(initial);
 				gd->notifyDisplay(initial);
 			}
 			changePlayer();
 			if (checkCheck(theGrid[fr][fc]->getColour())) check = true;
			else check = false;
 			return true;
 		}
	}
	// undoes enpassant
	if (lastPiece) {
		string posn = lastPiece->getCoords();
		if (!(posn == initial)) {
			int posr = posn[1] - '1';
			int posc = posn[0] - 'a';
			theGrid[posr][posc] = lastPiece;
			lastPiece = nullptr;

			theGrid[fr][fc] = theGrid[ir][ic];
			theGrid[fr][fc]->setCoords(dest);
			theGrid[fr][fc]->increment();
			theGrid[ir][ic] = nullptr;

			td->notifyDisplay(initial, dest, theGrid[fr][fc]);
			gd->notifyDisplay(initial, dest, theGrid[fr][fc]);

			td->notifyDisplay(theGrid[posr][posc], posn);
			gd->notifyDisplay(theGrid[posr][posc], posn);
			
			enPossible = true;
			enPassantPos = initial;

			changePlayer();
			if (checkCheck(theGrid[fr][fc]->getColour())) check = true;
			else check = false;
			return true;
		}
	}
  	// undoes normal moves
 	theGrid[fr][fc] = theGrid[ir][ic];
 	theGrid[fr][fc]->setCoords(dest);
 	theGrid[fr][fc]->increment();
 	
 	theGrid[ir][ic] = lastPiece;
 	if (theGrid[ir][ic] != nullptr) {
 		theGrid[ir][ic]->setCoords(initial);
 		theGrid[ir][ic]->increment();
 	}
 	lastPiece = nullptr;

 	notify(initial, dest);
 	if (theGrid[ir][ic] != nullptr) {
 		td->notifyDisplay(theGrid[ir][ic], initial);
 		gd->notifyDisplay(theGrid[ir][ic], initial);
 	} else {
 		td->notifyDisplay(initial);
 		gd->notifyDisplay(initial);
 	}
  	changePlayer();
  	if (checkCheck(theGrid[fr][fc]->getColour())) check = true;
		else check = false;
  	return true;
}


bool Grid::enPassant(const string& initial, const string& dest) {
	
	int ir = initial[1] - '1';
  	int ic = initial[0] - 'a';

 	int fr = dest[1] - '1';
  	int fc = dest[0] - 'a';

	int dir = dest[1] - initial[1];

	int actualRow = fr;
	
	if (dir > 0) {
		actualRow--;
	} else {
		actualRow++;
	}
	Piece* p = theGrid[actualRow][fc];	
	removed.push_back(p);
	theGrid[actualRow][fc] = nullptr;

	theGrid[fr][fc] = theGrid[ir][ic];
	theGrid[fr][fc]->setCoords(dest);
	theGrid[fr][fc]->increment();
	theGrid[ir][ic] = nullptr;
	
	makeHistory(initial, dest);
	changePlayer();

	enPossible = false;
	enPassantPos = "  ";
	
	string pos = getString(actualRow, fc);

	td->notifyDisplay(initial, dest, theGrid[fr][fc]);
	gd->notifyDisplay(initial, dest, theGrid[fr][fc]);

	td->notifyDisplay(pos);
	gd->notifyDisplay(pos);
	return true;	
}
