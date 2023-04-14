#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "../libs/strcap.h"
#include "../libs/cs50.h"
#include "../libs/colors.h"

#define hitship "\033[31;47m"
#define missed "\033[37;44m"

void initialize(void);
void place(void);
void instructions(void);

void clear(void);
void waitfor(char input);
void quit(void);

void print(char you[10][10], char enemy[10][10]);
int checkInput(string input);
int checkPlacement(int user, int shipnr, string coords, char dir);

char boardp1[10][10]; 
/* = {
{'X', 'O', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
{'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
{'H', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
{'H', ' ', ' ', ' ', 'O', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', 'O', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X'},
};
 */
char boardp2[10][10];
/*  = {
{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', 'X', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', 'O', 'X', 'O', ' ', ' '},
{' ', ' ', ' ', 'O', ' ', ' ', 'X', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', 'H', 'O', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', 'O', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
}; */


char tablenames[2][10] = {{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}, {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'}};
int done = 0;
int turnp1;
int turnp2;
int turns = 0;

string input1;
string input2;


#define MAX_SHIPS 5
struct shipp1
{
    int size;
    int row;
    int col;
    char dir;
};

struct shipp1 shipsp1[MAX_SHIPS];


struct shipp2
{
    int size;
    int row;
    int col;
    char dir;
};

struct shipp2 shipsp2[MAX_SHIPS];


int main(void)
{
    clear();
    initialize();
    instructions();

    while (!done) 
    {
        if (turns == 0)
        {
            place();
            printf("Press ENTER to start as player one");
        }
        else
        {
            clear();
            printf("Press ENTER to continue as player one");
        }
        
        waitfor('\n');
        turnp1 = 1;

        while (turnp1)
        {
            turns++;
            clear();
            print(boardp1, boardp2);
            do
            {
                input1 = strup(get_string("Player 1> "));
            } 
            while (checkInput(input1) != 0);


            //check if was hit
            printf("%s\n", input1);

            //if miss
            turnp1 = 0;
            turnp2 = 1;
            printf("ENTER to end turn");
            waitfor('\n');
        }

        clear();
        printf("ENTER to continue as Player 2");
        waitfor('\n');

        while (turnp2)
        {
            turns++;
            clear();
            print(boardp2, boardp1);
            do
            {
                input2 = strup(get_string("Player 2> "));
            } 
            while (checkInput(input2) != 0);


            printf("%s\n", input2);

            turnp2 = 0;
            printf("ENTER to end turn");
            waitfor('\n');
        }

    }
}

void clear(void)
{
    printf("\e[1;1H\e[2J");
}

void initialize(void)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            boardp1[i][j] = ' ';
            boardp2[i][j] = ' ';
        }
    }
}

void print(char you[10][10], char enemy[10][10])
{

    //print own sea
    printf("Your Sea: \n\n ");
    for (int i = 0; i < 10; i++)
    {
        printf(" | %c", tablenames[0][i]);
    }
    printf("\n\n");
    
    for (int i = 0; i < 10; i++)
    {
        printf("%c", tablenames[1][i]);
        for (int j = 0; j < 10; j++)
        {
            //normsal sea (nothing)
            if (you[i][j] == ' ')
            {
                printf(" | %s %s", bgBlue, off);
            }
            //ship placed on tile
            if (you[i][j] == 'X')
            {
                printf(" | %s %s", bgWhite, off);
            }
            //shot fires but missed
            if (you[i][j] == 'O')
            {
                printf(" | %sO%s", missed, off);
            }
            //shot fired and hit ship
            if (you[i][j] == 'H')
            {
                printf(" | %sX%s", hitship, off);
            }
        }
        printf("\n\n"); 
    }
    printf("\n\n");


    //print enemy sea
    printf("Enemy Sea: \n\n ");

    for (int i = 0; i < 10; i++)
    {
        printf(" | %c", tablenames[0][i]);
    }
    printf("\n\n");

    for (int i = 0; i < 10; i++)
    {
        printf("%c", tablenames[1][i]);
        for (int j = 0; j < 10; j++)
        {
            if (enemy[i][j] == 'O') //shot fired and missed
            {
                printf(" | %sO%s", missed, off);
            }
            else if (enemy[i][j] == 'H') //shot fired and ship hit
            {
                printf(" | %sX%s", hitship, off);
            }
            else
            {
                printf(" | %s %s", bgBlue, off);
            }
        }
        printf("\n\n");
    }
    printf("\n\n");
}

void waitfor(char input)
{
    while (getchar() != input);
}

void instructions(void)
{
    printf("//instructions\n");
}

