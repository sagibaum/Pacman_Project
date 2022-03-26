// מחלקה לניהול המסך 
#include "Board.h"

Board::~Board() {}

 //This function is a default destructor
void  Board::Deletecopyarr()
{
	 for (int i = 0; i < BoardsSize[ROWS]; ++i)
		 delete[] Mapcpy[i];
		delete Mapcpy;

}
 char** Board::Getmap() { return (this->Map); }
 
//----------------------------getters----------------------------

 //This function get the symbol on specified cord
 char Board::GetSymbol(int x, int y,bool ItsFruit)
 {
	 if (ItsFruit)
		 return Map[y][x];
	 else
	 return Mapcpy[y][x];
 }

 //This function gets the lives left
 int Board::GetLives() const
 {
	 return this->Lives;
 }

 //This function gets the score
 int Board::GetScore() const
 {
	 return this->score;
 }

 //This function gets the score to win 
 int Board::GetScoreToWin() const
 {
	 return scoretowin;
 }

 //this function returns num of rows of specified map from map data base
 int Board::GetmapRows() { return (this->BoardsSize[ROWS]);}

 //this function returns num of cols of specified map from map data base
 int Board::GetmapCols() { return (this->BoardsSize[COLS]); }

 // This function returns the ghost X index
 int Board::GetGhostXCords(int Arrindex)const { return GhostCords[Arrindex][X]; }

 //This function returns the ghost Y index
 int Board::GetGhostYCords(int Arrindex)const { return GhostCords[Arrindex][Y]; }

 //This function returns ghosts array size
 int Board::GetGhostArrSize()const { return Gharrsize; }

 //This function returns the pacman X index
 int Board::GetPacmanXCords()const{return PacmanCords[X];}

 //This function returns the pacman Y index
 int Board::GetPacmanYCords()const{return PacmanCords[Y];}

 //This function returns the score X index
 int Board::GetScoreXCord()const { return Scorcords[X]; }

 //This function returns the score Y index
 int Board::GetScoreYCord()const { return Scorcords[Y]; }

 //This function returns the lives X index
 int Board::GetLiveXCord()const { return (Livescords[X]); }

 //This function returns the live Y index
 int Board::GetLiveYCord()const { return (Livescords[Y]); }

 //This function returns pointer to a row of this board
 char* Board::GetRowPointer(int index) { return Map[index]; }

 //This function returns pointer to DataRecorder object
 DataRecorder* Board::GetDataRecorderObject() {
	 return &r;
 }

 //----------------------------setters----------------------------//

 //This function Sets the map initial locations of packamn,lives,score and ghosts 
 void Board::SetLocationsForMap()
 {
	 int breadcounter = 0;
	 Gharrsize = 0;
	 for (int i = 0; i < BoardsSize[ROWS]; i++)
	 {
		 for (int j = 0; j < BoardsSize[COLS]; j++) {
			 
				 if (this->Map[i][j] == ' ') {
					 this->Map[i][j] = '.';
					 breadcounter++;
				 }
				 else if (this->Map[i][j] == '@')
				 {
					 PacmanCords[X] = j;
					 PacmanCords[Y] = i;
				 }
				 else if (this->Map[i][j] == '$'&& Gharrsize<4)
				 {
					 GhostCords[Gharrsize][X] = i;
					 GhostCords[Gharrsize][Y] = j;
					 Gharrsize++;
				 }
				 else if (this->Map[i][j] == '&')
				 {
					 Scorcords[X] = i;
					 Scorcords[Y] = j + SCORECOLGAP;
					 Livescords[X] = i + LIVEROWGAP;
					 Livescords[Y] = j + LIVECOLGAP;
				 }
				 
			 }
		 } 
	 SetScoreToWin(breadcounter);
 }

 //This function sets the score
 void Board::SetScoreWithGlobal(int globalscore) {

	 score = globalscore;
 }

 //This function sets the lives
 void Board::SetLivesWithGlobal(int globallives) {
	 Lives = globallives;
 }

 //This function sets the score when pacman eats 
 void Board::SetScore(bool WithColors, int val)
 {
	 if (WithColors)
		 setTextColor(Color::LIGHTGREEN);
	 if (val != 0)
		 score += val;
	 else ++score;
	 if (!Is_silent) {
		 gotoxy(Scorcords[Y], Scorcords[X]);
		 cout << score;
	 }
 }

 //This function sets the score according to a map
 void Board::SetScoreToWin(int value)
 {
	 this->score = 0;
	 this->scoretowin = value;
 }

 //This function sets life when pacman dies
 void Board::SetLife(bool WithColors)
 {
	 if (WithColors)
		 setTextColor(Color::LIGHTGREEN);
	 --Lives;
	 if (!Is_silent) {
		 gotoxy(Livescords[Y], Livescords[X]);
		 cout << Lives;
	 }
 }

 void Board::SetSilence(bool value) {
	 this->Is_silent = value;
 }

 //This function sets arr value to space when pacman eats fruit
 void Board::SetArrCell(int x, int y)
 {
	 this->Mapcpy[y][x] = ' ';
 }

 //This function Sets num of rows 
 void Board::SetmapRows(int FileRows){BoardsSize[ROWS] = FileRows;} 

 //This function Sets num of columns 
 void Board::SetmapCols(int Columns) {BoardsSize[COLS] = Columns;}

 //This function set this board map
 void Board::SetMap(char** map) { this->Map = map; }

 //This function Sets a specified ghost cord in gosts cords array
 void Board::SetGhostCords(int x, int y, int Arrindex)
 {
	 GhostCords[Arrindex][X] = x;
	 GhostCords[Arrindex][Y] = y;
 }

 //This function sets ghosts array size
 void  Board::SetGhostArrSize(int newsize) {Gharrsize=newsize; }


 //This function Sets pacman cords in pacman cords array
 void Board::SetPacmanCords(int x, int y)
 {
	 PacmanCords[X] = x;
	 PacmanCords[Y] = y;
 }

 //----------------------------public functions----------------------------//
 
 //This function creats the game board we play in 
 void Board::Creatcpy()
 {
	 Mapcpy = new char* [BoardsSize[COLS]];
	 for (int i = 0; i < BoardsSize[ROWS]; ++i) {
		 Mapcpy[i] = new char[BoardsSize[COLS]];
		 memcpy(Mapcpy[i], Map[i], BoardsSize[COLS]);
	 }
	 score = 0;
	 Lives = 3;
 }


 //This function prints the map and sometimes  updates the copy  
 void Board::Printmap(bool WithColors,bool IsSilent)
 {
	 int Hx=0, Hy=0;
	 for (int i = 0; i < BoardsSize[ROWS]; i++)
	 {
		 for (int j = 0; j < BoardsSize[COLS]; j++) {
			 if (this->Mapcpy[i][j] == ' ' && j == 0) continue;
			 else {
				 if (this->Mapcpy[i][j] == '#') {
					 if (WithColors)
						 setTextColor(Color::BLUE);
					if(!IsSilent) cout << this->Mapcpy[i][j];
				 }
				 else if (this->Mapcpy[i][j] == '%' || this->Mapcpy[i][j] == '$' || this->Mapcpy[i][j] == '@')
				 {
						 this->Mapcpy[i][j] = ' ';
						 if (!IsSilent) cout << ' ';
				 }
				 else if (this->Mapcpy[i][j] == '.') {
					 if (WithColors)
						 setTextColor(Color::LIGHTRED);
					 if (!IsSilent) cout << ".";
				 }
				 else if (this->Mapcpy[i][j] == '&')
				 {
					 if (!IsSilent) cout << ' ';
					 Hx = j;
					 Hy = i;
				 }
			 }
		 }
		 cout << "\n";
	 }if (!IsSilent) {
		 if (WithColors)
			 setTextColor(Color::RED);
		 gotoxy(Hx, Hy);
		 cout << "Your score is:" << score;
		 gotoxy(Hx, Hy + 1);
		 cout << "You have " << Lives << " lives";
	 }
 }
