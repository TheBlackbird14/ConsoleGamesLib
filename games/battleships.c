#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


#include "../libs/strcap.h"
//#include "../libs/cs50.h"
#include "../libs/colors.h"

#define hitship "\033[31;47m"
#define missed "\033[37;44m"

#define FIELD_SIZE 10
//player data
typedef struct
{
    int id;

    char sea[FIELD_SIZE][FIELD_SIZE];

    bool isTurn;

    //for stats
    int shots;
    int hits;
    int misses;
} player;

//functions to be included with cglGeneral.h
void clear(void);
void waitfor(char input);
void quit(void);

void initialize(void);
void instructions(void);
void print(int id, int mode);

void place(void);
int placeOnBoard(player *user, int row, int col, char dir, int length);


int turn(player *p);
int shoot(player *p, int row, int col);

int checkInput(char *input);

int checkWinner(player *p);
int won(player *p);



char coords[FIELD_SIZE][FIELD_SIZE] = {{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}, {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'}};

//ships
#define MAX_SHIPS 5

int shipsLengths[MAX_SHIPS] = {2, 3, 3, 4, 5};

//Debug switches
//debug mode to set seas manually in the program or initialize them to ' '; 0 = debug off, 1 = debug on
#define SET_SEA_MANUAL 0
//enable debug prints troughout the file
#define DEBUG_PRINTS 0



//players
player p1 = 
{1
#if SET_SEA_MANUAL
   ,{
        {'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', 'X', 'X', 'H', 'H', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
    }
#endif
};

player p2 = 
{2
#if SET_SEA_MANUAL
   ,{
        {'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'X', ' ', ' ', 'H', 'H', 'X', 'X', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', 'O', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', 'O', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
    }
#endif
};

int turns = 0;

int main(void)
{
    #if !SET_SEA_MANUAL
        initialize();
    #endif

    clear();
    instructions();

    bool done = false;

    while (!done)
    {
        if (turns == 0)
        {
            clear();
            printf("ENTER to start as player 1");

            #if !SET_SEA_MANUAL
                initialize();
                place();
            #endif

            p1.isTurn = true;
            waitfor('\n');
        }

        clear();

        int r1 = turn(&p1);

        if (r1 == 1)
        {
            int r = won(&p1);
            if (r == 1)
            {
                turns = 0;
                continue;
            }
            else
            {
                done = true;
                continue;
            }
        }

        int r2 = turn(&p2);

        if (r2 == 1)
        {
            int r = won(&p2);
            if (r == 1)
            {
                turns = 0;
                continue;
            }
            else
            {
                done = true;
                continue;
            }
        }
    }

    clear();
    printf("Until Next Time!\n");

    return 0;
}

int turn(player *p)
{

    player *you;
    player *enemy;
    
    if (p->id == 1)
    {
        you = &p1;
        enemy = &p2;
    }
    else if (p->id == 2)
    {
        you = &p2;
        enemy = &p1;
    }

    clear();
    if (turns > 0)
    {
        printf("ENTER to continue as player %d", p->id);
        waitfor('\n');
    }
    else
    {
        printf("ENTER to start as player 1");
        waitfor('\n');
    }
    

    while (p->isTurn)
    {

        char input[3];
        bool valid = false;

        do
        {
            clear();
            print(p->id, 1);
            printf("Player %d> ", p->id);
            scanf("%2s", input);

            // if input is valid
            if (!checkInput(input))
            {
                int row = (int) toupper(input[0]) - 65;
                int col = (int) input[1] - 48;

                int returnValue = shoot(enemy, row, col);


                #if DEBUG_PRINTS
                    printf("return value of shoot = %d\n", returnValue);
                #endif
                
                clear();
                print(p->id, 1);
                waitfor('\n');

                switch (returnValue)
                {
                    case 0: //miss
                        printf("MISS! ENTER to end turn");
                        waitfor('\n');
                        valid = true;
                        p->isTurn = false;
                        break;

                    case 1: //hit
                        printf("HIT! ENTER to go again");
                        waitfor('\n');
                        valid = true;
                        p->isTurn = true;
                        break;

                    case 2: //already shot
                        printf("You've already shot there. ENTER to try again");
                        waitfor('\n');
                        valid = false;
                        p->isTurn = true;
                        break;

                    case 3: //shoot returns 3 in default case (if no other case has worked, so there must be an error of some kind)
                        printf("usage error");
                        waitfor('\n');
                        valid = false;
                        p->isTurn = true;
                        break;
                    
                    default: //this should not happen
                        printf("unknown error");
                        waitfor('\n');
                        break;
                }
                
                #if DEBUG_PRINTS
                    waitfor('\n');
                    printf("won return = %d\n", checkWinner(p));
                    waitfor('\n');
                #endif
                //if player has won 
                if (checkWinner(p) == 1)
                {
                    return 1;
                }

            }
            else //if input is invalid
            {
                waitfor('\n');
                printf("Invalid coordinate. ENTER to try again!");
                waitfor('\n');
                valid = false;
            }

        } while(!valid);
    }
    
    turns++;

    you->isTurn = false;
    enemy->isTurn = true;

    return 0;
}

void initialize(void)
{
    memset(p1.sea, ' ', sizeof(p1.sea));
    memset(p2.sea, ' ', sizeof(p2.sea));
}

//print the board during the game; pass in player id and mode
// mode 0 = place; 1 = in game; 2 = display winner
void print(int id, int mode) 
{
    char water[9] = bgBlue;

    if (mode == 2)
    {
        strcpy(water, bgYellow);
    }

    char you[10][10];
    char enemy[10][10];

    if (id == 1)
    {
        memcpy(you, p1.sea, sizeof(p1.sea));
        memcpy(enemy, p2.sea, sizeof(p2.sea));
    }
    else if (id == 2)
    {
        memcpy(you, p2.sea, sizeof(p2.sea));
        memcpy(enemy, p1.sea, sizeof(p1.sea));
    }
    else 
    {
        printf("invalid use of function print\n");
    }

    //print own sea
    printf("Your Sea: \n\n ");
    for (int i = 0; i < 10; i++) // write nums on the cols of sea
    {
        printf(" | %c", coords[0][i]);
    }

    printf(" |\n  ");

    for (int i = 0; i < 10; i++)
    {
        printf("----");
    }

    printf("-\n");
    
    for (int i = 0; i < 10; i++)
    {
        printf("%c", coords[1][i]); //print the row letters
        for (int j = 0; j < 10; j++)
        {
            //normal sea (nothing)
            if (you[i][j] == ' ')
            {
                printf(" | %s %s", water, off);
            }
            //ship placed on tile
            else if (you[i][j] == 'X')
            {
                printf(" | %s %s", bgWhite, off);
            }
            //shot fires but missed
            else if (you[i][j] == 'O')
            {
                printf(" | %sO%s", missed, off);
            }
            //shot fired and hit ship
            else if (you[i][j] == 'H')
            {
                printf(" | %sX%s", hitship, off);
            }
            else 
            {
                printf("?");
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
    if (mode != 0)
    {    
        printf("Enemy Sea: \n\n ");

        for (int i = 0; i < 10; i++)
        {
            printf(" | %c", coords[0][i]);
        }

        printf(" |\n  ");

        for (int i = 0; i < 10; i++)
        {
            printf("----");
        }

        printf("-\n");

        for (int i = 0; i < 10; i++)
        {
            printf("%c", coords[1][i]);
            for (int j = 0; j < 10; j++)
            {
                //normsal sea (nothing)
                if (enemy[i][j] == ' ')
                {
                    printf(" | %s %s", water, off);
                }
                //shot fires but missed
                else if (enemy[i][j] == 'O')
                {
                    printf(" | %sO%s", missed, off);
                }
                //shot fired and hit ship
                else if (enemy[i][j] == 'H')
                {
                    printf(" | %sX%s", hitship, off);
                }
                //ship placed on tile
                else if (enemy[i][j] == 'X')
                {
                    if (mode == 2)
                    {
                        printf(" | %s %s", bgWhite, off);
                    }
                    else
                    {
                        printf(" | %s %s", bgBlue, off);
                    }
                }
                else 
                {
                    printf("?");
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

}

void place(void)
{
    clear();
    printf("ENTER to Place Ships for Player 1");
    waitfor('\n');

    for (int i = 0; i < MAX_SHIPS; i++)
    {
        clear();
        print(p1.id, 0);

        char input[3];
        int c;

        do
        {
            printf("Place Ship %d with length %d> ", i + 1, shipsLengths[i]);
            scanf("%2s", input);
            while ((c = getchar()) != '\n' && c != EOF);  // clear input buffer

            if (checkInput(input) != 0)
            {
                printf("Invalid Coordinate entered, try again\n");
            }
        }
        while (checkInput(input) != 0);

        #if DEBUG_PRINTS
            printf("%s\n", input);
            waitfor('\n');
        #endif

        char dir;
        c = 0;

        do
        {
            printf("Direction (u, d, l, r)> ");
            scanf("%c", &dir);

            while ((c = getchar()) != '\n' && c != EOF);  // clear input buffer

            if (toupper(dir) == 'Q')
            {
                quit();
            }
        }
        while (toupper(dir) != 'U' && toupper(dir) != 'D' && toupper(dir) != 'L' && toupper(dir) != 'R');

        int row = toupper(input[0]) - 65;
        int col = input[1] - 48;

        if (placeOnBoard(&p1, row, col, toupper(dir), shipsLengths[i]))
        {
            switch (placeOnBoard(&p1, row, col, toupper(dir), shipsLengths[i]))
            {
            case 1:
                printf("Ship is out of bounds, try again!");
                waitfor('\n');
                break;

            case 2:
                printf("Ship is already there, try again!");
                waitfor('\n');
                break;

            case 3:
                printf("Error in usage of function placeOnBoard (this should not happen)");
                waitfor('\n');
                break;
            
            default:
                break;
            }

            i--;
            continue;
        }

    }

    clear();
    print(p1.id, 0);
    printf("ENTER to end turn");
    waitfor('\n');
    clear();
    printf("ENTER to Place Ships for Player 2");
    waitfor('\n');

    for (int i = 0; i < MAX_SHIPS; i++)
    {
        clear();
        print(p2.id, 0);

        char input[3];
        int c;

        do
        {
            printf("Place Ship %d with length %d> ", i + 1, shipsLengths[i]);
            scanf("%2s", input);
            while ((c = getchar()) != '\n' && c != EOF);  // clear input buffer

            if (checkInput(input) != 0)
            {
                printf("Invalid Coordinate entered, try again\n");
            }
        }
        while (checkInput(input) != 0);

        #if DEBUG_PRINTS
            printf("%s\n", input);
            waitfor('\n');
        #endif

        char dir;
        c = 0;

        do
        {
            printf("Direction (u, d, l, r)> ");
            scanf("%c", &dir);

            while ((c = getchar()) != '\n' && c != EOF);  // clear input buffer

            if (toupper(dir) == 'Q')
            {
                quit();
            }
            else if (toupper(dir) != 'U' && toupper(dir) != 'D' && toupper(dir) != 'L' && toupper(dir) != 'R')
            {
                printf("\"%c\" is not a valid direction\n", dir);
            }

        }
        while (toupper(dir) != 'U' && toupper(dir) != 'D' && toupper(dir) != 'L' && toupper(dir) != 'R');

        int row = toupper(input[0]) - 65;
        int col = input[1] - 48;

        if (placeOnBoard(&p2, row, col, toupper(dir), shipsLengths[i]))
        {
            switch (placeOnBoard(&p1, row, col, toupper(dir), shipsLengths[i]))
            {
            case 1:
                printf("Ship is out of bounds, try again!");
                waitfor('\n');
                break;

            case 2:
                printf("Ship is already there, try again!");
                waitfor('\n');
                break;

            case 3:
                printf("Error in usage of function placeOnBoard (this should not happen)");
                waitfor('\n');
                break;
            
            default:
                break;
            }

            i--;
            continue;
        }

    }

    clear();
    print(p2.id, 0);
    printf("ENTER to end turn and start game");
}

//returns 0 if the placement is possible; 1 if ship is out of bounds; 2 if ship already there, 3 if error in function usage
int placeOnBoard(player *user, int row, int col, char dir, int length)
{
    switch (dir)
    {
    case 'U':
        if ((row - (length - 1)) < 0)
        {
            return 1;
        }

        for (int i = 0, c = row; i < length; i++, c--)
        {
            if (user->sea[c][col] == 'X')
            {
                return 2;
            }
        }

        for (int i = 0, c = row; i < length; i++, c--)
        {
            user->sea[c][col] = 'X';
        }
        return 0;
        break;

    case 'D':
        if ((row + (length - 1)) > 10)
        {
            return 1;
        }

        for (int i = 0, c = row; i < length; i++, c++)
        {
            if (user->sea[c][col] == 'X')
            {
                return 2;
            }
        }

        for (int i = 0, c = row; i < length; i++, c++)
        {
            user->sea[c][col] = 'X';
        }
        return 0;
        break;

    case 'L':
        if ((col - (length - 1)) < 0)
        {
            return 1;
        }

        for (int i = 0, c = col; i < length; i++, c--)
        {
            if (user->sea[row][c] == 'X')
            {
                return 2;
            }
        }

        for (int i = 0, c = col; i < length; i++, c--)
        {
            user->sea[row][c] = 'X';
        }
        return 0;
        break;

    case 'R':
        if ((col + (length - 1)) > 10)
        {
            return 1;
        }

        for (int i = 0, c = col; i < length; i++, c++)
        {
            if (user->sea[row][c] == 'X')
            {
                return 2;
            }
        }

        for (int i = 0, c = col; i < length; i++, c++)
        {
            user->sea[row][c] = 'X';
        }
        return 0;
        break;
    
    default:
        printf("invalid use of function placeOnBoard");
        return 3;
        break;
    }
}

//checks if the  entered input is a valid coord
int checkInput(char *input) //return 0 when is ok, 1 when not
{
    if (strcmp(strup(input), "QUIT") == 0 || strcmp(strup(input), "EXIT") == 0 || strcmp(strup(input), "Q") == 0)
    {
        quit();
    }

    bool validLet = false;
    bool validNum = false;

    for (int i = 0; i < FIELD_SIZE; i++)
    {
        if (toupper(input[0]) == coords[1][i])
        {
            validLet = true;
            break;
        }
    }
    
    for (int i = 0; i < FIELD_SIZE; i++)
    {
        if (toupper(input[1]) == coords[0][i])
        {
            validNum = true;
            break;
        }
    }

    if (validLet == true && validNum == true)
    {
        return 0;
    }
    else
    {
        return 1;
    }

}


//return 0 if miss, 1 if hit, 2 if already hit, 3 if usage error
int shoot(player *p, int row, int col)
{
    switch (p->sea[row][col])
    {
    case ' ':
        p->sea[row][col] = 'O';
        return 0;

    case 'X':
        p->sea[row][col] = 'H';
        return 1;

    case 'H':
        return 2;

    case 'O':
        return 2;
    
    default:
        return 3;
    }

}

//prints winning screen and ask for another round
//return 0 = quit, 1 continue
int won(player *p)
{
    clear();
    printf("%sPlayer %d has Won!%s\n", win, p->id, off);
    print(p->id, 2);

    char input;

    do
    {
        printf("Play another round? (y/n)> ");
        scanf("%c", &input);
        waitfor('\n');
    } while (toupper(input) != 'Y' && toupper(input) != 'N');
    
    if (toupper(input) == 'Y')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// 0 if has not won, 1 if has won, 2 = error
int checkWinner(player *p)
{
    player *enemy;
    if (p->id == 1)
    {
        enemy = &p2;
    }
    else if (p->id == 2)
    {
        enemy = &p1;
    }
    else 
    {
        return 2;
    }

    bool shipsLeft = false;
    for (int i = 0; i < FIELD_SIZE; i++)
    {
        for (int j = 0; j < FIELD_SIZE; j++)
        {
            if (enemy->sea[i][j] == 'X')
            {
                shipsLeft = true;
                break;
            }
        }
        if (shipsLeft == true)
        {
            break;
        }
    }

    if (shipsLeft == true)
    {
        return 0;
    }
    else 
    {
        return 1;
    }
}

//clear the screen
void clear(void)
{
    printf("\e[1;1H\e[2J");
}

//wait for an input (eg '\n')
void waitfor(char input)
{
    while (getchar() != input);
}

//print the instructions
void instructions(void)
{
    printf("%sWelcome to %sBattleships!%s\n", red, bgWhite, off);
    printf("In this game you shoot at eachothers ships and try to sink all your enemies ships first.\n");
    printf("But first, you have to %splace%s your ships at the beginning of the game.\n", cyan, off);
    printf("To do so, enter the %scoordinate%s at which the ships should start, and then the %sdirection%s it should point to (%su%sp, %sd%sown, %sl%seft, %sr%sight).\n", yellow, off, yellow, off, uWhite, off, uWhite, off, uWhite, off, uWhite, off);
    printf("To enter a %scoordinate%s, look at the grid captions, then write the %srow%s first, then the %scolumn%s (eg %sd8%s).\n", yellow, off, red, off, red, off, uWhite, off);
    printf("%sPlayer 1%s starts. have fun!\n\n", green, off);
    printf("Press %sENTER%s to start", bRed, off);
    
    waitfor('\n');
}

//quit the program
void quit(void)
{
    clear();
    printf("Until Next Time!\n");
    exit(2);
}