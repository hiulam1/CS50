// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"
bool loaded = false;
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const int N = 509;

// Hash table
node *table[N];

// 3. Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    node *pointer = table[index];
    if (pointer == NULL || strlen(word) > LENGTH + 1)
    {
        return false;
    }

    while (pointer != NULL)
    {
        if (strcasecmp(pointer->word, word) == 0)
        {
            return true;
        }
        pointer = pointer->next;
    }
    return false;
}

// 2. Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // hash function from https://www.geeksforgeeks.org/string-hashing-using-polynomial-rolling-hash-function/
    int p = 31;
    int hash = 0;
    long long p_pow = 1;
    int n = strlen(word);
    for (int i = 0; i < n; i++)
    {
        hash = (hash + (toupper(word[i]) - 'A' + 1) * p_pow) % N;
        p_pow = (p_pow * p) % N;
    }
    return hash;
}

// 1. Loads dictionary into memory, returning true if successful, else false

bool load(const char *dictionary)
{
    // TODO
    FILE *dictionary_file = fopen(dictionary, "r");
    if (dictionary_file == NULL)
    {
        printf("dictionary file is null");
        return false;
    }

    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    char string[LENGTH + 2];
    while (fgets(string, sizeof(string), dictionary_file))
    {
        node *new_word = (node *) malloc(sizeof(node));
        if (new_word == NULL)
        {
            printf("new word is null");
            return false;
        }
        char *new_line = strchr(string, '\n');
        if (new_line != NULL)
        {
            *new_line = '\0';
        }
        strcpy(new_word->word, string);
        new_word->next = NULL;
        int index = hash(string);
        if (table[index] == NULL)
        {
            table[index] = new_word;
        }
        else
        {
            new_word->next = table[index];
            table[index] = new_word;
        }
    }

    fclose(dictionary_file);
    loaded = true;
    return true;
}

// 4.Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (loaded)
    {
        int count = 0;
        for (int n = 0; n < N; n++)
        {
            node *counter = table[n];
            while (counter != NULL)
            {
                counter = counter->next;
                count++;
            }
        }
        return count;
    }
    return 0;
}

// 5. Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int bucket = 0; bucket < N; bucket++)
    {
        node *head = table[bucket];
        while (head != NULL)
        {
            node *next = head->next;
            free(head);
            head = next;
        }
    }
    return true;
}
