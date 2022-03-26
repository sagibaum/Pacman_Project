#ifndef _GAME_H_
#define _GAME_H_
#define NOTSTARTED 0
#define STARTED 1
#define SCORE 0
#define LIVES 3
#define EXITWITHP 112
#define ESC 27
#define _CRT_SECURE_NO_WARNINGS
#define INVALID 42
#include "Board.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"
#include"Menu.h"
#include "BoardDataBase.h"
#include <vector>
enum Choice { Load, Save, LoadSilent,SaveSilent };
enum CharMoves {up_C = 'U' , down_C = 'D' , right_C = 'R' , left_C = 'L' , pac_stay_C = 'S' };

using namespace std;
class Game
{
public:
	Game();
	//----------------------------------------RUN AND CONTROL FUNCTIONS----------------------------------------
	
	void WhichGameTostart(int argc, char* argv[]);
	void StartGame(bool savingmood);
	void run( bool WithColors,int selection, bool& quited,int GhostLevel, bool savingmode);
	void InitializeGame(Pacman& player, Ghost* Gharr, int Gharrsize, Board& map, bool WithColors, Fruit& f, int GhostLevel, bool IsSilent);
	void GhostInitializer(Ghost* Ghostarr, int Gharrsize, Board& map, int GhostLevel,bool issilent);
	void PacmanInitializer(Pacman& player, Board& map, bool issilent);
	void DeleteGhosts(Ghost* Ghostarr, int Gharrsize, Board& map, bool WithColors);
	bool CheckPlayerGhostCollision(Pacman& player, Ghost* Ghostarr, int Gharrsize, Board& map, bool WithColors, int GhostLevel,bool issilent);
	void GhostShellFunctionForMovment(Ghost* Ghostarr, int Gharrsize, Pacman& c, Board& map, bool WithColors, int load, int LoadDirection,bool savingmode);
	void GhostColorInitializer(Ghost* Ghostarr, int Gharrsize, bool WithColor);
	void CheckIfSilentSucceed(Board& map, Menu& M, int stepstilfinished, int deathsteps[3]);

	//------------------FILES AND RUN SIMULATIONS FUNCTIONS---------------
	int FindNumOfStepFiles(ifstream& myfile);
	void SimulateFromFile(bool IsSilent);
	void LoadSimulation(int level, bool WithColors, bool IsSilent);
	void ExtractInfoFromVecTillMovement(Board& b, vector<string>::iterator& GameMoves, Fruit& F, int& value, int& AppearX, int& AppearY);
	Direction DirectionFromVecChar(char direction);
	char PacMovesFromChar(char direction);
	void RcoredDeath(Board& b, Pacman& c, int moves);
	void RecordScreenFinish(Board& b, int moves);
	void GhostStepsSimulation(vector<string>::iterator& GameMoves, Ghost* Ghostarr, int Gharrsize, Pacman& c, Board& b, bool WithColors);
	void EntireFruitSimulation(Fruit& F, Pacman& c, Board& b, bool WithColors, vector<string>::iterator& GameMoves, int& AppearX, int& AppearY, int& value, bool savingmode);
private:
	BoardDataBase MapsDatabase;
	Menu M;
	int globalscore = 0;
	int globallives = 3;

};
#endif
