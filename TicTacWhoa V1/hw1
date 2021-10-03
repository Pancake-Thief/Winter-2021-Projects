/*********************************************************************/
/* Reference solution for Assignment 1 for EECS 22 @ UCI Winter 2021 */
/*                                                                   */
/* This is an "A" level representation of the Tic-Tac-Whoa game.     */
/* There are improvements that can be made, but this is considered   */
/* very good.                                                        */
/*                                                                   */
/* This solution is for your reference for this course and           */
/* copyright belongs to the authors below. Reproduction or sharing   */
/* of this code outside of this class is prohibited except with the  */
/* express written consent of the authors.                           */
/*                                                                   */
/* Authors: Mozhgan Moradiganjeh, QV Dang                            */
/* Modifications:                                                    */
/* 01/18/21 QV  AI, function, and comment updates                    */
/* 01/13/21 MM  Initial version                                      */
/*********************************************************************/
#include <stdio.h>

// Handle Menu Options
int print_menu()
{
	int select=0;
	printf("1. Start New Game (Human v. Human)\n");
	printf("2. Start New Game (Human v. AI)\n");
	printf("3. Game Settings\n");
	printf("4. Exit Game\n");
	printf("Choose Option: ");
	scanf("%d",&select);
	getchar(); // one solution for clearing the "\n" char from the input
	return select;
}

// This function prints the board
void print_fun(int board[3][3],char player1_char,char player2_char,char player1_color, char player2_color)
{
    // start with row
    for(int i=0;i<3;i++)
	{
        // print out vertical legend
		if(i==0)
			printf("C ");
		if(i==1)
			printf("B ");
		if(i==2)
			printf("A ");
	
        // find corresponding column    
		for(int j=0;j<3;j++)
		{
			if(board[i][j]==0) // empty space
				printf(" ");
			else if (board[i][j]==1) // player 1
			{
				if (player1_color== 'r')
				{
					printf("\x1b[31m%c\x1b[0m",player1_char); //Red
				}
				else if (player1_color== 'g')
				{
					printf("\x1b[32m%c\x1b[0m",player1_char); //Green
				}
				else if (player1_color== 'y')
				{
					printf("\x1b[33m%c\x1b[0m",player1_char); // Yellow
				}
				else if (player1_color== 'b')
				{
					printf("\x1b[34m%c\x1b[0m",player1_char); // Blue
				}
				else
				{
					printf("%c\x1b[0m",player1_char); // Default color (theme dependent)
				}
			}
			else if (board[i][j]==2) // player 2
			{
				if (player2_color== 'r')
				{
					printf("\x1b[31m%c\x1b[0m",player2_char); //Red
				}
				else if (player2_color== 'g')
				{
					printf("\x1b[32m%c\x1b[0m",player2_char); //Green
				}
				else if (player2_color== 'y')
				{
					printf("\x1b[33m%c\x1b[0m",player2_char); // Yellow
				}
				else if (player2_color== 'b')
				{
					printf("\x1b[34m%c\x1b[0m",player2_char); // Blue
				}
				else
				{
					printf("%c\x1b[0m",player2_char); // Default color (theme dependent)
				}
			}
				
			// print out lines in between columns 
            if(j!=2)
				printf("|");
		}
		if(i!=2) // print out lines between rows
			printf("\n  -----\n");
		else if(i==2) // prints out horizontal legend
			printf("\n  1 2 3\n");
	}
}

//This function checks if there is empty place in board.
int is_there_empty_cell(int board[3][3])
{
	int count=0;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
				if(board[i][j]==0)
					count++;	
		}
	}
	if (count!=0)
		return 1; // we have empty cell
	else
		return 0; // we do not have empty cell
}

// players can choose their characters.
void choose_char(char *player1_char, char *player2_char)
{
	printf("player 1 choose your char between A to Z\n");
	scanf("%c",player1_char);
	getchar();
	printf("player 2 choose your char between A to Z\n");
	scanf("%c",player2_char);
	getchar();
}

