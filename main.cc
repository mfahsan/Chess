#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "grid.h"
#include "window.h"

using namespace std;
bool load = false;

void help(){			//lists all the valid commands
	cout << "List of commands: " << endl;
  cout << "1) game type type - starts a new game, AI levels range from 1 to 4" << endl;
  cout << "	a) move inital final - move from position initial to postion final" << endl;
  cout << "	b) move inital final type - promote pawn" << endl;
  cout << "	c) move - move computer player" << endl;
  cout << "	d) resign - concede the game" << endl;
  cout << "	e) undo" << endl;
  cout << "	f) history - view list of moves played" << endl;
 	cout << "2) setup - enter setup" << endl; 
 	cout << "	a) + piece position - add piece at position" << endl;
 	cout << "	b) - position - remove piece at position" << endl;
 	cout << "	c) = colour - set the next player of colour" << endl;
 	cout << "	d) done - exit setup" << endl;
 	cout << "3) load - load new game from a file" << endl;
}

void commandProcess(std::istream* iss, Grid& grid, Xwindow& xw){		//Process entered command, iss is the type of istream
		
  	string input;

  	while(true){
  	  cout << "Enter Command: ";
  		*iss >> input;
  		if (iss->eof()) break;
  		if(input == "game"){																					//game command
        if(!grid.getIsCustom()) grid.init(xw);
        string type1 = "";
        string type2 = "";
        while(type1 == "" || type2 == ""){
  				*iss >> type1;																						//get player1 fromm input
  				if (type1 == "human") {
  					grid.setCompLevel1(0);
  				}
  				else if (type1.substr(0,8) == "computer" && !(type1 == "human")) {
  					int difficulty1 = type1[8] - '0';
  					if(difficulty1 >= 1 && difficulty1 <= 4) grid.setCompLevel1(difficulty1);
  					else {
  						cout << "Wrong Input" << endl;
  			 			type1 = "";
  					}
  				}
  				else{
  			 		cout << "Wrong Input" << endl;
  			 		type1 = "";
  				}
  				*iss >> type2;																						//get player2 from input
  				if (type2 == "human") {
  					grid.setCompLevel2(0);
  				}
  				else if (type2.substr(0,8) == "computer" && !(type2 == "human")) {
  					int difficulty2 = type2[8] - '0';
  					if(difficulty2 >= 1 && difficulty2 <= 4) grid.setCompLevel2(difficulty2);
  					else {
  						cout << "Wrong Input" << endl;
  			 			type1 = "";
  					}
  				}
  				else{
  			 		cout << "Wrong Input" << endl;
  			 		type2 = "";
  				}
  			}
  			cout << grid;
  			while(true){
  				cout << "Player turn: " << grid.getPlayer() << endl;
          string input2;
          getline(*iss, input2);
          string word;
          stringstream count{input2};
          stringstream actual{input2};
          int num = 0;
          while (count >> word) num++;
          string text;
          string initial;
          string dest;
          char type;
          if(input2 == "help"){																				//help command
          	help();
          	continue;
          }
          if (num == 1) {
            actual >> text;
            if (text == "resign") {																		//resign command
              grid.updateScore();
              string plr = grid.getPlayer();
              if (plr == "White") {
              	cout << "Black wins!" << endl;
              } else {
              	cout << "White wins!" << endl;
              }
              if(grid.getIsCustom()) grid.setIsCustom(false);
              break;
            } else if (text == "move") {															//move command
                grid.move();
                cout << grid;
            } else if (text == "history") {														//history command
              vector<string> hist = grid.getHistory();
              for (int i = 0 ; i < hist.size() ; i++) {
                cout << hist[i] << endl;
              }
            } else if (text == "undo") {															//undo command
              if (grid.undo()){
                cout << grid; 
              } else {
                cout << "Cannot undo" << endl;
              }
            } else {
            	cout << "Invalid input" << endl;
              continue;
            }
          } else if (num == 3) {
            actual >> text;
            actual >> initial;
            actual >> dest;
            if(grid.move(initial, dest)){
              cout << grid;
            }
            else cout << "Invalid move!" << endl;
          } else if (num == 4) {
            actual >> text;
            actual >> initial;
            actual >> dest;
            actual >> type;
            if(grid.move(initial, dest, type)){															//promotion
              cout << grid;
            }
            else cout << "Invalid move!" << endl; 
          } else {
            continue;
          }
  				if (grid.getCheckMate()) {																												//check for Checkmate
  					if(grid.getIsCustom()) grid.setIsCustom(false);
  					cout << "Checkmate! " << grid.getPlayer() << " wins!" << endl;
  					if(grid.getIsCustom()) grid.setIsCustom(false);
  					break;
  				}
  				else if(grid.getCheck()) cout << grid.getPlayer() << " is in check." << endl;			//check for Check
          else if (grid.getStaleMate()) {																										//check for Stalemate
          	if(grid.getIsCustom()) grid.setIsCustom(false);
          	cout << "Stalemate!" << endl;
          	if(grid.getIsCustom()) grid.setIsCustom(false);
            break;
          }
  			}
  		}
  		else if (input == "setup") {																							//Enter setup mode
  			grid.setIsCustom(true);
  			grid.init(xw);
  			cout << grid;
  			while (true) {
  				string command;
  				*iss >> command;
  				char t;
  				string pos;
  				if (command == "done") {																							//exit command
  					if(grid.checkConditions()) {																				//check if setup conditions are met
  							cout << "Setup complete" << endl;
            			break;
          			}
          			cout << "Setup exit conditions not met!" << endl;								//setup conditions
          			cout << "1) There must be one king of each colour" << endl;			
          			cout << "2) Neither of the kings must be in check" << endl;
          			cout << "3) There must be no pawns on row 1 and 8" << endl;
          			continue;
  				}
  				else if(command == "help"){																						//help command
  					help();
  				}
    			else if(command ==	"+"){ 																						//add piece t at pos
  					*iss >> t;	
  					*iss >> pos;
  					grid.removePiece(pos);
  					grid.addPiece(t, pos);
  					cout << grid;
  				}
  				else if(command == "-"){																							//remove piece at pos
  					*iss >> pos;
  					grid.removePiece(pos);
  					cout << grid;
  				}
  				else if(command == "="){																							//set next player
  					string colour;
  					*iss >> colour;
  					if (colour == "white") {
  						grid.setPlayer(WHITE);
  					}
  					else {
  						grid.setPlayer(BLACK);
  					}
  				}	
  			}
  		}
  		else if(input == "load"){																									//load game from a file
  			load = false;
  			break;
  		}
  		else if(input == "help"){																									//help command
  			help();
  		}
  	}
}

