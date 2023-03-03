#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Prototypes
string check_winner(string w1, string w2);
int compute_score(int p, string w);

int main(void)
{
    // Get input words from both players
    string wrd1 = get_string("Player 1: ");
    string wrd2 = get_string("Player 2: ");
    printf("\n");

    // Prints the winner by getting the words value
    printf("Winner: %s\n", check_winner(wrd1, wrd2));
}

string check_winner(string w1, string w2)
{
    string winner = "";

    // Returns the sums from the given words from the players
    int p1 = compute_score(1, w1);
    int p2 = compute_score(2, w2);

    // Checks who is the winner by the sums
    if(p1 > p2) winner = "Player 1";
    else if(p1 == p2) winner = "Draw!";
    else winner = "Player 2";

    printf("\n");
    return winner;
}

int compute_score(int p, string w)
{
    int sum = 0;

    // Iterating through the chars of the given text
    for(int i = 0; i < strlen(w); i++)
    {
        // Since the only characters that will have a value are alphabet letters
        // it's possible to use isupper and islower to filter only the letters of the given texts
        if(isupper(w[i]))
        {
            // Substracts the value that indicates the start of uppercase letters (-65)
            // then, get this value and use it to search the exact position of the POINTS array (POINTS[(int) w[i]])
            // now the char value is equal to the respective array coordenate. Finally, this value is add up to the final sum.
            w[i] -= 65;
            w[i] = (POINTS[(int) w[i]]);

            sum += w[i];
        }
        if(islower(w[i]))
        {
            w[i] -= 97;
            w[i] = (POINTS[(int) w[i]]);

            sum += w[i];
        }
    }

    // Prints the player, his score and return the final sum
    printf("> Player %i | Score: %i\n", p, sum);
    return sum;
}