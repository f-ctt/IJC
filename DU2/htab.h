/*
* 	File:		htab.h
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

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/**
 * @brief A hastable item
 * 
 */
typedef struct htab_listitem htab_listitem;

struct htab_listitem
{
    struct htab_listitem *next;     // next item
    unsigned int data;              // number of occurences
    char key[];             

};

/**
 * @brief Hashtable
 * 
 */
typedef struct hashtable htab_t;

/**
 * @brief Hash function that returns hastable index
 * 
 * @param str string used to compute the hash
 * @param htab_arr_size hashtable size
 * @return unsigned int hashtable index
 */
unsigned int htab_hash_function(const char *str, unsigned int htab_arr_size);

/**
 * @brief Constructor - creating and initializing hashtable
 * 
 * @param size Number of items in hashtable
 * @return htab_t* If mallock returns null, then null
 */
htab_t *htab_init(unsigned int size);

/**
 * @brief Move constructor - creating and initializing hashtable with t2 items. T2 will be empty and allocated
 *  
 * @param newsize New size of hashtable
 * @param t2 Pointer to hashtable
 * @return htab_t* If allocation fails, return NULL
 */
htab_t *htab_move(unsigned int newsize, htab_t *t2);

/**
 * @brief Returns an actual number of items in hashtable (.size)
 * 
 * @param t Pointer to hastable
 * @return size_t Number of items
 */
size_t htab_size(htab_t *t);

/**
 * @brief Returns a number of elements of hashtable (.arr_size)
 * 
 * @param t Pointer to hashtable
 * @return size_t Number of elements of hashtable
 */
size_t htab_bucket_count(htab_t *t);

/**
 * @brief Looks up item in htab and:
 *  - if found, returns pointer to that item
 *  - if not, crates the item and inserts into htab
 * 
 * @param t Pointer to hashtable
 * @param key String - key
 * @return htab_listitem* Pointer to item, NULL if malloc fails
 */
struct htab_listitem *htab_lookup_add(htab_t *t, const char *key);

/**
 * @brief 'look_up' like func, doesn't insert item if not found
 * 
 * @param t Pointer to hashtable
 * @param key String - key
 * @return htab_listitem* Pointer to item, NULL if not found
 */
struct htab_listitem *htab_find(htab_t *t, const char *key);

/**
 * @brief Finds item and removes it
 * 
 * @param t Pointer to hashtable
 * @param key String - key
 * @return true Item deletion has been successful
 * @return false Item does not exist in hashtable
 */
bool htab_remove(htab_t *t, const char *key);

/**
 * @brief Removes all items in hashtable - htab is empty
 * 
 * @param t Pointer to hashtable
 */
void htab_clear(htab_t *t);

/**
 * @brief Destructor - calls htab_clear()
 * 
 * @param t Pointer to hashtable
 */
void htab_free(htab_t *t);

/**
 * @brief Calls given function for every item in hashtable. Does not alter data
 * 
 * @param t Pointer to hash table
 * @param func Pointer to function with parameters (key, valueptr)
 */
void htab_foreach(htab_t *t, void (*func)(const char *key, unsigned int valueptr));
