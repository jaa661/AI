/////////////////////////////
//
// Jacob Abbott
// AI final project
// Camelot Game
//
////////////////////////////



#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdio>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std;
enum GameState {PLAY, DRAW, BLACK_WIN, WHITE_WIN};
enum Type {EMPTY, INVALID, BLACK, WHITE};
enum Moves {PLAIN, CANTER, CAPTURE, DISALLOWED};
enum Direction {N, NE, E, SE, S, SW, W, NW};
int gameState = PLAY;
int playerLeft = 6;
int aiLeft = 6;
///////////////////define necessary structures
struct Space{ 

	Type type;
	char display; 
	int xCoord; 
	int yCoord;
	string coords;
	int pieceNum;
	bool isCastle;
};

struct Piece{ 
 
 	Type type;
	int xCoord; 
	int yCoord;
	int pieceNum;
	bool alive;
};

struct gameBoard{ 
 
 	vector<vector<Space> > board;
 	vector<Piece> pieces;
	vector<Piece> aipieces;
	int whitePieces; 
	int blackPieces;
	Type turn;
};

struct mov{
	int x;
	int y;
};
//////////////////////initializing, setup, and display funtions
void displayBoard(vector<vector<Space> >& space){ 
	cout << '\n'
		<< "              _______" << '\n'
		<< "             | " << space[4][1].display<< " | " << space[5][1].display << " | " << '\n'
		<< "          ___|___|___|___" << '\n'
		<< "         | " << space[3][2].display << " | " << space[4][2].display << " | " << space[5][2].display << " | " << space[6][2].display << " | " << '\n'
		<< "      ___|___|___|___|___|___" << '\n'
		<< "     | " << space[2][3].display << " | " << space[3][3].display << " | " << space[4][3].display << " | " << space[5][3].display << " | " << space[6][3].display << " | " << space[7][3].display << " | " << '\n'
		<< "  ___|___|___|___|___|___|___|___" << '\n'
		<< " | " << space[1][4].display << " | " << space[2][4].display << " | " << space[3][4].display << " | " << space[4][4].display << " | " << space[5][4].display << " | " << space[6][4].display << " | " << space[7][4].display << " | " << space[8][4].display << " | " << '\n'
		<< " |___|___|___|___|___|___|___|___|" << '\n'
		<< " | " << space[1][5].display << " | " << space[2][5].display << " | " << space[3][5].display << " | " << space[4][5].display << " | " << space[5][5].display << " | " << space[6][5].display << " | " << space[7][5].display << " | " << space[8][5].display << " | " << '\n'
		<< " |___|___|___|___|___|___|___|___|" << '\n'
		<< " | " << space[1][6].display << " | " << space[2][6].display << " | " << space[3][6].display << " | " << space[4][6].display << " | " << space[5][6].display << " | " << space[6][6].display << " | " << space[7][6].display << " | " << space[8][6].display << " | " << '\n'
		<< " |___|___|___|___|___|___|___|___|" << '\n'
		<< " | " << space[1][7].display << " | " << space[2][7].display << " | " << space[3][7].display << " | " << space[4][7].display << " | " << space[5][7].display << " | " << space[6][7].display << " | " << space[7][7].display << " | " << space[8][7].display << " | " << '\n'
		<< " |___|___|___|___|___|___|___|___|" << '\n'
		<< " | " << space[1][8].display << " | " << space[2][8].display << " | " << space[3][8].display << " | " << space[4][8].display << " | " << space[5][8].display << " | " << space[6][8].display << " | " << space[7][8].display << " | " << space[8][8].display << " | " << '\n'
		<< " |___|___|___|___|___|___|___|___|" << '\n'
		<< " | " << space[1][9].display << " | " << space[2][9].display << " | " << space[3][9].display << " | " << space[4][9].display << " | " << space[5][9].display << " | " << space[6][9].display << " | " << space[7][9].display << " | " << space[8][9].display << " | " << '\n'
		<< " |___|___|___|___|___|___|___|___|" << '\n'
		<< " | " << space[1][10].display << " | " << space[2][10].display << " | " << space[3][10].display << " | " << space[4][10].display << " | " << space[5][10].display << " | " << space[6][10].display << " | " << space[7][10].display << " | " << space[8][10].display << " | " << '\n'
		<< " |___|___|___|___|___|___|___|___|" << '\n'
		<< " | " << space[1][11].display << " | " << space[2][11].display << " | " << space[3][11].display << " | " << space[4][11].display << " | " << space[5][11].display << " | " << space[6][11].display << " | " << space[7][11].display << " | " << space[8][11].display << " | " << '\n'
		<< " |___|___|___|___|___|___|___|___|" << '\n'
		<< "     | " << space[2][12].display << " | " << space[3][12].display << " | " << space[4][12].display << " | " << space[5][12].display << " | " << space[6][12].display << " | " << space[7][12].display << " | " << '\n'
		<< "     |___|___|___|___|___|___|" << '\n'
		<< "         | " << space[3][13].display << " | " << space[4][13].display << " | " << space[5][13].display << " | " << space[6][13].display << " | " << '\n'
		<< "         |___|___|___|___|" << '\n'
		<< "             | " << space[4][14].display << " | " << space[5][14].display << " | " << '\n'
		<< "             |___|___|" << '\n'
		<< '\n'
		<< '\n';
		return;
}

