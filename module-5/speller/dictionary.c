// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

#define HASHTABLE_SIZE 10000

// Struct for node
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

node *hashtable[HASHTABLE_SIZE];

// Hashing the word, this gives the word a index to search it later
int hash_index(char *hash_this)
{
    unsigned int hash = 0;
    for (int i = 0, n = strlen(hash_this); i < n; i++)
    {
        hash = (hash << 2) ^ hash_this[i];
    }
    return hash % HASHTABLE_SIZE;
}

// Tracks the amount of words in the dictionary
int word_count = 0;

// Loads the dictionary in the memory
bool load(const char *dictionary)
{
    // Tries to open the dictionary if exists
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    // Gets every word in the dictionary and populates the hash table with nodes
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        // Allocating memory for every new word found
        node *new_node = malloc(sizeof(node));
        // Check if the memory was properly allocated
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        // Copies the word into the node
        strcpy(new_node->word, word);

        // Initializes the index for word to insertion in the hashtable
        int h = hash_index(new_node->word);

        // Makes head to point to the hashtable
        node *head = hashtable[h];

        // Makes new nodes at the beggining of lists if the head is null
        if (head == NULL)
        {
            hashtable[h] = new_node;
            word_count++;
        }
        else
        {
            new_node->next = hashtable[h];
            hashtable[h] = new_node;
            word_count++;
        }
    }
    fclose(file);
    return true;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Makes a lowercase copy of the word
    int n = strlen(word);
    char word_copy[LENGTH + 1];
    for (int i = 0; i < n; i++) word_copy[i] = tolower(word[i]);
    
    // NUL to the last char
    word_copy[n] = '\0';
    
    // Initializes index for hashed word
    int h = hash_index(word_copy);
    // Setting cursor to point to the hashtable address
    node *cursor = hashtable[h];

    // Loop to search the word in the entire dictionary
    while (cursor != NULL)
    {
        // Check if the word is the same as the dictionary
        if (strcasecmp(cursor->word, word_copy) == 0) return true;
        // If isn't the word we are looking for, go to the next
        else cursor = cursor->next;
    }
    // When it gets to null, the cursor readed all the list and did not find the word
    // so it was probably spelled wrong
    return false;
}

// Returns the number of words in the dictionary
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *head = NULL;
    node *cursor = head;
    
    // Free all linked lists
    while (cursor != NULL)
    {
        node *temp = cursor;
        cursor = cursor->next;
        free(temp);
    }
    
    return true;
}