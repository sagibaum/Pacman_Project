#include "Ghost.h"

//This funcion gets ghostintellegency level
Intellegence Ghost::Get_Ghost_Intellegence() const
{
	return this->Level;
}

//this function sets the intellegence of the ghost
void Ghost::Set_Ghost_Intellegence(Intellegence Level)
{
	this->Level = Level;
}

//This funcion is a constructor
Ghost::Ghost(int x, int y, char c, Intellegence Level)
{
	Set_Ghost_Intellegence(Level);
	this->Set_XandY_Pos(x, y);
	this->Set_GameObj_Symbol(c);
}

Ghost::Ghost() {} //empty ctor

//This funcion is a destructor
Ghost::~Ghost()
{

}

//------------------------------------------------

//This funcion manage the ghost movement
void Ghost::GhostMove(Board& b, bool WithColors, Pacman& C, int index , int load , int LoadDirection,bool savingmode)
{
	int x = this->Get_X_Pos(), y = Get_Y_Pos();
	Direction direction = Direction::down;
	//Here Implementation of different Intellegence algorithms of ghosts , based on which ghost it is
	if (load == 0)
	{
		if (this->Get_Ghost_Intellegence() == Best)
			direction = BestGhostAlgorithm(b, C);
		if (this->Get_Ghost_Intellegence() == Good)
			direction = GoodGhostAlgorithm(b, WithColors, C);
		if (this->Get_Ghost_Intellegence() == Novice)
			direction = NoviceGhostAlgorithm();
		if (savingmode == true) {
			b.GetDataRecorderObject()->GetGameMovesVec().push_back("G");
			b.GetDataRecorderObject()->GetGameMovesVec().push_back(to_string(index)); // 0 1 2 3
			b.GetDataRecorderObject()->GetGameMovesVec().push_back(b.GetDataRecorderObject()->ConvertIputeToString((int)direction));
		}
	}
	else direction = (Direction)LoadDirection;
	switch (direction)
	{
	case Direction::right:
		x++;
		this->ChangePosAndMakeMove(x, y, b, WithColors);
		break;
	case Direction::left:
		x--;
		this->ChangePosAndMakeMove(x, y, b, WithColors);
		break;
	case Direction::up:
		y--;
		this->ChangePosAndMakeMove(x, y, b, WithColors);
		break;
	case Direction::down:
		y++;
		this->ChangePosAndMakeMove(x, y, b, WithColors);
		break;
	}
}

//This funcion responsible to move the ghost to specified location 
void Ghost::ChangePosAndMakeMove(int x, int y, Board& b, bool WithColors)
{
	if (!this->CheckLimits(x, y, b))
	{
		this->DeletePrevLocGhostandFriut(b, WithColors);
		this->Set_XandY_Pos(x, y);
		this->Draw_GameObj();
	}
}

//worse ghost movement based on random every~20 moves
Direction Ghost::NoviceGhostAlgorithm()
{
	static int direction = 0;
	static int Moves = 0;
	if (Moves % NoveMoveEvery == 0)
		direction = rand() % MoveAmountAvailable; // 0 / 1 / 2 / 3
	else Moves++;
	return (Direction)direction;
}

//good ghost algo based on radom move every ~14 moves , else best ghost algo
Direction Ghost::GoodGhostAlgorithm(Board& b, bool WithColors, Pacman C)
{
	static int About20Moves = rand() % GoodGhostRandMoveRange + GoodGhostRandMoveInitial; // 16 17 18 19 20 
	static int FiveMoves = 1; static int direction = rand() % MoveAmountAvailable; static int Moves = 0;
	if (Moves % About20Moves == 0) // in this case ghost needs to change to a random direction and stick with it 5 times
	{
		if (FiveMoves % GoodGhost5MoveCount != 0) //needs to stay with its move
		{
			FiveMoves++;
		}
		else {
			direction = rand() % MoveAmountAvailable; Moves++; //calculates the next time direction , and increases moves to start counting
			About20Moves = rand() % GoodGhostRandMoveRange + GoodGhostRandMoveInitial; // if this random 20 moves has gotten to calculate the next random 20 move
		}
	}
	else {
		direction = (int)BestGhostAlgorithm(b, C); //otherwise its a smart ghost
		Moves++;
	}//if the 5 moves not being smart finished increase the moves untill the next about 20
	return (Direction)direction;
}

