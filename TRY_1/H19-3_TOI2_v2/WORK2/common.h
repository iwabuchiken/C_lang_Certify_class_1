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
#define MEMBER_MAX	    200			/* ���ް�� MAX */
#define AKICODE_TBL_NAME    "akicode.tbl"	/* ������ˮ� ̧�� Ҳ */
#define CODEDATA_TBL_NAME   "codedata.tbl"  	/* ���� �ް� ����� ˮ� ̧�� Ҳ */
#define KEISOKU_TBL_NAME    "keisoku.tbl"	/* ���� �ް� ˮ� ̧�� Ҳ */

#define  TRUE          1    /* ��            */
#define  FALSE         0    /* ��            */
#define  OK            0    /* ���ޮ�        */
#define  CANCEL        1    /* ��� ����      */
#define  NG           -1    /* ��ޮ�         */

//#define MEMBER_MAX 10

struct   KEISOKU_TBL {
    int  kaiin_code;       /* ���� ����     */
    int  count;            /* ���� ����     */
    char first_date[ 9 ];  /* ���� ��޹     */
    int  first_data;       /* ���� �ް�     */
    char max_date[ 9 ];    /* ���� �۸ ��޹ */
    int  max_data;         /* ���� �۸ �ް� */
    char soku_date[ 9 ];   /* ���� ��޹     */
    int  soku_data[ 10 ];  /* ���� �ް�     */
};


//===============EOF==============================