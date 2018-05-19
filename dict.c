#include "dict.h"

// Returns a new TrieNode (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *tNode = NULL;

    tNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));

    if (tNode)
    {
        int i;

        tNode->isEndOfWord = false;

        for (i = 0; i < ALPHABET_SIZE; i++)
            tNode->children[i] = NULL;
    }

    return tNode;
}


// Inserts key into trie, if it is not present in it
// If the key is prefix of trie node, just marks leaf node
void insert(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;

    struct TrieNode *tCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = INDEX(key[level]);
        if (!tCrawl->children[index])
            tCrawl->children[index] = getNode();

        tCrawl = tCrawl->children[index];
    }

    // mark the last node as leaf node
    tCrawl->isEndOfWord = true;
}

// Returns true if key presents in trie, else false
bool search(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *tCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = INDEX(key[level]);
        if (index < INDEX('a')) {
            index = TO_LOWERCASE(index);
        }
        if (index > INDEX('z') || index < INDEX('a')) { // Puntuation not supported in dictionary
            return false;
        }
        else {

            if (!tCrawl->children[index])
                return false;

            tCrawl = tCrawl->children[index];
        }
    }

    return (tCrawl != NULL && tCrawl->isEndOfWord);
}