int main(){
		Grid grid;
  	Xwindow xw;
		istream* in;
		cin.exceptions(ios::failbit|ios::eofbit);
 		char s;
 		string fileName = "";
  
  	cout << "Welcome to Chess Master 5";
  	for(int i = 0; i < 10; i++){
    	cout << "0";
  	}
  	cout << endl;
  	while(!load){
  		while(true){
  			cout << "Load a game from a file [Y/N]?: ";
  			cin >> s;
  			if(s == 'Y' || s == 'y'){
  				cout << "Enter file to load: ";
  				cin >> fileName;
  				try{
						ifstream file{fileName};
						file.exceptions(ios::failbit | ios::eofbit);
					}
					catch(ifstream::failure &){																//check if file exists
						cout << "File does not exist" << endl;
						continue;
					}
					in = new ifstream(fileName.c_str());											//set in to ifstream
					load = true;
					cout << "Load Complete" << endl;
  				break;
  			}
  			else if(s == 'N' || s == 'n'){
  			 	load = true;
  			 	break;
  			}
  			else{
  				cout << "Invalid command" << endl;
  				continue;
  			}
  		}
  		try{
  			if(s == 'Y' || s == 'y'){
  				commandProcess(in, grid, xw);															//call commandProcess with ifstream
  				delete in;
  			}
  			in = &cin;																									//set in to cin
  			commandProcess(in, grid, xw);																//call commandProcess with cin
  		}
  		catch (ios::failure) {}
  	}
  	cout << "Final Score:" << endl;																	//Print final score
  	cout << "White: " << grid.getWhiteScore() << endl;
  	cout << "Black: " << grid.getBlackScore() << endl;
}
