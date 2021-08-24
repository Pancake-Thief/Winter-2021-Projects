//TicTacWhoa.c by Samuel Briones-Plascencia [Finished Jan. 16 2021]
//Tic Tac Toe Part 2 cuz the first c file got deleted
//To-Do List:
//UI: Done
//Game Settings: Done
//Inputs: Done
//AI: Done
//Win Condition: Done

//Declaration of libraries and functions in order
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main_Menu(void);
int settings_Menu_Input(void);

void my_user_Input_Game(int, char *p1Sym, char *p2Sym, char *uInpt);
void genBoard(int,  int *board, int *p1Col, int *p2Col, char *p1Sym, char *p2Sym, char *boardImg, char *uInpt, int *colorBoard, int, int, int);

int winCon(char *boardImg, char *p1Sym, char *p2Sym, int row, int board);

int gameAI(int *colorBoard, int board);
//Colors initialization
//"Dynamic" Color
#define COLOR_START "\x1b["
//Reset the Color as to not change other characters
#define COLOR_RESET "\x1b[0m"
//Clear Screen
#define clear() printf("\n\33[H\033[J")

//Main Menu input and UI combined
int main_Menu(void){
	int i;

	printf("Welcome to Secure-Tic-Tac-Whoa!\n");
	printf("1. Start New Game (Human v. Human)\n");
	printf("2. Start New Game (Human v. AI)\n");
	printf("3. Game Settings\n");
	printf("4. Exit Game\n");
	printf("Choose Option: _");
	scanf("%d", &i);
	return i;
}

//Settings Menu
//Settings Menu UI and Input
int settings_Menu_Input(void){
	int l;
	printf("Player 1:\n");
	printf("	1: Text Color\n");
	printf("	2: Symbol(Default 'X')\n");
	printf("Player 2:\n");
	printf("	3: Text Color\n");
	printf("	4: Symbol(Default 'O')\n");
	printf("5: Size of Board(Default 3)\n");
	printf("6: In A Row to Win(Default 3)\n");
	printf("7: Back\n");
	printf("Choose Option: _");
	scanf("%d", &l);
	return l;
}

//Settings Menu Overall
int settings_Menu(int *p1Col, char *p1Sym, int *p2Col, char *p2Sym, int *board, int *row){
	int input;
	do{
		system("clear");
		input = settings_Menu_Input();
		switch(input){
			case 1 :
				// P1 Text Color
				printf("Player 1 Color Options:\n");
				printf("	97: Default	\n");
				printf("31: Red		32: Green\n");
				printf("33: Yellow 	34: Blue\n");
				printf("35: Magenta	36: Cyan\n");
				printf("Choose Option: _");
				scanf("%d", p1Col);
				break;
			case 2 :
				// P1 Symbol
				printf("Player 1 Symbol: ");
				scanf("%s", p1Sym);
				break;
			case 3 :
				// P2 Text Color
				printf("Player 2 Color Options:\n ");
				printf("	97: Default\n");
				printf("31: Red		32: Green\n");
				printf("33: Yellow	34: Blue\n");
				printf("35: Magenta	36: Cyan\n");
				printf("Choose Option: _");
				scanf("%d", p2Col);
				break;
			case 4 :
				// P2 Symbol
				printf("Player 2 Symbol: ");
				scanf("%s", p2Sym);
				break;
			case 5 :
				//Size of Board
				printf("Size of Board: ");
				scanf("%d", board);
				break;
			case 6 :
				// In A Row to Win
				printf("In a Row to Win(less than or equal to %d): ", *board);
				scanf("%d", row);
				break;
		}
	}while(input < 7 );
	return 0;
}

