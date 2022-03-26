#include "GameManeger.h"

//----------------------------------------RUN FUNCTIONS----------------------------------------

//This funcion  is for start the game from cmd/commandline 
void Game::WhichGameTostart(int argc, char* argv[])
{
	string* command = new  string[argc];
	for (int i = 1; i < argc; i++) command[i] = argv[i];
	switch (argc)
	{
	case 1:
		StartGame(false);
		break;
	case 2:
		if (command[1] == "-load")
			SimulateFromFile(false);

		else if ((command[1] == "-save") || (command[1] == "-save") && command[2] == "[-silent]") {
			StartGame(true);
		}
		else goto SWdefault;
		break;
	case 3:
		if (command[1] == "-load" && command[2] == "[-silent]")
			SimulateFromFile(true);
		else goto SWdefault;
		break;

	default:
	SWdefault:
		M.InputHelperMessage();
		exit(INVALID);
		break;
	}
	clear_screen();
	delete[] command;
}

//This function conduct the preparation for playing in savemode / regular mode 
void Game::StartGame(bool savingmode) {
	char x = 0;
	int i, j, selection = 0, GhostLevel = 0;
	bool WithColors = false,quited = false;
	if (!MapsDatabase.FindFilesInDictionary()) {return;}

	for (i = 0; i < MapsDatabase.GetDB_Size(); i++)
		MapsDatabase.get_Database()[i].map.SetLocationsForMap();
	while (x != '9')
	{
		quited = false;
		clear_screen();
		M.ShowMenu(MENU);
		std::cin >> x;
		if (!(x == '1' || x=='2' || x == '9' || x == '8'))
			M.CheckValidOption(x, MENU);
		if (x == '1') {
			if (M.PlayWithColors())
				WithColors = true;
			GhostLevel = M.SelectGhostLevel();
			for (j = 0; j < MapsDatabase.GetDB_Size(); j++)
			{
				this->run(WithColors,j,quited,GhostLevel,savingmode);
				if (quited) {
					j = MapsDatabase.GetDB_Size();
				}
				else M.MovingLevel();
			}
			if (!quited)M.ChampMessage();
		}
		else if (x == '2') {//play with map selectoin menu
			if (!savingmode) {
			if (M.PlayWithColors())
				WithColors = true;
				GhostLevel = M.SelectGhostLevel();
				selection = M.MapSelectionMenu(MapsDatabase);
				this->run(WithColors, selection, quited, GhostLevel, savingmode);
			}
			else { M.CantPlayMapSelInSavemodeAlert(); }
		}
		else if (x == '8')
			x=M.instrucions();
		else { 
			std::cout << "Goodbye !" << endl; 
		}
		WithColors = false;
		globalscore = 0;
		globallives = 3;
	}
}
 