//this calculates the min amount of tiles from certain position to the pacman
int Ghost::minDistance(int x, int y, Board& map, const Pacman& pacman, int LastMin)
{
	QueueNode source(0, 0, 0);
	int** visited = VisitedArrAndSetWalls(map.GetmapRows(), map.GetmapCols(), map);

	source.Set_Row(y); //receiving the starting location to be the thoretical next ghost move
	source.Set_Col(x);

	// applying BFS on matrix cells starting from source
	queue<QueueNode> q;
	q.push(source);
	visited[source.Get_Row()][source.Get_Col()] = 1;
	while (!q.empty()) {
		QueueNode p = q.front();
		q.pop();

		// Destination found;
		if (p.Get_Row() == pacman.Get_Y_Pos() && p.Get_Col() == pacman.Get_X_Pos())
		{
			FreeVisitedArr(map.GetmapRows(), visited);
			return p.Get_Dist();
		}
		//-------------------
		if (p.Get_Row() - 1 >= 0 &&
			visited[p.Get_Row() - 1][p.Get_Col()] == 0) {// moving up
			q.push(QueueNode(p.Get_Row() - 1, p.Get_Col(), p.Get_Dist() + 1));
			visited[p.Get_Row() - 1][p.Get_Col()] = 1;
		}
		if (p.Get_Row() + 1 < map.GetmapRows() &&
			visited[p.Get_Row() + 1][p.Get_Col()] == 0) {// moving down
			q.push(QueueNode(p.Get_Row() + 1, p.Get_Col(), p.Get_Dist() + 1));
			visited[p.Get_Row() + 1][p.Get_Col()] = 1;
		}
		if (p.Get_Col() - 1 >= 0 &&
			visited[p.Get_Row()][p.Get_Col() - 1] == 0) {// moving left
			q.push(QueueNode(p.Get_Row(), p.Get_Col() - 1, p.Get_Dist() + 1));
			visited[p.Get_Row()][p.Get_Col() - 1] = 1;
		}
		if (p.Get_Col() + 1 < map.GetmapCols() &&
			visited[p.Get_Row()][p.Get_Col() + 1] == 0) { // moving right
			q.push(QueueNode(p.Get_Row(), p.Get_Col() + 1, p.Get_Dist() + 1));
			visited[p.Get_Row()][p.Get_Col() + 1] = 1;
		}
	}
	FreeVisitedArr(map.GetmapRows(), visited);
	return LastMin; //if no way is found return the last minimum value
}

//helper matrix to bfs search algo and wall initialization 
int** Ghost::VisitedArrAndSetWalls(const int rows, const int cols, Board& map) {
	int** arr = new int* [rows];
	for (int i = 0; i < rows; ++i) { //initialize helper matrix
		arr[i] = new int[cols];
		for (int j = 0; j < cols; ++j) {
			arr[i][j] = 0;
		}
	}
	for (int i = 0; i < map.GetmapRows(); i++) {
		for (int j = 0; j < map.GetmapCols(); j++)
		{
			if (map.GetSymbol(j, i,false) == '#') //set walls to "visited"
				arr[i][j] = 1;
			else
				arr[i][j] = 0;
		}
	}
	return arr;
}

//releasing the helper matrix
void Ghost::FreeVisitedArr(const int height, int** visited) {
	for (int i = 0; i < height; ++i) { //delete helper matrix
		delete[] visited[i];
	}
}

//best ghost algorithm , calculates from every move possible and takes the direction of the minimal amount of steps
Direction Ghost::BestGhostAlgorithm(Board& b, Pacman C)
{
	int MinDistance = minDistance(Get_X_Pos(), Get_Y_Pos(), b, C, b.GetmapCols() * b.GetmapRows()); //number of tiles from this specific pixel
	//the min distance will always be smaller then all the rows * all the cols , initial value to be changed in this func
	Direction NextStep = Direction::up;
	if (CheckLimits(Get_X_Pos(), Get_Y_Pos() - 1 , b) == 0)
		if (CheckIfWall(Get_X_Pos(), Get_Y_Pos() - 1, b) == 0
			&& minDistance(Get_X_Pos(), Get_Y_Pos() - 1, b, C, MinDistance) < MinDistance) //this is the case for up
		{//basically if next theoretical place isnt a wall , and the distance is smaller then before use it
			NextStep = Direction::up;
			MinDistance = minDistance(Get_X_Pos(), Get_Y_Pos() - 1, b, C, MinDistance);
		}
	if (CheckLimits(Get_X_Pos(), Get_Y_Pos() + 1, b) == 0)
		if (CheckIfWall(Get_X_Pos(), Get_Y_Pos() + 1, b) == 0 && minDistance(Get_X_Pos(), Get_Y_Pos() + 1, b, C, MinDistance) < MinDistance) //this is the case for down
		{
			NextStep = Direction::down;
			MinDistance = minDistance(Get_X_Pos(), Get_Y_Pos() + 1, b, C, MinDistance);
		}
	if (CheckLimits(Get_X_Pos() + 1, Get_Y_Pos(), b) == 0)
		if (CheckIfWall(Get_X_Pos() + 1, Get_Y_Pos(), b) == 0 
			&& minDistance(Get_X_Pos() + 1, Get_Y_Pos(), b, C, MinDistance) < MinDistance) //this is the case for right
		{
			NextStep = Direction::right;
			MinDistance = minDistance(Get_X_Pos() + 1, Get_Y_Pos(), b, C, MinDistance);
		}
	if (CheckLimits(Get_X_Pos() - 1, Get_Y_Pos(), b) == 0)
		if (CheckIfWall(Get_X_Pos() - 1, Get_Y_Pos(), b) == 0 
			&& minDistance(Get_X_Pos() - 1, Get_Y_Pos(), b, C, MinDistance) < MinDistance) //this is the case for left
		{
			NextStep = Direction::left;
			MinDistance = minDistance(Get_X_Pos() - 1, Get_Y_Pos(), b, C, MinDistance);
		}

	return NextStep;
}