//Board Generation Human v. Human(I know it can be optimized but I dont have the time)
void genBoard(int turn, int *board, int *p1Col, int *p2Col, char *p1Sym, char *p2Sym, char *boardImg, char *uInpt, int *colorBoard, int switch_AI, int AI_move, int AIplace){
	//Initialization
	int i, j, charColor;
	int row = 0, col = 0, rowCol = 0;
	char Inpt[3] = "";
	char Vert[2] = "|";
	char Horz[3] = "--";
	char letters[11] = "ABCDEFGHIJ";
	char numbers[10] = "123456789";
	char symbol[2] = "";
	char blank[2] = " ";
	int boardSize = *board, player1_Color = *p1Col, player2_Color = *p2Col;
	
	//Deciding on whether p1 or p2 Symbol
	if(turn == 0){
		strcpy(symbol, blank);
	}else if(turn % 2 == 1){
		//p1 
		strcpy(symbol, p1Sym);
		charColor = player1_Color;
	} else if (turn % 2 == 0){
		//p2
		strcpy(symbol, p2Sym);
		charColor = player2_Color;
	}

	//Setting boardArray with either p1Sym, p2Sym (done from above if statement), or " "
	strcpy(Inpt, uInpt);
	row = 0, col = 0;
	row = boardSize - (Inpt[0] - 'A');
	col = Inpt[1] - '1';
	if(Inpt[2] == '0')
		col = 9;
	rowCol = (row - 1) * boardSize + col;
	
	//AI input 
	if(switch_AI == 1){
		//AI is player 1
		if(AIplace == 1 && turn % 2 == 1){
			rowCol = AI_move;
		}
		//AI is player 2
		if(AIplace == 0 && turn % 2 == 0){
			rowCol = AI_move;
		}
	}

	//Copy symbol to output array
	strncpy(&boardImg[rowCol], &symbol[0], 1);
	
	//Set the Player Color to that position
	colorBoard[rowCol] = charColor;
	
	//Makes sure to reset symbol on first turn as it carries data from previous game
	if(turn == 0)
		symbol[2] = 0;
	
	//Generating actual board with two loops
	for(i = 0; i < boardSize; i++){
		for(j = 0; j <= (boardSize); j++){
			//Vertical Lines and Letters
			if(j == 0){
				printf("\n%c ", letters[boardSize - 1 - i - j]);
			} else if(j < boardSize){
				printf(COLOR_START"%dm%c"COLOR_RESET"%s",colorBoard[i*boardSize + j - 1 ], boardImg[i*boardSize + j - 1] , Vert);
			} else if(j == (boardSize )){
				printf(COLOR_START"%dm%c\n"COLOR_RESET, colorBoard[i*boardSize + j - 1],boardImg[i*boardSize + j - 1] );
			}
		}
		for(j = 0; j <= boardSize; j++){
			//Horizontal Lines
			if(i + 1 == boardSize){
				break;
			}else if(j == 0){
				printf("  ");
			}else if(j < boardSize){
				printf("%s", Horz);
			} else if(j == boardSize){
				printf("%s", Horz);
			}

		}
	}
	
	//Generate the Row of #'s
	printf("  ");
	for(i = 0; i < boardSize; i++){
		//if statement cuz of edge case
		if(i == 9){
			printf("10");
		}else if(i < boardSize){
			printf("%c ", numbers[i]);
		}else if(i == boardSize){
			printf("\n");
		}
	}
}

//Actual Game
//User Input + Generating the board(from function above) 
void my_user_Input_Game(int i, char *p1Sym, char *p2Sym, char *uInpt){	
	if(i % 2 == 0){
		printf("\nPlayer %s, please choose your move: _", p1Sym);
	} else {
		printf("\nPlayer %s, please choose your move: _", p2Sym);
	}	
	scanf("%s", uInpt);
	if(i % 2 == 0){
		printf("\nPlayer %s chose %s", p1Sym, uInpt);
	} else {
		printf("\nPlayer %s chose %s", p2Sym, uInpt);
	}
}