void initVec(vector<vector<Space> >& spaces) { //takes a vector of a vector that represents the goal and fills it as needed
	for (int i = 0; i < 10; i++){
		vector<Space> spaceRow;
		for (int j = 0; j < 16; j++){
			Space newspace;
			newspace.type = EMPTY;
			newspace.display = ' '; 
			newspace.xCoord = j; 
			newspace.yCoord = i;
			ostringstream os;
  			os << "("<<i<<", "<<j<<")";
  			string s = os.str();
			newspace.coords = s;
			newspace.pieceNum = 0;
			newspace.isCastle = false;
			spaceRow.push_back(newspace);
		}
		spaces.push_back(spaceRow);
	}
	//define castle spaces
	spaces[4][1].isCastle = true;
	spaces[5][1].isCastle = true;
	spaces[4][14].isCastle = true;
	spaces[5][14].isCastle = true;
	//define out of bounds 
	for(int q = 0; q < 10;q++)
		spaces[q][0].type = INVALID;
	for(int q = 0; q < 10;q++)
		spaces[q][15].type = INVALID;
	for(int q = 0; q < 16;q++)
		spaces[0][q].type = INVALID;
	for(int q = 0; q < 16;q++)
		spaces[9][q].type = INVALID;
	spaces[1][1].type = INVALID;
	spaces[2][1].type = INVALID;
	spaces[3][1].type = INVALID;
	spaces[6][1].type = INVALID;
	spaces[7][1].type = INVALID;
	spaces[8][1].type = INVALID;
	spaces[1][2].type = INVALID;
	spaces[2][2].type = INVALID;
	spaces[7][2].type = INVALID;
	spaces[8][2].type = INVALID;
	spaces[1][3].type = INVALID;
	spaces[8][3].type = INVALID;
	spaces[1][14].type = INVALID;
	spaces[2][14].type = INVALID;
	spaces[3][14].type = INVALID;
	spaces[6][14].type = INVALID;
	spaces[7][14].type = INVALID;
	spaces[8][14].type = INVALID;
	spaces[1][13].type = INVALID;
	spaces[2][13].type = INVALID;
	spaces[7][13].type = INVALID;
	spaces[8][13].type = INVALID;
	spaces[1][12].type = INVALID;
	spaces[8][12].type = INVALID;
	//define white pieces
	spaces[3][5].type = WHITE;
	spaces[3][5].display = '1';
	spaces[3][5].pieceNum = 1;
	spaces[4][5].type = WHITE;
	spaces[4][5].display = '2';
	spaces[4][5].pieceNum = 2;
	spaces[5][5].type = WHITE;
	spaces[5][5].display = '3';
	spaces[5][5].pieceNum = 3;
	spaces[6][5].type = WHITE;
	spaces[6][5].display = '4';
	spaces[6][5].pieceNum = 4;
	spaces[4][6].type = WHITE;
	spaces[4][6].display = '5';
	spaces[4][6].pieceNum = 5;
	spaces[5][6].type = WHITE;
	spaces[5][6].display = '6';
	spaces[5][6].pieceNum = 6;
	//define black pieces
	spaces[4][9].type = BLACK;
	spaces[4][9].display = 'B';
	spaces[4][9].pieceNum = 5;
	spaces[5][9].type = BLACK;
	spaces[5][9].display = 'B';
	spaces[5][9].pieceNum = 6;
	spaces[3][10].type = BLACK;
	spaces[3][10].display = 'B';
	spaces[3][10].pieceNum = 1;
	spaces[4][10].type = BLACK;
	spaces[4][10].display = 'B';
	spaces[4][10].pieceNum = 2;
	spaces[5][10].type = BLACK;
	spaces[5][10].display = 'B';
	spaces[5][10].pieceNum = 3;
	spaces[6][10].type = BLACK;
	spaces[6][10].display = 'B';
	spaces[6][10].pieceNum = 4;

}


