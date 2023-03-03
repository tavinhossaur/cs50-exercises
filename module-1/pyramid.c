#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

// Protoype
void pyramid(void);

int main(void)
{
    // Pyramid generator method
    pyramid();
}

// Encapsulated method
void pyramid(void)
{
    // Creating new variables
    int n;
    char o;

    // Getting user inputs
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    o = get_char("Right (r) or Left (l): ");

    // Checking user option
    if (o == 'r' || o == 'R')
    {
        // Prints a pyramid with # from right to left
        for (int i = 0; i < n; i++)
        {
            for (int k = n-1; k > i; k--)
            {
                printf(" ");
            }
            for (int j = -1; j < i; j++)
            {
                printf("#");
            }
            printf("\n");
        }
    }
    else if (o == 'l' || o == 'L')
    {
        // Prints a pyramid with # from left to right
        for (int i = 0; i < n; i++)
        {
            for (int j = -1; j < i; j++)
            {
                printf("#");
            }
            printf("\n");
        }
    }
    else
    {
        // Closes program and tells user why
        printf("\nProgram exited.\n> You didn't typed what you was supposed to (r or l)\n");
        exit(0);
    }
}