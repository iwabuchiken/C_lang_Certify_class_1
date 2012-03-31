/************************************/
/*  sakujyo.c                       */
/*    ĳ۸ ���ޮ ��� ��۸��� ̧��   */
/************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "common.h"
#include "main.h"
#include "sakujyo.h"

extern int akicode_tbl[ MEMBER_MAX + 1 ];		/* ������ ˮ� */
extern int codedata_tbl[ MEMBER_MAX ];			/* �����ް� ����� ˮ� */ /* main.c  */
extern struct KEISOKU_TBL kojin_keisoku_tbl;		/* ������� ���� �ް�ˮ� */

/************************************/
/* ���ް ��� ��۸���                */
/*  ĳ۸ ���ޮ ���                  */
/*   Ҳ�                            */
/*   ���Ұ� : ż                    */
/*   ����   : 0:OK                  */
/*           -1:NG                  */
/************************************/
int touroku_sakujyo( void )
{
    int     ret;            /* ���� ����        */
    int     loop = TRUE;    /* ٰ�� �׸�        */
    int     kaiin_code;     /* ���ޮ ���� ����  */
    char    work[ 128 ];    /* ƭ�خ� ܰ�       */

    while( loop ) {
        printf( "\n ������ � ���� ���� � ƭ�خ� �ø�޻�" );
        printf( "\n ? " );

        /* ���� ���� ƭ�خ� */
        work[ 0 ] = '\0';
        scanf( "%s", work );

        /* ƭ��د� ���� -> �����޲ ? */
        if( strspn( work, "1234567890" ) < strlen( work ) ) {
            printf( "\n ��� ��޲ �� ƭ�خ� ��ϼ�" );
            continue;
        }

        /* ƭ�خ� �ݲ ���� -> ( 0 < kaiin_code <= MEMBER_MAX ) ? */
        kaiin_code = atoi( work );
        if( kaiin_code > MEMBER_MAX || kaiin_code <= 0 ) {
            printf( "\n ƭ�خ� н �޽" );
            continue;
        }

        /* ���� �ް� ����� ˮ� ���ޮ -> OK ? */
        ret = codedata_tbl_delete( kaiin_code );
        
        //debug
        printf("\n[%s:%d] ret=%d\n", __FILE__, __LINE__, ret);
        if (ret == OK) {
            loop = FALSE;

        } else {//if (ret == OK)
        }//if (ret == OK)
        
    }

    return ret;
}
/*  codedata_tbl_delete()
 * 1. read: codedata_tbl[]
 * 2. read: 
 * 
 * 
 * 
 */
static int codedata_tbl_delete( int kaiin_code )
{
    int     ret;                        /* ���� ����                */
    int     i;                          /* ���ޯ��                  */
    char    msg[ 64 ];                  /* ү���� �ر               */
    FILE    *fp;                        /* ̧�� �߲��               */
    char    *fname = CODEDATA_TBL_NAME;	/* ���� �ް� ����� ˮ� ̧�� */
    
    /* ���� �ް� ����� ˮ� ̧�� OPEN -> NULL ? */
    if( (fp = fopen( fname, "r+b" )) == NULL ) {
        printf( "\n ���� �ް� ����� ˮ� ̧�� OPEN �װ" );
        return NG;
    }
    
    /* read: codedata_tbl       */
    ret = fread( (char *)codedata_tbl, sizeof( codedata_tbl ), 1, fp );
    if (ret != 1) {
        /* READ �װ */
        printf( "\n ���� �ް� ����� ˮ� ̧�� READ �װ" );

        /* ���� �ް� ����� ˮ� ̧�� CLOSE */
        fclose( fp );
        return NG;
    }//if (ret != 1)
    
    /* ���� ĳ۸ ���� -> �ĳ۸ ? */
    if( codedata_tbl[ kaiin_code - 1 ] == 0 ) {
        printf( "\n �� ���� ���� � �ĳ۸ �޽" );

        /* ���� �ް� ����� ˮ� ̧�� CLOSE */
        fclose( fp );
        return CANCEL;
    }
    
    /* ���� �ް� ˮ� READ -> NG ? */
    if( (ret = kojin_data_read( kaiin_code )) == NG ) {
        /* ���� �ް� ����� ˮ� ̧�� CLOSE */
        fclose( fp );
        return ret;
    }
    
    /* ���� �ް� ˮ��� */
    kojin_data_disp( kaiin_code, "\n ** ���ޮ �ް� **" );   
    
    /* ���� �ް� ˮ� ���ޮ ���� */
    sprintf( msg, "\n\n �� � �ް� � ���ޮ �Ͻ. �ۼ� �޽�( Y/N )" );
    
    ret = kakunin_input( msg );
    if (ret !=OK) {
        return CANCEL;
    }//if (ret ==OK)
    
    /* ���� �ް� ˮ� ���ޮ -> OK ? */
    ret = kojin_data_delete( kaiin_code );
    
    //debug
//    printf("kojin_keisoku_tbl.kaiin_code=%d\n",
//                    kojin_keisoku_tbl.kaiin_code);
//    printf("kojin_keisoku_tbl[%d].kaiin_code=%d\n",
  //          kaiin_code, kojin_keisoku_tbl[kaiin_code].kaiin_code);

    //debug
//    printf("\n[%s:%d]\n", __FILE__, __LINE__);
//    printf("kaiin_code=%d\n", kaiin_code);
//    printf("\n");
//    
//    for (i = 0; i < 10; i++) {
//        printf("codedata_tbl[%d]=%d\n", i, codedata_tbl[i]);
//    }//for (i = 0; i < 10; i++)
//    printf("\n");
    
    //debug
    //printf("\n[%d] codedata_tbl_delete()\n", __LINE__);
    
    /* return       */
    return OK;
    
}//static int codedata_tbl_delete( int kaiin_code )

