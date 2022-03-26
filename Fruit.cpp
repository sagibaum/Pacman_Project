#include "Fruit.h"

//This Function returns fruit value
	int Fruit::GetFruitValue()const
	{
		return (int)this->value;
	}

	//This Function checks if fruit on board
	bool Fruit::IsFruitOnBoard()const
	{
		return this->onboard;
	}
	//-----------------------------------------------------------

	//This Function set fruit value
	void Fruit::Set_Fruit_Value(enum value val)
	{
		value = val;
		this->Set_GameObj_Symbol((int)value + INTTOASCII);
	}

	//This Function sets fruit values in simulation
	void Fruit::Set_Fruit_In_Simulation(int x , int y , int value)
	{
		Set_XandY_Pos(x, y);
		Set_Fruit_Value(enum value(value));
		Draw_GameObj();
		Set_Fruit_OnBoard(true);
	}

	//This Function set the fruit color 
	Fruit::Fruit(Color c)
	{
		this->Set_GameObj_Color(c);
	}

	//This Function sets the boolean value of the fruit
	void Fruit::Set_Fruit_OnBoard(bool change)
	{
		this->onboard = change;
	}

	//This Function is dtor
	Fruit::~Fruit()
	{

	}

	//This Function is empty ctor
	Fruit::Fruit()
	{

	}

	//This function is shell function that responsible for the fruit functionallity
	bool Fruit::FruitFunctionality(Board& b, bool WithColors,Pacman& C, Ghost *Ghostarr,int Gharrsize, string currChar,bool savingmode)
	{       
		static int AppearTime = (rand() % APPERATIMERANGE) + APPERATIMEMOVE;
		static int Moves = 0;
		bool PlayerAteFruit = false;
		
			if (this->IsFruitOnBoard() == false && AppearTime == Moves)
			{//in this case the fruit is not on board
				this->GiveFruitValue();
				this->AppearRandomly(b, WithColors, C, Ghostarr, Gharrsize , AppearTime,savingmode);
				this->Draw_GameObj();
				AppearTime = (rand() % APPERATIMERANGE) + APPERATIMEMOVE; Moves = 0;
			}//fruit needs to appear in a random amount of time
			else if (this->IsFruitOnBoard() == false) Moves++;
		if (this->IsFruitOnBoard() == true) // in this case he is on board , he needs to move slowly until he meets pacman , a ghost , or time runs out
		{
			PlayerAteFruit = FruitBehaviorOnScreen(b, WithColors, C,Ghostarr,Gharrsize,savingmode);
		}
		return PlayerAteFruit;
	}

	//This function randomly sets the value of the fruit
	void Fruit::GiveFruitValue()
	{
		int fruitval = (rand() % FRUITVALUERANGE + FRUITVALNUM);
		if (fruitval == 5) this->Set_Fruit_Value(five);
		if (fruitval == 6) this->Set_Fruit_Value(six);
		if (fruitval == 7) this->Set_Fruit_Value(seven);
		if (fruitval == 8) this->Set_Fruit_Value(eight);
		if (fruitval == 9) this->Set_Fruit_Value(nine);
	}

	//This function changes the location of the fruit onscreen
	void Fruit::ChangePosAndMakeMove(int x, int y, Board& b, bool WithColors)
		{ //POLYMORPHISM 
		if (!this->CheckLimits(x, y, b))
			{
			this->DeletePrevLocGhostandFriut(b, WithColors);
			this->Set_XandY_Pos(x, y);
			this->Draw_GameObj();
			}
		}

	//This function randomly chooses the location where the fruit appears
	void Fruit::AppearRandomly(Board& b, bool WithColors, Pacman& C, Ghost* Ghostarr, int Gharrsize ,int AppearTime,bool savingmode)
	{
		//vector <string> out = b.GetDataRecorderObject().GetFruitVec();
		int randx, randy;
		while (this->IsFruitOnBoard() == false)
		{
			randx = (rand() % b.GetmapCols()); randy = (rand() % b.GetmapRows());
			if (this->CheckLimits(randx, randy, b) == 0 && randx != C.Get_X_Pos() && randy != C.Get_Y_Pos()
				&& this->FruitAnyGhostHit(randx, randy, Ghostarr, Gharrsize) == 1 && randx < strlen(b.GetRowPointer(randy)))
				if(b.GetSymbol(randx, randy,true) != '%')//if not wall , or not fruit accessible
			{ //drop the fruit if it doesnt touch the  walls , pacman , or the ghosts
				this->Set_XandY_Pos(randx, randy);
				this->Set_Fruit_OnBoard(true);
				if (savingmode == true) {
					b.GetDataRecorderObject()->GetGameMovesVec().push_back("Fi"); //stand for initialization
					b.GetDataRecorderObject()->GetGameMovesVec().push_back(to_string(this->Get_X_Pos()));
					b.GetDataRecorderObject()->GetGameMovesVec().push_back(to_string(this->Get_Y_Pos()));
					b.GetDataRecorderObject()->GetGameMovesVec().push_back(to_string(GetFruitValue()));
				}
			}
		}
	}