//This funcion runs the game in save mode and in regular mode
void Game::run(bool WithColors,int Selection,bool &quited,int GhostLevel, bool savingmode)
{
	Board b = MapsDatabase.get_Database()[Selection].map;
	int GameMoves = 0,deathmoverecorder=0, GameBegun = 0, whyend, Gharrsize = b.GetGhostArrSize(), speedmode = 0;
	bool AteFruit = false;
	char key = 't', keyhelper = 0;
	Pacman c;
	Ghost Ghostarr[4];
	Fruit F(Color::WHITE);
	InitializeGame(c, Ghostarr, Gharrsize, b ,WithColors,F,GhostLevel,false);
	do {// p(Ascii 112) ends the loop
		hideCursor();
		if (CheckPlayerGhostCollision(c, Ghostarr, Gharrsize, b, WithColors, GhostLevel,false)){
			key = 's';
			if(savingmode==true)RcoredDeath(b,c, GameMoves);
			deathmoverecorder = 0;}
		if (_kbhit())key = _getch();
		if (key == ESC)//esc was pressed 
			M.PauseUnPauseFunc(key, keyhelper, b.GetLiveYCord(), b.GetLiveXCord());
		if (c.ValidKeys(key)){
			GameBegun = STARTED;
			if (key != ESC) { keyhelper = key; }
			c.Pacman_movment(key, c, b,WithColors , 0,savingmode);}
		else if (key != 's' && tolower(key) != EXITWITHP) //KEEP MOVING
			c.Pacman_movment(keyhelper, c, b ,WithColors , 0,savingmode);
		//---------------FRUIT IMPLEMENTATION---------------
		if(GameBegun != NOTSTARTED)
		AteFruit = F.FruitFunctionality(b, WithColors, c, Ghostarr, Gharrsize , "",savingmode);
		if (AteFruit == true)
			c.UpdateScore(c.Get_X_Pos(), c.Get_Y_Pos(),b, WithColors, AteFruit, F.GetFruitValue());
		//---------------Ghosts---------------
		++speedmode;
		if (key != ESC && GameBegun != NOTSTARTED && speedmode % 2 == 0) {
			GhostShellFunctionForMovment(Ghostarr, Gharrsize, c, b ,WithColors , 0 , 0,savingmode);
		}Sleep(180); 
		if (GameBegun != NOTSTARTED) {deathmoverecorder++;
			GameMoves++;}
	} while (tolower(key) != EXITWITHP && (b.GetScore()-globalscore) < b.GetScoreToWin()&& b.GetLives()!= 0);
		whyend = M.CheckWhyEndGame(key, b.GetScore(), b.GetScoreToWin(), b.GetLives());
		if (whyend == WONLEVEL) globalscore += b.GetScore();
		if(key==EXITWITHP) quited = true; 
		if (savingmode == true) { RecordScreenFinish(b, GameMoves);
			b.GetDataRecorderObject()->PrintToFilesShell(MapsDatabase.get_Database()[Selection].mapname);}
		b.Deletecopyarr();
}

//This funcion is a defult constractor
Game::Game()
{

}

//This funcioninitilaizing objects location and colors if demanded
void Game::InitializeGame(Pacman& player, Ghost *Gharr,int Gharrsize, Board& map, bool WithColors,Fruit& f,int GhostLevel,bool IsSilent)
{
	if (!IsSilent) {
		if (WithColors) {
			f.Set_GameObj_Color(Color::LIGHTGREEN);
			player.Set_GameObj_Color(Color::YELLOW);
			GhostColorInitializer(Gharr, Gharrsize, WithColors);
		}
		else {
			f.Set_GameObj_Color(Color::WHITE);
			player.Set_GameObj_Color(Color::WHITE);
			GhostColorInitializer(Gharr, Gharrsize, WithColors);
		}
	}
	else {
		map.SetSilence(true); f.SetSilence(true);
	}
	clear_screen();
	map.Creatcpy();
	map.SetScoreWithGlobal(globalscore);
	map.SetLivesWithGlobal(globallives);
	map.Printmap(WithColors,IsSilent);
	PacmanInitializer(player, map,IsSilent);
	GhostInitializer(Gharr,Gharrsize, map, GhostLevel,IsSilent);
}

//This funcion check id ghost hit pacman, if so pacman goes back to start(also ghosts) and loses life
bool Game::CheckPlayerGhostCollision(Pacman& player, Ghost* Ghostarr, int Gharrsize,Board& map,bool WithColors, int GhostLevel,bool issilent)
{
	for (int i = 0; i < Gharrsize; i++) {
		if (player.Get_X_Pos() == Ghostarr[i].Get_X_Pos() && player.Get_Y_Pos() == Ghostarr[i].Get_Y_Pos())
		{
			if(!issilent)M.GhostHitNotification(map.GetLiveYCord(), map.GetLiveXCord());
			DeleteGhosts(Ghostarr,Gharrsize,map, WithColors);
			player.DeletePrevLoc();
			map.SetLife(WithColors);
			--globallives;
			PacmanInitializer(player, map,issilent);
			GhostInitializer(Ghostarr, Gharrsize, map, GhostLevel,issilent);
			return true;
		}
	}
	return false;
}

//This function sets the pacman initial location on current map
void Game::PacmanInitializer(Pacman& player, Board& map,bool issilent) //זה הפאקמן  ואחריו זה הגוסט - להפוך לגנרי בהורשה
{
	if(issilent)player.SetSilence(true);
	player.Set_XandY_Pos(map.GetPacmanXCords(), map.GetPacmanYCords());
	player.Set_GameObj_Symbol('C');
	player.Draw_GameObj();
} 

