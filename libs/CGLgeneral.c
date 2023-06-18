#include "colors.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//clear the screen
void pclear(void)
{
    printf("\e[1;1H\e[2J");
}

//wait for an input (eg '\n')
void waitfor(char input)
{
    while (getchar() != input);
}

//quit the program
void quit(void)
{
    printf(off);
    pclear();
    printf("Until Next Time!\n");
    exit(2);
}