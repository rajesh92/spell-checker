
#include "dict.h"
#include "corrector.h"


int correctword(struct TrieNode *root, const char *word, int editdistance) {
    int wordlen;
    char curr_word[MAX_CHAR_COUNT+2];
    wordlen = strlen(word);
    int i, j, k;
    FILE *ftmp;


    // Deletions one char -- eg. applre becomes apple
    for(i = 0; i < wordlen; i++) {
        for (j = 0; j < i; j++) {
            curr_word[j] = word[j];
        }
        for (j = i+1; j < wordlen; j++) {
            curr_word[j-1] = word[j];
        }

        // End of string
        curr_word[wordlen-1] = '\0';

        //printf("new word = |%s|\n",curr_word);
        if(search(root,curr_word)) { // 1 is found in dictionary
            //printf("new word = |%s| delete\n",curr_word);
            ftmp = fopen("tmp.txt", "a");
            fprintf(ftmp, "%s\n",curr_word);
            fclose(ftmp);
        }
        else {
            if (editdistance == 0) {
                correctword(root, curr_word, 1);
            }
        }
    }


    // Swap adjacent char -- eg: appel becomes apple
    for (i = 0; i < wordlen - 1; i++) {
        strcpy (curr_word, word);

        char local;

        local = curr_word[i];
        curr_word[i] = curr_word[i+1];
        curr_word[i+1] = local;
        if(search(root,curr_word)) { // 1 is found in dictionary
            //printf("new word = |%s| swap\n",curr_word);
            ftmp = fopen("tmp.txt", "a");
            fprintf(ftmp, "%s\n",curr_word);
            fclose(ftmp);
        }
        else {
            if (editdistance == 0) {
                correctword(root, curr_word, 1);
            }
        }
    }

    // Change one char -- eg: applw becomes apple
    for (i = 0; i < wordlen; i++) {
        strcpy (curr_word,word);
        for (j = 'a'; j <= 'z'; j++) {
            curr_word[i] = (char)j;
            if(search(root,curr_word)) { // 1 is found in dictionary
                //printf("new word = |%s| change\n",curr_word);
                ftmp = fopen("tmp.txt", "a");
                fprintf(ftmp, "%s\n",curr_word);
                fclose(ftmp);
            }
            else {
                if (editdistance == 0) {
                    correctword(root, curr_word, 1);
                }
            }
        }
    }

    // Insert one char -- eg: appe become apple
    for (i = 0; i < wordlen + 1; i++) {
        for (j = 'a'; j <= 'z'; j++) {
            for (k = 0; k < i; k++) {
                curr_word[k] = word[k];
            }
            curr_word[i] = j;
            for (k = i; k < wordlen; k++) {
                curr_word[k+1] = word[k];
            }
            curr_word[wordlen+1] = '\0';
            if(search(root,curr_word)) { // 1 is found in dictionary
                //printf("new word = |%s| insert\n",curr_word);
                ftmp = fopen("tmp.txt", "a");
                fprintf(ftmp, "%s\n",curr_word);
                fclose(ftmp);
            }
            else {
                if (editdistance == 0) {
                    correctword(root, curr_word, 1);
                }
            }
        }
    }

    return 0;
}