//This function controls the movement and checks collision with the ghosts / pacman
//also randomly calculates the disappearance time of the fruit
bool Fruit::FruitBehaviorOnScreen(Board& b, bool WithColors, Pacman& C, Ghost* Ghostarr, int Gharrsize,bool savingmode)
{
	bool PlayerAteFruit = false;
	static int SomeTime = (rand() % FRUITDISSAPEARRANGE) + FRUITDISSAPEARMOVE;
	static int TimeCounter = 0;
	if (TimeCounter != SomeTime)
	{
		this->Move_Slowly(b, WithColors, 0, 0, savingmode); //PROBLEM - NEED
		for (int i = 0; i < Gharrsize; i++)
		{
			if (this->FruitHitAGhost(Ghostarr[i]) == 1) { 
				b.GetDataRecorderObject()->GetGameMovesVec().push_back("Fx"); //time to die
				this->DeleteFruit(b, WithColors , 0 , false,savingmode); 
				Ghostarr[i].Draw_GameObj();
			}
		}//fruit is deleted if it meets a ghost
		if (this->Get_X_Pos() == C.Get_X_Pos() && this->Get_Y_Pos() == C.Get_Y_Pos())
		{
			PlayerAteFruit = true;
			this->DeleteFruit(b, WithColors , 0 , true,savingmode);
			C.Draw_GameObj();
		}
		TimeCounter++;
	}
	else
	{
		b.GetDataRecorderObject()->GetGameMovesVec().push_back("Fx"); //time to die
		this->DeleteFruit(b, WithColors , 0 , false,savingmode);
		SomeTime = (rand() % FRUITDISSAPEARRANGE) + FRUITDISSAPEARMOVE; //next someTime randomizer
		TimeCounter = 0;            //reinitialize timer counter
	}
	return PlayerAteFruit;
}

//This function returns 1 if the fruit doesnt touch ANY GHOST
bool Fruit::FruitAnyGhostHit(int x, int y, Ghost* Ghostarr, int Gharrsize)
{ 
	for (int i = 0; i < Gharrsize; i++)
	{
		if (this->FruitHitAGhost(Ghostarr[i]) == 0)
			return true;
	}
	 return false;
} 

//This function controls the movement fruit, also moves in a slow order
bool Fruit::Move_Slowly(Board& b, bool WithColors , int LoadMode , int LoadModeDirection , bool savingmode)
{
	bool FruitMoved = false;
	int x = this->Get_X_Pos(), y = this->Get_Y_Pos(), direction;
	static int MoveCounter = 0;
	if (MoveCounter == SLOWMOVEVAL || LoadMode != 0)
	{
		MoveCounter = 0;
		if (LoadMode == 0) //saving mode
		{
			direction = rand() % 4; // 0 / 1 / 2 / 3
			EnterSlowMovementIntoLoadVector(b, direction); //every nine steps in load mode
		}
		else direction = LoadModeDirection;
		switch (direction)
		{
		case 0: // Moves right
			x++;
			this->ChangePosAndMakeMove(x, y, b, WithColors);
			break;
		case 1: // Moves left
			x--;
			this->ChangePosAndMakeMove(x, y, b, WithColors);
			break;
		case 2: // Moves up
			y--;
			this->ChangePosAndMakeMove(x, y, b, WithColors);
			break;
		case 3: // Moves down
			y++;
			this->ChangePosAndMakeMove(x, y, b, WithColors);
			break;
		}
		FruitMoved = true;
	}
	else MoveCounter++;
	return FruitMoved;
}

//This function delets the fruit 
void Fruit::DeleteFruit(Board& b, bool WithColors , int LoadMode , bool PlayerAteFruit,bool savingmode)
{
	this->DeletePrevLocGhostandFriut(b, WithColors);
	this->Set_XandY_Pos(0, 0);
	this->Set_Fruit_OnBoard(false);
}

//This function returns 0 if the fruit doesnt touch A GHOST , return 1 if it is touching!
bool Fruit::FruitHitAGhost(Ghost& AnyGhost)
{ 
	if (this->Get_X_Pos() != AnyGhost.Get_X_Pos()   //if the x is different or the y is differnt its not touching
		|| this->Get_Y_Pos() != AnyGhost.Get_Y_Pos())  //doesnt hit ghost x
		return 0;
	else return 1;
} 

//This function prints to file the moves of a fruit accordind to direction
void Fruit::EnterSlowMovementIntoLoadVector(Board& b, int direction)
{
	switch (direction)
	{
	case 0: // Moves right
		b.GetDataRecorderObject()->GetGameMovesVec().push_back("F");
		b.GetDataRecorderObject()->GetGameMovesVec().push_back("R");
		break;
	case 1: // Moves left
		b.GetDataRecorderObject()->GetGameMovesVec().push_back("F");
		b.GetDataRecorderObject()->GetGameMovesVec().push_back("L");
		break;
	case 2: // Moves up
		b.GetDataRecorderObject()->GetGameMovesVec().push_back("F");
		b.GetDataRecorderObject()->GetGameMovesVec().push_back("U");
		break;
	case 3: // Moves down
		b.GetDataRecorderObject()->GetGameMovesVec().push_back("F");
		b.GetDataRecorderObject()->GetGameMovesVec().push_back("D");
		break;
	}
}