void initPieces(gameBoard& BOARD){ // sets the pieces on the given board
	Piece temp;
	temp.type = WHITE;
	temp.xCoord = 3;
	temp.yCoord = 5;
	temp.pieceNum = 1;
	temp.alive = true;
	BOARD.pieces.push_back(temp);
	temp.xCoord = 4;
	temp.pieceNum = 2;
	BOARD.pieces.push_back(temp);
	temp.xCoord = 5;
	temp.yCoord = 5;
	temp.pieceNum = 3;
	BOARD.pieces.push_back(temp);
	temp.xCoord = 6;
	temp.pieceNum = 4;
	BOARD.pieces.push_back(temp);
	temp.xCoord = 4;
	temp.yCoord = 6;
	temp.pieceNum = 5;
	BOARD.pieces.push_back(temp);
	temp.xCoord = 5;
	temp.pieceNum = 6;
	BOARD.pieces.push_back(temp);
	//black BOARD.pieces
	temp.type = BLACK;
	temp.xCoord = 3;
	temp.yCoord = 10;
	temp.pieceNum = 1;
	temp.alive = true;
	BOARD.aipieces.push_back(temp);
	temp.xCoord = 4;
	temp.pieceNum = 2;
	BOARD.aipieces.push_back(temp);
	temp.xCoord = 5;
	temp.yCoord = 10;
	temp.pieceNum = 3;
	BOARD.aipieces.push_back(temp);
	temp.xCoord = 6;
	temp.pieceNum = 4;
	BOARD.aipieces.push_back(temp);
	temp.xCoord = 4;
	temp.yCoord = 9;
	temp.pieceNum = 5;
	BOARD.aipieces.push_back(temp);
	temp.xCoord = 5;
	temp.pieceNum = 6;
	BOARD.aipieces.push_back(temp);
}

int directionToInt(string d){ /// converting from text to int
	if(d == "SW")
		return 0;
	if(d == "W")
		return 1;
	if(d == "NW")
		return 2;
	if(d == "S")
		return 3;
	if(d == "N")
		return 5;
	if(d == "SE")
		return 6;
	if(d == "E")
		return 7;
	if(d == "NE")
		return 8;
	return -1;
}

bool validDirection(string d){ /// verify text
	if((d == "SW")||(d == "W")||(d == "NW")||(d == "S")||(d == "N")||(d == "SE")||(d == "E")||(d == "NE"))
		return true;
	return false;
}

mov directionToMov(string d){ // converting from text to (x,y) displacement
	mov change;
	if(d == "SW"){
		change.x = -1;
		change.y = 1;
	}
	if(d == "W"){
		change.x = -1;
		change.y = 0;
	}
	if(d == "NW"){
		change.x = -1;
		change.y = -1;
	}
	if(d == "S"){
		change.x = 0;
		change.y = 1;
	}
	if(d == "N"){
		change.x = 0;
		change.y = -1;
	}
	if(d == "SE"){
		change.x = 1;
		change.y = 1;
	}
	if(d == "E"){
		change.x = 1;
		change.y = 0;
	}
	if(d == "NE"){
		change.x = 1;
		change.y = -1;
	}
	return change;
}
//////////////////////////////////////////////////////////////////////////////////////////////utility functions
bool isValid(Piece piece, mov direction, gameBoard BOARD){
	//cout<<"checkvalid";
	if(BOARD.board[piece.xCoord+direction.x][piece.yCoord+direction.y].type == EMPTY)
		return true;
	return false;
}

bool isValidCanter(Piece piece, mov direction, gameBoard BOARD){
	if(BOARD.board[piece.xCoord+direction.x][piece.yCoord+direction.y].type == piece.type)
		if(BOARD.board[piece.xCoord+(direction.x*2)][piece.yCoord+(direction.y*2)].type == EMPTY)
			return true;
	return false;

}

