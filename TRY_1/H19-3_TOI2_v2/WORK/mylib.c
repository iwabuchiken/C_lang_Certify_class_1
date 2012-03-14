/************************************`
 * <Basics>
 *	1. File: mylib.c
 *	2. Author: Iwabuchi Ken				*
 *	3. Date: 20120309_222918
 *	4. Dependencies:
 *		1)
 * <Aim>
 * 	1.
 * <Usage>
 *	1. Execute the program			*
 * <Source>
 * 	1. 
 * <Related>
 * 	1.
 * <Others>
 * <Description of the program>
 * 	1. 
 ************************************/

#ifndef INCLUDE_STDIO_H
#define INCLUDE_STDIO_H
#include <stdio.h>
#endif

#ifndef INCLUDE_STDLIB_H
#define INCLUDE_STDIO_H /* exit() */
#include <stdlib.h>
#endif

#ifndef INCLUDE_STRING_H
#define INCLUDE_STRING_H
#include <string.h>
#endif
#ifndef INCLUDE_TIME_H
#define INCLUDE_TIME_H
#include <time.h>
#endif

#ifndef INCLUDE_CTYPE_H
#define INCLUDE_CTYPE_H
#include <ctype.h>
#endif

#define show(dt, typ) \
			printf(#dt"=%"#typ"(%%"#typ")\n", dt)
#define show1(dt) \
			printf(#dt"\n")

/*
#include "mylib.h"
*/
#ifdef MYLIB
#ifndef INCLUDE_MYLIB_1_H
#define INCLUDE_MYLIB_1_H
#include "mylib.h"
#endif
#endif

// prototypes ============================
/*
int is_digit(char string[]);
int sum_of_array(int first, int last, int array[]);
*/

// functions ============================
int sum_of_array(int first, int last, int array[])
{
    if (first == last) {
        return (array[first]);
    } else {//if (first == last)
        return (array[first] + sum_of_array(first + 1, last, array));
    }//if (first == last)
}//int sum_of_array(int first, int last, int array[])

int is_digit(char string[])
{
    /* vars     */
    int     length; /* length of the given string   */
    int     span;   /* span of the number chars     */
    
    /* processes    */
    length  = strlen(string);
    span    = strspn(string, "-0123456789");
    
    /* judge and return */
    if (length == span) {
        return 1;
    } else {//if (length == span)
        return 0;
    }//if (length == span)
    
}//int is_digit(char string[])

char* read_all(FILE* fp)
{
    /* vars         */
    //char*   content[] = "abcde";
    char*   content[1028];   /* line read from the file  */
    //int     num;             /* number of bytes read */
    
    /* read file    */
    //num = fread(content, sizeof(content), 1, fp);
    fread(content, sizeof(content), 1, fp);
    //fgets((char*)content, sizeof(content), fp);
    
    //return content;
    return (char*)content;
    
}//char* read_all(FILE* file)


/*
#ifdef D
    printf("[LINE:%d]", __LINE__);
#endif
*/
