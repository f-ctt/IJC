/*
* 	File:		htab_hash_function.c
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

//(http://www.cse.yorku.ca/~oz/hash.html - varianta sdbm):
unsigned int htab_hash_function(const char *str, unsigned int htab_arr_size)
{
    unsigned int h = 0; // 32bit 
    const unsigned char *p; 
    for( p = (const unsigned char*)str; *p != '\0'; p++ )  
        h = 65599 * h + *p; 
    return h % htab_arr_size;
}
