//Header file for Game by Samuel Briones-Plascencia

#ifndef GAME_H
#define GAME_H
#include "Settings.h"
#include "Board.h"

HANDLE *Game(PLAYER *p1, PLAYER *p2, int AI_choice);

int winCon(BOARD *board, PLAYER *p1, PLAYER *p2);
void My_User_Input_Game(int i, PLAYER *p1, PLAYER *p2, char *uInpt);

#endif
