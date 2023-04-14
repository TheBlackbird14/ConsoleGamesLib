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
void placeOnBoard(int user, int row, int col, char dir, int length);
void printPlacement(char user[10][10]);
void instructions(void);

void clear(void);
void waitfor(char input);
void quit(void);

void print(char you[10][10], char enemy[10][10]);
int checkInput(int user, string input);
int checkPlacement(int user, int shipnr, string coords, char dir);
int shoot(int user, int row, int col);

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
            clear();
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
            while (checkInput(1, input1) != 0);

            //if hit
            if (shoot(1, input1[0], input1[1]) != 0)
            {
                shoot(1, input1[0], input1[1]);
                clear();
                print(boardp1, boardp2);
                printf("HIT! Your turn again\n");
                waitfor('\n');
            }
            else if (shoot(1, input1[0], input1[1]) == 0)
            {
                printf("Miss!\n");
                turnp2 = 1;
                turnp1 = 0;
                printf("ENTER to end turn");
                waitfor('\n');

            }

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
            while (checkInput(2, input2) != 0);

            //if hit
            if (shoot(2, input2[0], input2[1]) != 0)
            {
                shoot(2, input2[0], input2[1]);
                clear();
                print(boardp2, boardp1);
                printf("HIT! Your turn again\n");
                waitfor('\n');
            }
            else if (shoot(2, input2[0], input2[1]) == 0)
            {
                
                turnp2 = 0;
                turnp1 = 1;
                printf("ENTER to end turn");
                waitfor('\n');
            }

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
    printf(" |\n  ");
        for (int i = 0; i < 10; i++)
        {
            printf("----");
        }
    printf("-\n");
    
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
        printf(" |\n  ");
        for (int i = 0; i < 10; i++)
	    {
	        printf("----");
	    }
	printf("-\n");
    }
    printf("\n\n");


    //print enemy sea
    printf("Enemy Sea: \n\n ");

    for (int i = 0; i < 10; i++)
    {
        printf(" | %c", tablenames[0][i]);
    }
    printf(" |\n  ");
        for (int i = 0; i < 10; i++)
        {
            printf("----");
        }
    printf("-\n");

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
        printf(" |\n  ");
        for (int i = 0; i < 10; i++)
        {
            printf("----");
        }
        printf("-\n");
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

