#include "Pacman.h"

//This function is a constructor
Pacman::Pacman(int x, int y, char c)
{
	this->Set_XandY_Pos(x, y);
	this->Set_GameObj_Symbol(c);
}
//This function is a destructor
Pacman::~Pacman()
{

}
//This function is empty ctor
Pacman::Pacman() {};

//------------------------------------------------------------------------------------

//This funcion manage the pacman movement
void Pacman::Pacman_movment(char direction, Pacman& p, Board& b, bool WithColors,int load,bool savingmode) const
{
	
	char input = 0;
	int x = this->Get_X_Pos();
	int y = this->Get_Y_Pos();
	direction = tolower(direction);
	if (load == 0)
	{
		if ((direction != '\0') && (savingmode)) {
			b.GetDataRecorderObject()->GetGameMovesVec().push_back("P");
			b.GetDataRecorderObject()->GetGameMovesVec().push_back(b.GetDataRecorderObject()->ConvertIputeToString(direction));
		}
	}
	switch (direction)
	{
	case Directions_p::right:
		if (!p.IsTunnelAhead(x, y, b,direction))
			x++;
		else x = 0;
		p.MovePlayer(x, y, b, p, direction, WithColors);
		break;
	case Directions_p::left:
		if (!p.IsTunnelAhead(x, y, b, direction))
			x--;
		else x = b.GetmapCols()-1;
		p.MovePlayer(x, y, b, p, direction, WithColors);
		break;
	case Directions_p::up:
		if (!p.IsTunnelAhead(x, y, b, direction))
			y--;
		else y = b.GetmapRows()-1;
		p.MovePlayer(x, y, b, p, direction, WithColors);
		break;
	case Directions_p::down:
		if (!p.IsTunnelAhead(x, y, b, direction))
			y++;
		else y = 0;
		p.MovePlayer(x, y, b, p,direction, WithColors);
		break;
	case Directions_p::stay://s = stop
		break;
	default:
		//KEEP MOVING SAME DIRECTION
		break;
	}
}

//This function checks if there is a tunnel ahead
int Pacman::IsTunnelAhead(int x,int y, Board& b,char dir)
{
	if (y+ BORDER_GAP ==b.GetmapRows()&&dir==Directions_p::down || y == 0&&dir == Directions_p::up
		|| x + BORDER_GAP == b.GetmapCols()&& dir == Directions_p::right|| x == 0&& dir == Directions_p::left)
		return 1;
	else return 0;
}

//This funcion responsible update 
void Pacman::UpdateScore(int x, int y, Board&  b, bool WithColors, bool PlayerAteFruit, int val)
{
		if (b.GetSymbol(x, y,false) == '.' && PlayerAteFruit == false)
		{
			b.SetArrCell(x, y);
			b.SetScore(WithColors, 0);
		}
		else if (PlayerAteFruit == true)
		{
			b.SetArrCell(x, y);
			b.SetScore(WithColors, val);
		}
}

//This funcion strats the movment process acorrding to Pacman_movment function inputs
void Pacman::MovePlayer(int x,int y,Board& b,Pacman& p,char direction ,bool WithColors)
{
	int TunnelExit, additionx = 0, additiony = 0;;
	if (!p.CheckIfWall(x, y, b))
	{
			this->ChangePosAndMakeMove(x, y,b,WithColors);
			p.UpdateScore(x, y, b, WithColors, false, 0);
	}
}

//This funcion checks if the user hits legal input
int Pacman::ValidKeys(char input)
{
	if (input == 'a' || input == 'd' || input == 'w' || input == 'x' || input == 's')
		return 1;
	else if (input == 'A' || input == 'D' || input == 'W' || input == 'X' || input == 'S')
		return 1;
	return 0;
}



