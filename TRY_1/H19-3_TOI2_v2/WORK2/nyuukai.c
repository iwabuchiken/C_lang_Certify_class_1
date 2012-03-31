/************************************/
/*  nyuukai.c                       */
/*    ƭ��� ĳ۸ ��� ��۸��� ̧��   */
/************************************/
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "main.h"
#include "nyuukai.h"

extern int akicode_tbl[ MEMBER_MAX + 1 ];			/* ������ ˮ� */
extern int codedata_tbl[ MEMBER_MAX ];				/* �����ް� ����� ˮ� */
extern struct KEISOKU_TBL kojin_keisoku_tbl;			/* ������� ���� �ް�ˮ� */

/***********************************/
/* ���ް ��� ��۸���               */
/*  ƭ��� ĳ۸ ���                 */
/*   Ҳ�                           */
/*   ���Ұ� : ż                   */
/*   ����   : 0:OK                 */
/*           -1:NG                 */
/***********************************/
int nyuukai_touroku( void )
{
    int    ret;             /* ���� ����        */
    int    kaiin_code;      /* ĳ۸ ���� ����   */
    long   fptr;            /* ̧�� �߲��       */
    char   msg[ 64 ];       /* ү���� �ر       */
    
    /* �� ���� ˮ� READ -> NG ? */
	if( (ret = akicode_tbl_read( )) == NG ) {
        return ret;
	}

    /* �� ���� �� ? */
    if( akicode_tbl[ 0 ] <= 0 ) {
        printf( "\n �����Ŷ�� ��޲� ���ް � ���� ��Ͼ�\n" );
        ret = OK;
        return ret;
    }
    
    /* �� ���� ���� */
    /* setup msg variable   */
    sprintf( msg, "\n ���� ���� � %d �޽. �ۼ� �޽�( Y/N )", akicode_tbl[ 1 ] );
    
    /* validate the input   */
    ret = kakunin_input( msg );
    
    /* set: kaiin_code      */
    if (ret == OK) {
        kaiin_code = akicode_tbl[1];
    } else {//if (ret == OK)
        return ret;
    }//if (ret == OK)
    
    /* update akicode_tbl   */
    ret = akicode_tbl_update( );
    
    /* add: new record to keisoku_tbl     */
    if (ret == OK) {
        ret = keisoku_tbl_add(&fptr, kaiin_code);
    } else {//if (ret == OK)
        return ret;
    }//if (ret == OK)
    
    /* update: codedata_tbl */
    if (ret == OK) {
        ret = codedata_tbl_update( kaiin_code, fptr );
    } else {//if (ret == OK)
        return ret;
    }//if (ret == OK)
    
    if (ret == OK) {
        printf("Register => complete\n");

    }//if (ret == OK)
    
    return ret;
}//int nyuukai_touroku( void )

