#ifndef _GAMEOBJ_H
#define _GAMEOBJ_H
#include"General.h"
#include "Colors.h"
#include"Position.h"
#include "Board.h"
class GameObj
{
public:
	~GameObj();
	void Draw_Obj(char ch)const;
	void Set_Positiot_cor(int x, int y);
	void DeletePrevLoc(GameObj& Object)const;
	void SetObjPosAndMakeMove(int x, int y, GameObj& Object)const;
	void Object_movment(char direction, GameObj& Object) const;
private:
	Color color;
	Position Pos;
	char Symbol;
};
#endif // !_GAMEOBJ_



