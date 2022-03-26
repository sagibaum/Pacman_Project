#ifndef _BOARD_H
#define _BOARD_H
#pragma once
#include "General.h"
#include "DataRecorder.h"
#define MAXSIZE 256
#define HOERLINE1LEN 17
#define HOERLINE2LEN 18
#define X 0
#define Y 1
#define ROWS 0
#define COLS 1
#define LEFT_T 0
#define RIGHT_T 1
#define UP_T 2 
#define DOWN_T 3
#define LIVEROWGAP 1
#define LIVECOLGAP 9
#define SCORECOLGAP 14

using namespace std;
class  Board
{
	
public:
	int GetLives() const;
	int GetScore() const;
	int GetScoreToWin()const;
	int GetGhostXCords(int Arrindex)const;
	int GetGhostYCords(int Arrindex)const;
	int GetPacmanXCords()const;
	int GetPacmanYCords()const;
	int GetGhostArrSize()const;
	int GetScoreXCord()const;
	int GetScoreYCord()const;
	int GetLiveXCord()const;
	int GetLiveYCord()const;
	char GetSymbol(int x, int y, bool ItsFruit);
	int GetmapRows();
	char* GetRowPointer(int index);
	int GetmapCols();
	char** Getmap();
	DataRecorder* GetDataRecorderObject();
	//-----------------------------------------------------------------------
	void SetScore(bool WithColors, int val);
	void SetScoreWithGlobal(int globalscore);
	void SetLivesWithGlobal(int globallives);
	void SetScoreToWin(int value);
	void SetLife(bool WithColors);
	void SetArrCell(int x, int y);
	void SetmapRows(int FileRows);
	void SetmapCols(int Columns);
	void SetSilence(bool value);
	void SetMap(char** map);
	void SetLocationsForMap();
	void SetGhostCords(int x, int y, int Arrindex);
	void SetGhostArrSize(int newsize);
	void SetPacmanCords(int x, int y);
	//-----------------------------------------------------------------------
	 ~ Board();
	 Board(int score = 0, int lives = 3) :score(score), Lives(lives) {}
	 //----------------------------public functions----------------------------//
	 void Creatcpy();
	 void Deletecopyarr();
	 void Printmap(bool WithColors, bool IsSilent);
	 
	 
private:
	char** Map=nullptr,**Mapcpy=nullptr;
	int BoardsSize[2], Livescords[2], Scorcords[2], PacmanCords[2];
	int GhostCords[4][2],Gharrsize;	//0=Ghost 1, 1=Ghost 2,2=Ghost 3,3= Ghost 4
	int score, scoretowin;
	int Lives;
	DataRecorder r;
	bool Is_silent = false;
};
#endif
