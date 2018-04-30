/*
* 	File:		wordcount.c
*	Name:		IJC - DU2
*   Date:       2018-04-20
*	Author:		Filip Kuchar - xkucha26
* 	Faculty:	Faculty of Information Technology, Brno University of Technology
*
* 	Compiled:	Apple LLVM version 9.0.0 (clang-900.0.39.2)
                Target: x86_64-apple-darwin16.7.0
                Thread model: posix
*
*/

#include <stdio.h>
#include <ctype.h>
#include "htab.h"
#include "io.c"

#define WORD_LEN_LIMIT 128
/**
 * @brief Prints keys and number of occurences in hashtable
 * 
 * @param key Key
 * @param ptrvalue listitem.data
 */
void htab_print(const char *key, unsigned int ptrvalue)
{
    printf("%s\t%d\n", key, ptrvalue);
}

int main()
{
    char word[WORD_LEN_LIMIT] = {0};

    /**
     * TODO: // add explanation for choosing this size of hash table
     */
    htab_t *t = htab_init(7500);
    int count = 0;
    bool limit_reached = false;

    while( (count = get_word(word, WORD_LEN_LIMIT, stdin)) != EOF )
    {
        if( !limit_reached && count == WORD_LEN_LIMIT && word[WORD_LEN_LIMIT - 1] != '\0' ) // last char has to be '\0', if not and count == max, print warning. Only once.
        {
            fprintf(stderr, "Word lenght limit - %i chars. Rest of the word will be ignored\n.", WORD_LEN_LIMIT-1);
        }
        htab_listitem *item = htab_lookup_add(t, word);
        item->data++;
    }

    htab_t *t2 = htab_move(7500, t); // for testing purposes

    htab_foreach(t2, &htab_print);

    // ****** STATISTICS *******

    /*
    printf("\nActual num of items:\t%zu\n", htab_size(t2));
    printf("\nArr size:\t%zu\n", htab_bucket_count(t2));
    printf("\nAverage items:\t%f\n",((double)htab_size(t2)/(double)htab_bucket_count(t2)));
    */

    htab_free(t2);
    htab_free(t);
    return 0;
}
//TODO:DONE:
//- [x] declare and implement ‘foreach’
//- [x] Create libraries according to the task
//- [x] make hash table private
//- [x] itemlist private? to respect the task, making data++ outside lookup function is a good idea
//- [x] Complete english comments
//- [x] [?] define my own name of type struct htab_listitem. 
//- [x] Move function redef: newsize vs oldsize -> new index -> find()
//- [x] Print warning if word limit has been reached
//- [x] Figure out the size of hashtable -> O(1) vs O(N) vs memoory usage

// test changes