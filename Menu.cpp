#include "Menu.h"

// This funcion navigate the user in the maps database
int Menu::MapSelectionMenu(BoardDataBase &Db)const
{
	char choice;
	int out;
	MapSelectionMenuprinter(Db.GetDB_Size(),Db);
	std::cin >> choice;
	while ((choice- CONVERTCHARTOINT) > Db.GetDB_Size() || (choice- CONVERTCHARTOINT) <= 0  /*!isdigit(choice)*/) {
		while (getchar() != '\n') {}

		MapSelectionMenuprinter(Db.GetDB_Size(), Db);
		std::cout << "Please enter number between 1 to "<< Db.GetDB_Size()<<"!" << endl;
		std::cin >> choice;
	}
	clear_screen();
	out = choice - CONVERTCHARTOINT-1;
	return out;
}

// This funcion asks the user for ghost level he wants to play
int Menu::SelectGhostLevel()const {
	char level; 
	cout << " ____________________________________________________________" << endl;
	cout << "|                                                            |" << endl;
	cout << "|    Please choose ghost level:                              |" << endl;
	cout << "|                                                            |" << endl;
	cout << "|    1 - Hard                                                |" << endl;
	cout << "|    2 - Normal                                              |" << endl;
	cout << "|    3 - Easy                                                |" << endl;
	cout << "|____________________________________________________________|" << endl;
	std::cin >> level;
	while ((level - CONVERTCHARTOINT) > 3 || (level - CONVERTCHARTOINT) <= 0) {
		while (getchar() != '\n') {}
		std::cout << "Please enter number between 1 to 3 !" << endl;
		std::cin >> level;
	}
	clear_screen();
		return (level - CONVERTCHARTOINT - 1);
}

// This funcion print the maps names
void Menu::MapSelectionMenuprinter(int dbsize , BoardDataBase& Db)const {
	
	
	clear_screen();
	cout << " ____________________________________________________________" << endl;
	cout << "|                                                            |" << endl;
	cout << "|    Please select one of the following options:             |" << endl;
	cout << "|                                                            |" << endl;
	for (int i = 0; i < dbsize; i++) 
	cout << "|    "<< i + 1  << " - Start a new game with map " << Db.getRawFileName(i) <<"          |" << endl;
	cout << "|____________________________________________________________|" << endl;
}

// This funcion asks the user if he wants to play with colors
int Menu::PlayWithColors(){
	char choice;
	clear_screen();
	cout << " ____________________________________________________________" << endl;
	cout << "|                                                            |" << endl;
	cout << "|    Please select one of the following options:             |" << endl;
	cout << "|                                                            |" << endl;
	cout << "|    0 - Play without colors                                 |" << endl;
	cout << "|    1 - Play with colors                                    |" << endl;
	cout << "|____________________________________________________________|" << endl;
	std::cin >> choice;
	while ((choice - CONVERTCHARTOINT) != 0 && (choice - CONVERTCHARTOINT) != 1) {
		while (getchar() != '\n') {}
		std::cout << "Please enter number enter 0 or 1!!" << endl;
		std::cin >> choice;
	}
	clear_screen();
	return (choice - CONVERTCHARTOINT);
}

//This funcion prints the menu of the game
void Menu::ShowMenu(int From)const {
	hideCursor();
	setTextColor(Color::WHITE);

	if (From == MENU)
	{
		cout << " ____________________________________________________________" << endl;
		cout << "|                   Hello and welcome!                       |" << endl;
		cout << "|                                                            |" << endl;
		cout << "|    Please select one of the following options:             |" << endl;
		cout << "|                                                            |" << endl;
		cout << "|    1 - Start a new game by defult levels                   |" << endl;
		cout << "|    2 - Start a new game by selecting map                   |" << endl;
		cout << "|    8 - Present instructions and keys                       |" << endl;
		cout << "|    9 - EXIT                                                |" << endl;
		cout << "|____________________________________________________________|" << endl;
	}
	else {
		cout << " ____________________________________________________________" << endl;
		cout << "|                   Hello and welcome!                       |" << endl;
		cout << "|                                                            |" << endl;
		cout << "|    Please select one of the following options:             |" << endl;
		cout << "|                                                            |" << endl;
		cout << "|    1 - Start a new game                                    |" << endl;
		cout << "|    9 - EXIT                                                |" << endl;
		cout << "|____________________________________________________________|" << endl;
	}
}

