#ifndef _POSITION_H
#define _POSITION_H
//#include"General.h"
class Position
{
private:
	int X_Pos;
	int Y_Pos;

public:
	int Get_X_Pos() const;
	int Get_Y_Pos() const;
	void Set_XandY_Pos(int x, int y);
	~Position();

};
#endif // !_POSITION_



