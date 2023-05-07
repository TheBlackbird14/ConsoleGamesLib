#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char *strup(char *input){
    int inputlen = strlen(input);
    char current;
    for (int i = 0; i < inputlen; i++)
    {
        current = input[i];

        char new = toupper(current);
        input[i] = new;
    }
    return input;

}

char *strlow(char *input){
    int inputlen = strlen(input);
    char current;
    for (int i = 0; i < inputlen; i++)
    {
        current = input[i];

        char new = tolower(current);
        input[i] = new;
    }
    return input;
}