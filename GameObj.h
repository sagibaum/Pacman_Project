#ifndef _GAMEOBJ
#define _GAMEOBJ
#pragma once
#include "Position.h"
#include "Colors.h"
#include "Board.h"
#define WALL '#'
#define BORDER_GAP 1
class GameObj : public Position
{
private:
	char symbol;
	Color color;
	bool Is_Silent_Game = false;
public:
	Color GetColor()const;
	char GetSym()const;
	//------------------------------------------------------------------------------------
	void Set_GameObj_Color(Color c);
	void Set_GameObj_Symbol(char Sym);
	void SetSilence(bool value);
	//----------these functions can be hereditery:---------------------------------------
	void Draw_GameObj()const;
	int  CheckIfWall(int x, int y, Board& b);
    void DeletePrevLoc()const;
	void DeletePrevLocGhostandFriut(Board& b, bool WithColors)const;
	virtual void ChangePosAndMakeMove(int x, int y, Board& b, bool WithColors);
	virtual int CheckLimits(int x, int y, Board& b);
};
#endif

