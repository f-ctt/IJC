/*
* 	File:		tail2.cc
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

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <cctype>
#include <algorithm>

/**
 * @brief error message -> stderr. Exits program.
 * 
 * @param message String - error message
 */
void error_exit(std::string message)
{
    std::cerr << message << std::endl;
    exit(1);
}

/**
 * @brief Checks wheter string is an unsigned integer. If so, returns it, otherwise returns -1
 * 
 * @param s String - number
 * @return int -1 if not a digit, else -> digit
 */
long long is_number(std::string argv)
{
    size_t invalid_char_index;
    long long num;
    try{
        num = std::stoll(argv, &invalid_char_index, 10);

    }catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
        return -1;
    }

    if ( argv[invalid_char_index] != '\0')
        return -1;
    else if ( num < 0 )
        return -1;

    return num;  
}

/**
 * @brief Reads lines from specified stream and pushs them in to queue.
 *  If num of read lines > n, queue.pop() 
 *  
 * @param stream Target stream (file or stdin)
 * @param buff queue FIFO
 * @param n Num of lines, that queue contains
 */
void read_lines(std::istream &stream, std::queue<std::string> &buff, long long n)
{
        std::string line;
        while(std::getline(stream, line))
        {
            buff.push(line);
            if( buff.size() > n )
                buff.pop();
        }
}

/**
 * @brief Prints each line form queue and pops it. At the end, queue'll be empty
 * 
 * @param buff queue
 */
void print_lines(std::queue<std::string> &buff)
{
    while( !buff.empty() )
    {
        std::cout << buff.front() << '\n';
        buff.pop();
    }
}

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(false);
    std::ifstream f;
    long long n = 10;
    
    while( true )       // finite state machine
    {
        switch( argc )
        {
            case 1:
            {
                std::queue<std::string> buffer;
                
                if( !f.is_open() )
                    read_lines(std::cin, buffer, n);
                else
                    read_lines(f, buffer, n);

                print_lines(buffer);

                if( f.is_open() )
                    f.close();

                return 0;
            }
            case 2: case 4: 
            {
                if( argc == 2 )
                    f.open(argv[1]);
                else
                    f.open(argv[3]);

                if( !f.is_open() )
                    error_exit("cannot open file");

                argc = ( argc == 2 ? 1 : 3 );
                break;
            }
            case 3:
            {
                if( std::string(argv[1]).compare("-n") != 0 )
                    error_exit("tail -n num soubor (num >= 0)") ;
                
                n = is_number(argv[2]);
                if( n < 0)
                    error_exit("tail -n num soubor (num >= 0)");
                if( n == 0)
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

//TODO:DONE:
//- [x] Refactor main function -> repetitive code -> finite state machine
//- [x] std::ios::sync_with_stdio(false);
