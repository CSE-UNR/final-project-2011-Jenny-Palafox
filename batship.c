//Jenny Palafox
//final project Batship Game
//7.26.2024
//This program will be a take on the game battleship. The user will be shown a blank board with letters for columns and numbers for rows, which will be used to reference spaces on the board. The user will be prompted to enter a location on the board and it will then be uncovered. Once all ships have been found or all spaces shown the users score will appear on the screen. Next they will be given the choice to play again or exit. 

#include <stdio.h>
#include <stdbool.h>
#define SIZE 10
#define FILE_NAME "easy.txt"

void loadBoard(FILE* fin, char shiplocation[][SIZE]);
void Printboard(char batshipboard[][SIZE]);
void GetMove(int UserMoves[][SIZE], char batshipboard[][SIZE],char shiplocation[][SIZE]);
void updateboard(char shiplocation[][SIZE], char batshipboard[][SIZE], int colposition, int rowposition, int* ptrHits, int* ptrguesses);
bool GameOver(int shiphit, int tries);
bool Playagain(char batshipboard[SIZE][SIZE]);

int main ()
{	bool PlayGame = true;

	do
	{	
		char batshiploc[SIZE][SIZE];
		int playerMoves[SIZE][SIZE];
		char batshipboard[SIZE][SIZE];
		
		for(int row = 0; row < SIZE; row++)
		{for(int col = 0; col < SIZE; col ++)
			{
				batshipboard[row][col] = ' ';
			}
		}
		
		printf("\n*****LET'S PLAY BATSHIP*****\n\n");
			
		FILE* fp;
		fp = fopen(FILE_NAME, "r");
		if(fp == NULL)
		{ 
			printf("Can't open file. \n");
			return 0;	
		}
			
		loadBoard(fp , batshiploc);
		fclose(fp);
		GetMove(playerMoves, batshipboard,batshiploc);
		PlayGame = Playagain(batshipboard);
	}
	while(PlayGame == true);
	
	return 0;
}



void Printboard(char batshipboard[][SIZE])
{	int incrementletter = 0, increasenum = 0, num = 1;
	char colname;
	
	printf("  ");
	for(int i = 0; i < SIZE; i++)
	{ 
		colname = 'A' + incrementletter;
		printf("%2c", colname);
		incrementletter++;
	}
	
	for (int row = 0; row < SIZE; row++)
	{
		printf("\n%d ", num);
		for(int col = 0; col < SIZE; col++)
		{	if(row==9)
			{printf("%c ", batshipboard[row][col]);}
			else
			{printf(" %c", batshipboard[row][col]);}
		}
		num++;
	}
	printf("\n");
}

void loadBoard(FILE* fin, char shiplocation[][SIZE])
{
	char temp;
	for(int row = 0; row < SIZE; row++){
		for(int col = 0; col < SIZE; col++){
			fscanf(fin,"%c", &shiplocation[row][col]);
		}
		fscanf(fin, "%c", &temp);
	}	
}

void GetMove(int UserMoves[][SIZE], char batshipboard[][SIZE], char shiplocation[][SIZE]) 
{	
	bool valid = false, Done;
	int row, rowposition, colposition, col, hits = 0, tries= 0;
	char colcharacter;
Printboard(batshipboard);
	do
 	{	printf("      FIRE AWAY!");
		
		while( valid == false )
		{
			printf("\n(enter a spot in the grid like A1) ");
			scanf(" %c %d", &colcharacter, &rowposition);

			switch(colcharacter)
			{
				case 'A':
					colposition = 0;
				break;
				case 'B':
					colposition = 1;
					break;
				case 'C':
					colposition = 2;
					break;
				case 'D' :
					colposition = 3;
					break;
				case 'E' :
					colposition = 4;
					break;
				case 'F':
					colposition = 5;
					break;
				case 'G':
					colposition = 6;
					break;
				case 'H':
					colposition = 7;
					break;
				case 'I':
					colposition = 8;
					break;
				case 'J' :
					colposition = 9;
					break;
				default:
					colposition = 20;
					break;	
			}
			
				 if(colposition > SIZE )
					{	printf("\nInvalid column letter. Try again!");
						valid= false;
					}
						
				else if(rowposition > SIZE)
					{	printf("\nInvalid row number. Try again!");
						valid= false;
					}
			
				
				else if(colposition <= SIZE && rowposition <= SIZE)
				{	valid= true;
					updateboard(shiplocation, batshipboard, colposition, rowposition, &hits, &tries);
					Done = GameOver(hits, tries);
				}
		}
		valid = false;		
	}
	while( Done == false);
}


void updateboard(char shiplocation[][SIZE], char batshipboard[][SIZE], int colposition, int rowposition, int* ptrHits, int* ptrguesses)
{

int numhits=0, numtries=0;
for(int row = 0; row< SIZE; row++){
	for(int col = 0; col < SIZE; col ++){
		if(row==rowposition-1 && col== colposition)
		{
			if(shiplocation[row][col] == 'S')
			{
				batshipboard[row][col] = 'X';
				*ptrHits = ( 1 + *ptrHits);
				//Put E for empty space in case the same position is called again. With the E in its place the X will not be counted twice.
				shiplocation[row][col] = 'E';
			}
			else if(shiplocation[row][col] == ' ')
			{batshipboard[row][col] = 'O'; }
		}
	}
}
	*ptrguesses= ( 1 + *ptrguesses);
	Printboard(batshipboard);
}

bool GameOver(int shiphit, int tries)
{	
	int score, shipamount = 31;
	bool over;
	
	if(shipamount == shiphit)
	{
		score = 100-(tries - shipamount);
		printf("\nCONGRATULATIONS!!!!\n");
		printf("It took %d turns for you to hit 31 spots and destroy all the ships\n", tries);
		printf("Your score is %d!\n", score);
		return true;
	}
	
	else
	{ return false;	}
}

bool Playagain(char batshipboard[SIZE][SIZE])
{
	char answer;
	printf("\nPlay again? (Y/N) ");
	scanf(" %c", &answer);
	
	if(answer == 'Y' || answer == 'y')
	{ 
		for(int row = 0; row < SIZE; row++)
		{for(int col = 0; col < SIZE; col ++)
			{batshipboard[row][col] = ' '; }
		}
		 return true; 
	}
	
	else if(answer == 'N' || answer== 'n')
	{ return false; }

}

