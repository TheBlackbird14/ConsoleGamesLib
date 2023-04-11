#include <stdio.h>

#include "../libs/strcap.h"
#include "../libs/cs50.h"
#include "../libs/colors.h"

void initialize(void);
void printp1(void);
void printp2(void);

char boardp1[10][10];
char boardp2[10][10];

int main(void)
{

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

void printp1(void)
{
    printf("Your Sea: \n");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (boardp1[i][j] == ' ')
            {
                printf(bgCyan" "off);
            }
            if (boardp1[i][j] == 'X')
            {
                printf(bgBlack " " off);
            }
            if (boardp1[i][j] == 'O')
            {
                printf(bgCyan white"O"off);
            }
            if (boardp1[i][j] == 'h')
            {
                printf(bgBlack red"X"off);
            }
            
        }
        printf("\n"); 
    }
    printf("\n\n");

    printf("Enemy Sea: \n");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (boardp1[i][j] == ' ')
            {
                printf(bgCyan" "off);
            }
            if (boardp1[i][j] == 'O')
            {
                printf(bgCyan white"O"off);
            }
            if (boardp1[i][j] == 'h')
            {
                printf(bgBlack red"X"off);
            }
            
        }
    }
}