//This funcion prints the instructions of the game--להעביר למחלקת MAIN
char Menu::instrucions() const
{
	char x;
	clear_screen();
	cout << " ____________________________________________________________" << endl;
	cout << "|                 WELCOME TO THE PACMAN GAME !               |" << endl;
	cout << "|                                                            |" << endl;
	cout << "|                         The keys:                          |" << endl;
	cout << "|                         ---------                          |" << endl;
	cout << "|                     LEFT   |a| or |A|                      |" << endl;
	cout << "|                     RIGHT  |d| or |D|                      |" << endl;
	cout << "|                     UP     |w| or |W|                      |" << endl;
	cout << "|                     DOWN   |x| or |X|                      |" << endl;
	cout << "|                     STAY   |s| or |S|                      |" << endl;
	cout << "|                     FINISH |p| or |P|                      |" << endl;
	cout << "|                     PAUSE  |ESC|                           |" << endl;
	cout << "|                                                            |" << endl;
	cout << "|                         How To Play:                       |" << endl;
	cout << "|                         ------------                       |" << endl;
	cout << "|  Use the keys listed above to collect all the points (.).  |" << endl;
	cout << "|  Avoid the Ghosts! If a ghost catches you you lose 1 life. |" << endl;
	cout << "|  You have 3 lives at the start of each game.               |" << endl;
	cout << "|  If you lose all 3 lives then GAME OVER!                   |" << endl;
	cout << "|  Fruits will add you points according to their value.      |" << endl;
	cout << "|  If you manage to collect all the points (.) without dying |" << endl;
	cout << "|  YOU WIN! Have fun!!!                                      |" << endl;
	cout << "|                                                            |" << endl;
	cout << "|               enter 1 or 2 To Play , 9 To Exit             |" << endl;
	cout << "|____________________________________________________________|" << endl;
	cin >> x;
	return x;
}

//This funcion checks if the input inserted in the menu is legal
void Menu::CheckValidOption(char& x, int From) 
{
	clear_screen();
	cout << "invalid option!" << endl;
	if (From == MENU)
		ShowMenu(MENU);
	else ShowMenu(INSTRUCTIONS);
	getchar();
	cin >> x;

	/*-------*/
	if (From == MENU)
	{
		while (!(x == '1' || x == '9' || x == '8')) {
			clear_screen();
			cout << "invalid option!" << endl;
			ShowMenu(MENU);
			getchar();
			cin >> x;
		}
	}
	else while (!(x == '1' || x == '9')) {
		clear_screen();
		cout << "invalid option!" << endl;
		ShowMenu(INSTRUCTIONS);
		getchar();
		cin >> x;
	}
}

//This funciont checks why the game ended , and prints massage acorrding to the reason 
int Menu::CheckWhyEndGame(char key, int score,int scoretowin,int lives)const
{
	setTextColor(Color::WHITE);
	clear_screen();
	if (lives == 0) {
		cout << " ____________________________________________________________" << endl;
		cout << "|                                                            |" << endl;
		cout << "|        You have lost all of your lives, GAME OVER!         |" << endl;
		cout << "|____________________________________________________________|" << endl;
	}
	else if (score >= scoretowin) {
		cout << " ____________________________________________________________" << endl;
		cout << "|                                                            |" << endl;
		cout << "|                  You have won the level!                   |" << endl;
		cout << "|____________________________________________________________|" << endl;
		return WONLEVEL;
	}
	else//(key == EXITWITHP)
	{
		cout << " ____________________________________________________________" << endl;
		cout << "|                                                            |" << endl;
		cout << "|                    Thanks for playing!!                    |" << endl;
		cout << "|____________________________________________________________|" << endl;
	}
	cout << "Press any key to coninue..." << endl;
	Sleep(800);
	while (!_kbhit());
	_flushall();
	return QUITGAME;
}