int checkInput(string input)
{
    int validnum = 0;
    int validletter = 0;
    if (strcmp(input, "QUIT") == 0)
    {
        quit();
    }
    
    for (int i = 0; i < 10; i++)
    {
        if (input[0] == tablenames[1][i])
        {
            validletter = 1;
            break;
        }
        
    }
    
    for (int i = 0; i < 10; i++)
    {
        if (input[1] == tablenames[0][i])
        {
            validnum = 1;
            break;
        }
        
    }

    if (validletter == 1 && validnum == 1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
    

}

void quit(void)
{
    clear();
    printf("Until Next Time!\n");
    exit(2);
}

void place(void)
{
    shipsp1[0].size = 2;
    shipsp1[1].size = 3;
    shipsp1[2].size = 3;
    shipsp1[3].size = 4;
    shipsp1[4].size = 5;
    
    shipsp2[0].size = 2;
    shipsp2[1].size = 3;
    shipsp2[2].size = 3;
    shipsp2[3].size = 4;
    shipsp2[4].size = 5;

    clear();
    print(boardp1, boardp2);

    for (int i = 0; i < MAX_SHIPS; i++)
    {
        string rowcol;
        char dir;

        do
        {
            rowcol = strup(get_string("Starting Point of Ship %d with length %d> ", i + 1, shipsp1[i].size));

            if (checkInput(rowcol) != 0)
            {
                continue;
            }

            dir = toupper(get_char("Direction of ship (u, d, l, r)> "));

            if (dir != 'u' && dir != 'd' && dir != 'l' && dir != 'r')
            {
                continue;
            }
        }
        while (checkPlacement(1, i, rowcol, dir) != 0);
        
        
        shipsp1[i].row = (rowcol[0] - 65);
        shipsp1[i].col = (rowcol[1] - 48);

        printf("Coords: [%d][%d]\n", shipsp1[i].row, shipsp1[i].col);

        shipsp1[i].dir = dir;

        printf("Dir: %c\n", shipsp1[i].dir);
       
    }

}

int checkPlacement(int user, int shipnr, string coords, char dir)
{
    int valid = 0;
    int empty = 1;
    int row = coords[0] - 65;
    int col = coords[1] - 48;
    int length = shipsp1[shipnr].size - 1;
    
    printf("Startcords: [%d][%d]\n", row, col);
    printf("Travellength: %d\n", length);
    printf("Endcoords if up: [%d][%d]\n", row - length, col);


    switch (dir)
    {
        case 'U':
            if ((row - length) >= 0)
            {
                valid = 1;
            }
            break;
        case 'D':
            if ((row + length) <= 9)
            {
                valid = 1;
            }
            break;
        case 'L':
            if ((col - length) >= 0)
            {
                valid = 1;
            }
            break;
        case 'R':
            if ((col + length) <= 9)
            {
                valid = 1;
            }
            break;
    }

    if (valid == 0)
    {
        return 1;
    }
    
    if (user == 1)
    {
        switch (dir)
        {
            case 'U':

                for (int i = row; i < length; i--)
                {
                    if (boardp1[i][col] == 'X')
                    {
                        empty = 0;
                        break;
                    }
                }
                
                break;

            case 'D':

                for (int i = row; i < length; i++)
                {
                    if (boardp1[i][col] == 'X')
                    {
                        empty = 0;
                        break;
                    }
                }

                break;

            case 'L':

                for (int i = col; i < length; i--)
                {
                    if (boardp1[row][i] == 'X')
                    {
                        empty = 0;
                        break;
                    }
                }

                break;

            case 'R':

                for (int i = col; i < length; i++)
                {
                    if (boardp1[row][i] == 'X')
                    {
                        empty = 0;
                        break;
                    }
                }

                break;

        }
    }

    if (user == 2)
    {
        switch (dir)
        {
            case 'U':

                for (int i = row; i < length; i--)
                {
                    if (boardp2[i][col] == 'X')
                    {
                        empty = 0;
                        break;
                    }
                }
                
                break;

            case 'D':

                for (int i = row; i < length; i++)
                {
                    if (boardp2[i][col] == 'X')
                    {
                        empty = 0;
                        break;
                    }
                }

                break;

            case 'L':

                for (int i = col; i < length; i--)
                {
                    if (boardp2[row][i] == 'X')
                    {
                        empty = 0;
                        break;
                    }
                }

                break;

            case 'R':

                for (int i = col; i < length; i++)
                {
                    if (boardp2[row][i] == 'X')
                    {
                        empty = 0;
                        break;
                    }
                }

                break;

        }
    }

    
    printf("Valid: %d\n", valid);
    printf("Empty: %d\n", empty);


    if (empty == 1 && valid == 1)
    {
	return 0;
    }
    else
    {
        return 1;
    }
}
