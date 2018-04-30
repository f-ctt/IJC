/*
* 	File:		htab_clear.c
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

void htab_clear(htab_t *t)
{
    if( t == NULL)
        return;
    for( unsigned int i = 0; i < t->arr_size; ++i )
    {
        htab_listitem *ptr = t->list[i];
        t->list[i] = NULL;

        while( ptr != NULL )
        {
            htab_listitem *temp = ptr->next;
            free(ptr);
            ptr = temp;
        }
    }
    t->size = 0;
}
