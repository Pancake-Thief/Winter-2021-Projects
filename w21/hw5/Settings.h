//Settings Header by Samuel Briones-Plascencia

#ifndef SETTINGS_H
#define SETTINGS_H

#include <string.h>

typedef struct {
	int Num;
	int Col;
	char Sym[1];

} PLAYER;

void Settings_Menu(PLAYER *p1, PLAYER *p2);

PLAYER *CreatePlayer(int PlayerNum, char *Symbol, int Color);
void DeletePlayer(PLAYER *p1);

void Print_Options(int *option);
#endif
