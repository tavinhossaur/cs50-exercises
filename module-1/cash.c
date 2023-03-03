#include <stdio.h>
#include <cs50.h>

// Protoype
void money_change(double c);

int main(void)
{
    double value = get_double("Change owed: ");

    // Calling method for the given money change
    money_change(value);
}

// Encapsulated method
void money_change(double m)
{
    // Create variables
    int c25 = 0, c10 = 0, c5 = 0, c1 = 0;
    int tc = 0;

    string text = "coins";

    double tot = m;

    // Convert to cents
    int cents = (int)(m * 100);

    // Divide the value for the 1/4 cent and add how much of them were used
    c25 = cents / 25;
    if (c25 == 1) text = "coin"; else text = "coins";
    printf("-> %i %s of $0.25 ($%.2f)\n", c25, text, c25 * 0.25);
    cents -= c25 * 25;
    tc += c25;

    // Prints the calculation
    printf("-> %.2f - %.2f = %.2f\n", tot, c25 * 0.25, cents / 100.0);

    c10 = cents / 10;
    if (c10 == 1) text = "coin"; else text = "coins";
    printf("-> %i %s of $0.10 ($%.2f)\n", c10, text, c10 * 0.10);
    cents -= c10 * 10;
    tc += c10;

    printf("-> %.2f - %.2f = %.2f\n", tot, c25 * 0.25 + c10 * 0.10, cents / 100.0);

    c5 = cents / 5;
    if (c5 == 1) text = "coin"; else text = "coins";
    printf("-> %i %s of $0.05 ($%.2f)\n", c5, text, c5 * 0.05);
    cents -= c5 * 5;
    tc += c5;

    printf("-> %.2f - %.2f = %.2f\n", tot, c25 * 0.25 + c10 * 0.10 + c5 * 0.05, cents / 100.0);

    c1 = cents;
    if (c1 == 1) text = "coin"; else text = "coins";
    printf("-> %i %s of $0.01 ($%.2f)\n\n", c1, text, c1 * 0.01);
    tc += c1;

    printf("Total coins used: %i\n", tc);
}