/************************************`
 * <Basics>
 *	1. File: sub2_special_que~akicode_tbl_update.c
 *	2. Author: Iwabuchi Ken				*
 *	3. Date: 20120202_075416
 * <Aim>
 *	1. �d�l�i�P�j�A���������邽�߂́A�L���[���
 * <Usage>
 *	1. bcc32 -DTOI1 <file list>
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

#define MEMBER_MAX	    5
#define AKICODE_TBL_NAME    "akicode.tbl"	/* ������ˮ� ̧�� Ҳ */
#define  TRUE          1    /* ��            */
#define  FALSE         0    /* ��            */
#define  OK            0    /* ���ޮ�        */
#define  CANCEL        1    /* ��� ����      */
#define  NG           -1    /* ��ޮ�         */
#define AKICODE_TBL_NAME    "akicode.tbl"	/* ������ˮ� ̧�� Ҳ */

int akicode_tbl[ MEMBER_MAX + 1 ];

/**********************************************
 * Prototypes
**********************************************/
static int akicode_tbl_create( void );
static int akicode_tbl_update( void );
static void show_akicode_tbl( void );
static int akicode_tbl_shuffle( int number );

/**********************************************
 * Functions
**********************************************/
static void show_akicode_tbl( void )
{
	int		i;		/* index */

	for(i = 0; i < MEMBER_MAX + 1; i++) {
		printf("akicode_tbl[%d]=%d\n",
					i, akicode_tbl[i]);
	}
}//static void show_akicode_tbl( void )

static int akicode_tbl_create( void )
{
    int     ret;				/* ���� ����        */
    int     i;					/* ���ޯ��          */
    FILE    *fp;				/* ̧�� �߲��       */
    char    *fname = AKICODE_TBL_NAME;		/* �� ���� ˮ� ̧�� */

    /* �� ���� �ݼ�� */
    akicode_tbl[ 0 ] = MEMBER_MAX;
    for( i = 1; i < MEMBER_MAX + 1; i++ ) {
        akicode_tbl[ i ] = i;
    }

    /* �� ���� ˮ� ̧�� OPEN -> NULL ? */
    if( (fp = fopen( fname, "w+b" )) == NULL ) {
        printf( "\n �� ����ˮ� ̧�� OPEN �װ" );
        return NG;
    }

    /* �� ���� ˮ� ̧�� WRITE -> 1��޲ ? */
    if( (ret = fwrite( (char *)akicode_tbl, sizeof( akicode_tbl ), 1, fp ) )
               != 1 ) {
        printf( "\n �� ����ˮ� ̧�� WRITE �װ" );
        ret = NG;
    }
    else {
        ret = OK;
    }

    /* �� ���� ˮ� ̧�� CLOSE */
    fclose( fp );

    return ret;
}//static int akicode_tbl_create( void )

static int akicode_tbl_update( void )
{
    int     ret;					/* ���� ����        */
    int     i;						/* ���ޯ��          */
    int     cnt;					/* �� ���� ��       */
    FILE    *fp;					/* ̧�� �߲��       */
    char    *fname = AKICODE_TBL_NAME;  		/* �� ���� ˮ� ̧�� */

    /* �� ���� �ݽ� ��� */
    cnt = akicode_tbl[ 0 ];

    //return 0;

#ifdef DEBUG
    printf("[%s:%d]\n", __FILE__, __LINE__);
    printf("�󂫃R�[�h����(cnt)�F %d\n", cnt);
    printf("\n");
#endif

    /* �� ���� �ݼ�� */
    for( i = 1; i < cnt; i++ ) {
        if( akicode_tbl[ i + 1 ] == 0 ) {
            break;
        }
        akicode_tbl[ i ] = akicode_tbl[ i + 1 ];
    }

    akicode_tbl[ i ] = 0;

    /* �� ���� �ݽ� ��� */
    akicode_tbl[ 0 ] = cnt - 1;

    /* �� ���� ˮ� ̧�� OPEN -> NULL ? */
    if( (fp = fopen( fname, "w+b" )) == NULL ) {
        printf( "\n ������ ˮ� ̧�� OPEN �װ" );
        return NG;
    }

    /* �� ���� ˮ� ̧�� WRITE -> 1��޲ ? */
    if( (ret = fwrite( (char *)akicode_tbl,
               sizeof( int ) * (akicode_tbl[ 0 ] + 1), 1, fp )) != 1 ) {
        printf( "\n �� ���� ˮ� ̧�� WRITE �װ" );
        ret = NG;
    }
    else {
        ret = OK;
    }

    /* �� ���� ˮ� ̧�� CLOSE */
    fclose( fp );

    return ret;
}//static int akicode_tbl_update( void )

/*
 * akicode_tbl_shuffle()
 * <Parameter>
 * 	1. number:int =>
 * <Return>
 */
static int akicode_tbl_shuffle( int number )
{
    int     ret;					/* ���� ����        */
    int     i;						/* ���ޯ��          */
    int     cnt;					/* �� ���� ��       */
    FILE    *fp;					/* ̧�� �߲��       */
    char    *fname = AKICODE_TBL_NAME;  		/* �� ���� ˮ� ̧�� */

    int		akicode_tbl_tmp[MEMBER_MAX + 1];	/* ��Ɨp */
    int		j;			/* index for akicode_tbl */
    int		k;			/* index for akicode_tbl_tmp */

#ifdef DEBUG
    printf("[%s:%d]", __FILE__, __LINE__);
    printf("Enter: %s\n", "akicode_tbl_shuffle()");
#endif

    /* Copy: From number to tail */
    for(j = number, k = 1; j <= akicode_tbl[0]; j++, k++) {
    	akicode_tbl_tmp[k] = akicode_tbl[j];
    }//for(j = number, k = 1; j <= akicode_tbl[0]; j++, k++) {

    /* Copy: From head to (number - 1) */
    for(j = 1; j < number; j++, k++) {
    	akicode_tbl_tmp[k] = akicode_tbl[j];
    }

    /* Copy: akicode_tbl_tmp[] to akicode_tbl[] */
    for(j = 1; j <= akicode_tbl[0]; j++) {
    	akicode_tbl[j] = akicode_tbl_tmp[j];
    }

#ifdef DEBUG
    printf("[%s:%d]", __FILE__, __LINE__);
    printf("Exit: %s\n", "akicode_tbl_shuffle()");
#endif

    //return 0;
    return 0;

}//static int akicode_tbl_shuffle( void )

int main( int argc, char *argv[] )
{
#ifdef NUM
	int		shuffle_num = NUM;
#else
	int		shuffle_num = 2;	/* akicode_tbl_shuffle() */
#endif

	akicode_tbl_create();

	/* Show akicode_tbl[] */
	show_akicode_tbl();

	/* Update akicode_tbl[] */
	//akicode_tbl_update();

	/* �󂫃R�[�h���� */
	printf("[%s:%d]", __FILE__, __LINE__);
	printf("akicode_tbl[0]=%d\n", akicode_tbl[0]);

	/* �󂫃R�[�h�\�F���בւ� */
	//akicode_tbl_shuffle(2);
	akicode_tbl_shuffle(shuffle_num);

	/* Show akicode_tbl[] */
	show_akicode_tbl();

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