// players can choose their colors.
void choose_color(char *player1_color, char *player2_color)
{
	int valid_entered = 0;
	printf("player 1 choose from the following list for your color please...\n");
	printf("'r' for red, 'g' for green, 'y' for yellow, 'b' for blue', 'd' for default\n");
	while (valid_entered == 0)
	{
		char col;
		scanf("%c",&col);
		getchar();
		if (col=='r' || col=='g' || col=='y' || col=='b' || col=='d')
		{
			*player1_color = col;
			valid_entered = 1;
		}
		else
		{
			printf("Invalid input, please try agian ...\n");
		}
	}
	valid_entered = 0;
	printf("player 2 choose from the following list for your color please...\n");
	printf("'r' for red, 'g' for green, 'y' for yellow, 'b' for blue', 'd' for default\n");
	while (valid_entered == 0)
	{
		char col;
		scanf("%c",&col);
		getchar();
		if (col=='r' || col=='g' || col=='y' || col=='b' || col=='d')
		{
			*player2_color = col;
			valid_entered = 1;
		}
		else
		{
			printf("Invalid input, please try agian ...\n");
		}
	}
	
}

// handle settings for the game
void settings(char *player1_char, char *player2_char, char *player1_color, char *player2_color)
{
	int valid_entered = 0;
	while (valid_entered == 0)
	{
		int select = 0;
		printf("Entering Settings...\n");
		printf("Please enter the setting options below...\n");
		printf("1. Changing the players' character\n");
		printf("2. Changing players' character color\n");
		printf("3. Exiting setting\n");
		scanf("%d",&select);
		getchar();

		if (select == 1)
		{
			choose_char(player1_char, player2_char);
		}
		else if (select == 2)
		{
			choose_color(player1_color, player2_color);
		}
		else if (select == 3)
		{
			break;
		}
		else
		{
			printf("Invalid input. Please try again...\n");
		}
	}
	printf("Setting completed!\n");
}

// win condition
int IsWin(int board[3][3])
{
	
	int win_flag=0;
	if(((board[0][0]==1)&&(board[1][0]==1)&&(board[2][0]==1))||
		((board[0][1]==1)&&(board[1][1]==1)&&(board[2][1]==1))||
		((board[0][2]==1)&&(board[1][2]==1)&&(board[2][2]==1))||
		((board[0][0]==1)&&(board[0][1]==1)&&(board[0][2]==1))||
		((board[1][0]==1)&&(board[1][1]==1)&&(board[1][2]==1))||
		((board[2][0]==1)&&(board[2][1]==1)&&(board[2][2]==1))||
		((board[0][0]==1)&&(board[1][1]==1)&&(board[2][2]==1))||
		((board[0][2]==1)&&(board[1][1]==1)&&(board[2][0]==1)))
		{
			win_flag =1;
		}
	
	else if(((board[0][0]==2)&&(board[1][0]==2)&&(board[2][0]==2))||
				((board[0][1]==2)&&(board[1][1]==2)&&(board[2][1]==2))||
				((board[0][2]==2)&&(board[1][2]==2)&&(board[2][2]==2))||
				((board[0][0]==2)&&(board[0][1]==2)&&(board[0][2]==2))||
				((board[1][0]==2)&&(board[1][1]==2)&&(board[1][2]==2))||
				((board[2][0]==2)&&(board[2][1]==2)&&(board[2][2]==2))||
				((board[0][0]==2)&&(board[1][1]==2)&&(board[2][2]==2))||
				((board[0][2]==2)&&(board[1][1]==2)&&(board[2][0]==2)))
				{
					win_flag =2;
				}

	return win_flag;		
}

// enters int 1 or 2 in desired position.
void entered_one_char(int board [3][3],int player_num)
{
	int valid_entered = 0;
	int c;
	int r;
	while(valid_entered == 0)
	{
		char letters_num[2];
		c=0;
		r=0;
		scanf("%s",letters_num);
		
		if (letters_num[0]=='A')
		{
			r=2;
		}
		else if(letters_num[0]=='B')
		{
			r=1;
		}
		else if(letters_num[0]=='C')
		{
			r=0;
		}
		
		if (letters_num[1]=='1')
		{
			c=0;
		}
		else if(letters_num[1]=='2')
		{
			c=1;
		}
		else if(letters_num[1]=='3')
		{
			c=2;
		}

		if (board[r][c] == 0)
		{
			valid_entered = 1;
		}
		else
		{
			printf("The entered position is not available! Please try again...\n");
		}
	}
	board [r][c]=player_num;
}

