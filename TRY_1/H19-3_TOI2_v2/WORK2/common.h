/************************************`
 * <Basics>
 *	1. File: common.h
 *	2. Author: Iwabuchi Ken				*
 *	3. Date: 20120314_085559
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

// include 
#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif STDIO

#ifndef STDLIB
#define STDLIB
#include <stdlib.h>
#endif STDLIB

#ifndef STRING
#define STRING
#include <string.h>
#endif STRING


// macros ============================
#define MEMBER_MAX	    200			/* ÒÝÊÞ°½³ MAX */
#define AKICODE_TBL_NAME    "akicode.tbl"	/* ±·º°ÄÞË®³ Ì§²Ù Ò² */
#define CODEDATA_TBL_NAME   "codedata.tbl"  	/* º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù Ò² */
#define KEISOKU_TBL_NAME    "keisoku.tbl"	/* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù Ò² */

#define  TRUE          1    /* ¼Ý            */
#define  FALSE         0    /* ·Þ            */
#define  OK            0    /* ¾²¼Þ®³        */
#define  CANCEL        1    /* ¼®Ø Á­³¼      */
#define  NG           -1    /* ²¼Þ®³         */

//#define MEMBER_MAX 10

struct   KEISOKU_TBL {
    int  kaiin_code;       /* ¶²²Ý º°ÄÞ     */
    int  count;            /* ¹²¿¸ ¶²½³     */
    char first_date[ 9 ];  /* ¼®¶² ËÂÞ¹     */
    int  first_data;       /* ¼®¶² ÃÞ°À     */
    char max_date[ 9 ];    /* »²º³ ·Û¸ ËÂÞ¹ */
    int  max_data;         /* »²º³ ·Û¸ ÃÞ°À */
    char soku_date[ 9 ];   /* ¹²¿¸ ËÂÞ¹     */
    int  soku_data[ 10 ];  /* ¹²¿¸ ÃÞ°À     */
};


//===============EOF==============================