int winCon(char *boardImg, char *p1Sym, char *p2Sym, int row, int board){
	int i, j, k, l;
	int count = 0;
	int boardSize = board, rowWin = row;
	char symbols[3] = "";
	
	strncpy(&symbols[0], &p1Sym[0], 1);
	strncpy(&symbols[1], &p2Sym[0], 1);
	       
	//Check Rows
	for(k = 0; k < 2; k++){
		for(i = 0; i < boardSize; i++){
			count = 0;
			for(j = 0; j < boardSize ; j++){
				if(symbols[k] != boardImg[i*boardSize + j]){
					count = 0;
				} else if (symbols[k] == boardImg[i*boardSize + j]){
					count += 1;
				}
				if(count == rowWin){
					printf("\nPlayer %c won!!\n", symbols[k]);
					return 1;
				}
			}
		}
	//Check Columns
		for(i = 0; i < boardSize; i++){
			count = 0;
			for(j = 0; j < boardSize; j++){
				if(symbols[k] != boardImg[j*boardSize + i]){
					count = 0;
				} else if(symbols[k] == boardImg[j*boardSize + i]){
					count += 1;
				}
				if(count == rowWin){
					printf("\nPlayer %c won!!\n", symbols[k]);
					return 1;
				}
			}
		}
	//Check for Diagonals
		//Left to Right
		for(l = 0; l < boardSize; l++){
			for(i = 0; i < boardSize; i++){
				count = 0;
				for(j = 0; j < boardSize - i; j++){
					if(symbols[k] != boardImg[((boardSize + 1) * j + i) + l * boardSize]){
						count = 0;
					} else if(symbols[k] == boardImg[((boardSize + 1) * j + i) + l * boardSize]){
						count += 1;
					}
					if(count == rowWin){
						printf("\nPlayer %c won!!\n", symbols[k]);
						return 1;
					}
				}
			}
		}
		//Right to Left
		for(l = 0; l < boardSize; l++){
			for(i = 0; i <= boardSize; i++){
				count = 0;
				for(j = 0; j < boardSize - (boardSize - i); j++){
					if(symbols[k] != boardImg[((boardSize - 1) * j + i - 1) + l * boardSize]){
						count = 0;
					} else if(symbols[k] == boardImg[((boardSize - 1)* j + i - 1) + l * boardSize]){
						count += 1;
					}
					if(count == rowWin){
						printf("\nPlayer %c won!!\n", symbols[k]);
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

int gameAI(int *colorBoard, int board){
	int i;
	int boardSize = board;
	for(i = 0; i < (boardSize * boardSize); i++){
		if(colorBoard[i] == 0){
			return i;
		} else {
			continue;	
		}
	}
	return -1; 
}

int main (void){
	int input = 0, i = 0, win = 0, temp, AIplace, switch_AI, AI_move;
	//Initialize values
	char p1Symbol[2] = "X", p2Symbol[2] = "O", boardImage[122][1], userInput[3] = "";
	int boardSize = 3, rowWin = 3, p1Color = 97, p2Color = 97, colorBoard[100] = { };
	//Initialize Pointers
	char *p1Sym, *p2Sym, *uInpt;
	int *board, *row, *p1Col, *p2Col;
	//Initialize Both together
	p1Col = &p1Color;
	p2Col = &p2Color;
	p1Sym = p1Symbol;
	p2Sym = p2Symbol;
	board = &boardSize;
	row = &rowWin;
	uInpt = userInput;
	
	do{
		system("clear");
		switch(input){
			case 0 :
				break;
			case 1 :
			       	//Human v. human
				switch_AI = 0;
				win = 0;
				memset( boardImage, ' ', 121);
				memset( colorBoard, 0, sizeof(colorBoard));
				printf("Human v. Human Game Started\n");
				for(i = 0; i <= (boardSize * boardSize); i++){
					if(i)
						system("clear");

					genBoard(i, &boardSize, &p1Color, &p2Color, p1Symbol, p2Symbol, *boardImage, uInpt, colorBoard, switch_AI, AI_move, AIplace);
					win = winCon(*boardImage, p1Symbol, p2Symbol, rowWin, boardSize);
					
					if(win || i == (boardSize * boardSize))
						break;
					if(i != ((boardSize * boardSize) + 1) || win != 1){
						temp = i;
						my_user_Input_Game(temp , p1Symbol, p2Symbol, uInpt);
					}
				}
				if( win == 0)
					printf("\nTie\n");
				break;
			case 2 :
				//Human v. AI
				//Making sure everything is empty
				switch_AI = 1;
				AIplace = 0;
				win = 0;
				memset( boardImage, ' ', 121);
				memset( colorBoard, 0, sizeof(colorBoard));
				//Who is Player 1?
				printf("Will (0)Player or (1)AI Be Player 1?\n");
				printf("Choose Option: ");
				scanf("%d", &AIplace);
				system("clear");
				printf("Human vs. AI Game Started");
				for(i = 0; i <= (boardSize * boardSize); i++){
					if(i)
						system("clear");
					
					genBoard(i, &boardSize, &p1Color, &p2Color, p1Symbol, p2Symbol, *boardImage, uInpt, colorBoard, switch_AI, AI_move, AIplace);
					win = winCon(*boardImage, p1Symbol, p2Symbol, rowWin, boardSize);

					if(win || i == (boardSize * boardSize))
						break;
					
					//AI is Player 2 couldve switched the loops but I am too deep
					if(AIplace == 0 && (i + 2) % 2 == 0){
						if(i != ((boardSize * boardSize) + 1) || win != 1){
							temp = i;
							my_user_Input_Game(temp, p1Symbol, p2Symbol, uInpt);
						}
					} else if(AIplace == 0 && (i + 2) % 2 == 1){
						if(i != ((boardSize * boardSize) + 1) || win != 1){
							AI_move = gameAI(colorBoard, boardSize);
						}
					}

					//AI is Player 1 ~~ooo~~ scary AI takeover
					if(AIplace == 1 && (i + 2) % 2 == 0){
						if(i != ((boardSize * boardSize) + 1) || win != 1){
							AI_move = gameAI(colorBoard, boardSize);
						}
					} else if(AIplace == 1 && (i + 2) % 2 ==1){
						if(i != ((boardSize * boardSize) + 1) || win != 1){
							temp = i;
							my_user_Input_Game(temp, p1Symbol, p2Symbol, uInpt);
						}
					}
				}
				if( win == 0)
					printf("\nTie\n");
				break;
			case 3 :
				//Settings
				settings_Menu(&p1Color, p1Symbol, &p2Color, p2Symbol, &boardSize, &rowWin);
				break;
		}		
		input = main_Menu();
	}while(input < 4);
	return 0;
}
