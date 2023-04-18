#include <stdio.h>

int main(void)
{
    instructions();
    getword();
    while (guessed() == 0)
    {
        guess();
    }
}