void makeMove(Piece& piece, mov direction, gameBoard& BOARD){ // this assumes the move requested is valid
	//cout<<"MM";
	Space tempSpace;
	tempSpace = BOARD.board[piece.xCoord+direction.x][piece.yCoord+direction.y];
	BOARD.board[piece.xCoord+direction.x][piece.yCoord+direction.y] = BOARD.board[piece.xCoord][piece.yCoord];
	BOARD.board[piece.xCoord][piece.yCoord] = tempSpace;
	//cout<<"swap"<<BOARD.board[piece.xCoord][piece.yCoord].type<<endl;;
	piece.xCoord = piece.xCoord + direction.x;
	piece.yCoord = piece.yCoord + direction.y;
}

void makeCanterMove(Piece& piece, mov direction, gameBoard& BOARD){ // this assumes the move requested is valid
	Space tempSpace;
	direction.x = direction.x*2;
	direction.y = direction.y*2;
	tempSpace = BOARD.board[piece.xCoord+direction.x][piece.yCoord+direction.y];
	BOARD.board[piece.xCoord+direction.x][piece.yCoord+direction.y] = BOARD.board[piece.xCoord][piece.yCoord];
	BOARD.board[piece.xCoord][piece.yCoord] = tempSpace;

	piece.xCoord = piece.xCoord + direction.x;
	piece.yCoord = piece.yCoord + direction.y;
}

void makeCaptureMove(Piece& piece, mov direction, gameBoard& BOARD){ // this assumes the move requested is valid
	//capture piece
	BOARD.board[piece.xCoord+(direction.x/2)][piece.yCoord+(direction.y/2)].display = ' ';
	BOARD.board[piece.xCoord+(direction.x/2)][piece.yCoord+(direction.y/2)].type = EMPTY;
	BOARD.aipieces[BOARD.board[piece.xCoord+(direction.x/2)][piece.yCoord+(direction.y/2)].pieceNum-1].alive = false;
	if(piece.type == WHITE)
		BOARD.whitePieces--;
	if(piece.type == BLACK)
		BOARD.blackPieces--;

	//make move
	Space tempSpace;
	tempSpace = BOARD.board[piece.xCoord+direction.x][piece.yCoord+direction.y];
	BOARD.board[piece.xCoord+direction.x][piece.yCoord+direction.y] = BOARD.board[piece.xCoord][piece.yCoord];
	BOARD.board[piece.xCoord][piece.yCoord] = tempSpace;

	piece.xCoord = piece.xCoord + direction.x;
	piece.yCoord = piece.yCoord + direction.y;
}

void makeaiCaptureMove(Piece& piece, mov direction, gameBoard& BOARD){ // this assumes the move requested is valid
	//capture piece
	BOARD.board[piece.xCoord+(direction.x/2)][piece.yCoord+(direction.y/2)].display = ' ';
	BOARD.board[piece.xCoord+(direction.x/2)][piece.yCoord+(direction.y/2)].type = EMPTY;
	BOARD.pieces[BOARD.board[piece.xCoord+(direction.x/2)][piece.yCoord+(direction.y/2)].pieceNum-1].alive = false;
	if(piece.type == WHITE)
		BOARD.whitePieces--;
	if(piece.type == BLACK)
		BOARD.blackPieces--;

	//make move
	Space tempSpace;
	tempSpace = BOARD.board[piece.xCoord+direction.x][piece.yCoord+direction.y];
	BOARD.board[piece.xCoord+direction.x][piece.yCoord+direction.y] = BOARD.board[piece.xCoord][piece.yCoord];
	BOARD.board[piece.xCoord][piece.yCoord] = tempSpace;

	piece.xCoord = piece.xCoord + direction.x;
	piece.yCoord = piece.yCoord + direction.y;
}

vector<mov> canCaptureDirection(Piece p, Type color, gameBoard& BOARD){
	mov change;
	vector<mov> options;
	change.x = 0;
	change.y = 0;
	for(int x = -1; x < 2; x++){
		for(int y = -1; y < 2; y++){
			if(!((x==0)&&(y==0))){
				if(color == WHITE){
					if (BOARD.board[p.xCoord + x][p.yCoord + y].type == BLACK){
						if (BOARD.board[p.xCoord + 2*x][p.yCoord + 2*y].type == EMPTY){
							change.x = 2*x;
							change.y = 2*y;
							options.push_back(change);
						}}
				}
				if(color == BLACK){
					if (BOARD.board[p.xCoord + x][p.yCoord + y].type == WHITE)
						if (BOARD.board[p.xCoord + 2*x][p.yCoord + 2*y].type == EMPTY){
							change.x = 2*x;
							change.y = 2*y;
							options.push_back(change);
						}
				}
			}
		}
	}
	return options;
}

