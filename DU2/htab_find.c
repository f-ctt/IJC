/*
* 	File:		htab_find.c
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

struct htab_listitem *htab_find(htab_t *t, const char *key)
{
    if( t == NULL)
        return NULL;
    unsigned int index = htab_hash_function(key, t->arr_size);
    htab_listitem *tar_item = t->list[index];
    if( tar_item == NULL)
        return NULL;
    
    while( tar_item != NULL)
    {
        if( strcmp(tar_item->key, key) == 0 )
            return tar_item;
        tar_item = tar_item->next;
    }

    return NULL;
}
