/************************************`
 * <Basics>
 *	1. File: sub1_use_bcc_macro_option.c
 *	2. Author: Iwabuchi Ken				*
 *	3. Date: 20120202_075416
 * <Aim>
 *	1. Use bcc32 command line option '-D'
 * <Usage>
 *	1.bcc32 -D"D=1" <filename>
 * <Source>
 *	1.
 * <Result>
 * 	1. The macro "D" defined with a value.
 * 		The 'D' option used: "-DD=1"
 * 		=> Printed value still is 22
 * 			(not 1)
 ************************************/
#ifndef INCLUDE_STDIO
#define INCLUDE_STDIO
#include <stdio.h>
#endif
#ifndef INCLUDE_STDLIB
#define INCLUDE_STDLIB
#include <stdlib.h>
#endif
#ifndef INCLUDE_STRING
#define INCLUDE_STRING
#include <string.h>
#endif
#ifndef INCLUDE_TIME
#define INCLUDE_TIME
#include <time.h>
#endif
#ifndef INCLUDE_MATH
#define INCLUDE_MATH
#include <math.h>
#endif

//v=1.0
//created_at=20120202_072802
//project=C:\workspaces\ws_ubuntu_1\G20120202_072802_CExam_class1\main.c
#define D 22

int main( int argc, char *argv[] )
{
    printf("D=%d\n", D);

    return 0;
}//int main( int argc, char *argv[] )

/*
#ifdef D
    printf("[%s:%d]", __FILE__, __LINE__);
#endif

    printf("Content-Type: text/html;charset=shift-jis\n\n");
    printf(__FILE__); printf("<br>\n");
    printf(CREATED_AT); printf("<br>\n");
*/
