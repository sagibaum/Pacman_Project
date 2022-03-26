#pragma once
#include"General.h"
#include "BoardDataBase.h"
#define MENU 0
#define QUITGAME 2
#define WONLEVEL 1
#define INSTRUCTIONS 1
#define Xcordcorrection 1
#define Ycordcorrection 9

class Menu
{
	//----------------------------------------MENU----------------------------------------
public:
	void ShowMenu(int From)const;
	int MapSelectionMenu(BoardDataBase& Db)const;
	int SelectGhostLevel()const;
	void MapSelectionMenuprinter(int dbsize, BoardDataBase& Db)const;
	int PlayWithColors();
	char instrucions() const;
	void CheckValidOption(char& x, int From);
	int CheckWhyEndGame(char key, int score, int scoretowin, int lives)const;
	void GhostHitNotification(int LiveYCord, int LiveXCord);
	void PauseUnPauseFunc(char& key, char keyreminder, int LiveYCord, int LiveXCord);
	void ChampMessage();
	void MovingLevel();
	void InputHelperMessage();
	bool CheckIfSimulatOver(vector<string>::iterator& GameMoves,Board& map, bool IsSilent);
	void SilentMessege(bool IsSucceed);
	void CantPlayMapSelInSavemodeAlert();
};

