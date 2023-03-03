#include <stdio.h>
#include <cs50.h>

// Prototype
int population_grow(void);

int main(void)
{
    // Show the amount of years
    printf("%i years\n", population_grow());
}

// Encapsulated method
int population_grow(void)
{
    // Creating variables
    int p1;
    int p2;
    int y = 0;

    // Retriving the initial and final populations
    do {
        p1 = get_int("Enter the initial size of the population: ");;
    } while(p1 < 9);

    do {
        p2 = get_int("Enter the final size of the population: ");
    } while(p2 <= p1);

    // Do the formula until the initial size be equal or higher than the final size
    while (p1 < p2)
    {
        p1 = p1 + (p1 / 3) - (p1 / 4);
        y++;
    }

    return y;
}