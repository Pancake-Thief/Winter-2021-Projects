//Functions dealing with the board itself (Drawing and modifying the board) by Samuel Briones-Plascencia
//TO-DO List:
//Drawing the current board: NOT DONE
//Appending a new board to a list (Only done when someone does something): NOT DONE
//Going back a board (Done when takesies-backsies): NOT DONE
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Board.h"
#include "Constants.h"

HANDLE *NewBoardList(){
	HANDLE *board;
	board = malloc(sizeof(HANDLE));
	if(!board) perror("Error in HANDLE");
	
	board->length = 0;
	board->First = NULL;
	board->Last = NULL;
	board->Winner = 0;
	return board;
};

BOARD *CreateBoard(){
	BOARD *board;
	board = (BOARD *)malloc(sizeof(BOARD));
	if (!board) perror("Error in Board.");
	memset(board, 0, sizeof(BOARD));
	board->next = NULL;
	board->prev = NULL;
	board->boardImg = (char *)malloc(sizeof(char) * 13);
	
	memset( board->uInpt, ' ', 2);
	memset( board->boardImg, ' ', 12);
	memset( board->colorBoard, 0, sizeof(board->colorBoard));

	return board;
}

BOARD *genBoard(int turn, const PLAYER *p1, const PLAYER *p2, char *uInpt, BOARD *board, int AImove){
	int i, j, row, col, rowCol, charColor;
	char Inpt[3] = "";
	char Vert[2] = "|";
	char Horz[3] = "--";
	char letters[4] = "ABC";
	char numbers[4] = "123";
	char *symbol = (char *)malloc(sizeof(char) * 2);
	char blank[2] = " ";
	BOARD *tempBoard;
	tempBoard = CreateBoard();
	for(i = 0; i < 9; i++){
		tempBoard->colorBoard[i] = board->colorBoard[i];
	}
	memcpy(tempBoard->boardImg, board->boardImg, sizeof(board->boardImg) + 1);
	
	//Deciding p1 or p2 Symbol
	if(turn == 0 || uInpt[0] == '9'){
		strcpy(symbol, blank);	
	} else if (turn % 2 == 1) {
		//p1
		*symbol = *p1->Sym;
		charColor = p1->Col;
	} else if (turn % 2 == 0) {
		//p2
		*symbol = *p2->Sym;
		charColor = p2->Col;
	}

	strcpy(Inpt, uInpt);
	row = 3 - (Inpt[0] - 'A');
	col = Inpt[1] - '1';
	rowCol = (row - 1)  * 3 + col;
	
	//AI Input
	if(AImove > -1 && turn % 2 == 0){
		rowCol = AImove;
	}

	//Copy symbol to board
	strncpy(&tempBoard->boardImg[rowCol], &symbol[0], 1);
       
	//Set the player color in the color board
	tempBoard->colorBoard[rowCol] = charColor;	

	if(!turn) symbol[2] = 0;

	//"Reading" board data and printing it
	for(i = 0; i < 3 ; i++){
		for(j = 0; j <= 3; j++){
			//Vertical Lines incl. letters
			if(j == 0){
				printf("\n%c ", letters[2 - i - j]);
			} else if (j < 3){
				printf(COLOR_START"%dm%c"COLOR_RESET"%s", tempBoard->colorBoard[i * 3 + j - 1], tempBoard->boardImg[i * 3 + j - 1], Vert);
			} else if (j == 3){
				printf(COLOR_START"%dm%c\n"COLOR_RESET, tempBoard->colorBoard[i * 3 + j - 1], tempBoard->boardImg[i * 3 + j - 1]);
			}
		}
		for(j = 0; j <= 3; j++){
			//Horizontal Lines
			if(i + 1 == 3){
				break;
			} else if (j == 0){
				printf("  ");
			} else if(j > 0){
				printf("%s", Horz);
			}
		}
	}

	//Generate the Row of #'s
	printf("  ");
	for(i = 0; i < 3; i++){
		if(i < 3){
			printf("%c ", numbers[i]);
		} else if (i == 3){
			printf("\n");
		}
	}
	free(symbol);
	return tempBoard;
}

