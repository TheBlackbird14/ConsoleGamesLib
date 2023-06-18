#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <unistd.h>
#include <libgen.h>

#include "./libs/strcap.h"
#include "./libs/colors.h"
#include "./libs/CGLgeneral.h"

int checkInput(char *input);
void instructions();
void help(void);
void list(void);



#define totalGames 3

char *games[2][totalGames] = {{"tictactoe", "battleships", "hangman"}, {"1", "2", "3"}};

int main(int argc, char *argv[])
{
    pclear();

    instructions();


    while(1)
    {
        char input[21];
        do
        {
            printf("ConsoleGamesLib> ");
            int tmp = scanf(" %20s", input);
            if (tmp == EOF || tmp == -1)
            {
                return 1;
            }
            int c;
            while ((c = getchar()) != '\n' && c != EOF);  // Pclear input buffer
            if (!(tmp > 0))
            {
                continue;
            }
        }
        while ((checkInput(strlow(input)) - 1)  < 0);

        int gameNum = -1;
        char rungame[strlen(input) + 1];
        memset(rungame, 0, sizeof(rungame));
        for (int i = 0; i < strlen(input); i++)
        {
            rungame[i] = 0;
        }
        
        gameNum = checkInput(input) - 1;
        strcpy(rungame, games[0][gameNum]);


        char *path = malloc(1024);

        if (strlen(argv[0]) > 3)
        {
            strcat(path, argv[0]);
            
            // Find the last occurrence of '/' in the program path
            char *last_slash = strrchr(path, '/');
            if (last_slash == NULL)
            {
                perror("Error finding path");
                return 1;
            }

            sprintf(last_slash + 1, "%s", "\0");
        }
        else
        {
            sprintf(path, "/usr/local/bin/");
        }

        char *command = malloc(strlen(path) + strlen(rungame) + 1);
        sprintf(command, "%s%s", path, rungame);

        /* printf("Game is:\n%s\n", rungame);
        printf("Launch cmd is:\n%s\n", command);
        while (getchar() != '\n'); */

        int tmp = system(command);
        if (tmp == -1)
        {
            return 1;
        }

        pclear();

        printf(red"Welcome back\n"off);

        free(command);
        free(path);

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