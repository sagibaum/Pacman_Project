#pragma once
#include "Board.h"
#include "General.h"
typedef struct BoardNode
{
	Board map;
	string  mapname;

};

class BoardDataBase
{
public:
	bool FindFilesInDictionary();
	int FindNumOfFiles(ifstream& myfile);
	void GetMapFromFile(const char* filename, int Index);
	int GetColsLenFromFile(ifstream& myfile);
	int GetRowsNumberFromFile(ifstream& myfile, int columnLen, int& rowoflegend, int& coloflegend);
	void AllocateNewMapAndSetIt(ifstream& myfile, Board& b);
	const char* getRawFileName(int index) const;
	//-----------------------
	int GetDB_Size() const;
	BoardNode* get_Database();
	~BoardDataBase();
	
private:
	int DBsize;
	BoardNode* Database=nullptr;
};