// Handle a Human v. Human game
void HumanVsHuman(int board[3][3],char player1_char,char player2_char,char player1_color,char player2_color)
{
	printf("Human v. Human game started\n");
	print_fun(board,player1_char,player2_char,player1_color,player2_color);
	int tie=1;
	while((is_there_empty_cell(board)))
	{
		printf("Player 1, please choose your move:");
		entered_one_char(board,1);
		print_fun(board,player1_char,player2_char,player1_color,player2_color);
		int win_flag = IsWin(board);
		if(win_flag != 0)
		{
			if (win_flag == 1)
			{
				printf("Player 1 wins! Game Over!\n\n");
			}
			else if (win_flag == 2)
			{
				printf("Player 2 wins! Game Over!\n\n");
			}
			tie=0;
			break;
		}
		else if (is_there_empty_cell(board)==0)
			break;
	
		printf("Player 2, please choose your move:");
		entered_one_char(board,2);
		print_fun(board,player1_char,player2_char,player1_color,player2_color);
		win_flag = IsWin(board);
		if(win_flag != 0)
		{
			if (win_flag == 1)
			{
				printf("Player 1 wins! Game Over!\n\n");
			}
			else if (win_flag == 2)
			{
				printf("Player 2 wins! Game Over!\n\n");
			}
			tie=0;
			break;
		}
	}
	if (tie==1)
		printf("The game is a tie!\n");
}

// Handle a Human v. AI game
void Human_Vs_AI(int board[3][3],char player1_char,char player2_char,char player1_color,char player2_color) // Human is always player1 and AI is player2
{
	printf("Human v. AI game started\n");
	print_fun(board,player1_char,player2_char,player1_color,player2_color);
	int tie=1;
	while((is_there_empty_cell(board)))
	{
		printf("Player 1, please choose your move:");
		entered_one_char(board,1);
		print_fun(board,player1_char,player2_char,player1_color,player2_color);
		int win_flag = IsWin(board);
		if(win_flag != 0)
		{
			if (win_flag == 1)
			{
				printf("Player 1 wins! Game Over!\n\n");
			}
			else if (win_flag == 2)
			{
				printf("AI wins! Game Over!\n\n");
			}
			tie=0;
			break;
		}
		else if (is_there_empty_cell(board)==0)
			break;

		printf("AI is choosing its move:\n");
        int foundMove = 0;
		for (int i=0; i<3; i++)
		{
			for (int j=0; j<3; j++)
			{
				if (board[i][j] == 0)
				{
                    board[i][j] = 2;
                    foundMove = 1;
					break;
				}
			}

            if(foundMove)
            {
                break;
            }
		}
		
		print_fun(board,player1_char,player2_char,player1_color,player2_color);
		win_flag = IsWin(board);
		if(win_flag != 0)
		{
			if (win_flag == 1)
			{
				printf("Player 1 wins! Game Over!\n\n");
			}
			else if (win_flag == 2)
			{
				printf("AI wins! Game Over!\n\n");
			}
			tie=0;
			break;
		}
		else if (is_there_empty_cell(board)==0)
			break;
	}
	if (tie==1)
	{
		printf("The game is a tie!\n");
	}

}

// Main Program for Tic-Tac-Whoa
int main()
{
    // initialize game
	char player1_char='X';
	char player2_char='O';
	char player1_color='d';
	char player2_color='d';

	printf("Welcome to Secure-Tic-Tac-Whoa!\n");
	int done=0;
	while(done==0)
	{
		int board[3][3]={{0,0,0},{0,0,0},{0,0,0}};
		int option = print_menu();
		switch(option)
		{
			case 1:
				HumanVsHuman(board,player1_char,player2_char,player1_color,player2_color);
				break;
			case 2:
				Human_Vs_AI(board,player1_char,player2_char,player1_color,player2_color);
				break;
			case 3:
				settings(&player1_char, &player2_char, &player1_color, &player2_color);
				break;
			case 4:
				printf("Thanks for playing. Exiting game...\n");
				done=1;
				break;
		}
		
	}
	return 0;
}

/* EOF */