static int kojin_data_delete( int kaiin_code )
{
    int     ret;				/* ���� ����                */
    int     i;					/* ���ޯ��                  */
    FILE    *fp;				/* ���� �ް� ˮ� ̧�� �߲�� */
    FILE    *tmp;				/* ������ ̧�� �߲��        */
    char    *fname = KEISOKU_TBL_NAME;		/* ���� �ް� ˮ� ̧��       */
    char    *tmpfl = "keisoku.tmp";		/* ������ ̧��              */

    /* ���� �ް� ˮ� ̧�� OPEN -> NULL ? */
    if( (fp = fopen( fname, "rb" )) == NULL ) {
        printf( "\n ���� �ް� ˮ� ̧�� OPEN �װ" );
        return NG;
    }

    /* ������ ̧�� OPEN -> NULL ? */
    if( (tmp = fopen( tmpfl, "w+b" )) == NULL ) {
        printf( "\n ������ ̧�� OPEN �װ" );
        fclose( fp );
        return NG;
    }

    i = 0;
    for( ; ; ) {

        /* ���� �ް� ˮ� ̧�� READ -> 1��޲ ? */
        if( (ret = fread( (char *)&kojin_keisoku_tbl,
                   sizeof( kojin_keisoku_tbl ), 1, fp )) != 1 ) {

            /* READ �װ ? */
            if( ferror( fp ) != 0 ) {
                printf( "\n ���� �ް� ˮ� ̧�� READ �װ" );
                ret = NG;
            }
            else {
                /* ̧�� EOF �� Ų ? */
                if( feof( fp ) == 0 ) {
                    printf( "\n ���� �ް� ˮ� ̧�� READ �װ" );
                    ret = NG;
                }
                else {
                   ret = OK;
                }
            }
            break;
        }

        /* ���ޮ �ް� ? */
        if( kaiin_code == kojin_keisoku_tbl.kaiin_code ) {
            continue;
        }

        /* ������ ̧�� WRITE -> 1��޲ ? */
        if( (ret = fwrite( (char *)&kojin_keisoku_tbl,
                   sizeof( kojin_keisoku_tbl ), 1, tmp )) != 1 ) {
            printf( "\n ���� �ް� ˮ� ̧�� WRITE �װ" );
            ret = NG;
            break;
        }
        i++;
    }

    /* ������ ̧�� CLOSE */
    fclose( tmp );

    /* ���� �ް� ˮ� ̧�� CLOSE */
    fclose( fp );

    /* ���ޮ� ���خ� ? */
    if( ret == OK ) {

        /* ���� �ް� ˮ� ̧�� DELETE -> 0��޲ ? */
        if( (ret = remove( fname )) != 0 ) {
            printf( "\n ���� �ް� ˮ� ̧�� ���ޮ �װ" );
            ret = NG;
        }
        else {
            /* ���� �ް� �� ? */
            if( i > 0 ) {

                /* ������ ̧�� � ���� �ް� ˮ� ̧�� � �Ȱ� �� -> 0��޲ ? */
                if( (ret = rename( tmpfl, fname )) != 0 ) {
                    printf( "\n ���� �ް� ˮ� ̧�� �Ȱ� �װ" );
                    ret = NG;
                }
            }
            else {
                /* ������ ̧�� ���ޮ */
                remove( tmpfl );
            }
        }
    }
    else {
        /* ������ ̧�� ���ޮ */
        remove( tmpfl );
    }

    return ret;
}//static int kojin_data_delete( int kaiin_code )
