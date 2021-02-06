// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Prototypes for hashing.
bool check(const char *word);
unsigned int hash(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);
void into_table(FILE *file, char buffer[]);

// Prototypes for hashing.
node *create(char value[]);
node *insert(node *head, char value[]);
bool find(node *head, char value[]);
void del(node *head);
int strcasecmp(const char *s1, const char *s2);

#endif // DICTIONARY_H