//This funcion alart the player when he hits a ghost
void Menu::GhostHitNotification(int LiveYCord, int LiveXCord)
{
	setTextColor(Color::WHITE);
	gotoxy((LiveYCord - Ycordcorrection), (LiveXCord + Xcordcorrection));
	cout << "YOU HIT A GHOST!" << endl;
	Sleep(800);
	gotoxy((LiveYCord - Ycordcorrection), (LiveXCord + Xcordcorrection));
	cout << "                " << endl;
}

//This funcion pauses/unpauses the game if user ask for 
void Menu::PauseUnPauseFunc(char& key, char keyreminder, int LiveYCord, int LiveXCord)
{
	setTextColor(Color::WHITE);
	gotoxy((LiveYCord - Ycordcorrection), (LiveXCord + Xcordcorrection));
	gotoxy((LiveYCord - Ycordcorrection), (LiveXCord + Xcordcorrection));
	cout << "PAUSED,ESC TO PLAY" << endl;
	do
	{
		_kbhit();
		key = _getch();
	} while (key != ESC);
	key = keyreminder;//resume game
	gotoxy((LiveYCord - Ycordcorrection), (LiveXCord + Xcordcorrection));
	cout << "                   ";
}

//This funcion prints winning message 
void Menu::ChampMessage() {
	clear_screen();
	cout << " ____________________________________________________________" << endl;
	cout << "|                                                            |" << endl;
	cout << "|                 You have won the game!!!                   |" << endl;
	cout << "|____________________________________________________________|" << endl;
	Sleep(1500);
}

//This funcion prints moving level message
void Menu::MovingLevel() {
	cout << "Press any key to continue to the next level "<<endl;
	while (!_kbhit());
	clear_screen();
}

//This funcion prints a helper message to user about how to operate the game from cmd
void Menu::InputHelperMessage() {
	cout << " ____________________________________________________________" << endl;
	cout << "|                   Incorrect input  !                       |" << endl;
	cout << "|                                                            |" << endl;
	cout << "|    Please select one of the following options:             |" << endl;
	cout << "|                                                            |" << endl;
	cout << "|    1 - Load mode: Enter please pacman.exe -load            |" << endl;
	cout << "|    2 - Save mode: Enter please pacman.exe -save            |" << endl;
	cout << "|    3 - Load mode: Enter please pacman.exe -load [-silent]  |" << endl;
	cout << "|                                                            |" << endl;
	cout << "|   Note!: Entering pacman.exe -save [-silent] will get you  |" << endl;
	cout << "|       to save mode                                         |" << endl;
	cout << "|____________________________________________________________|" << endl;
}

//This funcion checks why simulation over and prunts a message if it goes correctly
bool Menu::CheckIfSimulatOver(vector<string>::iterator& GameMoves, Board& map,bool IsSilent) {
	bool end=false;
	if (GameMoves == --(map.GetDataRecorderObject()->GetGameMovesVec().end()))
	{
		if (!IsSilent) {
			clear_screen();
			cout << "Simulation done successfuly!\n";
			Sleep(1500);
		}
		return end;
	}
	else return false;
}

//This funcion prints message acorrding to silent simulation results
void Menu::SilentMessege(bool IsSucceed) {
	clear_screen();
	if (IsSucceed) 
		cout << "Silent Simulation finished Successfully\n";
	else cout << "Silent Simulation faild!\n";
	Sleep(1500);
	clear_screen();
}

//This funcion prints user notification about running a simulation not part of story mode!
void Menu::CantPlayMapSelInSavemodeAlert()
{
	cout << " ____________________________________________________________" << endl;
	cout << "|                                                            |" << endl;
	cout << "|                           !Note!                           |" << endl;
	cout << "|                                                            |" << endl;
	cout << "|   You cant play this option in save mode ,Only story mode! |" << endl;
	cout << "|____________________________________________________________|" << endl;
	Sleep(2000);
	clear_screen();
}