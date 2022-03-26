#ifndef _GENERAL_
#define _GENERAL_
#define _CRT_SECURE_NO_WARNINGS
#define ESC 27
#define CONVERTCHARTOINT 48

using namespace std;

#include "Colors.h"
#include <process.h>
#include <stdlib.h>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include<iostream>
#include<string.h>
#include<stdbool.h>
#include<fstream>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

void gotoxy(int x, int y);
void setTextColor(Color);
void hideCursor();
void clear_screen();
#endif // !_GENERAL_
