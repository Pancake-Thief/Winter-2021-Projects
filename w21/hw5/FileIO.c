// C file for Possibly reading and saving replays by Samuel Briones-Plascencia
#include "Board.h"
#include "Settings.h"
#include "Constants.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void WriteReplayFile(HANDLE *board, PLAYER *p1, PLAYER *p2, char *OutFileName, char *PlayerType){
	FILE *OutFile = stdout;
	char p1ColWord[8], p2ColWord[8];
	BOARD *tempBoard;
	char *Inpt = (char *)malloc(sizeof(char) * 5);
	int i;

	if(OutFileName){
		strcat(OutFileName, ".txt");
		OutFile = fopen(OutFileName, "w");
		if(!OutFile){
			perror("Error in Write File .1");
			exit(10);
		}
	
	}

	tempBoard = board->First;
	fprintf(OutFile, "#TicTacWowWeeWow\n");
	fprintf(OutFile, "Version: v%s\n", VERSION);
	fprintf(OutFile, "Filename: %s.txt\n", OutFileName);
	time_t t;
	time(&t);
	fprintf(OutFile, "Date: %s\n\n", ctime(&t));

	fprintf(OutFile, "#Settings\n");
	switch(p1->Col){
		case 97:
			strcpy(p1ColWord ,"White");
			break;
		case 31:
			strcpy(p1ColWord ,"Red");
			break;
		case 32:
			strcpy(p1ColWord ,"Green");
			break;
		case 33:
			strcpy(p1ColWord ,"Yellow");
			break;
		case 34:
			strcpy(p1ColWord ,"Blue");
			break;
		case 35:
			strcpy(p1ColWord ,"Magenta");
			break;
		case 36:
			strcpy(p1ColWord ,"Cyan");
			break;
	}
	
	switch(p2->Col){
		case 97:
			strcpy(p2ColWord ,"White");
			break;
		case 31:
			strcpy(p2ColWord ,"Red");
			break;
		case 32:
			strcpy(p2ColWord ,"Green");
			break;
		case 33:
			strcpy(p2ColWord ,"Yellow");
			break;
		case 34:
			strcpy(p2ColWord ,"Blue");
			break;
		case 35:
			strcpy(p2ColWord ,"Magenta");
			break;
		case 36:
			strcpy(p2ColWord ,"Cyan");
			break;
	}
	
	fprintf(OutFile, "Player 1(Human): '%c', '%s'\n", *p1->Sym, p1ColWord);
	fprintf(OutFile, "Player 2(%s): '%c', '%s'\n\n", PlayerType, *p2->Sym, p2ColWord);
	
	fprintf(OutFile, "#Winner\n");
	if(board->Winner){
		fprintf(OutFile, "Player %d\n\n", board->Winner);
	} else {
		fprintf(OutFile, "Tie\n\n");
	}
	//Print User inputs
	fprintf(OutFile, "#MovesList\n");
	tempBoard = board->First;
	for(i = 0; i < board->length - 1; i++){
		if(!tempBoard){
			perror("Error in Write File .2");
			exit(10);
		}
		if(i % 2 == 0){
			fprintf(OutFile,"Player 1: %s\n", tempBoard->uInpt);
		} else if(i % 2 == 1){
			fprintf(OutFile,"Player 2: %s\n", tempBoard->uInpt);
		}
		tempBoard = tempBoard->next;
	}
	fprintf(OutFile, "\n#Replay\n");
	tempBoard = board->First->next;
	for(i = 0; i < board->length - 1; i++){

		fDrawBoard(OutFile, tempBoard);
		fprintf(OutFile, "\n");
		tempBoard = tempBoard->next;
	}

	if(board->Winner){
		fprintf(OutFile, "\n\nPlayer %d wins!!\n\n", board->Winner);
	} else {
		fprintf(OutFile, "\n\nTie\n\n");
	};
	free(Inpt);
	fprintf(OutFile, "#EOF");
	fclose(OutFile);
	OutFile = NULL;

}
