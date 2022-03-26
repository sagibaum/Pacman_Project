//מיקום של אובייקט כלשהו במסך, תכיל כנראה פונקציה לתזוזה במסך
#include"Position.h"

//This function returns the x cord
int Position::Get_X_Pos() const
 {
	 return X_Pos;
 }
//This function returns the y cord
int Position::Get_Y_Pos() const
{
	return Y_Pos;
}
//This function sets x cord and y cord
void Position::Set_XandY_Pos(int x, int y) {
	this->X_Pos = x;
	this->Y_Pos = y;
}
//This function is dtor
Position::~Position()
{

}