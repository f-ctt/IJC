/*
* 	File:		htab_move.c
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

htab_t *htab_move(unsigned int newsize, htab_t *t2)
{
    htab_t *new_hastable = NULL;
    if( newsize > 0 && t2 != NULL)
    {
        new_hastable = htab_init(newsize);
        if( new_hastable == NULL )
            return NULL;
        
        for(unsigned int i = 0; i < t2->arr_size; ++i)
        {
            htab_listitem *item_to_move = t2->list[i];
            while( item_to_move != NULL )
            {
                unsigned int new_index = htab_hash_function(item_to_move->key, newsize);

                htab_listitem **ptr = &new_hastable->list[new_index];      // taking adress of the pointer
                while( *ptr != NULL )                       // iterate to the end of the list
                    ptr = &(*ptr)->next;                    // new adress of pointer that points to next item

                *ptr = item_to_move;                                // add the item at the end of the list

                item_to_move = item_to_move->next;
                (*ptr)->next = NULL;                          // don't include old next either
            }
            t2->list[i] = NULL;                             // after moving all items, old h_tab's empty
        }
    }
    new_hastable->size = t2->size;
    t2->size = 0;
    return new_hastable;
}
