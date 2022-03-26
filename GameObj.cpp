#include "GameObj.h"

//This function gets pacman color
Color GameObj::GetColor()const
{
	return this->color;
}

//This function gets pacman symbol
char GameObj::GetSym()const
{
	return this->symbol;
}

//------------------------------------------------------------------------------------
//This function sets pacman color
void GameObj::Set_GameObj_Color(Color c)
{
	color = c;
}

//This function sets pacman symbol
void GameObj::Set_GameObj_Symbol(char Sym)
{
	this->symbol = Sym;
}

void GameObj::SetSilence(bool value) {
	this->Is_Silent_Game = true;
}

//This function draws onject symbol
void GameObj::Draw_GameObj()const
{
	if (!Is_Silent_Game) {
		setTextColor(color);
		gotoxy(this->Get_X_Pos(), this->Get_Y_Pos());
		cout << this->symbol << endl;
	}
}

//This function checks if wall is ahead
int  GameObj::CheckIfWall(int x, int y, Board& b)
{
	if (b.GetSymbol(x, y,false) == WALL)
		return 1;
	return 0;
}

//This funcion delets ghosts or fruits prev location
void GameObj::DeletePrevLocGhostandFriut(Board& b, bool WithColors)const
{
	if (!Is_Silent_Game) {
		if (WithColors)
			setTextColor(Color::LIGHTRED);
		gotoxy(this->Get_X_Pos(), this->Get_Y_Pos());
		cout << b.GetSymbol(this->Get_X_Pos(), this->Get_Y_Pos(), false);
	}
}

//This funcion delets pacmans prev location
void GameObj::DeletePrevLoc()const
{
	if (!Is_Silent_Game) {
		gotoxy(this->Get_X_Pos(), this->Get_Y_Pos());
		setTextColor(Color::WHITE);
		cout << " ";
	}
}

//This function make an object movement
void GameObj::ChangePosAndMakeMove(int x, int y, Board& b, bool WithColors)
{

	DeletePrevLoc();
	Set_XandY_Pos(x,y);
	Draw_GameObj();
}

//This function checks limit acorrding to heir 
int GameObj::CheckLimits(int x, int y, Board& b)
{ 
	if (y + BORDER_GAP > b.GetmapRows()/*down*/ || y - BORDER_GAP < 0 /*up*/ || x + BORDER_GAP > b.GetmapCols()/*right*/ 
		|| x - BORDER_GAP < 0/*left*/|| b.GetSymbol(x, y,false) == WALL)
		return 1;

	return 0;
		
}