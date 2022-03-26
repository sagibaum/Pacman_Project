#include "BoardDataBase.h"

//----------------------------------------FILES----------------------------------------

//This Function returns databsesize
int BoardDataBase::GetDB_Size() const
{
	return this->DBsize;
}

//This Function returns pointer to database
BoardNode* BoardDataBase::get_Database() 
{
	return this->Database;
}

//This Function returns filename
const char* BoardDataBase::getRawFileName(int index) const
{
	return Database[index].mapname.c_str();
}

//This Function finds how many files in folder has name of Pacman_*.screen.txt
bool BoardDataBase::FindFilesInDictionary()
{
	int Index = 0;
	bool Nofiles = false;
	char s[MAXSIZE];
	ifstream myfile;
	if (system("dir *.screen /a-d/b> file_names.txt")) {
		cout << "Error with opening the file , probably the files like *.screen is not exist...";
		exit(1);
	}
	myfile.open("file_names.txt", ios_base::in);
	if (!myfile.is_open()) {
		cout << "Error with opening the file ";
		exit(1);
	}
	DBsize = FindNumOfFiles(myfile);
	if (DBsize != 0)Database = new BoardNode[DBsize];
	while (myfile.getline(s, 't') && (DBsize != 0))
	{
		Nofiles = true;
		GetMapFromFile(s, Index++);
	}
	myfile.close();
	return Nofiles;
}

//This Function finds how many files in textfile of files name
int BoardDataBase::FindNumOfFiles(ifstream& myfile)
{
	int counter = 0;
	char s[MAXSIZE];
	while (myfile.getline(s,'t')) {
		counter++;
	}
	myfile.clear();
	myfile.seekg(0);
	return counter;
}

//This function creats a map from file input 
void BoardDataBase::GetMapFromFile(const char* filename, int Index)
{
	int legendcords[2] = { 0 };
	int Rows, Columns, LineofHero;
	ifstream newfile;
	newfile.open(filename, ios_base::in);
	if (!newfile.is_open())
	{
		std::cout << "Error with opening the file , probably the file is not exist... ";
		return ;
	}
	else {

		Columns = GetColsLenFromFile(newfile);
		Rows = GetRowsNumberFromFile(newfile, Columns, legendcords[0],legendcords[1]);
		Database[Index].mapname=string(filename);
		Database[Index].map.SetmapCols(Columns);
		Database[Index].map.SetmapRows(Rows+1);
		AllocateNewMapAndSetIt(newfile, Database[Index].map);
	}
	newfile.close();
}

//This function gets the rows number of map from file 
int BoardDataBase::GetColsLenFromFile(ifstream& myfile)
{
	string line, maxline;
	getline(myfile, maxline);
	for (int i = 0; getline(myfile, line); i++)
		if (maxline.length() < line.length())
			maxline = line;
	myfile.clear();
	myfile.seekg(0, myfile.beg);
	return(maxline.length());
}

//This function gets the rows number of map from file 
int BoardDataBase::GetRowsNumberFromFile(ifstream& myfile, int columnLen,int& rowoflegend, int& coloflegend)
{
	int linecount;
	size_t found;
	string line;
	for (linecount = 0; getline(myfile, line); linecount++) {
		found = line.find('&');
		if (!(found == string::npos))
		{
			rowoflegend = linecount;
			coloflegend = found;
		}
	}
	linecount--;
	myfile.clear();
	myfile.seekg(0, myfile.beg);
	return (linecount);
}

//This function allocats a new map acoording to the file rows and cols 
void BoardDataBase::AllocateNewMapAndSetIt(ifstream& myfile, Board& b)
{
	int a = b.GetmapCols(),lenght=0;
	char s[MAXSIZE];
	char** NewMap = new char* [b.GetmapCols()];
	for (int i = 0; i < b.GetmapRows(); ++i) {
		myfile.getline(s, MAXSIZE);
		lenght = strlen(s)+1;
		NewMap[i] = new char[lenght];
		strcpy(NewMap[i], s);
	}
	b.SetMap(NewMap);
}

//This function is a dtor that Frees Databas Arr;
BoardDataBase::~BoardDataBase() {
	if (Database != nullptr) {
		char* row;
		int Rownums;
		for (int j = 0; j < DBsize; j++) {
			Rownums = Database[j].map.GetmapRows();
			for (int i = 0; i < Rownums; i++) {
				row = Database[j].map.Getmap()[i];
				delete[] row;
			}
		}
		delete[] Database;
	}
}