vector<int> aiCanCapture(Type color, gameBoard& BOARD){
	int pos = 0;
	vector<int> options;
	for (Piece p : BOARD.aipieces){
		if (p.alive == true)
		for(int x = -1; x < 2; x++){
			for(int y = -1; y < 2; y++){
				if(!((x==0)&&(y==0))){
					if(color == WHITE){
						if (BOARD.board[p.xCoord + x][p.yCoord + y].type == BLACK){
							if (BOARD.board[p.xCoord + 2*x][p.yCoord + 2*y].type == EMPTY){
								options.push_back(pos);
							}
						}
					}
					if(color == BLACK){
						if (BOARD.board[p.xCoord + x][p.yCoord + y].type == WHITE)
							if (BOARD.board[p.xCoord + 2*x][p.yCoord + 2*y].type == EMPTY){
								options.push_back(pos);
							}
					}
				}
			}
		}
		pos++;
	}
	//cout<<"cannot capture."<<endl;
	return options;
}

vector<int> pCanCapture(Type color, gameBoard BOARD){
	int pos = 0;
	vector<int> options;
	for (Piece p : BOARD.pieces){
		if (p.alive == true)
		for(int x = -1; x < 2; x++){
			for(int y = -1; y < 2; y++){
				if(!((x==0)&&(y==0))){
					if(color == WHITE){
						if (BOARD.board[p.xCoord + x][p.yCoord + y].type == BLACK){
							if (BOARD.board[p.xCoord + 2*x][p.yCoord + 2*y].type == EMPTY){
								options.push_back(pos);
							}
						}
					}
					if(color == BLACK){
						if (BOARD.board[p.xCoord + x][p.yCoord + y].type == WHITE)
							if (BOARD.board[p.xCoord + 2*x][p.yCoord + 2*y].type == EMPTY){
								options.push_back(pos);
							}
					}
				}
			}
		}
		pos++;
	}
	//cout<<"cannot capture."<<endl;
	return options;
}

vector<mov> aiCanMove(Piece p, Type color, gameBoard BOARD){
	//cout<<"AICANMOVE"<<endl;
	mov change;
	vector<mov> options;
	change.x = 0;
	change.y = 0;
	for(int x = -1; x < 2; x++){
		for(int y = -1; y < 2; y++){
			if(!((x==0)&&(y==0))){
				if(color == WHITE){
					change.x = x;
					change.y = y;
					if (isValid(p, change, BOARD)){
						options.push_back(change);
					}
				}
				if(color == BLACK){
					change.x = x;
					change.y = y;
					if (isValid(p, change, BOARD)){
						options.push_back(change);
					}
				}
			}
		}
	}
	return options;
}

vector<mov> aiCanCanter(Piece p, Type color, gameBoard BOARD){
	//cout<<"AICANMOVE"<<endl;
	mov change;
	vector<mov> options;
	change.x = 0;
	change.y = 0;
	for(int x = -1; x < 2; x++){
		for(int y = -1; y < 2; y++){
			if(!((x==0)&&(y==0))){
				if(color == WHITE){
					change.x = x;
					change.y = y;
					if (isValidCanter(p, change, BOARD)){
						options.push_back(change);
					}
				}
				if(color == BLACK){
					change.x = x;
					change.y = y;
					if (isValidCanter(p, change, BOARD)){
						options.push_back(change);
					}
				}
			}
		}
	}
	return options;
}

