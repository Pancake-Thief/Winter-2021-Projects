//AI file by Samuel BRiones-Plascencia
#include "Board.h"
#include "Settings.h"
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdlib.h>



void Level1(BOARD *board, char *uInpt, PLAYER *p2){
	int i;
	for(i = 0; i < 9; i++){
		if(board->boardImg[i] == ' '){
			//Brute Force
			if(i == 0){
				strcpy(uInpt, "C1");
				break;
			} else if(i == 1){
				strcpy(uInpt, "C2");
				break;
			} else if(i == 2){
				strcpy(uInpt, "C3");
				break;
			} else if(i == 3){
				strcpy(uInpt, "B1");
				break;
			} else if(i == 4){
				strcpy(uInpt, "B2");
				break;
			} else if(i == 5){
				strcpy(uInpt, "B3");
				break;
			} else if(i == 6){
				strcpy(uInpt, "A1");
				break;
			} else if(i == 7){
				strcpy(uInpt, "A2");
				break;
			}else if (i == 8){
				strcpy(uInpt, "A3");
				break;
			}
		} else {
			continue;
		}
	}
	printf("\nPlayer %s chose: %s", p2->Sym,uInpt);
}

void Level2(BOARD *board, char *uInpt){
	int i;
	srand(time(NULL));
	while(1){
		i = rand()%(9);
		if(board->boardImg[i] == ' '){
			//Brute Force
			if(i == 0){
				strcpy(uInpt, "C1");
				break;
			} else if(i == 1){
				strcpy(uInpt, "C2");
				break;
			} else if(i == 2){
				strcpy(uInpt, "C3");
				break;
			} else if(i == 3){
				strcpy(uInpt, "B1");
				break;
			} else if(i == 4){
				strcpy(uInpt, "B2");
				break;
			} else if(i == 5){
				strcpy(uInpt, "B3");
				break;
			} else if(i == 6){
				strcpy(uInpt, "A1");
				break;
			} else if(i == 7){
				strcpy(uInpt, "A2");
				break;
			}else if (i == 8){
				strcpy(uInpt, "A3");
				break;
			}
		} else {
		continue;
		}
	
	}	

}

void Level3(BOARD *board, char *uInpt, PLAYER *p1, PLAYER *p2){
	int count = 0, i, j, l;
	int tempNumber = 0, number = 0;
	//Check Rows
	if(count != 2){	
		for(i = 0; i < 3; i++){
			count = 0;
			for(j = 0; j < 3; j++){
				if(p1->Sym[0] != board->boardImg[i * 3 + j]){
					tempNumber = i * 3 + j;
				}else if (p1->Sym[0] == board->boardImg[i * 3 + j]){
					count += 1;
				} 
			}
			if(count == 2 && (board->boardImg[tempNumber] == ' ')){
				number = tempNumber;
				break;
			} else {
				count = 0;
			}
		}
	}
	if(count != 2){
		//Check Columns
		for(i = 0; i < 3; i++){
			count = 0;
			for(j = 0; j < 3; j++){
				if(p1->Sym[0] != board->boardImg[j * 3 + i]){
					tempNumber = j * 3 + i;
				}else if (p1->Sym[0] == board->boardImg[j * 3 + i]){
					count += 1;
				}
			}
			if(count == 2 && (board->boardImg[tempNumber] == ' ')){
				number = tempNumber;
				break;
			} else {
				count = 0;
			}
		}
	}
	if(count != 2){
		//Check for Diagonals
		//Left to Right
		for(l = 0; l < 3; l++){
			for(i = 0; i < 3; i++){
				count = 0;
				for(j = 0; j < 3 - i; j++){
					if((4 * j + i + l * 3) <= 8){
						if(p1->Sym[0] != board->boardImg[4 * j + i + l * 3]){
							tempNumber = 4 * j + i + l * 3;
						} else if (p1->Sym[0] == board->boardImg[4 * j + i + l * 3]){
							count += 1;
						}
					}
				}
				if(count == 2 && (board->boardImg[tempNumber] == ' ')){
					number = tempNumber;
					break;
				} else {
					count = 0;
				}
			}
			if(count == 2){
				break;
			}
		}
	}

	if(count != 2){
		//Right to Left
		for(l = 0; l < 3; l++){
			for(i = 0; i <= 3; i++){
				count = 0;
				for(j = 0; j < 3 - (3 - i); j++){
					if((2 * j + i - 1 + l * 3) <= 8){
						if(p1->Sym[0] != board->boardImg[2 * j + i - 1 + l * 3]){
							tempNumber = 2 * j + i - 1 + l * 3;
						} else if (p1->Sym[0] == board->boardImg[2 * j + i - 1 + l * 3]){
							count += 1;
						}
					}
				}
				if(count == 2 && (board->boardImg[tempNumber] == ' ')){ 
					number = tempNumber;
					break;
				}else {
					count = 0;
				}
			}
			if(count == 2){
				break;
			}
		
		}
	}

		
		if(count == 2){
			i = number;
			//Brute Force
			if(i == 0){
				strcpy(uInpt, "C1");
			} else if(i == 1){
				strcpy(uInpt, "C2");
			} else if(i == 2){
				strcpy(uInpt, "C3");
			} else if(i == 3){
				strcpy(uInpt, "B1");
			} else if(i == 4){
				strcpy(uInpt, "B2");
			} else if(i == 5){
				strcpy(uInpt, "B3");
			} else if(i == 6){
				strcpy(uInpt, "A1");
			} else if(i == 7){
				strcpy(uInpt, "A2");
			}else if (i == 8){
				strcpy(uInpt, "A3");
			}
			printf("\nPlayer %s chose: %s", p2->Sym, uInpt);
		} else {
			Level1(board, uInpt, p2);
		}
}


