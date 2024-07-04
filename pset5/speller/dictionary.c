// Implements a dictionary's functionality
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 676;
bool Is_Loaded = false;
int NrWords;
// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //TODO: Improve this hash function
    unsigned int index = 0, first, second;
    first = toupper(word[0]) - 'A';
    second = toupper(word[1]) - 'A';
    if (strlen(word) == 1)
    {
        index = first;
    }
    else if (strlen(word) == 2)
    {
        index = 26 * first + second;
    }
    return index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    Is_Loaded = false;
    NrWords = 0;
    FILE *Input = fopen(dictionary, "r");
    if (Input == NULL)
    {
        return false;
    }
    int index;
    char words[LENGTH + 1];
    while (fscanf(Input, "%s", words) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        n->next = NULL;
        strcpy(n->word, words);
        index = hash(words);
        n->next = table[index];
        table[index] = n;
        NrWords++;
    }
    fclose(Input);
    Is_Loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    //TODO
    if (Is_Loaded == true)
    {
        return NrWords;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //TODO
    node *temp;
    node *head;
    for (int i = 0; i < N; i++)
    {
        head = table[i];
        while (head != NULL)
        {
            temp = head->next;
            free(head);
            head = temp;
        }
    }
    return true;
}
