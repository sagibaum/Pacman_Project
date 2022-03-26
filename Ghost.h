#ifndef _GHOST_H
#define _GHOST_H

#pragma once

#include "Board.h"
#include "Pacman.h"
#include "GameObj.h"
#include "General.h"
#include <queue>

#define NoveMoveEvery 20
#define GoodGhostRandMoveRange 5
#define GoodGhostRandMoveInitial 16
#define MoveAmountAvailable 4
#define GoodGhost5MoveCount 5

enum Intellegence { Best, Good, Novice };
enum class Direction { right = 0, left = 1, up = 2, down = 3 };

class QueueNode { //assistant class to use BFS algo for ghost chase algorithm
private:
	int row;
	int col;
	int dist;
public:
	QueueNode(int x, int y, int w)
		: row(x), col(y), dist(w)
	{
	}
	void Set_Row(const int row) { this->row = row; };
	void Set_Col(const int col) { this->col = col; };
	void Set_Dist(const int col) { this->dist = dist; };
	//------------
	int Get_Row() { return row; };
	int Get_Col() { return col; };
	int Get_Dist() { return dist; };
};

class Ghost : public GameObj
{
private:
	Intellegence Level;
public:
	Intellegence Get_Ghost_Intellegence() const;
	//-----------------------------------------------------------
	void Set_Ghost_Intellegence(Intellegence Level);
	Ghost(int x, int y, char c, Intellegence Level);
	~Ghost();
	Ghost();
	//-----------------------------------------------------------
	void GhostMove(Board& b, bool WithColors, Pacman& C,int index, int load ,  int LoadDirection,bool savingmode);
	void ChangePosAndMakeMove(int x, int y, Board& b, bool WithColors);//POLYMORPHISM
	//-----------------------------------------------------------
	Direction BestGhostAlgorithm(Board& b, Pacman C);
	int minDistance(int x, int y, Board& map, const Pacman& pacman, int LastMin);
	int** VisitedArrAndSetWalls(const int rows, const int cols, Board& map);
	void FreeVisitedArr(const int height, int** visited);
	//------------------------------------------------------------
	Direction NoviceGhostAlgorithm();
	Direction GoodGhostAlgorithm(Board& b, bool WithColors, Pacman C);
	//------------------------------------------------------------
};

#endif