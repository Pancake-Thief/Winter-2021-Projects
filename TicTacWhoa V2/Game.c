//The game itself by Samuel Briones-Plascencia
//Win/Loss/Tie
//Takes in Player input and turn number

#include "Settings.h"
#include "Game.h"
#include "Board.h"
#include "AI.h"
#include <stdio.h>
#include <stdlib.h>

HANDLE *Game(PLAYER *p1, PLAYER *p2, int AI_choice){
	int i, temp, count = 0, AImove = -1;
	char *uInpt = (char *)malloc(sizeof(char) * 3);	
	BOARD *boardTemp;
	HANDLE *board;
	//If statement depending on whether or not AI is enabled and which is active
	if(AI_choice == 0){
		//for loop for length of the game/size of board squared
		for(i = 0; i <= 9; i++)	{
			if(i) system("clear");
			temp = i;
			
			if(!count && !i){
				boardTemp = CreateBoard();
				board = NewBoardList();	
				AppendBoard(board, boardTemp);
			}

			if(i == 0) drawBoard(board->Last);

			if(i != 0 && uInpt[0] != '9'){
				memcpy(board->Last->uInpt, uInpt, sizeof(*uInpt) + 1);
				AppendBoard(board, genBoard(i, p1, p2, uInpt, board->Last, -1));
			}
			if(winCon(board->Last, p1, p2)){
				if(i % 2 == 0){
					board->Winner = 2;
				}else if (i % 2 == 1){
					board->Winner = 1;
				}
				break;
			}
			
			if(i == 9) break;

			My_User_Input_Game(temp, p1, p2, uInpt);
			count++;
		}
	
	
	} else if(AI_choice > 0){
		for(i = 0; i <= 9; i++){
			if(i) system("clear");
			temp = i;
	
			if(!count && !i){
				boardTemp = CreateBoard();
				board = NewBoardList();
				AppendBoard(board, boardTemp);
			}
			
			if(i == 0) drawBoard(board->Last);
	
			if(i != 0 && uInpt[0] != '9') AppendBoard(board, genBoard(i, p1, p2, uInpt, board->Last, AImove));		
			if(winCon(board->Last, p1, p2)){
				if(i % 2 == 0){
					board->Winner = 2;
				}else if(i % 2 == 1){
					board->Winner = 1;
				}	
				break;
			}
			if(i == 9) break;
			
			//bot or user input
			if(i % 2 == 0){
				if(i >= 2){
					printf("\nInput \"99\" for take back moves.");
				}
				My_User_Input_Game(temp, p1, p2, uInpt);
			}else{
				if(AI_choice == 1){
					//Level 1 AI
					Level1(board->Last, uInpt, p2);
				} else if (AI_choice == 2){
					//Level 2 AI
					Level2(board->Last, uInpt);
					printf("\nPlayer %s chose: %s", p2->Sym, uInpt);
				} else if (AI_choice == 3){
					//Level 3 AI
					Level3(board->Last, uInpt, p1, p2);
				}
			}

			if(uInpt[0] == '9' && i >= 2){
				i -= 3;
				for(int j = 0; j < 2; j++){
					DeleteLastBoard(board);
				}
			}else if(i < 2){
				while(uInpt[0] == '9'){
					printf("\nInvalid input try again");
					My_User_Input_Game(temp, p1, p2, uInpt);
				}
			}
			count++;
		}
	
	}
	//return final board that has linked lists 
	free(uInpt);
	return board;
}

void My_User_Input_Game(int i, PLAYER *p1, PLAYER *p2, char *uInpt){
	if(i % 2 == 0){
		printf("\nPlayer %c, please choose your move: ", p1->Sym[0]);
	} else {
		printf("\nPlayer %c, please choose your move: ", p2->Sym[0]);
	}
	scanf("%s", uInpt);
	if(i % 2 == 0){
		printf("\nPlayer %c chose %s", p1->Sym[0], uInpt);
	} else {
		printf("\nPlayer %c chose %s", p2->Sym[0], uInpt);
	}
}

int winCon(BOARD *board, PLAYER *p1, PLAYER *p2){
	int i, j, k, l;
	int count = 0;
	char symbols[3] = "";

	strncpy(&symbols[0], &p1->Sym[0], 1);
	strncpy(&symbols[1], &p2->Sym[0], 1);

	for(k = 0; k < 2; k++){
		//Check Rows
		for(i = 0; i < 3; i++){
			count = 0;
			for(j = 0; j < 3; j++){
				if(symbols[k] != board->boardImg[i * 3 + j]){
					count = 0;
				}else if (symbols[k] == board->boardImg[i * 3 + j]){
					count += 1;
				}
				if(count == 3){
					printf("\nPlayer %c won!!\n", symbols[k]);
					return 1;
				}
			}
		}
		//Check Columns
		for(i = 0; i < 3; i++){
			count = 0;
			for(j = 0; j < 3; j++){
				if(symbols[k] != board->boardImg[j * 3 + i]){
					count = 0;
				}else if (symbols[k] == board->boardImg[j * 3 + i]){
					count += 1;
				}
				if(count == 3){
					printf("\nPlayer %c won!!\n", symbols[k]);
					return 1;
				}
			}
		}
		//Check for Diagonals
		//Left to Right
		for(l = 0; l < 3; l++){
			for(i = 0; i < 3; i++){
				count = 0;
				for(j = 0; j < 3 - i; j++){
					if((4 * j + i + l * 3) <= 8){
						if(symbols[k] != board->boardImg[4 * j + i + l * 3]){
						count = 0;
						} else if (symbols[k] == board->boardImg[4 * j + i + l * 3]){
							count += 1;
						}
						if(count == 3){
							printf("\nPlayer %c won!!\n", symbols[k]);
							return 1;
						}
					}
				}
			}
		}
		//Right to Left
		for(l = 0; l < 3; l++){
			for(i = 0; i <= 3; i++){
				count = 0;
				for(j = 0; j < 3 - (3 - i); j++){
					if((2 * j + i - 1 + l * 3) <= 8){
						if(symbols[k] != board->boardImg[2 * j + i - 1 + l * 3]){
							count = 0;
							} else if (symbols[k] == board->boardImg[2 * j + i - 1 + l * 3]){
							count += 1;
						}
						if(count == 3){
							printf("\nPlayer %c won!!\n", symbols[k]);
							return 1;
						}
					}
				}
			}
		
		}
	}
	return 0;
}
