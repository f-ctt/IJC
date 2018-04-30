/*
* 	File:		htab_free.c
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
#include "htab.h"

void htab_free(htab_t *t)
{
    if( t == NULL)
        return;
    htab_clear(t);
    free(t);
    t = NULL;
}