//This function sets the ghosts initial location on current map
void Game::GhostInitializer(Ghost*Ghostarr, int Gharrsize, Board& map,int GhostLevel, bool issilent)
{
	for (int i = 0; i < Gharrsize; i++) {
		if(issilent)Ghostarr[i].SetSilence(true);
		Ghostarr[i].Set_XandY_Pos(map.GetGhostYCords(i), map.GetGhostXCords(i));
		Ghostarr[i].Set_GameObj_Symbol(234);
		Ghostarr[i].Draw_GameObj();
		switch (GhostLevel)
		{
		case 0:
			Ghostarr[i].Set_Ghost_Intellegence(Best);
			break;
		case 1:
			Ghostarr[i].Set_Ghost_Intellegence(Good);
			break;
		default://2
			Ghostarr[i].Set_Ghost_Intellegence(Novice);
			break;
		}
	}
}

//This function initial the ghosts colors
void Game::GhostColorInitializer(Ghost*Ghostarr, int Gharrsize, bool WithColor) {
	for (int i = 0; i < Gharrsize; i++) {
		if (WithColor) {
			switch (i)
			{
			case 0:
				Ghostarr[i].Set_GameObj_Color(Color::BROWN);
				break;
			case 1:
				Ghostarr[i].Set_GameObj_Color(Color::CYAN);
				break;
			case 2:
				Ghostarr[i].Set_GameObj_Color(Color::WHITE);
				break;
			case 3:
				Ghostarr[i].Set_GameObj_Color(Color::LIGHTMAGENTA);
				break;
			default:
				break;
			}
		}
		else Ghostarr[i].Set_GameObj_Color(Color::WHITE);
	}
}

//This function deletes the ghosts from thier locations on current map
void Game::DeleteGhosts(Ghost*Ghostarr, int Gharrsize, Board& map,bool WithColors)
{
	for (int i = 0; i < Gharrsize; i++)
	Ghostarr[i].DeletePrevLocGhostandFriut(map, WithColors);
}

//This function responsible for the ghost movment
void Game::GhostShellFunctionForMovment(Ghost*Ghostarr, int Gharrsize, Pacman& c, Board& map, bool WithColors ,  int load, int LoadDirection,bool savingmode) {
	for (int i = 0; i < Gharrsize; i++)
	{
		Ghostarr[i].GhostMove(map, WithColors, c, i, load, LoadDirection,savingmode);
	}
}

//This function conduct the preparation of loading all simulations 
void Game::SimulateFromFile(bool IsSilent)
{
	int lvl = 0;
	bool Nofiles = false;
	char s[MAXSIZE];
	ifstream myfile,resultfile;
	if (!MapsDatabase.FindFilesInDictionary()) {
		return;
	}
	for (int i = 0; i < MapsDatabase.GetDB_Size(); i++)
		MapsDatabase.get_Database()[i].map.SetLocationsForMap();
	if (system("dir *.steps /a-d/b> file_steps.txt")) {
		cout << "Error with opening the file , probably the files like *.steps is not exist...";
		exit(1);
	}
	myfile.open("file_steps.txt", ios_base::in);
	if (!myfile.is_open()) {
		cout << "Error with opening the file ";
		exit(1);
	}
	int NumOfFiles = FindNumOfStepFiles(myfile);
	while (myfile.getline(s,MAXSIZE) && (NumOfFiles != 0)/*&&(globallives!=0)*/) //SIMULATES ALL MAPS REGARDLESS OF LIVES
	{  
		MapsDatabase.get_Database()[lvl].map.GetDataRecorderObject()->PrintFilesToSteps(s); //create the vectors
		if(IsSilent)MapsDatabase.get_Database()[lvl].map.GetDataRecorderObject()->PrintRFileToResult(s);//create the result vector
		LoadSimulation(lvl ,false ,IsSilent);
		lvl++;
	}

	myfile.close();
}

