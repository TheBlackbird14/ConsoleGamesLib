#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char *strup(char *input){
    int inputlen = strlen(input);
    char *output = (char *) malloc(inputlen + 1);
    char current;
    for (int i = 0; i < inputlen; i++)
    {
        current = input[i];

        char new = toupper(current);
        output[i] = new;
    }
    output[inputlen] = '\0';
    return output;
}

char *strlow(char *input){
    int inputlen = strlen(input);
    char *output = (char *) malloc(inputlen + 1);
    char current;
    for (int i = 0; i < inputlen; i++)
    {
        current = input[i];

        char new = tolower(current);
        output[i] = new;
    }
    output[inputlen] = '\0';
    return output;
}