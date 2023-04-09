#include <stdio.h>
#include <stdlib.h>
#include "cs50.h"
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>

#include "strcap.h"

#define off "\e[m"

//colors
#define black "\e[0;30m"
#define red "\e[0;31m"
#define green "\e[0;32m"
#define yellow "\e[0;33m"
#define blue "\e[0;34m"
#define purple "\e[0;35m"
#define cyan "\e[0;36m"
#define white "\e[0;37m"

//bold
#define bBlack "\e[1;30m"
#define bRed "\e[1;31m"
#define bGreen "\e[1;32m"
#define bYellow "\e[1;33m"
#define bBlue "\e[1;34m"
#define bPurple "\e[1;35m"
#define bCyan "\e[1;36m"
#define bWhite "\e[1;37m"

//underline
#define uBlack "\e[4;30m"
#define uRed "\e[4;31m"
#define uGreen "\e[4;32m"
#define uYellow "\e[4;33m"
#define uBlue "\e[4;34m"
#define uPurple "\e[4;35m"
#define uCyan "\e[4;36m"
#define uWhite "\e[4;37m"

//background
#define bgBlack "\e[40m"
#define bgRed "\e[41m"
#define bgGreen "\e[42m"
#define bgYellow "\e[43m"
#define bgBlue "\e[44m"
#define bgPurple "\e[45m"
#define bgCyan "\e[46m"
#define bgWhite "\e[47m"

//extras
#define warning "\033[37;41m"
#define title "\033[1;32;44m"


void initialize(void);
void print(void);
void instructions(void);
void clear(void);
void setTile(char filler, char row, char column);
bool checkInput(char *input);
bool hasWon(char user);
int won(void);
int tie(void);
void help(void);

char board[3][3];


bool done;
char winner;

//const char *inputs[] = {"TL","TC","TR","ML","MC","MR","BL","BC","BR"};
char *fields[2][9] = {{"TL","TC","TR","ML","MC","MR","BL","BC","BR"}, {"0", "0", "0", "0", "0", "0", "0", "0", "0"}};

int main(void)
{
	clear();
	initialize();
	instructions();

	char user;
	user = 'X';
	string input;

	while(!done)
	{
		print();

		if(user == 'X')
		{
			do
			{
				input = strup(get_string(green"X" off " Turn> "purple));
			}
			while(checkInput(input) != 0);
			printf(off);

			setTile('X', input[0], input[1]);
			user = 'O';

		}
		else
		{
			do
			{
				input = strup(get_string(green"O" off " Turn> "purple));
			}
			while(checkInput(input) != 0);
			printf(off);

			setTile('O', input[0], input[1]);
			user = 'X';
		}

		if (tie() == 1)
		{
			printf(bgBlue "Tie!\n" off);
			char repeat;

			do
			{
				repeat = get_char(uBlack "Play another Round(y/n)> " bgRed);
			}
			while(toupper(repeat) != 'Y' && toupper(repeat) != 'N');
			printf(off);

			if (toupper(repeat) == 'Y')
			{
				winner = '\0';
				done = false;
				initialize();
				clear();
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

			if (won() == 0)
			{
				winner = '\0';
				done = false;
				initialize();
				clear();
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

			if (won() == 0)
			{
				winner = '\0';
				done = false;
				initialize();
				clear();
				continue;
			}
			else
			{
				break;
			}
		}
		clear();
	}
	clear();
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
	printf(title "Welcome to TicTacToe\n\n" off);
	printf("To set an " green "X " off "or" green" O" off ", type the location you would like to put it.\n\n");
	printf(cyan "Rows " off "from top to bottom are Top, Middle and Bottom " cyan "(or T, M and B)." off "\n");
	printf(cyan "Columns " off "are Left, Center and Right " cyan "(or L, C and R)." off "\n\n");
	printf("To Place a tile, type the letters for the Row and Column, eg. " bPurple "ML" off " for " bPurple "Middle Left" off " " warning "first Row then Column!" off "\n\n");
	printf("Type " bYellow "\"help\"" off " at any time to view board layout.\n\n");
	printf(green "X " off "starts. Have fun!\n\n");
	printf("Press" bRed " ENTER " off "to start");
	while( getchar() != '\n' );
	clear();
}

void clear(void)
{
	printf("\e[1;1H\e[2J");
}


void setTile(char filler, char row, char column)
{
	int arow;
	int acolumn;

	switch(row)
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

	switch(column)
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

bool checkInput(char *input)
{
	if (strcmp(input, "QUIT") == 0)
	{
		clear();
		printf(off);
		exit(2);
	}

	if (strcmp(input, "HELP") == 0)
	{
		help();
	}

	bool valid = false;
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
	clear();
	print();
	printf("\n");
	printf(green"%c " off "has won!" off"\n", winner);
	char repeat;

	do
	{
		repeat = get_char(uBlack "Play another Round(y/n)> " bgRed);
	}
	while(toupper(repeat) != 'Y' && toupper(repeat) != 'N');
	printf(off);

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
}
