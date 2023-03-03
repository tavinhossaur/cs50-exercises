#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Prototype
string substitution(string text, string seq);

int main(int argc, string argv[])
{
    string seq = argv[1];

    // Checks if the command line doesn't have the right amount of arguments
    if (argc != 2)
    {
        printf("The command was typed in the wrong way.\n");
        printf("Use: ./code key\n");
        // Returns 1 as an error to finish the program.
        return 1;
    }

    // Checks if the argument has exacts 26 characters
    if(strlen(seq) != 26)
    {
        printf("Enter a sequence with 26 characters\n");
        // Returns 1 as an error to finish the program.
        return 1;
    }

    // Gets the text that the user wants to encrypt and shows the result by calling the "cipher" function
    string ptxt = get_string("Plaintext: ");
    printf("Ciphertext: %s\n", substitution(ptxt, seq));

    // Returns 0 as the program was executed without problems
    return 0;
}

string substitution(string text, string seq)
{
    // Iterating through the chars of the given text
    for(int i = 0; i < strlen(text); i++)
    {
        // Checks if is lowercase or uppercase and apply the formula
        if (isupper(text[i]))
        {
            // subtract the value that indicates the start of uppercase letters in ascii -> -65
            // take that value and searches for the respective letter in the given sequence by using 
            // the integer value of the text char from current iteration -> seq[(int) text[i]]
            // and uses the toupper function, since it's a uppercase letter -> toupper()
            text[i] -= 65;
            text[i] = toupper(seq[(int) text[i]]);
        }
        else if(islower(text[i]))
        {
            text[i] -= 97;
            text[i] = tolower(seq[(int) text[i]]);
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