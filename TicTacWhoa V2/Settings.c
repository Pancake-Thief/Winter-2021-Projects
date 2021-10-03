//Settings by Samuel Briones-Plascencia
#include <stdio.h>
#include <stdlib.h>
#include "Settings.h"

void Settings_Menu(PLAYER *p1, PLAYER *p2){
	int option = 0;
	
	//Print_Options(&option);	
	do{
		system("clear");
		switch(option){
			case 1 :
				//P1 Text Color
				printf("Player 1 Color Options:\n");
				printf("	97: Default	\n");
				printf("31: Red		32: Green\n");
				printf("33: Yellow	34: Blue\n");
				printf("35: Magenta	36: Cyan\n");
				printf("Choose Option: ");
				scanf("%d", &p1->Col);
				break;
			case 2 :
				//P1 Symbol
				printf("Player 1 Symbol: ");
				scanf("%s", p1->Sym);
				break;
			case 3 :
				//P2 Color
				printf("Player 2 Color Options:\n");
				printf("	97: Default	\n");
				printf("31: Red		32: Green\n");
				printf("33: Yellow	34: Blue\n");
				printf("35: Magenta	36: Cyan\n");
				printf("Choose Option: ");
				scanf("%d", &p2->Col);
				break;
			case 4:
				//P2 Symbol
				printf("Player 2 Symbol: ");
				scanf("%s", p2->Sym);
		}
		system("clear");
		Print_Options(&option);
	} while (option < 5);

}

void Print_Options(int *option){
	printf("Player 1:\n");
	printf("	1: Text Color\n");
	printf("	2: Symbol(Default 'X')\n");
	printf("Player 2:\n");
	printf("	3: Text Color\n");
	printf("	4: Symbol(Default 'O')\n");
	printf("5: Back\n");
	printf("Choose Option: ");
	scanf("%d", option);
}

PLAYER *CreatePlayer(int PlayerNum,char *Symbol, int Color){
	PLAYER *p0;
	p0 = malloc(sizeof(PLAYER));
	memset(p0, 0, sizeof(PLAYER));
	if(!p0) perror("Error");

	p0->Num = PlayerNum;
	p0->Col = Color;
	memset(p0->Sym, ' ', 1);
	*p0->Sym = *Symbol;
	return p0;
}

void DeletePlayer(PLAYER *p1){
	free(p1);

}

