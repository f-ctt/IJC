/*
* 	File:		htab_remove.c
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

bool htab_remove(htab_t *t, const char *str)
{
    if( t == NULL)
        return false;
    unsigned int index = htab_hash_function(str, t->arr_size);   
    htab_listitem *tar_item = t->list[index];
    htab_listitem *previous = t->list[index];  

    while( tar_item != NULL )
    {
        if( strcmp(tar_item->key, str) == 0 )
        {
            if( previous == tar_item )
                t->list[index] = tar_item->next;    // first item
            else
                previous->next = tar_item->next;    // concatenating list again

            t->size--;
            free(tar_item);
            return true;
        }
        else
        {
            previous = tar_item;
            tar_item = tar_item->next;
        }
    }

    return false;
}
