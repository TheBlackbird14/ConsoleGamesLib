#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>
#include <stdbool.h>

#include "../libs/strcap.h"
#include "../libs/colors.h"
#include "../libs/CGLgeneral.h"


void initialize(void);
void print(void);
void instructions(void);
void setTile(char filler, char row, char column);
int checkInput(char *input);
bool hasWon(char user);
int won(void);
int tie(void);
void help(void);
void pclearBoard(void);

char board[3][3];


bool done;
bool reset;
char winner;
int turns = 0;

//const char *inputs[] = {"TL","TC","TR","ML","MC","MR","BL","BC","BR"};
char *fields[2][9] = {{"TL","TC","TR","ML","MC","MR","BL","BC","BR"}, {"0", "0", "0", "0", "0", "0", "0", "0", "0"}};

int main(void)
{
	reset = false;
	pclear();
	initialize();
	instructions();

	char user = 'X';
	char startingUser = 'X';


	while(!done)
	{
		if (turns == 0)
		{
			user = startingUser;
		}

		print();

		if(user == 'X')
		{
			turns++;

			char input[5];
			int c;
			do
			{
				printf(green"X" off " Turn> "purple);
				scanf("%4s", input);
				printf(off);
				while ((c = getchar()) != '\n' && c != EOF);  // pclear input buffer

				//printf("%s\n", strup(input));
				//while (getchar() != '\n');

			} 
			while(checkInput(strup(input)) != 0);

			if (reset == true)
			{
				pclearBoard();
				continue;
			}

			setTile('X', input[0], input[1]);
			user = 'O';

		}
		else
		{
			turns++;

			char input[5];
			int c;
			do
			{
				printf(green"O" off " Turn> "purple);
				scanf("%4s", input);
				printf(off);
				while ((c = getchar()) != '\n' && c != EOF);  // pclear input buffer
			} 
			while(checkInput(strup(input)) != 0);

			if (reset == true)
			{
				pclearBoard();
				continue;
			}

			setTile('O', input[0], input[1]);
			user = 'X';
		}

		if (tie() == 1)
		{
			printf(bgBlue "Tie!\n" off);
			char repeat;

			do
			{
				printf(uGreen "Play another Round(y/n)> " bgRed);
				scanf("%1c", &repeat);
				printf(off);
			}
			while(toupper(repeat) != 'Y' && toupper(repeat) != 'N');

			if (toupper(repeat) == 'Y')
			{
				pclearBoard();
				continue;
			}
			else
			{
				break;
			}
		}

		if (hasWon('X') == true)
		{
			done = true;
			winner = 'X';
			startingUser = 'O';

			if (won() == 0)
			{
				pclearBoard();
				continue;
			}
			else
			{
				break;
			}
		}

		if (hasWon('O') == true)
		{
			done = true;
			winner = 'O';
			startingUser = 'X';

			if (won() == 0)
			{
				pclearBoard();
				continue;
			}
			else
			{
				break;
			}
		}
		pclear();
	}
	pclear();
	printf(uBlack "Until Next Time!\n"off);
}


void initialize(void)
{
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			board[i][j] = ' ';
		}
	}
	for (int i = 0; i < 9; i++)
	{
		fields[1][i] = "0";
	}
}


void print(void)
{
	setlocale(LC_CTYPE, "");
	// Define variables for box drawing characters
    wchar_t vLine = L'\u2502';
    wchar_t hLine = L'\u2500';
    wchar_t cross = L'\u253C';

    // Print the game
    for (int i = 0; i < 3; i++)
	{
		printf("%lc%lc%lc%lc%lc%lc%lc\n", hLine, hLine, hLine, hLine, hLine, hLine, hLine);
		for (int j = 0; j < 3; j++)
		{
			printf("%lc%c", vLine, board[i][j]);
		}
		printf("%lc\n", vLine);
	}
	printf("%lc%lc%lc%lc%lc%lc%lc\n", hLine, hLine, hLine, hLine, hLine, hLine, hLine);


}

