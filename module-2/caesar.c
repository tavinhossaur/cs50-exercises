#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Prototype
string cipher(string text, int key);

int main(int argc, string argv[])
{
    // Checks if the command line doesn't have the right amount of arguments
    if (argc != 2)
    {
        printf("The command was typed in the wrong way.\n");
        printf("Use: ./code key\n");
        // Returns 1 as an error to finish the program.
        return 1;
    }

    // Iterates the second argument (key) to check if there are only numbers
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if(!isdigit(argv[1][i]))
        {
            printf("Make sure that are only positive decimals on the key argument.\n");
            // Returns 1 as an error to finish the program.
            return 1;
        }
    }

    // Converts the argv (string) to int and prints it on the console
    int shift = atoi(argv[1]);
    printf("Shift: %i\n\n", shift);

    // Gets the text that the user wants to encrypt and shows the result by calling the "cipher" function
    string ptxt = get_string("Plaintext: ");
    printf("Ciphertext: %s\n", cipher(ptxt, shift));

    // Returns 0 as the program was executed without problems
    return 0;
}

string cipher(string text, int shift)
{
    // Iterating through the chars of the given text
    for(int i = 0; i <= strlen(text); i++)
    {
        // Checks if is lowercase or uppercase and apply the adapted formula
        // FORMULA: E(x) = (x + n)
        if(islower(text[i]))
        {
            // The decimal value of the char is x, then we add this value to the shift value and subtract 97 because lowercase chars start in the 97 decimal number
            // lowercase chars start in the 97 decimal number, then we use module 26 to this value and add 97 again to return to the lowercase decimals.
            text[i] = (text[i] + shift - 97) % 26 + 97;
        }
        else if(isupper(text[i]))
        {
            text[i] = (text[i] + shift - 65) % 26 + 65;
        }
        else
        {
            // If it's not lower or upper, then its not a alphabetic char and does not changes.
            text[i] = text[i];
        }
    }
    // Returns the encrypted text
    return text;
}