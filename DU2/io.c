/*
* 	File:		io.c
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
#include <ctype.h>

/**
 * @brief Funkce cte jedno slovo ze souboru a vraci jeho delku. 
 * Implementacni limit na delku slova je 127 znaku
 * 
 * @param s Retezec - vysledne slovo
 * @param max Max. delka slova (limit je 127 znaku)
 * @param f Soubor
 * @return int Pocet znaku
 */
int get_word(char *s, int max, FILE *f)
{
    if( f == NULL)
        return EOF;

    int count = 0;
    int ch = EOF;

    while( count < max && (ch = fgetc(f)) != EOF )
    {
        if( isspace(ch) )
        {
            if( count != 0 )    // skip multiple new lines.
            {
                break;
            }
        }
        else{
            s[count++] = ch;
        }
    }

    if( count < max )
        s[count] = '\0';
    
    return ( ch == EOF && count == 0 ? EOF : count ); 
}