/************************************/
/* ���ް ��� ��۸���                */
/*  ƭ��� ĳ۸ ���                  */
/*   �� ���� ˮ� ̧�� ����          */
/*   ���Ұ� : ż                    */
/*   ����   : 0:OK                  */
/*           -1:NG                  */
/************************************/
static int akicode_tbl_update( void )
{
    int     ret;					/* ���� ����        */
    int     i;						/* ���ޯ��          */
    int     cnt;					/* �� ���� ��       */
    FILE    *fp;					/* ̧�� �߲��       */
    char    *fname = AKICODE_TBL_NAME;  		/* �� ���� ˮ� ̧�� */

    /* �� ���� �ݽ� ��� */
    cnt = akicode_tbl[ 0 ];

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

/************************************/
/* ���ް ��� ��۸���                */
/*  ƭ��� ĳ۸ ���                  */
/*   ���� �ް� ˮ� ̧�� ²�         */
/*   ���Ұ� : ���� �ް� �߲��       */
/*            ĳ۸ ���� ����        */
/*   ����   : 0:OK                  */
/*           -1:NG                  */
/************************************/
static int keisoku_tbl_add( long *fptr, int kaiin_code )
{
    int     ret;					/* ���� ����            */
    FILE    *fp;					/* ̧�� �߲��           */
    char    *fname = KEISOKU_TBL_NAME;			/* ���� �ް� ˮ� ̧��   */

    /* ���� �ް� ˮ� ̧�� OPEN -> NULL ? */
    if( (fp = fopen( fname, "a+b" )) == NULL ) {
        printf( "\n ���� �ް� ˮ� ̧�� OPEN �װ" );
        return NG;
    }

    /* ���� �ް� ˮ� ̧�� SEEK -> OK �� Ų ? */
    if( (ret = fseek( fp, 0L, SEEK_END )) != OK ) {
        printf( "\n ���� �ް� ˮ� ̧�� SEEK �װ" );
        /* ���� �ް� ˮ� ̧�� CLOSE */
        fclose( fp );
        return NG;
    }

    /* ̧�� �߲�� ��ĸ */
    *fptr = ftell( fp );

    /* ���� �ް� ˮ� �ر */
	kojin_keisoku_tbl = init_kojin_keisoku_tbl();

    /* ���� ���� ��� */
    kojin_keisoku_tbl.kaiin_code = kaiin_code;

    /* ���� �ް� ˮ� ̧�� WRITE -> 1��޲ ? */
    if( (ret = fwrite( (char *)&kojin_keisoku_tbl, sizeof( kojin_keisoku_tbl ),
               1, fp )) != 1 ) {
        printf( "\n ���� �ް� ˮ� ̧�� WRITE �װ" );
        ret = NG;
    }
    else {
        ret = OK;
    }

    /* ���� �ް� ˮ� ̧�� CLOSE */
    fclose( fp );

    return ret;
}//static int keisoku_tbl_add( long *fptr, int kaiin_code )

static int codedata_tbl_update( int kaiin_code, long fptr )
{
    int     ret;                        /* ���� ����                */
    FILE    *fp;                        /* ̧�� �߲��               */
    char    *fname = CODEDATA_TBL_NAME;	/* ���� �ް� ����� ˮ� ̧�� */

    /* ���� �ް� ����� ˮ� ̧�� OPEN -> NULL ? */
    if( (fp = fopen( fname, "r+b" )) == NULL ) {
        printf( "\n ���� �ް� ����� ˮ� ̧�� OPEN �װ" );
        return NG;
    }

    /* ���� �ް� ����� ˮ� ̧�� READ -> 1��޲ ? */
    if( (ret = fread( (char *)codedata_tbl, sizeof( codedata_tbl ), 1, fp ) )
               != 1 ) {
        printf( "\n ���� �ް� ����� ˮ� ̧�� READ �װ" );
        ret = NG;
    }
    else {
        /* �޲ĳ �ް� �߲�� ��� */
        codedata_tbl[ kaiin_code - 1 ] = 
            (int)( (fptr / sizeof( struct KEISOKU_TBL )) + 1 );

        /* ̧�� �߲�� � ��ĳ � SEEK -> OK �� Ų ? */
        if( (ret = fseek( fp, 0L, SEEK_SET )) != OK ) {
            printf( "\n ���� �ް� ����� ˮ� ̧�� SEEK �װ" );

            /* ���� �ް� ����� ˮ� ̧�� CLOSE */
            fclose( fp );
            return NG;
        }

        /* ���� �ް� ����� ˮ� ̧�� WRITE -> 1��޲ ? */
        if( (ret = fwrite( (char *)codedata_tbl, sizeof( codedata_tbl ), 1,
                   fp )) != 1 ) {
            printf( "\n ���� �ް� ����� ˮ� ̧�� WRITE �װ" );
            ret = NG;
        }
        else {
            ret = OK;
        }
    }

    /* ���� �ް� ����� ˮ� ̧�� CLOSE */
    fclose( fp );

    return ret;
}//static int codedata_tbl_update( int kaiin_code, long fptr )
