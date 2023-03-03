#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

// Protoype
void double_pyramid(void);

int main(void)
{
    // Pyramid generator method
    double_pyramid();
}

// Encapsulated method
void double_pyramid(void)
{
    // Creating new variables
    int n;

    // Getting user inputs
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);


    // Prints a double pyramid with a gap between them
    for (int i = 0; i < n; i++)
    {
        for (int j = n-1; j > i; j--)
        {
            printf(" ");
        }
        for (int k = -1; k < i; k++)
        {
            printf("#");
        }
        printf("  ");
        for (int l = -1; l < i; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}