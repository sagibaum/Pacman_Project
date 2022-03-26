#include "DataRecorder.h"
//This function is Empty Ctor
DataRecorder::DataRecorder(){}

//This function is Dtor
DataRecorder::~DataRecorder(){}

//This function returns the Game moves vector
vector<string>& DataRecorder::GetGameMovesVec() {
	return this->GameMoves;
}

//This function returns the result vector
vector <string>& DataRecorder::GetResVec() {
	return  result;
}

//This function converts file input to string for vector
string DataRecorder::ConvertIputeToString(int input) {

	if (input == LEFT || input == 'a')
		return "L";
	else if (input == RIGHT || input == 'd')
		return "R";
	else if (input == UP || input == 'w')
		return "U";
	else if (input == DOWN || input == 'x')
		return "D";
	else if (input == 's')
		return "S";
}

//This function is Shell function for print to file the result vector and steps vector
void DataRecorder::PrintToFilesShell(string filename) {
	PrintToStepsFile(filename);
	PrintToResultFile(filename);
}

//This function prints steps vector to file
void DataRecorder::PrintToStepsFile(string filename) { 
	ofstream myfile;
	int i = 0;
	string newname;
	newname.assign(CreatNewName(filename,STEPS));
	myfile.open(newname, ios_base::out | ios_base::trunc);
	if (!myfile.is_open())
	{
		std::cout << "Error with opening the file , probably the file is not exist... ";
		return;
	}
	if (!GameMoves.empty()) {
		for (std::vector<string>::iterator it = GameMoves.begin(); it != GameMoves.end(); ++it) {
			myfile << (*it) << " ";
		}
		GameMoves.clear();
		myfile << '\n';
	}
	myfile.close();
}

//This function prints steps vector to file
void DataRecorder::PrintToResultFile(string filename)
{
	ofstream myfile;
	string newname;
	newname.assign(CreatNewName(filename, RESULT));
	myfile.open(newname, ios_base::out | ios_base::trunc);
	if (!myfile.is_open())
	{
		std::cout << "Error with opening the file , probably the file is not exist... ";
		return;
	}
	for (std::vector<string>::iterator it = result.begin(); it != result.end(); ++it) {
		myfile << (*it) << " ";
	}
	myfile << '\n';
	result.clear();
	myfile.close();
}

//This function creats a name for files acoording to which one user asks for
string DataRecorder::CreatNewName(string filename,int which){
	size_t found = filename.find_first_of(".");;
	string newname;// = new char[index+6];//pacmann_a.s/pacman_00./pacman_01.
	newname.append(filename, 0, found+1);
	if(which==STEPS)
	newname.append("steps");
	else newname.append("results");
	return newname;
	
}

//This function gets the steps from file to  steps vector
void DataRecorder::PrintFilesToSteps(string filename) {
	ifstream myfile;
	int Vcounter = 0, i = 2;
	string fruitin, line, move;
	char* s, seps[] = " abcd", * token;
	myfile.open(filename, ios_base::in);
	if (!myfile.is_open())
	{
		std::cout << "Error with opening the file , probably the file is not exist... ";
		return;
	}
	getline(myfile, line);
	while (line.size() != 0)
	{
		s = new char[line.length() + 1];
		strcpy(s, line.c_str());
		token = strtok(s, seps);
		while (token != NULL)
		{
			move = token;
			GameMoves.push_back(move);
			token = strtok(NULL, seps);
		}
		delete[]s;
		getline(myfile, line);
		Vcounter++;
	}
	myfile.close();
}

//This function gets the steps from file to result vector
void DataRecorder::PrintRFileToResult(string filename) { 
	ifstream myfile;
	string  line, move,newname;
	newname.assign(CreatNewName(filename, RESULT));
	char* s, seps[] = " :", * token;
	myfile.open(newname, ios_base::in);
	if (!myfile.is_open())
	{
		std::cout << "Error with opening the file , probably the file is not exist... ";
		return;
	}
	getline(myfile, line);
	while (line.size() != 0)
	{
		s = new char[line.length() + 1];
		strcpy(s, line.c_str());
		token = strtok(s, seps);
		while (token != NULL)
		{
			move = token;
			result.push_back(move);
			token = strtok(NULL, seps);
		}
		delete[]s;
		getline(myfile, line);
	}
	myfile.close();
}
