/*
* 	File:		tail.c
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
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

#define DEFAULT_LINE_LEN 1026

/**
 * @brief Circular buffer
 * 
 */
typedef struct circular_buffer {
    unsigned long size;             // lines[size][DEFAULT_LINE_LEN]
    unsigned long tail;              // index of last inserted line
    bool concatenated;            // first round finished indicator ( tail >= size ? tail = 0)
    char lines[][DEFAULT_LINE_LEN];    
} c_buffer_t;

/**
 * @brief Creates c_buffer and sets members
 * 
 * @param size Size of array of chars[DEFAULT)LINE_LEN]
 * @return c_buffer_t* Pointer to c_buffer, NULL if malloc fails
 */
c_buffer_t *c_buffer_init(unsigned long size)
{
    c_buffer_t *buffer = malloc(sizeof(c_buffer_t) + sizeof(char[DEFAULT_LINE_LEN]) * size);
    if( buffer == NULL)
        return NULL;

    buffer->size = size;
    buffer->tail = 0;
    buffer->concatenated = false;

    return buffer;
}

/**
 * @brief Prints given msg to sterr
 * 
 * @param msg String
 */
void error_exit(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

/**
 * @brief Prints lines from lines[x]
 * 
 * @param buffer c_buffer
 */
void print_lines(c_buffer_t *buffer)
{
    unsigned long head = ( !buffer->concatenated ? 0 : buffer->tail + 1);
    if( buffer->concatenated )
    {
        do
        {
            head = head % buffer->size;
            printf("%s", buffer->lines[head++]); // WATCH OUT!
        } while( head != buffer->tail + 1 );
    }
    else
    {
        while( head <= buffer->tail )
        {
            printf("%s", buffer->lines[head++]); // WATCH OUT!
        }
    }
}

/**
 * @brief Reads lines from given stream and inserts them into buffer
 * 
 * @param file target stream
 * @param buffer c_buffer
 */
void read_lines(FILE *file, c_buffer_t *buffer)
{
    bool limit_breached = false;
    unsigned long tail = 0;
    while( fgets(buffer->lines[tail], DEFAULT_LINE_LEN, file) !=  NULL )
    {
        if( !limit_breached )
            if( strlen(buffer->lines[tail]) >= DEFAULT_LINE_LEN ) // strlen stops at '\0' -> if last char not '\0', limit has been reached
            {
                fprintf(stderr, "Line limit breached - (%i chars, including null-char). Continuation with this limit", DEFAULT_LINE_LEN);
                limit_breached = true;
            }
        
        buffer->tail = tail++;
        if( tail >= buffer->size ) // reset tail
        {
            tail = 0;           
            buffer->concatenated = true;
        }
    }
}

long is_number(const char *argv)
{
    errno = 0;
    char *ptr = NULL;
    long num = strtol(argv, &ptr, 10);

    if ( *ptr != '\0' )
        return -1;
    else if ( errno != 0 || num < 0 )
        return -1;

    return num;  
}

int main(int argc, char **argv)
{
    FILE *f = NULL;
    long n = 10;
    
    while( true )       // finite state machine
    {
        switch( argc )
        {
            case 1:
            {
                c_buffer_t *buffer = c_buffer_init(n);
                if( buffer == NULL )
                    error_exit("Cannot allocate memory for c_buffer_t");
                
                if( f == NULL )
                    read_lines(stdin, buffer);
                else
                    read_lines(f, buffer);

                print_lines(buffer);

                free(buffer);
                if( f != NULL )
                    fclose(f);

                return 0;
            }
            case 2: case 4: 
            {
                f = ( argc == 2 ? fopen(argv[1], "r") : fopen(argv[3], "r") );
                if( f == NULL )
                    error_exit("cannot open file");

                argc = ( argc == 2 ? 1 : 3 );
                break;
            }
            case 3:
            {
                if( strcmp("-n",argv[1]) != 0 )
                    error_exit("tail -n num soubor (num >= 0)") ;
                
                n = is_number(argv[2]);
                if( n < 0)
                    error_exit("tail -n num soubor (num >= 0)");
                else if( n == 0)
                    return 0;

                argc = 1;
                break;
            }
            default:
                error_exit("tail -n num soubor (num >= 0)");
        }
    }

   return 0;
}
