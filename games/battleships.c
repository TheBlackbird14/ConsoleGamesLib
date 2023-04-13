#include <stdio.h>

#include "../libs/strcap.h"
#include "../libs/cs50.h"
#include "../libs/colors.h"

#define hitship "\033[31;47m"
#define missed "\033[37;44m"

void initialize(void);
void clear(void);
void waitfor(char input);
void print(char you[10][10], char enemy[10][10]);

char boardp1[10][10] = {
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

char boardp2[10][10] = {
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
};


char tablenames[2][10] = {{'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'}, {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'}};

int main(void)
{
    clear();
    //initialize();


    printf("//instructions\n");
    printf("Press ENTER to start as player one");
    waitfor('\n');
    clear();
    print(boardp1, boardp2);
    printf("ENTER to continue");
    waitfor('\n');
    clear();
    printf("Press ENTER to continue as player two");
    waitfor('\n');
    clear();
    print(boardp2, boardp1);

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
    printf("Your Sea: \n ");
    for (int i = 0; i < 10; i++)
    {
        printf("%c ", tablenames[0][i]);
    }
    printf("\n");
    
    for (int i = 0; i < 10; i++)
    {
        printf("%c", tablenames[1][i]);
        for (int j = 0; j < 10; j++)
        {
            //normsal sea (nothing)
            if (you[i][j] == ' ')
            {
                printf(" %s %s", bgBlue, off);
            }
            //ship placed on tile
            if (you[i][j] == 'X')
            {
                printf(" %s %s", bgWhite, off);
            }
            //shot fires but missed
            if (you[i][j] == 'O')
            {
                printf(" %sO%s", missed, off);
            }
            //shot fired and hit ship
            if (you[i][j] == 'H')
            {
                printf(" %sX%s", hitship, off);
            }
        }
        printf("\n\n"); 
    }
    printf("\n\n");


    //print enemy sea
    printf("Enemy Sea: \n ");

    for (int i = 0; i < 10; i++)
    {
        printf("%c ", tablenames[0][i]);
    }
    printf("\n");

    for (int i = 0; i < 10; i++)
    {
        printf("%c", tablenames[1][i]);
        for (int j = 0; j < 10; j++)
        {
            //empty sea
            if (enemy[i][j] == ' ')
            {
                printf(" %s %s", bgBlue, off);
            }
            //shot fired and missed
            if (enemy[i][j] == 'O')
            {
                printf(" %sO%s", missed, off);
            }
            //shot fired and ship hit
            if (enemy[i][j] == 'H')
            {
                printf(" %sX%s", hitship, off);
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
