#include <stdio.h>
#include <ncurses.h>
#include <string.h>


#include "../libs/CGLgeneral.h"
#include "../libs/strcap.h"

void menu(void);



int main(void)
{
    menu();
}


void menu(void)
{
    //this part is done with ncurses

    //init
    initscr();
    keypad(stdscr, TRUE);
    noecho();

    // Get the dimensions of the terminal window
    int wrows, wcols;
    getmaxyx(stdscr, wrows, wcols);

    // Message to be centered
    const char* message[] = 
    {
        "Welcome to hangman!!",
        "You know the rules of the game. Try to guess the word before the man is dead!",
        "You can play local multiplayer, where on player enters the word and the other guesses.",
        "Or you can play singleplayer by picking a wordlist of different difficulty level."
    };
    int numLines = sizeof(message) / sizeof(message[0]);

    // Calculate the starting row for centering the text
    int startRow = (wrows - numLines) / 2;

    // Print the message centered on the screen
    for (int i = 0; i < numLines; i++) 
    {
        mvprintw(startRow + i, (wcols - strlen(message[i])) / 2, "%s", message[i]);
    }

    printw("\n\n\n");

    refresh();

    //getch();


    int endrow, endcol;
    getyx(stdscr, endrow, endcol);

    WINDOW *select = newwin(wrows - endrow, wcols, endrow, 1);

    //box(select, 10, 10);

    char *options[] =
    {
        "Singleplayer",
        "Multiplayer",
        "Help",
        "Quit"
    };
    int numOptions = sizeof(options) / sizeof(options[0]);
    int currentOption = 0;
    
    while (true) 
    {
        wclear(select);  // Clear the screen

        // Display menu options
        int printrow = endrow + 2;
        for (int i = 0; i < numOptions; i++) 
        {
            int printcol = (wcols - strlen(options[i])) / 2;
            move(printrow, printcol);
            if (i == currentOption) 
            {
                attron(A_REVERSE);  // Highlight the current option
            }
            printw("%s", options[i]);
            attroff(A_REVERSE);    // Turn off highlighting
            printrow++;
        }

        wrefresh(select);

        // Get user input
        int key = getch();
        int selected = 0;
        switch (key) 
        {
            case KEY_UP :
                currentOption = (currentOption - 1 + numOptions) % numOptions;
                break;
            case KEY_DOWN:
                currentOption = (currentOption + 1) % numOptions;
                break;
            case '\n':  // Enter key
                selected = 1;
                break;
        }

        if (selected == 1)
        {
            break;
        }
        
    }

    switch (currentOption)
    {
    case 0: //singleplayer
        
        break;
    case 1: //multiplayer

        break;
    case 2: //help

        break;
    case 3: //quit
        endwin();
        quit();
        break;
    default:
        break;
    }

    endwin();
    return; 

}