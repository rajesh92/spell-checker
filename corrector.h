
#ifndef CORRECTOR_H
#define CORRECTOR_H


#define MAX_CHAR_COUNT 30
#define MAX_POSSIBLE_WORDS 500

int correctword(struct TrieNode *root, const char *word, int editdistance);

#endif
