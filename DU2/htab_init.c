#include "htab_private.h"

htab_t *htab_init(unsigned int size)
{
    htab_t *htab = (htab_t*)malloc(sizeof(htab_t) + size * sizeof(htab_listitem));
    if( htab == NULL)
        return NULL;

    htab->size = 0;
    htab->arr_size = (size_t)size;

    for( unsigned int i = 0; i < size; ++i)
        htab->list[i] = NULL; 

    return htab;
}
