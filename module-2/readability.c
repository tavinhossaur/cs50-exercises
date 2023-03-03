#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Prototypes
float readability(string text);
int lettrcount(string text);

int main(void)
{
    string text = get_string("Text: ");
    float grade = readability(text);

    if (grade >= 16.0)
    {
        printf("> Grade 16 or higher\n");
    }
    else if (grade < 1.0)
    {
        printf("> Lower than grade 1\n");
    }
    else
    {
        // Shows the rounded grade
        printf("> Grade: %.f\n", grade);
    }
}

float readability(string text)
{
    // Defining useful variables
    float lttrs = 0.0, wrds = 0.0, stncs = 1.0, grade = 0.0;

    // Counting letters
    for(int i = 0; i <= lettrcount(text); i++) lttrs = i;
    
    // Counting words
    for(int j = 0; j <= strlen(text); j++) if (text[j] == ' ' || text[j] == '\0') wrds++;

    // Counting sentences
    for(int k = 0; k <= strlen(text); k++) if (text[k] == '!' || text[k] == '?' || text[k] == '.') stncs++;

    // Shows the values
    printf("Letters: %.2f\n", lttrs);
    printf("Words: %.2f\n", wrds);
    printf("Sentences: %.2f\n\n", stncs);

    // Aplying the Coleman-Liau formula and shows the calculation on console
    printf("%.2f / %.2f x 100 = ", lttrs, wrds);
    lttrs = lttrs / wrds * 100;
    printf("%.2f\n", lttrs);
    printf("%.2f / %.2f x 100 = ", stncs, wrds);
    stncs = stncs / wrds * 100;
    printf("%.2f\n\n", stncs);

    // Shows the formula being applied and returns the grade
    printf("0,0588 x %.2f - 0,296 * %.2f - 15,8 = ", lttrs, stncs);
    grade = 0.0588 * lttrs - 0.296 * stncs - 15.8;
    printf("%.2f\n\n", grade);

    return grade;
}

// To remove blank spaces in the letter count of the text
int lettrcount(string text)
{
    // Blank and used spaces
    int ws = 0, us = 0;

    // Counting letters
    for(int i = 0; i <= strlen(text); i++)
    {
        // Checks if there are chars that doesn't count as letters and add to white spaces
        if(text[i] == '!' || text[i] == '?' || text[i] == '.' || text[i] == ' ' || text[i] == ';' || text[i] == ',' || text[i] == ':' || text[i] == '\'' || text[i] == '-' || text[i] == '"' || text[i] == '(' || text[i] == ')')
        {
            ws++;
        }
        us = i;
    }

    // Removes the white spaces from the used spaces
    return us-ws;
}