void instructions(void)
{
	printf(title "Welcome to TicTacToe"off"\n\n");
	printf("To set an " green "X " off "or" green" O" off ", type the location you would like to put it.\n\n");
	printf(cyan "Rows " off "from top to bottom are Top, Middle and Bottom " cyan "(or T, M and B)." off "\n");
	printf(cyan "Columns " off "are Left, Center and Right " cyan "(or L, C and R)." off "\n\n");
	printf("To Place a tile, type the letters for the Row and Column, eg. " bPurple "ML" off " for " bPurple "Middle Left" off " " warning "first Row then Column!" off "\n\n");
	printf("Type " bYellow "\"help\"" off " at any time to view board layout.\n\n");
	printf(green "X " off "starts. Have fun!\n\n");
	printf("Press" bRed " ENTER " off "to start");
	while( getchar() != '\n' );
	pclear();
}

void setTile(char filler, char row, char column)
{
	int arow;
	int acolumn;

	switch(toupper(row))
	{
		case 'T':
			arow = 0;
			break;
		case 'M':
			arow = 1;
			break;
		case 'B':
			arow = 2;
			break;
	}

	switch(toupper(column))
	{
		case 'L':
			acolumn = 0;
			break;
		case 'C':
			acolumn = 1;
		 	break;
		case 'R':
			acolumn = 2;
			break;
	}

	board[arow][acolumn] = filler;
	int index = (arow * 3) + acolumn;
	fields[1][index] = "1";
}

int checkInput(char *input)
{
	
	bool valid = false;
	
	if (strcmp(input, "QUIT") == 0)
	{
		quit();
	}

	if (strcmp(input, "HELP") == 0)
	{
		help();
	}

	if (strcmp(input, "RESTART") == 0)
	{
		valid = true;
		reset = true;
	}

	for (int i = 0; i < 9; i++)
	{
		if (strcmp(input, fields[0][i]) == 0)
		{
			valid = true;
			break;
		}
	}
	for (int i = 0; i < 9; i++)
	{
		if (strcmp(input, fields[0][i]) == 0)
		{
			if (strcmp(fields[1][i], "0") == 0)
			{
				valid = true;
				break;
			}
			else
			{
				valid = false;
				break;
			}

		}
	}
	if (valid == true)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

bool hasWon(char user)
{
	//check rows
	for (int i = 0; i < 3; i++)
	{
		if (board[i][0] == user && board[i][1] == user && board[i][2] == user)
		{
			return 1;
		}
	}

	//check columns
	for (int i = 0; i < 3; i++)
	{
		if (board[0][i] == user && board[1][i] == user && board[2][i] == user)
		{
			return 1;
		}
	}

	//check diagonals
	if (board[0][0] == user && board[1][1] == user && board[2][2] == user)
	{
		return 1;
	}

	if (board[0][2] == user && board[1][1] == user && board[2][0] == user)
	{
		return 1;
	}

	return 0;
}

int won(void)
{
	pclear();
	print();
	printf("\n");
	printf(green"%c " off "has won!" off"\n", winner);
	char repeat;

	do
	{
		printf(uGreen "Play another Round(y/n)> " bgRed);
		scanf("%1c", &repeat);
		printf(off);
	}
	while(toupper(repeat) != 'Y' && toupper(repeat) != 'N');

	if (toupper(repeat) == 'Y')
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int tie(void)
{
	for (int i = 0; i < 9; i++)
	{
		if (strcmp(fields[1][i], "0") == 0)
		{
			return 0;
			break;
		}
	}
	if (hasWon('X') == true || hasWon('O') == true)
	{
		return 0;
	}
	return 1;
}

void help(void)
{
	setlocale(LC_CTYPE, "");
	// Define variables for box drawing characters
    wchar_t vLine = L'\u2502';
    wchar_t hLine = L'\u2500';
    wchar_t cross = L'\u253C';

	int index = 0;
    // Print the game
    for (int i = 0; i < 3; i++)
	{
		printf(bgCyan "%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc\n", hLine, hLine, hLine, hLine, hLine, hLine, hLine, hLine, hLine, hLine);
		for (int j = 0; j < 3; j++)
		{
			printf("%lc%s", vLine, fields[0][index++]);
		}
		printf("%lc\n", vLine);
	}
	printf("%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc\n\n" off, hLine, hLine, hLine, hLine, hLine, hLine, hLine, hLine, hLine, hLine);


	printf(bgRed "\"quit\" to exit program\n\n" off);
	printf(caution "\"restart\" to restart the game\n\n" off);
}


void pclearBoard(void)
{
	winner = '\0';
	done = false;
	reset = false;
	turns = 0;
	initialize();
	pclear();
}