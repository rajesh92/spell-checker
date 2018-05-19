
#ifndef DICT_H
#define DICT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// This is a simple trie data structure

// Supported characters size (# of symbols)
#define ALPHABET_SIZE 26
#define PUNCTUATION(c) ((c > 'z' || c < 'A') || (c > 'Z' && c < 'a'))
#define IS_UPPERCASE(c) ((c >= 'A') && (c <= 'Z'))

// Converts key current character into index
// Dictionary uses only 'a' through 'z' in lowercase
#define INDEX(c) ((int)c - (int)'a')
#define TOGGLECASE(c) ((int)c - (int)'A')
#define TO_LOWERCASE(c) (c + ('a' - 'A'))


// trie node
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];

    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void);

// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(struct TrieNode *root, const char *key);


// Returns true if key presents in trie, else false
bool search(struct TrieNode *root, const char *key);

#endif