//This funcion runs the game in load mode and in load silent mode
void Game::LoadSimulation(int level, bool WithColors, bool IsSilent)
{
	Board b = MapsDatabase.get_Database()[level].map;
	int Gharrsize = MapsDatabase.get_Database()[level].map.GetGhostArrSize(),
		deathsteps[3] = { 0 }, Dsize = 0, value, AppearX, AppearY, stepstilfinished = 0;
	char  key = 't';
	Pacman c; Ghost Ghostarr[4]; Fruit F(Color::WHITE); //game objects intialization
	vector<string>::iterator GameMoves = b.GetDataRecorderObject()->GetGameMovesVec().begin();
	InitializeGame(c, Ghostarr, Gharrsize, b, WithColors, F, FALSE, IsSilent);
	do {
		hideCursor();
		if (CheckPlayerGhostCollision(c, Ghostarr, Gharrsize, b, WithColors, 0, IsSilent))
		{
			deathsteps[Dsize] = stepstilfinished;
			globallives--;
			Dsize++;
		}
		if ((*GameMoves) == "P") {
			GameMoves++;
			key = (*GameMoves)[0];
			key = PacMovesFromChar(key);
			c.Pacman_movment(key, c, b, WithColors, TRUE, false);
			if (GameMoves != --(b.GetDataRecorderObject()->GetGameMovesVec().end()))
				GameMoves++;
		}
		//---------------FRUIT IMPLEMENTATION---------------
		if ((*GameMoves) == "Fi" || (*GameMoves) == "F" || (*GameMoves) == "Fx")
			EntireFruitSimulation(F, c, b, WithColors, GameMoves, AppearX, AppearY, value, 0);

		if (F.Get_X_Pos() == c.Get_X_Pos() && F.Get_Y_Pos() == c.Get_Y_Pos())
			c.UpdateScore(c.Get_X_Pos(), c.Get_Y_Pos(), b, WithColors, true, F.GetFruitValue());
		//---------------Ghosts---------------
		if ((*GameMoves) == "G")
			GhostStepsSimulation(GameMoves, Ghostarr, Gharrsize, c, b, WithColors);

		if (!IsSilent)Sleep(100);
		++stepstilfinished;

	} while (GameMoves != --(b.GetDataRecorderObject()->GetGameMovesVec().end()));
	M.CheckIfSimulatOver(GameMoves, b, IsSilent);
	globalscore += b.GetScore();
	if (IsSilent) { CheckIfSilentSucceed(b, M, stepstilfinished, deathsteps); }
	b.GetDataRecorderObject()->GetGameMovesVec().clear();
	b.GetDataRecorderObject()->GetResVec().clear();
	b.Deletecopyarr();
}

//This function checks if silent simulation was successful
void Game::CheckIfSilentSucceed(Board &map, Menu& M,int stepstilfinished,int deathsteps[3]) {
	vector<string>::iterator it = map.GetDataRecorderObject()->GetResVec().begin();
	char Case; int steps = 0,index = 0;
	bool fix = true;
	while ((it != --(map.GetDataRecorderObject()->GetResVec().end()))) {
		Case = (*it)[0];
		switch (Case)
		{
		case 'D':
			it++;
			steps= stoi((*it));
			if (steps != deathsteps[index])
				fix = false;
			index++;
			it++;
			break;
		case 'F':
			it++;
			steps = stoi((*it));
			if (steps = stepstilfinished + 1)stepstilfinished++;
			if (steps != stepstilfinished)
				fix = false;
			break; 
		}
	}
	if (fix == false) M.SilentMessege(false);
	else M.SilentMessege(true);
}

//This function convert direction if char from vector to int direction for ghosts 
Direction Game::DirectionFromVecChar(char direction)
{
	switch(direction){
	case(CharMoves::right_C):
		return Direction::right;
		break;
	case(CharMoves::left_C):
		return Direction::left;
		break;
	case(CharMoves::up_C):
		return Direction::up;
		break;
	case(CharMoves::down_C):
		return Direction::down;
		break;
	}
}