void AppendBoard(HANDLE *board, BOARD *tempBoard){
	assert(board);
	assert(tempBoard);
	
	if(board->Last){
		tempBoard->next = NULL;
		tempBoard->prev = board->Last;
		board->Last->next = tempBoard;
		board->Last = tempBoard;
	} else {
		tempBoard->next = NULL;
		tempBoard->prev = NULL;
		board->First = tempBoard;
		board->Last = tempBoard;
	}
	board->length++;	
}

void DeleteLastBoard(HANDLE *board){
	BOARD *newTempBoard;
	assert(board);
	if(board->Last){
		newTempBoard = board->Last;
		board->Last = newTempBoard->prev;
		if(board->Last){
			board->Last->next = NULL;
		} else {
			assert(board->First == newTempBoard);
			board->First = NULL;
		}
		
		board->length--;
		DeleteBoard(newTempBoard);
	}
}

void DeleteBoardList(HANDLE *board){
	BOARD *tempBoard, *temptempBoard;

	tempBoard = board->First;
	while(tempBoard){
		temptempBoard = tempBoard->next;
		DeleteBoard(tempBoard);
		tempBoard = temptempBoard;
	}
	free(board);
	board = NULL;
}

void DeleteBoard(BOARD *tempBoard){
	assert(tempBoard);
	
	tempBoard->next = NULL;
	tempBoard->prev = NULL;
	free(tempBoard->boardImg);
	tempBoard->boardImg = NULL;

	free(tempBoard);
	tempBoard = NULL;
	
}

void drawBoard(BOARD *board){
	int i, j;
	char Vert[2] = "|";
	char Horz[3] = "--";
	char letters[4] = "ABC";
	char numbers[4] = "123";

	for(i = 0; i < 3 ; i++){
		for(j = 0; j <= 3; j++){
			//Vertical Lines incl. letters
			if(j == 0){
				printf("\n%c ", letters[2 - i - j]);
			} else if (j < 3){
				printf(COLOR_START"%dm%c"COLOR_RESET"%s", board->colorBoard[i * 3 + j - 1], board->boardImg[i * 3 + j - 1], Vert);
			} else if (j == 3){
				printf(COLOR_START"%dm%c\n"COLOR_RESET, board->colorBoard[i * 3 + j - 1], board->boardImg[i * 3 + j - 1]);
			}
		}
		for(j = 0; j <= 3; j++){
			//Horizontal Lines
			if(i + 1 == 3){
				break;
			} else if (j == 0){
				printf("  ");
			} else if(j > 0){
				printf("%s", Horz);
			}
		}
	}

	//Generate the Row of #'s
	printf("  ");
	for(i = 0; i < 3; i++){
		if(i < 3){
			printf("%c ", numbers[i]);
		} else if (i == 3){
			printf("\n");
		}
	}

}

void fDrawBoard(FILE *OutFile, BOARD *board){
	int i, j;
	char Vert[2] = "|";
	char Horz[3] = "--";
	char letters[4] = "ABC";
	char numbers[4] = "123";

	for(i = 0; i < 3 ; i++){
		for(j = 0; j <= 3; j++){
			//Vertical Lines incl. letters
			if(j == 0){
				fprintf(OutFile, "\n%c ", letters[2 - i - j]);
			} else if (j < 3){
				fprintf(OutFile,"%c""%s", board->boardImg[i * 3 + j - 1], Vert);
			} else if (j == 3){
				fprintf(OutFile, "%c\n", board->boardImg[i * 3 + j - 1]);
			}
		}
		for(j = 0; j <= 3; j++){
			//Horizontal Lines
			if(i + 1 == 3){
				break;
			} else if (j == 0){
				fprintf(OutFile, "  ");
			} else if(j > 0){
				fprintf(OutFile, "%s", Horz);
			}
		}
	}

	//Generate the Row of #'s
	fprintf(OutFile, "  ");
	for(i = 0; i < 3; i++){
		if(i < 3){
			fprintf(OutFile, "%c ", numbers[i]);
		} else if (i == 3){
			fprintf(OutFile, "\n\n");
		}
	}

}
