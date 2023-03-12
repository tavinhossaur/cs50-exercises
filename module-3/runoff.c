#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Prototypes
bool vote(int voter, int rank, string name);
bool print_winner(void);
bool is_tie(int min);
void tabulate(void);
void eliminate(int min);
int find_min(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {
        printf("%iº voter\n", i+1);

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Iterating through the amount of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the candidate name exists, then
        // add the candidate index to the preferences and return true
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Iterating through the amount of voters
    for (int i = 0; i < voter_count; i++)
    {
        // Iterates through the amount of candidates to
        // get the current candidate and update his votes
        for (int j = 0; j < candidate_count; j++)
        {
            int c = preferences[i][j];

            // Check if the candidate wasn't eliminated
            if (!candidates[c].eliminated)
            {
                candidates[c].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // Iterating through the amount of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the amount of votes of the current candidate
        // is higher than the half amount of the voters, and then print as the winner
        if (candidates[i].votes > voter_count/2)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Variable to keep track of the lowest vote
    // it's initial value is the amount of voters
    int lwst_vote = voter_count;

    // Iterating through the amount of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the candidate wasn't eliminated and if
        // the amount of votes is lower than the current lowest vote
        // then get the lowest vote
        if (!candidates[i].eliminated && candidates[i].votes < lwst_vote)
        {
            lwst_vote = candidates[i].votes;
        }
    }
    return lwst_vote;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // Variable to keep track of amount of
    int tie_counter = 0;
    int run_counter = 0;

    // Iterating through the amount of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the candidate was not eliminated and if it's amount of votes are equal to min
        // then add up to the counter
        if (!candidates[i].eliminated && candidates[i].votes == min)
        {
            tie_counter++;
            run_counter++;
        }
        else if(!candidates[i].eliminated)
        {
            run_counter++;
        }
    }

    // Check if the counter value is equal to the amount of candidates, then return true
    if (tie_counter == run_counter) return true;
    else return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // Iterating through the amount of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the candidate wasn't eliminated and if the
        // amount of votes of the candidate is equal to the min
        // then eliminate the candidate
        if (!candidates[i].eliminated && candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
