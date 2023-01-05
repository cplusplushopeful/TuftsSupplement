// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
#include <ctype.h>
#include <strings.h>
#include <stdio.h>
#include <cs50.h>

// Represents a node in a hash table
int count = 0;

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 100000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    if (table[index] != NULL)
    {
        node *cursor = table[index];
        while (cursor != NULL)
        {
            if (strcasecmp(cursor -> word, word) == 0)
            {
                return true;
            }
            cursor = cursor -> next;
        }
        return false;
    }
    else
    {
        return false;
    }
}

// Hashes word to a number
//Credit to dan bernstein and the CS50 reddit community (https://www.reddit.com/r/cs50/comments/ggvgvm/pset5_djb2_hash_function/)
unsigned int hash(const char *word)
{
    ;
    unsigned int hash = 5381;
    int c;
    while ((c = tolower(*word++)))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}



// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
    {
        return false;
    }
    char i[LENGTH + 1];
    while (fscanf(input, "%s", i) != EOF)
    {
        node *newWord = malloc(sizeof(node));
        if (newWord == NULL)
        {
            return false;
        }
        newWord -> next = NULL;
        strcpy(newWord -> word, i);
        int area = hash(i);
        if (table[area] == NULL)
        {
            table[area] = newWord;
        }    
        else
        {
            newWord -> next = table[area];
            table[area] = newWord;
        }
        count++;
    }
    fclose(input);
    printf("%i", count);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *cursor = NULL;
    node *tmp = NULL;
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            cursor  = table[i];
            tmp = table[i];
            while (cursor != NULL)
            {
                cursor = cursor -> next;
                free(tmp);
                tmp = cursor;
            }
        }
        else
        {
            free(table[i]);
        }
    }
    return true;
}