int checkInput(int user, string input)
{
    int validnum = 0;
    int validletter = 0;

    int alreadyShot = 0;
    int row = input[0] - 65;
    int col = input[1] - 48;

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

    if (user == 1)
    {
        if (boardp1[row][col] == 'O' || boardp1[row][col] == 'H')
        {
            alreadyShot = 1;
        }
    }
    if (user == 2)
    {
        if (boardp2[row][col] == 'O' || boardp2[row][col] == 'H')
        {
            alreadyShot = 1;
        }
    }

    if (validletter == 1 && validnum == 1 && alreadyShot == 0)
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
    printPlacement(boardp1);

    for (int i = 0; i < MAX_SHIPS; i++)
    {
        string rowcol;
        char dir;

        do
        {
            rowcol = strup(get_string("Starting Point of Ship %d with length %d> ", i + 1, shipsp1[i].size));

            if (checkInput(1, rowcol) != 0)
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

        

        shipsp1[i].dir = dir;

        

        placeOnBoard(1, shipsp1[i].row, shipsp1[i].col, shipsp1[i].dir, shipsp1[i].size);
        
        clear();
        printPlacement(boardp1);
        
        /* printf("Dir: %c\n", shipsp1[i].dir);
        printf("Coords: [%d][%d]\n", shipsp1[i].row, shipsp1[i].col);
        
        waitfor('\n'); */
        
       
    }

    printf("ENTER to end turn");
    waitfor('\n');
    clear();
    printf("ENTER to continue as player 2");
    waitfor('\n');
    
    
    clear();
    printPlacement(boardp2);

    for (int i = 0; i < MAX_SHIPS; i++)
    {
        string rowcol;
        char dir;

        do
        {
            rowcol = strup(get_string("Starting Point of Ship %d with length %d> ", i + 1, shipsp2[i].size));

            if (checkInput(2, rowcol) != 0)
            {
                continue;
            }

            dir = toupper(get_char("Direction of ship (u, d, l, r)> "));

            if (dir != 'u' && dir != 'd' && dir != 'l' && dir != 'r')
            {
                continue;
            }
        }
        while (checkPlacement(2, i, rowcol, dir) != 0);
        
        
        shipsp2[i].row = (rowcol[0] - 65);
        shipsp2[i].col = (rowcol[1] - 48);

        

        shipsp2[i].dir = dir;

        

        placeOnBoard(2, shipsp2[i].row, shipsp2[i].col, shipsp2[i].dir, shipsp2[i].size);
        
        clear();
        printPlacement(boardp2);
        
        /* printf("Dir: %c\n", shipsp2[i].dir);
        printf("Coords: [%d][%d]\n", shipsp2[i].row, shipsp2[i].col);
        
        waitfor('\n'); */
        
       
    }

    printf("ENTER to end turn");
    waitfor('\n');

}

int checkPlacement(int user, int shipnr, string coords, char dir)
{
    int valid = 0;
    int empty = 1;
    int row = coords[0] - 65;
    int col = coords[1] - 48;
    int length = shipsp1[shipnr].size - 1;
    
    //printf("Startcords: [%d][%d]\n", row, col);
    //printf("Travellength: %d\n", length);
    //printf("Endcoords if up: [%d][%d]\n", row - length, col);


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

    //check for filled tiles
    
    if (user == 1)
    {
        switch (dir)
        {
            case 'U':

                for (int i = 0, j = row; i < length; i++, j--)
                {
                    if (boardp1[j][col] == 'X')
                    {
                        empty = 0;
                        break;
                    }
                }
                
                break;

            case 'D':

                for (int i = 0, j = row; i < length; i++, j++)
                {
                    if (boardp1[j][col] == 'X')
                    {
                        empty = 0;
                        break;
                    }
                }

                break;

            case 'L':

                for (int i = 0, j = col; i < length; i++, j--)
                {
                    if (boardp1[row][j] == 'X')
                    {
                        empty = 0;
                        break;
                    }
                }

                break;

            case 'R':

                for (int i = 0, j = col; i < length; i++, j--)
                {
                    if (boardp1[row][j] == 'X')
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

                for (int i = 0, j = row; i < length; i++, j--)
                {
                    if (boardp2[j][col] == 'X')
                    {
                        empty = 0;
                        break;
                    }
                }
                
                break;

            case 'D':

                for (int i = 0, j = row; i < length; i++, j++)
                {
                    if (boardp2[j][col] == 'X')
                    {
                        empty = 0;
                        break;
                    }
                }

                break;

            case 'L':

                for (int i = 0, j = col; i < length; i++, j--)
                {
                    if (boardp2[row][j] == 'X')
                    {
                        empty = 0;
                        break;
                    }
                }

                break;

            case 'R':

                for (int i = 0, j = col; i < length; i++, j--)
                {
                    if (boardp2[row][j] == 'X')
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

void placeOnBoard(int user, int row, int col, char dir, int length)
{
    if (user == 1)
    {
        switch (dir)
        {
            case 'U':
            
            for (int i = 0, j = row; i < length; i++, j--)
            {
                boardp1[j][col] = 'X';
            }

            break;

            case 'D':
            
            for (int i = 0, j = row; i < length; i++, j++)
            {
                boardp1[j][col] = 'X';
            }

            break;

            case 'L':
            
            for (int i = 0, j = col; i < length; i++, j--)
            {
                boardp1[row][j] = 'X';
            }

            break;

            case 'R':
            
            for (int i = 0, j = col; i < length; i++, j++)
            {
                boardp1[row][j] = 'X';
            }

            break;
        }

    }

    if (user == 2)
    {
        switch (dir)
        {
            case 'U':
            
            for (int i = 0, j = row; i < length; i++, j--)
            {
                boardp2[j][col] = 'X';
            }

            break;

            case 'D':
            
            for (int i = 0, j = row; i < length; i++, j++)
            {
                boardp2[j][col] = 'X';
            }

            break;

            case 'L':
            
            for (int i = 0, j = col; i < length; i++, j--)
            {
                boardp2[row][j] = 'X';
            }

            break;

            case 'R':
            
            for (int i = 0, j = row; i < length; i++, j++)
            {
                boardp2[row][j] = 'X';
            }

            break;
        }

    }
}

void printPlacement(char user[10][10])
{
    //print own sea
    printf("Your Sea: \n\n ");
    for (int i = 0; i < 10; i++)
    {
        printf(" | %c", tablenames[0][i]);
    }
    printf(" |\n  ");
        for (int i = 0; i < 10; i++)
        {
            printf("----");
        }
    printf("-\n");
    
    for (int i = 0; i < 10; i++)
    {
        printf("%c", tablenames[1][i]);
        for (int j = 0; j < 10; j++)
        {
            //normsal sea (nothing)
            if (user[i][j] == ' ')
            {
                printf(" | %s %s", bgBlue, off);
            }
            //ship placed on tile
            if (user[i][j] == 'X')
            {
                printf(" | %s %s", bgWhite, off);
            }
            //shot fires but missed
            if (user[i][j] == 'O')
            {
                printf(" | %sO%s", missed, off);
            }
            //shot fired and hit ship
            if (user[i][j] == 'H')
            {
                printf(" | %sX%s", hitship, off);
            }
        }
        printf(" |\n  ");
        for (int i = 0; i < 10; i++)
	    {
	        printf("----");
	    }
	printf("-\n");
    }
    printf("\n\n");
}

int shoot(int user, int row, int col)
{
    int hit = 0;
    if (user == 1)
    {
        switch (boardp2[row][col])
        {
            case ' ':
            boardp2[row][col] = 'O';
            break;

            case 'X':
            boardp2[row][col] = 'H';
            hit = 1;
            break;
        }
    }
    else
    {
        switch (boardp1[row][col])
        {
            case ' ':
            boardp1[row][col] = 'O';
            break;

            case 'X':
            boardp1[row][col] = 'H';
            hit = 1;
            break;
        }
    }

    return hit;
}