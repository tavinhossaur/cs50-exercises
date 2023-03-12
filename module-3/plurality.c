#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Custom type for candidate
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Amount of candidates
int candidate_count;

// Prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Checks if the command line doesn't have the right amount of arguments
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates (it's -1 because of the first argument that isn't a candidate)
    candidate_count = argc - 1;

    // The amount of candidates can't be greater than the stipulated maximum
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    // Iterates through the candidates and assigns name and votes to each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    // Gets the amount of voters
    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check if the input isn't a candidate name
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Iterating through the amount of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // If this name can be found on the candidates array, then add a vote and return true
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    // Return false if there is any match with the given name (Invalid vote)
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Variable to keep track of the highest vote
    int hgst_vote = 0;

    // Iterating through the amount of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the current candidate has more votes than the current highest vote
        // and then instantiate the candidate amount of votes to the highest vote variable
        if (candidates[i].votes > hgst_vote)
        {
            hgst_vote = candidates[i].votes;
        }
    }

    printf("Winner(s): \n");

    // Iterating through the amount of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the current candidate has the same amount of votes than the highest vote
        // and then print the candidate name
        if (candidates[i].votes == hgst_vote)
        {
            printf("● %s\n", candidates[i].name);
        }
    }

    return;
}