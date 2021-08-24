//Started March 9, 2021 by Samuel Briones-Plascencia
//Verion = 0.1
//Header Files
#include <stdio.h>
#include <stdlib.h>
#include "Settings.h"
#include "Board.h"
#include "Game.h"
#include "FileIO.h"

void PrintMenu(int *option);

int main(){
	int option = 0, AIchoice = 0;
	PLAYER *p1, *p2;
	HANDLE *board;
	char PlayerType[12], FileName[64];
	p1 = CreatePlayer(1, "X", 97);
	p2 = CreatePlayer(2, "O", 97);
	printf("Welcome to ");
	do{
		system("clear");
		switch(option) {
			case 1 : 
				//Human v. Human
				board = Game(p1, p2, 0);
				//MIGHT COMPACT INTO SAVE FUNCTION
				
				
				
				printf("\nWould you like to save the game's replay?\n");
				printf("1: Yes		2: No\n");
				printf("Choose Option: ");
				scanf("%d", &option);
				if(option == 1){
					printf("Name file: ");
					scanf("%s", FileName);
					strcpy(PlayerType, "Human");
					WriteReplayFile(board, p1, p2, FileName, PlayerType);
					DeleteBoardList(board);
				}else if (option == 2){
					DeleteBoardList(board);
				}
				break;
			case 2 :
				//Human v. AI
				printf("Please choose opponent's AI level:\n");
				printf("1: Level 1 (Inky)\n");
				printf("2: Level 2 (Blinky)\n");
				printf("3: Level 3 (Pinky)\n");
				printf("Choose option: ");
				scanf("%d", &AIchoice);
				board = Game(p1, p2, AIchoice);
				
				printf("\nWould you like to save the game's replay?\n");
				printf("1: Yes		2: No\n");
				printf("Choose Option: ");
				scanf("%d", &option);
				if(option == 1){
					switch(AIchoice){
						case 1:
							strcpy(PlayerType, "AI - Inky");
							break;
						case 2:
							strcpy(PlayerType, "AI - Blinky");
							break;
						case 3:
							strcpy(PlayerType, "AI - Pinky");
							break;
					}
					printf("Name file: ");
					scanf("%s", FileName);
					WriteReplayFile(board, p1, p2, FileName, PlayerType);
					DeleteBoardList(board);
				} else if(option == 2){
					DeleteBoardList(board);
				}

				break;
			case 3 :
				//Settings
				Settings_Menu(p1, p2);
				break;
		}
		system("clear");
		PrintMenu(&option);
	} while (option < 4);

	if(p1) DeletePlayer(p1);
	if(p2) DeletePlayer(p2);
	return 0;

}

void PrintMenu(int *option){
	printf("Welcome to Secure-Tic-Tac-Whoa!\n");
	printf("1: Start New Game (Human v. Human)\n");
	printf("2: Start New Game (Human v. AI)\n");
	printf("3: Game Settings\n");
	printf("4: Exit Game\n");
	printf("Choose Option: ");
	scanf("%d", option);
}
