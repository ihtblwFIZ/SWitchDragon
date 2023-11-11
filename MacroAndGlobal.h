#ifndef __MACRO_AND_GLOBAL_H__
#define __MACRO_AND_GLOBAL_H__

#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "UserControl.h"
#include "MacroAndGlobal.h"
#include "OtherModule.h"

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACE 32

#define GBOARD_ORIGIN_X 4
#define GBOARD_ORIGIN_Y 2

typedef struct Moogi
{
	struct Moogi* left;
	struct Moogi* right;
	COORD position;
}Moogi;

int** gameBoardInfo;
int direction = 0;
int stage = -1;
int stageBestScore[5];
int speed = 20;
int shield = 0;
int fever[5] = { 0,0,0,0,0 };
Moogi* head;
Moogi* tail;

#endif