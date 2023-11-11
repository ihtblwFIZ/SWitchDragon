#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>

#include "Constants.h"
#include "Moogi.h"

extern int gameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2];
extern int direction;
extern int stage;
extern int stageBestScore[5];
extern int speed;
extern int shield;
extern int fever[5];
extern Moogi* head;
extern Moogi* tail;
extern int curPosX, curPosY;

#endif