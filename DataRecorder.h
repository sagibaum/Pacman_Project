#pragma once
#include"General.h"
#include"Position.h"
#define RIGHT 0
#define LEFT 1
#define UP 2
#define DOWN 3
#define STEPS 1
#define RESULT 2
#define LINEMAXSIZE  10000

class DataRecorder
{
private:
	
	string CreatNewName(string filename,int which);
	vector <string> result;
	vector<string> GameMoves;

public:
	DataRecorder();
	~DataRecorder();

	vector<string>& GetGameMovesVec();
	vector<string>& GetResVec();

	string ConvertIputeToString(int input);
	void PrintToFilesShell(string filename);
	void PrintToStepsFile(string filename);
	void PrintToResultFile(string filename);
	void PrintFilesToSteps(string filename);
	void PrintRFileToResult(string filename);
};

