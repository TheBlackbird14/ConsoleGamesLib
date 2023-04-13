#include <stdio.h>

#include "../libs/strcap.h"
#include "../libs/cs50.h"
#include "../libs/colors.h"

void initialize(void);
void clear(void);
void waitfor(char input);
void print(char you[10][10], char enemy[10][10]);

char boardp1[10][10];
char boardp2[10][10];
char tablenames[2][10] = {{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'}, {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'}};

int main(void)
{
    clear();
    initialize();
    
    //testing
    boardp1[4][8] = 'X';
    boardp1[6][3] = 'O';
    boardp1[9][2] = 'h';

    boardp2[5][2] = 'X';
    boardp2[1][7] = 'O';
    boardp2[0][3] = 'h';

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
            if (you[i][j] == ' ')
            {
                printf(bgCyan"  "off);
            }
            if (you[i][j] == 'X')
            {
                printf(bgBlack "  " off);
            }
            if (you[i][j] == 'O')
            {
                printf(bgCyan white"O "off);
            }
            if (you[i][j] == 'h')
            {
                printf(bgBlack red"X "off);
            }
            
        }
        printf("\n"); 
    }
    printf("\n\n");

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
            if (enemy[i][j] == ' ')
            {
                printf(bgCyan"  "off);
            }
            if (enemy[i][j] == 'O')
            {
                printf(bgCyan white"O "off);
            }
            if (enemy[i][j] == 'h')
            {
                printf(bgBlack red"X "off);
            }
            
        }
        printf("\n");
    }
    printf("\n\n");
}

void waitfor(char input)
{
    while (getchar() != input);
}