int playerCanCapture(Type color, gameBoard BOARD){
	int pos = 0;
	mov change;
	change.x = 0;
	change.y = 0;
	for (Piece p : BOARD.pieces){
		//cout<<p.pieceNum<<p.alive<<endl;
		if (p.alive == true){
		for(int x = -1; x < 2; x++){
			for(int y = -1; y < 2; y++){
				if(!((x==0)&&(y==0))){
					if(color == WHITE){
						if (BOARD.board[p.xCoord + x][p.yCoord + y].type == BLACK){
							if (BOARD.board[p.xCoord + 2*x][p.yCoord + 2*y].type == EMPTY){
								return pos;
							}
						}
					}
					if(color == BLACK){
						if (BOARD.board[p.xCoord + x][p.yCoord + y].type == WHITE)
							if (BOARD.board[p.xCoord + 2*x][p.yCoord + 2*y].type == EMPTY){
								return pos;
							}
					}
				}
			}
		}}
		pos++;
	}
	//cout<<"cannot capture."<<endl;
	return -1;
}
/////////////////////////////////////////////////////////////////////////////input functions
int getPlayerChoice(gameBoard BOARD){
	int i = 0;
	cout << "\nSelect a piece to move this turn:(";
	for(Piece p: BOARD.pieces){
		if (p.alive)
		cout <<p.pieceNum<<",";
	}
	cout<<")"<<endl;
	while(true){
		while(!(cin >> i)){
			cout<<"invalid choice"<<endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cout<<"You chose piece "<<i<<endl;
		cout<<BOARD.pieces.empty()<<endl;
		cout<<"You chose piece "<<i<<endl;
		if((i>0)&&(i<6))
			for(Piece p: BOARD.pieces){
				if ((p.pieceNum == i)&&(p.alive)){
				cout<<BOARD.pieces[i-1].xCoord<<BOARD.pieces[i-1].yCoord<<endl;
				return i-1;
			}}
		cout<<"invalid choice"<<endl;	
	}
}

int getPlayerDifficulty(){
	int i = 0;
	cout << "\nSelect a pdifficulty (1,2,3) ";
	while(true){
		while(!(cin >> i)){
			cout<<"invalid choice"<<endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cout<<"You chose: "<<i<<endl;

		if((i>0)&&(i<4)){
			if (i == 3)
				i = 4;
			return i;
		}
		cout<<"invalid choice"<<endl;	
	}
}

mov getPlayerDirection(){
	string i;
	while(true){
		cout << "\nSelect a direction to move: ";
		cin >> i;
		if (validDirection(i)){
			cout<<"You chose Direction "<<i<<endl;
			return directionToMov(i);
		}
		cout<<"You chose an invalid direction"<<endl;
		cin.clear();
	}
}
/////////////////////////////////////////////////////////meaty functions
vector<gameBoard> genSuccesors(gameBoard& BOARD){ // generate all potential moves for a color on a board
	int index = 0;
	//cout<<"genSuccesors"<<endl;
	Type turn = BOARD.turn;
	gameBoard newBoard = BOARD;
	vector<gameBoard> boardOptions;
	if(turn == BLACK){
		//cout<<"genBlack"<<aiCanCapture(BLACK, BOARD).empty()<<endl;
		if(!aiCanCapture(BLACK, BOARD).empty()){
			for(Piece a : BOARD.aipieces){
				if(a.alive==true)
				for(int b : aiCanCapture(BLACK, BOARD)){
					//cout<<"b = "<<b<<"piece num -1 =" <<a.pieceNum-1<<endl;
					if(a.pieceNum-1 == b)
						for(mov hop : canCaptureDirection(BOARD.aipieces[b], BLACK, BOARD)){
							newBoard = BOARD;
							makeaiCaptureMove(newBoard.aipieces[b], hop, newBoard);
							newBoard.turn = WHITE;
							//displayBoard(newBoard.board);
							boardOptions.push_back(newBoard);
					}
				}
			}
		}
		else{
			for(Piece a : BOARD.aipieces){
				//cout<<a.pieceNum<<endl;
				if(a.alive==true){
				if(!aiCanMove(a, BLACK, BOARD).empty())
				for(mov hop : aiCanMove(a, BLACK, BOARD)){
					newBoard = BOARD;
					makeMove(newBoard.aipieces[a.pieceNum-1], hop, newBoard);
					newBoard.turn = WHITE;
					//displayBoard(newBoard.board);
					boardOptions.push_back(newBoard);
				}}
			}
			for(Piece a : BOARD.aipieces){
				//cout<<a.pieceNum<<endl;
				if(a.alive==true){
				if(!aiCanCanter(a, BLACK, BOARD).empty())
				for(mov hop : aiCanCanter(a, BLACK, BOARD)){
					newBoard = BOARD;
					makeCanterMove(newBoard.aipieces[a.pieceNum-1], hop, newBoard);
					newBoard.turn = WHITE;
					//displayBoard(newBoard.board);
					boardOptions.push_back(newBoard);
				}}
			}
		}
	}
	else if(turn == WHITE){
		//cout<<"genwhite"<<pCanCapture(WHITE, BOARD).empty()<<endl;
		if(!pCanCapture(WHITE, BOARD).empty()){
			for(Piece a : BOARD.pieces){
				if(a.alive==true)
				for(int b : pCanCapture(WHITE, BOARD)){
					if(a.pieceNum-1 == b)
						for(mov hop : canCaptureDirection(BOARD.pieces[b], WHITE, BOARD)){
							newBoard = BOARD;
							makeCaptureMove(newBoard.pieces[b], hop, newBoard);
							newBoard.turn = BLACK;
							boardOptions.push_back(newBoard);
					}
				}
			}
		}
		else{
			for(Piece a : BOARD.pieces){
				if(a.alive==true)
				for(mov hop : aiCanMove(a, WHITE, BOARD)){
					newBoard = BOARD;
					makeMove(newBoard.pieces[a.pieceNum-1], hop, newBoard);
					newBoard.turn = BLACK;
					boardOptions.push_back(newBoard);
				}
			}
			for(Piece a : BOARD.pieces){
				if(a.alive==true)
				for(mov hop : aiCanCanter(a, WHITE, BOARD)){
					newBoard = BOARD;
					makeCanterMove(newBoard.pieces[a.pieceNum-1], hop, newBoard);
					newBoard.turn = BLACK;
					boardOptions.push_back(newBoard);
				}
			}

		}
	}
	//cout<<"BOARD OPTIONS AVAILABLE ; "<<endl;
//cout<<boardOptions.size()<<endl;
	return boardOptions;
}

void playerTurn(gameBoard& BOARD){  ///// control for the player
	cout << "Your turn."<<endl;
	bool valid = false;
	int capPosition = playerCanCapture(WHITE, BOARD);
	if(capPosition != -1){
		cout<<"which capture would you like to make?"<<endl;
		vector<mov> capDirection = canCaptureDirection(BOARD.pieces[capPosition], WHITE, BOARD);
		string n;
		bool okay = false;
		do{
			cin >> n;
			for(mov m : capDirection){
				cout<<m.x<<m.y<<endl;
				cout<<directionToMov(n).x<<directionToMov(n).y<<endl;
				if((directionToMov(n).x*2 == m.x)&&(directionToMov(n).y*2 == m.y))
					okay = true;
			}
			if(okay != true)
				cout<<"sorry that was not a valid capture"<<endl;
			cin.clear();
		}while(!okay);
		mov hop = directionToMov(n);
		hop.x = hop.x*2;
		hop.y = hop.y*2;
		makeCaptureMove(BOARD.pieces[capPosition], hop, BOARD);
	}
	else{
		while(!valid){
			int pieceNum = getPlayerChoice(BOARD);
			mov direction = getPlayerDirection();
			if(isValid(BOARD.pieces[pieceNum], direction, BOARD)){
				makeMove(BOARD.pieces[pieceNum], direction, BOARD);
				valid = true;
			}
			else if(isValidCanter(BOARD.pieces[pieceNum], direction, BOARD)){
				makeCanterMove(BOARD.pieces[pieceNum], direction, BOARD);
				valid = true;
			}
			else{
				valid = false;
				cout<<"move  was not valid"<<endl;
			}
		}
	}
BOARD.turn = BLACK;
}

/////////////////////////////////////alphabeta stuff

int min(int a, int b){
	if (a<b)
		return a;
	else
		return b;
}
int max(int a, int b){
	if (a>b)
		return a;
	else
		return b;
}
int eval2(gameBoard board){
	return board.whitePieces - board.blackPieces;
}


int eval(gameBoard board){
	int whitedist = 0;
	int blackdist = 0;
	int cap = 0;
	int dist = 0;
	int util = 0;

	cap = 10 * (board.whitePieces - board.blackPieces);


	for(Piece p : board.pieces){
		blackdist += min(((p.xCoord - 4 )+(p.yCoord - 1)), ((p.xCoord - 5 )+(p.yCoord - 1)));
	}
	blackdist = blackdist/board.blackPieces;
	for(Piece p : board.aipieces){
		whitedist += min(((p.xCoord - 4 )+(p.yCoord - 14)), ((p.xCoord - 5 )+(p.yCoord - 14)));
	}
	whitedist = whitedist/board.whitePieces;
	dist = whitedist-blackdist;

	util = (dist + cap)/2;
	return util;
}
int maxdepth;
int numNodes;
int maxPrune;
int minPrune;
int chosenDepth;
std::chrono::steady_clock::time_point t1;

int minValue(gameBoard& board, int x, int y, int depth);
int maxValue(gameBoard& board, int x, int y, int depth){
	std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double> >(t2 - t1);
	int index = 0;
	//cout<<"Max"<<endl;
	int newDepth = depth + 1;
	maxdepth = max(maxdepth, newDepth);
	if ((depth > chosenDepth)||(time_span.count() > 5))
		return eval(board); 
	int v = -1000;
	for ( gameBoard a : genSuccesors(board)){
		//cout<<"Max"<<index;
		numNodes++;
		v = max(v, minValue(a, x, y, newDepth)) ;
		if (v >= y){
		 	maxPrune++;
		 	return v;
		 }
		x = max(x, v);
	}
	return v;
}
int minValue(gameBoard& board, int x, int y, int depth){
	std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double> >(t2 - t1);
	int index = 0;
	//cout<<"Min"<<endl;
	int newDepth = depth + 1;
	//maxdepth = max(maxdepth, newDepth);
	if ((depth > chosenDepth)||(time_span.count() > 5))
		return eval(board);
	int v = 1000;
	for ( gameBoard a : genSuccesors(board)){
		//cout<<"Min"<<index;
		index++;
		numNodes++;
		v = min(v, maxValue(a, x, y, newDepth));
		if (v <= x){
		 	minPrune++;
		 	return v;
		 }
		y = min(y, v);
	}
	return v;
}

gameBoard alphaBeta(gameBoard& board){
	maxdepth = 0;
	numNodes = 0;
	maxPrune = 0;
	minPrune = 0;
	t1 = std::chrono::steady_clock::now();
	int v  = maxValue(board, -1000, 1000, -1);
	cout<<"----------------------"<<endl;
	cout<<"max depth = "<<maxdepth<<endl;
	cout<<"number of nodes = "<<numNodes<<endl;
	cout<<"times max pruned = "<<maxPrune<<endl;
	cout<<"times min pruned = "<<minPrune<<endl;
	cout<<"v = "<<v<<endl;
	cout<<"----------------------"<<endl;
	for ( gameBoard a : genSuccesors(board)){
		cout<<eval(a)<<endl;
		if(eval(a) == v){
			return a;
		}}
	cout<<"V NOT FOUND"<<endl;
	for ( gameBoard a : genSuccesors(board)){
			return a;
		}
}
//////////////////////////////////////////////////end alphabeta stuff
void aiTurn(gameBoard& BOARD){ // foor AIs turn
	cout << "\nComputer's turn.\n";			
	BOARD = alphaBeta(BOARD);								
	BOARD.turn = WHITE;
}


GameState checkWin(gameBoard BOARD){ ////check condition
	if ((BOARD.board[4][1].type == BLACK)&&(BOARD.board[5][1].type == BLACK))
		return BLACK_WIN;
	if ((BOARD.board[4][14].type == WHITE)&&(BOARD.board[5][14].type == WHITE))
		return WHITE_WIN;
	if ((BOARD.whitePieces == 0)&&(BOARD.blackPieces >= 2))
		return BLACK_WIN;
	if ((BOARD.whitePieces >= 2)&&(BOARD.blackPieces == 0))
		return WHITE_WIN;
	if ((BOARD.whitePieces == 1)&&(BOARD.blackPieces == 1))
		return DRAW;
	return PLAY;
}

int main() // ya know :)
{
	gameBoard BOARD;
	BOARD.whitePieces = 6;
	BOARD.blackPieces = 6;
	//vector<vector<Space> > BOARD;
	initVec(BOARD.board);
	//vector<Piece> BOARD.pieces;
	//vector<Piece> BOARD.aipieces;
	initPieces(BOARD);
	displayBoard(BOARD.board);
	//Game start
	GameState state = PLAY;
	chosenDepth = getPlayerDifficulty();
	while(state == PLAY){
		playerTurn(BOARD);
		displayBoard(BOARD.board);
		aiTurn(BOARD);
		displayBoard(BOARD.board);
		state = checkWin(BOARD);
	}
	if (state == BLACK_WIN)
		cout<<"YOU LOSE :("<<endl;
	if (state == WHITE_WIN)
		cout<<"YOU WIN :)"<<endl;
	if (state == DRAW)
		cout<<"DRAW :|"<<endl;
	

}