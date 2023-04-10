#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "./libs/strcap.h"
#include "./libs/colors.h"

int checkInput(char *input);
void quit(void);
void clear(void);
void instructions();
void help(void);
void list(void);

bool done;

int totalGames = 1;
char *games[2][1] = {{"TICTACTOE"}, {"1"}};

int main(void)
{
    clear();

    instructions();

    char input[50];

    while(!done)
    {
        do
        {
            char inputCache[50];
            printf("ConsoleGamesLib> ");
            scanf("%s", inputCache);
            strcpy(input, strup(inputCache));
            //printf("Input: %s\n", input);
            //printf("Check: %d\n", checkInput(input));

        }
        while ((checkInput(input) - 1)  < 0);

        int gameNum;
        char rungame[strlen(input)];
        
        gameNum = checkInput(input) - 1;
        strcpy(rungame, games[0][gameNum]);


        char command[50] = "./games/";
        strcat(command, strlow(rungame));

        //printf("%s\n", command);

        system(command);

        printf("Welcome back\n");

    }

}

int checkInput(char *input)
{
    bool valid = false;
    int gameNum;

    if (strcmp(input, "QUIT") == 0)
    {
        quit();
    }

    if (strcmp(input, "HELP") == 0)
    {
        help();
    }

    if (strcmp(input, "LIST") == 0)
    {
        list();
    }


    for (int i = 0; i < totalGames; i++)
    {
        if (strcmp(games[0][i], input) == 0)
        {
            valid = true;
            gameNum = i + 1;
            break;
        }
        
        if (strcmp(games[1][i], input) == 0)
        {
            valid = true;
            gameNum = i + 1;
            break;
        }

    }
    if (valid == true)
    {
        return gameNum;
    }
    else
    {
        return 0;
    }
}

void quit(void)
{
    printf("Until next Time!\n");
    exit(0);
}

void clear(void)
{
    printf("\e[1;1H\e[2J");
}

void instructions(void)
{
    printf("Here are the instructions\n");
    //TODO
}

void help(void)
{
    printf("some help here ur welcome\n");
    //TODO
}

void list(void)
{
    printf("\n");
    for (int i = 0; i < totalGames; i++)
    {
        printf("%d. %s\n", i + 1, strlow(games[0][i]));
    }
    printf("\n");
}