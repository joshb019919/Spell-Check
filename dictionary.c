// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"
#include "xxhash.c"

// Number of buckets in hash table
const unsigned int N = 400000;

// Hash table and list head.
node *table[N];
node *sllhead = NULL;
unsigned int table_size = 0;

// Returns true if word is in dictionary else false
bool check(const char *word) {
  // Discord user Sanath helped a lot on this one, reminding
  // me of what works, where, and when.
  char slword[strlen(word) + 1];
  int i;

  // Lowercase each word.
  for (i = 0; word[i]; i++) {
    slword[i] = tolower(word[i]);
  }

  return find(table[hash(slword)], slword);
}

// Hashes word to a number
unsigned int hash(const char *word) {
  // xxHash from https://github.com/Cyan4973/xxHash
  unsigned int size = sizeof(word);
  return (XXH64_hash_t)XXH64(word, size, 1) % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary) {
  // Open dictionary.
  FILE *dict = fopen(dictionary, "r");
  if (dict == NULL) {
    return false;
  }

  // Iterator and buffer for built words.
  char buffer[LENGTH + 1];

  // Clear table so I'll know where nulls are.
  for (int i = 0; i < N; i++) {
    table[i] = NULL;
  }

  // Load buffers into hash table.
  into_table(dict, buffer);

  fclose(dict);
  return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void) { return table_size; }

// Unloads dictionary from memory, returning true if successful else false
bool unload(void) {
  // Stacks calls to del() until final link has been reached.
  // Returns through stack, deleting from memory as it goes.
  int i;
  for (i = 0; i < N; i++) {
    if (table[i] != NULL) {
      del(table[i]);
    }
  }

  if (i == N) {
    return true;
  }

  return false;
}

void into_table(FILE *file, char buffer[]) {
  int i;
  while (1) {
    // Zero out the buffer.
    for (i = 0; i < LENGTH + 1; i++) {
      buffer[i] = 0;
    }

    // Get first char.
    char c = fgetc(file);

    // Check for end of file.
    if (feof(file)) {
      break;
    }

    // Build word and get more chars.
    for (i = 0; c != '\n'; i++) {
      buffer[i] = c;
      c = fgetc(file);
    }

    // Add words to table in memory.
    if (!table[hash(buffer)]) {
      table[hash(buffer)] = create(buffer);
    } else {
      insert(table[hash(buffer)], buffer);
    }

    buffer[i] = '\0';

    // Increment table tize.
    table_size++;
  }
}

node *create(char value[]) {
  node *n = malloc(sizeof(node));
  if (n == NULL) {
    printf("No mem for create");
    return NULL;
  }

  strcpy(n->word, value);
  sllhead = n;
  n->next = NULL;

  return sllhead;
}

node *insert(node *head, char value[]) {
  node *n;
  n = malloc(sizeof(node));
  if (n == NULL) {
    printf("No mem for insert");
    return NULL;
  }

  strcpy(n->word, value);
  n->next = head->next;
  head->next = n;

  return head;
}

bool find(node *head, char value[]) {
  node *trav = NULL;
  trav = head;

  while (trav) {
    if (strcasecmp(trav->word, value) == 0) {
      return true;
    } else {
      trav = trav->next;
    }
  }

  return false;
}

void del(node *head) {
  if (head->next != NULL) {
    del(head->next);
  }

  free(head);
}