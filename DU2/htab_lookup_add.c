/*
* 	File:		htab_lookup_add.c
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

/**
 * @brief A function that creates an item
 * 
 * @param str Key
 * @return htab_listitem* Pointer to item in hashtable, NULL if malloc fails
 */
htab_listitem *htab_listitem_create(const char *str)
{
    htab_listitem *listitem = (htab_listitem*) malloc(sizeof(htab_listitem)      
                                                        + sizeof(char) 
                                                        * (strlen(str) + 1)); // len of str + null terminator
    if( listitem == NULL)
        return NULL;

    listitem->data = 0;
    listitem->next = NULL;
    memcpy(listitem->key, str, strlen(str) + 1); // +1 -> null temrinator, strlen stops at '\0'
    
    return listitem;
}

struct htab_listitem *htab_lookup_add(htab_t *t, const char *key)
{
    htab_listitem *item = htab_find(t, key);
    if( item != NULL )
    {
        return item;                    // itemm has been found, return it
    }
    item = htab_listitem_create(key);
    if( item == NULL)
        return NULL;

    unsigned int index = htab_hash_function(key, t->arr_size);
    
    htab_listitem **ptr = &t->list[index];      // taking adress of the pointer
    while( *ptr != NULL )                       // iterate to the end of the list
        ptr = &(*ptr)->next;                    // new adress of pointer that points to next item

    *ptr = item;                                // add the item at the end of the list
    t->size++;
    return item;
}
