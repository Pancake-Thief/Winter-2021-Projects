//Header for the board by Samuel Briones-Plascenica
#ifndef BOARD_H
#define BOARD_H

#include "Settings.h"
#include <stdio.h>

typedef struct Board
	BOARD;

typedef struct BoardHandle
	HANDLE;

struct Board {
	BOARD *next;
	BOARD *prev;
	char *boardImg; /*The data of the board in the player's symbols*/
	int colorBoard[9]; /*The data of the board in the player's colors */
	char uInpt[2];
};

struct BoardHandle{
	int length;
	int Winner;
	BOARD *First;
	BOARD *Last;
};

HANDLE *NewBoardList();
BOARD *CreateBoard();
void DeleteLastBoard(HANDLE *board);
void DeleteBoard(BOARD *tempBoard);
void DeleteBoardList(HANDLE *board);

void drawBoard(BOARD *board);
void fDrawBoard(FILE *OutFile, BOARD *board);

BOARD *genBoard(int turn, const PLAYER *p1, const PLAYER *p2, char *uInpt, BOARD *board, int AImove);

void AppendBoard(HANDLE *board, BOARD *tempBoard);
// Maybe get spots data functions???

#endif
