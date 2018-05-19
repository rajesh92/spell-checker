/**
* Rajesh Alwar
* spell-checker.c
*
*
*
* Most important functions -
* - insert() --inserts each word in dictionary data structure
* - search() -- searches if the word is present in dictionary data structure
* - correctword() -- finds the input word in loaded dictionary; if not found returns the nearest found word in the dictionary available
*
*
*   CORRECTOR LOGIC - Deletes, inserts, swaps, changes words 2 times (specified by editdistance).
*
*   when macro EDITDIST = 0 (checks two things) papel, ple, apel, etc. still becomes apple; -- this can also include
*   combination of deletes, inserts, swaps, changes
*
*   when macro EDITDIST = 1 it checks only one alphabet change
*   eg. aple, appwle, aplpe become apple
*
*   This implementation coniders that dictionary has camelcase words only -
*   as an extenstion can be further optimized
*
**/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "dict.h"
#include "corrector.h"

#define BILLION  1000000000L;
#define EDITDIST 0

int main (int argc, char *argv[]) {

    // Check for file names for dictionary and input file
    if(argc < 3) {
        printf("Invalid number of input parameters.. Correct usage is: \n./<myprogramname> dictionary.txt input.txt \n");
        return -1;
    }

    // More than two file names provided
    if(argc > 3) {
        printf("You have entered more than required arguments - only first two are being considered...\n");
    }

    int i,j,a,b,skip = 0;
    long int x = 0;
    long int match;
    char temp[MAX_CHAR_COUNT];
    long int count = 0;
    long int right = 0;

    // Max character count is 30.
    char tmp[MAX_CHAR_COUNT], local[MAX_CHAR_COUNT], name[MAX_CHAR_COUNT];
    char corrections[MAX_POSSIBLE_WORDS][MAX_CHAR_COUNT];
    struct timespec start, stop;
    double accum;
    FILE *fdict, *fin, *ftmp;

    // Start of my algorithm

    if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
        perror( "clock gettime" );
        return EXIT_FAILURE;
    }

    // Create root for the trie data structure
    struct TrieNode *root = getNode();

    // Open dictionary to read contents
    fdict = fopen(argv[1],"r");
    if (fdict == NULL) {
        printf("Unable to open file: %s\n", argv[1]);
    }
    else {
        // Reading dictionary
        printf("Reading dictionary file: %s with ", argv[1]);
        // Keep reading until EOL is reached
        while (!feof(fdict)) {
            if (fscanf(fdict, "%s", tmp) > 0) {
                //printf("%s\n", tmp);

                // Construct trie
                insert(root, tmp);
                count++;
            }
        }
        printf("%ld words\n", count);
    }
    count = 0;
    fin = fopen(argv[2],"r");
    if (fin == NULL) {
        printf("Unable to open file: %s\n", argv[2]);
    }
    else {
        // Reading input file
        printf("Reading input file: %s\n", argv[2]);
        printf("Starting analysis....\n");
        // Keep reading until EOL is reached
        while (!feof(fin)) {
            if (fscanf(fin, "%s", tmp) > 0) {
                //printf("%ld. %s -- \t\t", count, tmp);
                count++;
                // Construct trie
                a = 0;
                for (i = 0; i < strlen(tmp); i++) {
                    if (!PUNCTUATION(tmp[i])) {
                        if(IS_UPPERCASE(tmp[i])) {
                            local[a] = TO_LOWERCASE(tmp[i]);
                        }
                        else {
                            local[a] = tmp[i];
                        }
                        a++;
                        local[a] = '\0';

                    }
                    else {
                        local[a+1] = '\0';
                    }
                }
                if(search(root,local) == 0) {
                    printf("\n\n\"%s\" word NOT FOUND in dictionary",tmp);
                    correctword(root,local,EDITDIST);

                    ftmp = fopen("tmp.txt","r");
                    if(ftmp) {
                        x = 0;
                        match = 0;
                        skip = 0;
                        while (!feof(ftmp)) {
                            if(fscanf(ftmp,"%s",name) > 0) {
                                    //printf("%s\n",name);

                                    skip = 0;
                                    if (match == 0) {
                                        strcpy (corrections[x],name);
                                        //printf("%s, ", corrections[x]);
                                        x++;
                                    }
                                    if (match > 0) {
                                        for(b = 0; b < x; b++) {
                                            if(strcmp(corrections[b],name) ==0) { // name already present in corr
                                                skip = 1;
                                            }
                                        }
                                        if (skip == 0) { // add word to corr
                                            strcpy (corrections[x],name);
                                            //printf("%s, ",corrections[x]);
                                            x++;
                                        }
                                    }
                                    match++;

                            }
                        }
                        fclose(ftmp);
                        if (x > 0) {
                            printf(", did you mean: \n");
                        }
                        else {
                            printf(" and no suggestions found as well \n");
                        }

                        for (i = 0; i < x; i++) {
                            for (j = i+1; j < x; j++)
                                if (strcmp(corrections[i], corrections[j]) > 0) {
                                    strcpy (temp,corrections[i]);//temp = corrections[i];
                                    strcpy (corrections[i],corrections[j]);//corrections[i] = corrections[j];
                                    strcpy (corrections[j],temp);//corrections[j] = temp;
                            }
                            printf("%s ", corrections[i]);
                        }


                        if (remove("tmp.txt")) {
                            printf("\n Hmmm... Something does not look right.... \n");
                        }
                    }
                }
                else {
                    right++;
                }
            }
        }
        //printf("Count was %ld\n", count);
        printf("\n\nCorrect %ld \t Incorrect %ld\n", right, count-right);
    }
    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
        perror( "clock gettime" );
        return EXIT_FAILURE;
    }

    accum = ( stop.tv_sec - start.tv_sec ) + (double)( stop.tv_nsec - start.tv_nsec ) / (double) BILLION;

    printf( "Total time %lf seconds\n", accum );

    return EXIT_SUCCESS;
}
