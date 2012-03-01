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
extern int codedata_tbl[ MEMBER_MAX ];			/* �����ް� ����� ˮ� */
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
        if( (ret = codedata_tbl_delete( kaiin_code )) == OK ) {
            /* �� ���� ˮ� ²� -> OK ? */
            if( (ret = akicode_tbl_add( kaiin_code )) == OK ) {
                /* Ҳ� � ���� */
                loop = FALSE;
            }
        }
        else {
            /* Ҳ� � ���� */
            loop = FALSE;
        }//if( (ret = codedata_tbl_delete( kaiin_code )) == OK )
    }//while( loop )

    if( ret == OK ) {
        printf( "\n ƭ��� ĳ۸ ���ޮ ��� �� ���خ� �ϼ�" );
    }

    return ret;
}//int touroku_sakujyo( void )



/************************************/
/* ���ް ��� ��۸���                */
/*  ĳ۸ ���ޮ ���                  */
/*   ���� �ް� ����� ˮ� ̧�� ����  */
/*   ���Ұ� : ���ޮ ���� ����       */
/*   ����   : 0:OK                  */
/*            1:CANCEL              */
/*           -1:NG                  */
/************************************/
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

    /* ���� �ް� ����� ˮ� ̧�� READ -> 1��޲ ? */
    if( (ret = fread( (char *)codedata_tbl, sizeof( codedata_tbl ), 1, fp ) )
               != 1 ) {
        /* READ �װ */
        printf( "\n ���� �ް� ����� ˮ� ̧�� READ �װ" );

        /* ���� �ް� ����� ˮ� ̧�� CLOSE */
        fclose( fp );
        return NG;
    }

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

    if( (ret = kakunin_input( msg )) == OK ) {

        /* ���� �ް� ˮ� ���ޮ -> OK ? */
        if( (ret = kojin_data_delete( kaiin_code )) == OK ) {

            /* ���� �ް� �߲�� ���� */
            for( i = 0; i < MEMBER_MAX; i++ ) {
                if( codedata_tbl[ i ] > codedata_tbl[ kaiin_code - 1 ] ) {
                    codedata_tbl[ i ]--;
                }
            }

            /* ���� �ް� �߲�� �ر */
            codedata_tbl[ kaiin_code - 1 ] = 0;

            /* ���� �ް� ����� ˮ� ̧�� � ��ĳ�� � SEEK -> OK ? */
            if( (ret = fseek( fp, 0L, SEEK_SET )) == OK ) {

                /* ���� �ް� ����� ˮ� ̧�� WRITE -> 1��޲ ? */
                if( (ret = fwrite( (char *)codedata_tbl,
                           sizeof( codedata_tbl ),1, fp )) != 1 ) {
                    printf( "\n ���� �ް� ����� ˮ� ̧�� WRITE �װ" );
                    ret = NG;
                }
                else {
                    ret = OK;
                }
            }
            else {
                printf( "\n ���� �ް� ����� ˮ� ̧�� SEEK �װ" );
                ret = NG;
            }
        }
    }
    else {
        /* ��� ���� */
        ret = CANCEL;
    }

    /* ���� �ް� ����� ˮ� ̧�� CLOSE */
    fclose( fp );

    return ret;
}



/************************************/
/* ���ް ��� ��۸���                */
/*  ĳ۸ ���ޮ ���                  */
/*   ���� �ް� ˮ� ���ޮ            */
/*   ���Ұ� : ���ޮ ���� ����       */
/*   ����   : 0:OK                  */
/*           -1:NG                  */
/************************************/
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
}



/************************************/
/* ���ް ��� ��۸���                */
/*  ĳ۸ ���ޮ ���                  */
/*   �� ���� ˮ� ̧�� ²�           */
/*   ���Ұ� : ���ޮ ���� ����       */
/*   ����   : 0:OK                  */
/*           -1:NG                  */
/************************************/
static int akicode_tbl_add( int kaiin_code )
{
    int     ret;				/* ���� ����        */
    int     cnt;				/* �� ���޹ݽ�      */
    FILE    *fp;				/* ̧�� �߲��       */
    char    *fname = AKICODE_TBL_NAME;		/* �� ���� ˮ� ̧�� */

    /* �� ���� ˮ� READ -> NG ? */
    if( (ret = akicode_tbl_read( )) == NG ) {
        return ret;
    }

    /* �� ���� �ݽ� ��� */
    cnt = akicode_tbl[ 0 ];

    /* �� ���� ð��� ��� */
    akicode_tbl[ cnt + 1 ] = kaiin_code;

    /* �� ���� �ݽ� ��� */
    akicode_tbl[ 0 ] = cnt + 1;

    /* �� ���� ˮ� ̧�� OPEN -> NULL ? */
    if( (fp = fopen( fname, "w+b" )) == NULL ) {
        printf( "\n �� ����ˮ� ̧�� OPEN �װ" );
        return NG;
    }

    /* �� ���� ˮ� ̧�� WRITE -> 1��޲ ? */
    if( (ret = fwrite( (char *)akicode_tbl,
               sizeof( int ) * ( akicode_tbl[ 0 ] + 1 ), 1, fp )) != 1 ) {
        printf( "\n �� ���� ˮ� ̧�� WRITE �װ" );
        ret = NG;
    }
    else {
        ret = OK;
    }

    /* ������ ˮ� ̧�� CLOSE */
    fclose( fp );

    return ret;
}
