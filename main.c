#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "./libs/strcap.h"
#include "./libs/colors.h"
#include "./libs/cs50.h"

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

    string input;

    while(!done)
    {
        do
        {
            input = strup(get_string("ConsoleGamesLib> "));
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
    printf("%sWelcome to %sConsoleGamesLib%s!\n", red, bgWhite, off);
    printf("%s---------------------------------------%s\n\n", green, off);
    printf("%sConsoleGamesLib%s is a collection of small games that you can play in the command line.\n", yellow, off);
    printf("To see a list of all available games, type %slist%s.\n", cyan, off);
    printf("To start a game, type its number or full name and hit enter.\n");
    printf("For example, to start the game of Tic Tac Toe, type %s1%s or %stic_tac_toe%s.\n\n", cyan, off, cyan, off);
    printf("To see a list of all available commands, type %shelp%s.\n", purple, off);
    printf("Enjoy your gaming experience with %sConsoleGamesLib%s!\n", blue, off);

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
        printf("%d. %s\n", i + 1, strlow(games[0][i]));
    }
    printf("\n");
}