//This function convert direction if char from vector to int direction for pacman
char Game::PacMovesFromChar(char direction)
{
	switch (direction) {
	case(CharMoves::right_C):
		return Directions_p::right;
		break;
	case(CharMoves::left_C):
		return Directions_p::left;
		break;
	case(CharMoves::up_C):
		return Directions_p::up;
		break;
	case(CharMoves::down_C):
		return Directions_p::down;
		break;
	case(CharMoves::pac_stay_C):
		return Directions_p::stay;
	}
}

//This function operats the ghost steps for the loadmode and silent load mode
void Game::GhostStepsSimulation(vector<string>::iterator& GameMoves, Ghost* Ghostarr, int Gharrsize, Pacman& c, Board& b, bool WithColors)
{
	char ghostmove;
	//NOW GAMEMOVES HAS "G" IN IT , NEXT IS INDEX
	GameMoves++;
	int i = stoi(*GameMoves);
	GameMoves++; //NEXT IS THE MOVE
	ghostmove = (*GameMoves)[0];
	Ghostarr[i].GhostMove(b, WithColors, c, i, 1, (int)DirectionFromVecChar(ghostmove), false);
	if (GameMoves != --(b.GetDataRecorderObject()->GetGameMovesVec().end()))
		GameMoves++; //NEXT STEP IN GAMEMOVES
	if ((*GameMoves) == "G") //IF ANOTHER GHOST GO DO ITS MOVE AS WELL , Recursion untill no more ghosts..
		GhostStepsSimulation(GameMoves, Ghostarr, Gharrsize, c, b, WithColors);
}

//This function operats the fruit steps for the loadmode and silent load mode
void Game::EntireFruitSimulation(Fruit& F, Pacman& c, Board& b, bool WithColors, vector<string>::iterator& GameMoves, int& AppearX, int& AppearY, int& value, bool savingmode)
{
	static int StepsToEat=0,helper=0;
	if ((*GameMoves) == "Fi")
	{
		ExtractInfoFromVecTillMovement(b, GameMoves, F, value, AppearX, AppearY);
		helper++;
		F.Set_Fruit_In_Simulation(AppearX, AppearY, value);
	}
	if ((*GameMoves) == "F")
	{
			GameMoves++; //after F there is always a step
			F.Move_Slowly(b, WithColors, 1, (int)DirectionFromVecChar((*GameMoves)[0]), 0);
			if (GameMoves != --(b.GetDataRecorderObject()->GetGameMovesVec().end()))
				GameMoves++;
	}
	if ((*GameMoves) == "Fx")
	{
		F.DeleteFruit(b, WithColors, 1, false,false);
		if (GameMoves != --(b.GetDataRecorderObject()->GetGameMovesVec().end()))
			GameMoves++;
	}

}

//This function extracts the fruit moves from the vector
void Game::ExtractInfoFromVecTillMovement(Board& b, vector<string>::iterator& GameMoves, Fruit& F, int& value, int& AppearX, int& AppearY)
{
	//now the iterator points to Fi
	GameMoves++; //now to x
	AppearX = stoi((*GameMoves));
	GameMoves++;// now to y
	AppearY = stoi((*GameMoves));
	GameMoves++; // now to value
	value = stoi((*GameMoves));
	if (GameMoves != --(b.GetDataRecorderObject()->GetGameMovesVec().end()))
		GameMoves++; //next move in game moves
}

//----------------------------------------FILE FUNCTIONS----------------------------------------

//This function returns the number of steps files
int Game::FindNumOfStepFiles(ifstream& myfile)
{
	int counter = 0;
	char s[MAXSIZE];
	while (myfile.getline(s, 't')) {
		counter++;
	}
	myfile.clear();
	myfile.seekg(0);
	return counter;
}

//This function record death and print it into file
void Game::RcoredDeath(Board& b, Pacman& c, int moves) {
	b.GetDataRecorderObject()->GetResVec().push_back("D: ");
	b.GetDataRecorderObject()->GetResVec().push_back(to_string(moves));
}

//This function record finish and print it into file
void Game::RecordScreenFinish(Board& b, int moves) {
	b.GetDataRecorderObject()->GetResVec().push_back("F: ");
	b.GetDataRecorderObject()->GetResVec().push_back(to_string(moves));
}