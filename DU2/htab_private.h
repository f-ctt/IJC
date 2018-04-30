/*
* 	File:		htab_private.h
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

struct hashtable
{
    size_t size;    // actual number of items in hashtable            
    size_t arr_size;    // size of hashtable (numbr of lists of items)
    struct htab_listitem *list[];   // list of linked lits of items
};
