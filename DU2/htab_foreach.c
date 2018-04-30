/*
* 	File:		htab_foreach.c
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
#include "htab_private.h"

void htab_foreach(htab_t *t, void (*func)(const char *key, unsigned int valueptr))
{
    for( unsigned int i = 0; i < t->arr_size; ++i )     // for each list of items in hash table
    {
        htab_listitem *tar_item = t->list[i];
        while( tar_item != NULL )                      // for each item in list
        {
            func(tar_item->key, tar_item->data);
            tar_item = tar_item->next;
        }
    }
}
