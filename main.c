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

#define totalGames 2

char *games[2][totalGames] = {{"tictactoe", "battleships"}, {"1", "2"}};

int main(void)
{
    clear();

    instructions();


    while(!done)
    {
        char input[21];
        do
        {
            printf("ConsoleGamesLib> ");
            scanf("%20s", input);
        }
        while ((checkInput(strlow(input)) - 1)  < 0);

        int gameNum;
        char rungame[strlen(input)];
        
        gameNum = checkInput(input) - 1;
        strcpy(rungame, games[0][gameNum]);


        char command[50] = "./build/";
        strcat(command, strlow(rungame));

        /* printf("%s\n", command);
        while (getchar() != '\n');
        while (getchar() != '\n'); */

        system(command);

        clear();

        printf(red"Welcome back\n"off);

    }

}

int checkInput(char *input)
{
    bool valid = false;
    int gameNum = 0;

    if (strcmp(input, "quit") == 0)
    {
        quit();
    }
    else if (strcmp(input, "help") == 0)
    {
        help();
    }
    else if (strcmp(input, "list") == 0)
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
    printf("%sWelcome to %sConsoleGamesLib%s!\n", red, bgWhite, off);
    printf("%s---------------------------------------%s\n\n", green, off);
    printf("%sConsoleGamesLib%s is a collection of small games that you can play in the command line.\n", yellow, off);
    printf("To see a list of all available games, type %slist%s.\n", cyan, off);
    printf("To start a game, type its number or full name and hit enter.\n");
    printf("For example, to start the game of Tic Tac Toe, type %s1%s or %stictactoe%s.\n\n", cyan, off, cyan, off);
    printf("To see a list of all available commands, type %shelp%s.\n", purple, off);
    printf("Enjoy your gaming experience with %sConsoleGamesLib%s!\n\n", blue, off);
}

void help(void)
{
    printf("\n%s- \"quit\" to exit CGL%s\n", warning, off);
    printf("%s- \"list\" to list all available games%s\n\n", caution, off);
}

void list(void)
{
    printf("\n");
    for (int i = 0; i < totalGames; i++)
    {
        printf("%d. %s\n", i + 1, games[0][i]);
    }
    printf("\n");
}