/**************************************/
/*  keisoku.c                         */
/*  �����۸ ƭ�خ� ��� ��۸��� ̧��   */
/**************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "common.h"
#include "main.h"
#include "keisoku.h"

extern int akicode_tbl[ MEMBER_MAX + 1 ];			/* ������ ˮ� */
extern int codedata_tbl[ MEMBER_MAX ];				/* �����ް� ����� ˮ� */
extern struct KEISOKU_TBL kojin_keisoku_tbl;			/* ������� ���� �ް�ˮ� */
extern struct KEISOKU_TBL sort_keisoku_tbl[ MEMBER_MAX ];	/* ��� ֳ ���� �ް� ˮ� */


/* ƭ�خ� ���� �ް� ð��� */
static struct  KEISOKU_INPUT   keisoku_indata[ 5 ];

/************************************/
/* ���ް ��� ��۸���                */
/*  ���� �۸ ƭ�خ� ���             */
/*   Ҳ�                            */
/*   ���Ұ� : ż                    */
/*   ����   : 0:OK                  */
/*           -1:NG                  */
/************************************/
int keisoku_input( void )
{
    int     ret;                /* ���� ����        */
    int     i;                  /* ���ޯ��          */
    int     kaiin_code;         /* ���� ���� ����   */
    int     undou_sisuu;        /* �ݼ�� ���޳ ���  */
    char    msg[ 64 ];          /* ү���� �ر       */
    char    keisoku_date[ 9 ];  /* ���� ��޹        */

    /* �� ���� ˮ� READ -> NG ? */
    if( (ret = akicode_tbl_read( )) == NG ) {
        return ret;
    }

    /* ƭ����� ���� */
    if( akicode_tbl[ 0 ] >= MEMBER_MAX ) {
        printf( "\n ��ݻ޲ ƭ����� �� �Ͼ�" );
        return NG;
    }

    /* ���� �ް� ����� ˮ� ̧�� READ -> NG ? */
    if( (ret = codedata_tbl_read( )) == NG ) {
        return ret;
    }

    /* ���� ���� ���� ƭ�خ� */
    kaiin_code_input( &kaiin_code );

    /* ���� ��޹ ƭ�خ� */
    keisoku_date_input( keisoku_date );

    /* ����� ƭ�خ� ��� */
    for( i = 0; i < 5; i++ ) {
        keisoku_data_input( i );
    }

    /* ƭ�خ� �ް� ˮ��� */
    keisoku_data_disp( kaiin_code, keisoku_date );

    /* ƭ�خ� ���� */
    strcpy( msg, "\n ƭ�خ� � �ۼ� �޽�( Y/N )" );

    /* 'N' OR 'n' ƭ�خ� -> OK �� Ų ? */
    if( (ret = kakunin_input( msg )) != OK ) {
        return NG;
    }

    /* ���� �ް� ˮ� READ -> NG ? */
    if( (ret = kojin_data_read( kaiin_code )) == NG ) {
        return ret;
    }

    /* ����� ���� ��� */
    undou_sisuu_keisan( &undou_sisuu );

    /* ���� �ް� ˮ� SET */
    kojin_data_update( kaiin_code, keisoku_date, undou_sisuu );

    /* ���� ��� �ް� ˮ��� */
    kojin_data_disp( kaiin_code, "\n ** ���� ��� �ް� **" );

    /* �� ƭ�خ� �� */
    while( getchar( ) != '\n' ) ;
    printf( "\n ���� �� � ��ø�޻�." );
    getchar( );

    /* ���� ��� �ޭݲ ��� ˮ��� */
    ret = keisoku_rank( );

    return ret;
}



/************************************/
/* ���ް ��� ��۸���                */
/*  ���� �۸ ƭ�خ� ���             */
/*   ���� �ް� ����� ˮ� ̧�� READ  */
/*   ���Ұ� : ż                    */
/*   ����   : 0:OK                  */
/*           -1:NG                  */
/************************************/
static int codedata_tbl_read( void )
{
    int     ret;                        /* ���� ����                */
    FILE    *fp;                        /* ̧�� �߲��               */
    char    *fname = CODEDATA_TBL_NAME;	/* ���� �ް� ����� ˮ� ̧�� */

    /* ���� �ް� ����� ˮ� ̧�� OPEN -> NULL ? */
    if( (fp = fopen( fname, "rb" )) == NULL ) {
        printf( "\n ���� �ް� ����� ˮ� ̧�� OPEN �װ" );
        return NG;
    }

    /* ���� �ް� ����� ˮ� ̧�� READ -> 1��޲ ? */
    if( (ret = fread( (char *)codedata_tbl, sizeof( codedata_tbl ), 1, fp ))
               != 1 ) {
        printf( "\n ���� �ް� ����� ˮ� ̧�� READ �װ" );
        ret = NG;
    }
    else {
        ret = OK;
    }

    /* ���� �ް� ����� ˮ� ̧�� CLOSE */
    fclose( fp );

    return ret;
}



/************************************/
/* ���ް ��� ��۸���                */
/*  ���� �۸ ƭ�خ� ���             */
/*   ���ݺ��� ƭ�خ�                */
/*   ���Ұ� : ƭ�خ� ���� ����      */
/*   ����   : ż                    */
/************************************/
static void kaiin_code_input( int *kaiin_code )
{
    int     loop = TRUE;    /* ٰ�� �׸�    */
    char    work[ 128 ];    /* ƭ�خ� ܰ�   */

    while( loop ) {
        printf( "\n ������ � ���� ���� � ƭ�خ� �ø�޻�" );
        printf( "\n ? " );

        /* ���� ���� ƭ�خ� */
		work[ 0 ] = '\0';
        scanf( "%s", work );

        /* ƭ��د� ���� -> ��� ��޲ ? */
        if( strspn( work, "1234567890" ) < strlen( work ) ) {
            printf( "\n ��� ��޲ �� ƭ�خ� ��ϼ�" );
            continue;
        }

        /* ƭ�خ� �ݲ ����( 0 < kaiin_code <= MEMBER_MAX ) */
        *kaiin_code = atoi( work );
        if( *kaiin_code > MEMBER_MAX || *kaiin_code <= 0 ) {
            printf( "\n ƭ�خ� н �޽" );
            continue;
        }

        /* ���ݺ��� ĳ۸ ���� -> �ĳ۸ ? */
        if( codedata_tbl[ *kaiin_code - 1 ] == 0 ) {
            printf( "\n �� ���ݺ��� � �ĳ۸ �޽" );
            continue;
        }
        break;
    }
    return;
}



/************************************/
/* ���ް ��� ��۸���                */
/*  ���� �۸ ƭ�خ� ���             */
/*   ���� ��޹ ƭ�خ�               */
/*   ���Ұ� : ƭ�خ� ��޹           */
/*   ����   : ż                    */
/************************************/
static void keisoku_date_input( char *keisoku_date )
{
    int     loop = TRUE;    /* ٰ�� �׸�    */
    int     chk_date;       /* ��޹ ���     */
    char    conv[ 3 ];      /* ��� �ݶ� ֳ  */
    char    work[ 128 ];    /* ƭ�خ� ܰ�   */

    while( loop ) {
        printf( "\n ��޹ � ƭ�خ� �ø�޻�( YYYYMMDD )" );
        printf( "\n ? " );

        /* ��޹ ƭ�خ� */
		work[ 0 ] = '\0';
        scanf( "%s", work );

        /* ƭ�خ� ���� ���� -> 8��޲ ? */
        if( strlen( work ) != 8 ) {
            printf( "\n ƭ�خ� н �޽" );
            continue;
        }

        /* ƭ��د� ���� -> �����޲ ? */
        if( strspn( work, "1234567890" ) < strlen( work ) ) {
            printf( "\n ��� ��޲ �� ƭ�خ� ��ϼ�" );
            continue;
        }

        /* · ���� */
	conv[0] = work[4];
	conv[1] = work[5];
	conv[2] = '\0';

        chk_date = atoi( conv );
        if( chk_date > 12 || chk_date < 1 ) {
            printf( "\n ��޹( · ) ƭ�خ� �װ �޽" );
            continue;
        }

        /* � ���� */
	conv[0] = work[6];
	conv[1] = work[7];
	conv[2] = '\0';
        chk_date = atoi( conv );
        if( chk_date > 31 || chk_date < 1 ) {
            printf( "\n ��޹( � ) ƭ�خ� �װ �޽" );
            continue;
        }

        break;
    }

    /* ƭ�خ� �ް� ��� */
    strcpy(keisoku_date, work);
    return;
}



/************************************/
/* ���ް ��� ��۸���                */
/*  ���� �۸ ƭ�خ� ���             */
/*   ����� ƭ�خ� ���               */
/*   ���Ұ� : ���ޯ��               */
/*   ����   : ż                    */
/************************************/
static void keisoku_data_input( int idx )
{
    int     i;                  /* ���ޯ��      */
    int     loop = TRUE;        /* ٰ�� �׸�    */
    char    work[ 3 ][ 128 ];   /* ƭ�خ� ܰ�   */

    while( loop ) {
        printf( "\n ���޳ %d � ���� �ް� � ƭ�خ� �ø�޻�", idx + 1 );
        printf( "\n   ̶(999)  ���(100)  ����(100)" );
        printf( "\n ? " );

        /* ���� �ް� ƭ�خ� */
   	work[ 0 ][ 0 ] = '\0';
	work[ 1 ][ 0 ] = '\0';
	work[ 2 ][ 0 ] = '\0';
        scanf( "%s %s %s", work[ 0 ], work[ 1 ], work[ 2 ] );

        for( i = 0; i < 3; i++ ) {

            /* ƭ�خ� ���� ���� -> 3�ص��� ? */
            if( strlen( work[ i ] ) > 3 ) {
                printf( "\n ƭ�خ� н �޽" );
                break;
            }

            /* ƭ��د� ���� -> �����޲ ? */
            if( strspn( work[ i ], "1234567890" ) < strlen( work[ i ] ) ) {
                printf( "\n ��� ��޲ �� ƭ�خ� ��ϼ�" );
                break;
            }

            /* ̶ ��޲ � �ޮ���� ���� -> 100 �ص��� ? */
            if( i != 0 ) {
                if( atoi( work[ i ] ) > 100 ) {
                    printf( "\n �ޮ����(100) � ��òϽ" );
                    break;
                 }
            }
        }

        if( i < 3 ) {
            continue;
        }

        break;
    }

    /* ƭ�خ� �ް� ð��� ��� */
    keisoku_indata[ idx ].huka = atoi( work[ 0 ] );
    keisoku_indata[ idx ].set = atoi( work[ 1 ] );
    keisoku_indata[ idx ].kaisuu = atoi( work[ 2 ] );

    return;
}



/************************************/
/* ���ް ��� ��۸���                */
/*  ���� �۸ ƭ�خ� ���             */
/*   ƭ�خ� ����� ˮ��� ���         */
/*   ���Ұ� : ���� ����             */
/*            ��޹                  */
/*   ����   : ż                    */
/************************************/
static void keisoku_data_disp( int kaiin_code, char *keisoku_date )
{
    int     i;  	/* ���ޯ��      */

    printf( "\n ** ƭ�خ� ����� �ް� **" );
    printf( "\n ���ݺ��� %3d", kaiin_code );
    printf( "\n ��޹     %4.4s-%2.2s-%2.2s", 
        ( keisoku_date + 0 ), ( keisoku_date + 4 ), ( keisoku_date + 6 ) );

    printf( "\n\n ���޳    ̶    ���    ����" );

    for( i = 0; i < 5; i++ ) {
        printf( "\n   %d     %3d    %3d     %3d", i + 1, 
            keisoku_indata[ i ].huka,
            keisoku_indata[ i ].set,
            keisoku_indata[ i ].kaisuu );
    }

    return;
}



/************************************/
/* ���ް ��� ��۸���                */
/*  ���� �۸ ƭ�خ� ���             */
/*   ���޳ ��� ���� ���             */
/*   ���Ұ� : ���޳ ���             */
/*   ����   : ż                    */
/************************************/
static void undou_sisuu_keisan( int *undou_sisuu )
{
    int     i;              /* ���ޯ��      */
    double  sisuu;          /* ���� ܰ�     */
    double  sisuu_total;    /* ����� �޳��  */
    static  double  huka_sisuu[ 5 ] = { 0.24, 0.36, 0.52, 1.05, 2.13 };

    sisuu_total = 0.0;
    for( i = 0; i < 5; i++ ) {

        /* ���� 1�� ? */
        if( keisoku_indata[ i ].kaisuu <= 1 ) {
            continue;
        }

        sisuu = huka_sisuu[ i ] * (double)keisoku_indata[ i ].huka * 
               (double)keisoku_indata[ i ].set *
               ((pow( (double)keisoku_indata[ i ].kaisuu, 2.0 )) /
               ((double)keisoku_indata[ i ].kaisuu - 1.0));

        /* ����(ٲ��) � ���� */
        sisuu_total += sisuu;
    }

    /* Ͳγ�� � �ݼ�� */
    *undou_sisuu = (int)sqrt( sisuu_total );

    return;
}



/************************************/
/* ���ް ��� ��۸���                */
/*  ���� �۸ ƭ�خ� ���             */
/*   ���� �ް� ˮ� ̧�� ����        */
/*   ���Ұ� : ���� ����             */
/*            ��޹                  */
/*            ���޳ ���             */
/*   ����   : 0:OK                  */
/*           -1:NG                  */
/************************************/
static int kojin_data_update( int kaiin_code, char *keisoku_date, int undou_sisuu )
{
    int     ret;					/* ���� ����            */
    long    fptr;					/* ���� �ް� ̧�� �߲�� */
    FILE    *fp;					/* ̧�� �߲��           */
    char    *fname = KEISOKU_TBL_NAME;			/* ���� �ް� ˮ� ̧��   */
    int	    i;						/* ���ޯ��		*/

    /* 1��� ? */
    if( kojin_keisoku_tbl.count <= 0 ) {
		strcpy( kojin_keisoku_tbl.first_date, keisoku_date );
        kojin_keisoku_tbl.first_data = undou_sisuu;

		strcpy( kojin_keisoku_tbl.max_date, keisoku_date );
        kojin_keisoku_tbl.max_data = undou_sisuu;
    }
    else {

        /* ���� �۸ ? */
        if( kojin_keisoku_tbl.max_data < undou_sisuu ) {
			strcpy( kojin_keisoku_tbl.max_date, keisoku_date );
            kojin_keisoku_tbl.max_data = undou_sisuu;
        }
		for (i = sizeof kojin_keisoku_tbl.soku_data / sizeof(int) - 1; i > 0; i-- )
			kojin_keisoku_tbl.soku_data[ i ] = kojin_keisoku_tbl.soku_data[ i - 1 ];
    }

	strcpy( kojin_keisoku_tbl.soku_date, keisoku_date );
    kojin_keisoku_tbl.soku_data[ 0 ] = undou_sisuu;
    kojin_keisoku_tbl.count++;

    /* ���� �ް� ˮ� ̧�� OPEN -> NULL ? */
    if( (fp = fopen( fname, "r+b" )) == NULL ) {
        printf( "\n ���� �ް� ˮ� ̧�� OPEN �װ" );
        return NG;
    }

    /* �޲ĳ �ް� �߲�� ��� */
    fptr = ( codedata_tbl[ kaiin_code - 1 ] - 1 ) * 
        sizeof( struct KEISOKU_TBL );

    /* ���� �ް� ˮ� ̧�� SEEK -> OK �� Ų ? */
    if( (ret = fseek( fp, fptr, SEEK_SET )) != OK ) {
        printf( "\n ���� �ް� ˮ� ̧�� SEEK �װ" );

        /* ���� �ް� ˮ� ̧�� CLOSE */
        fclose( fp );
        return NG;
    }

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
}



/************************************/
/* ���ް ��� ��۸���                */
/*  ���� �۸ ƭ�خ� ���             */
/*   ���� ��� �ޭݲ ��� ˮ���       */
/*   ���Ұ� : ż                    */
/*   ����   : 0:OK                  */
/*           -1:NG                  */
/************************************/
#ifdef TOI1
int keisoku_rank( void )
{
    int     ret;						/* ���� ����            */
    int     i;							/* ���ޯ��              */
    FILE    *fp;						/* ̧�� �߲��           */
    char    *fname = KEISOKU_TBL_NAME;				/* ���� �ް� ˮ� ̧��   */

    /* ���� �ް� ˮ� ̧�� OPEN -> NULL ? */
    if( (fp = fopen( fname, "rb" )) == NULL ) {
        printf( "\n ���� �ް� ˮ� ̧�� OPEN �װ" );
        return NG;
    }

    i = 0;
    for( ; ; ) {

        /* ���� �ް� ˮ� ̧�� READ -> 1��޲ ? */
        if( (ret = fread( (char *)&sort_keisoku_tbl[ i ],
                   sizeof( struct KEISOKU_TBL ), 1, fp )) != 1 ) {

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
        }

        /* READ �װ ? */
        if( ret == NG ) {
            break;
        }

        /* ���� �ް� �� ? */
        if( sort_keisoku_tbl[ i ].count != 0 ) {
            i++;
        }

        /* eof ? */
        if( ret == OK ) {
            break;
        }
    }

    /* ���� �ް� ˮ� ̧�� CLOSE */
    fclose( fp );

    if( ret == OK ) {
    	/* descending	*/
    	/* ���� �ް� ��� */
		keisoku_data_sort( i, 1 );

		/* ���� �ް� ��� ��� ˮ��� */
		keisoku_sort_disp( i, 1 );

    	/* ascending	*/
        /* ���� �ް� ��� */
        //keisoku_data_sort( i );
    	/* sort => ascednd = 0	*/
    	keisoku_data_sort( i, 0 );
        /* ���� �ް� ��� ��� ˮ��� */
        //keisoku_sort_disp( i );
    	keisoku_sort_disp( i, 0 );
    }

    return ret;
}//int keisoku_rank( void )
#else
static int keisoku_rank( void )
{
    int     ret;						/* ���� ����            */
    int     i;							/* ���ޯ��              */
    FILE    *fp;						/* ̧�� �߲��           */
    char    *fname = KEISOKU_TBL_NAME;				/* ���� �ް� ˮ� ̧��   */

    /* ���� �ް� ˮ� ̧�� OPEN -> NULL ? */
    if( (fp = fopen( fname, "rb" )) == NULL ) {
        printf( "\n ���� �ް� ˮ� ̧�� OPEN �װ" );
        return NG;
    }

    i = 0;
    for( ; ; ) {

        /* ���� �ް� ˮ� ̧�� READ -> 1��޲ ? */
        if( (ret = fread( (char *)&sort_keisoku_tbl[ i ],
                   sizeof( struct KEISOKU_TBL ), 1, fp )) != 1 ) {

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
        }

        /* READ �װ ? */
        if( ret == NG ) {
            break;
        }

        /* ���� �ް� �� ? */
        if( sort_keisoku_tbl[ i ].count != 0 ) {
            i++;
        }

        /* eof ? */
        if( ret == OK ) {
            break;
        }
    }

    /* ���� �ް� ˮ� ̧�� CLOSE */
    fclose( fp );

    if( ret == OK ) {
        /* ���� �ް� ��� */
        keisoku_data_sort( i );
        /* ���� �ް� ��� ��� ˮ��� */
        keisoku_sort_disp( i );
    }

    return ret;
}//static int keisoku_rank( void )
#endif


/************************************/
/* ���ް ��� ��۸���                */
/*  ���� �۸ ƭ�خ� ���             */
/*   ���� ��� ���                   */
/*   ���Ұ� : ���� �ް� �ݽ�        */
/*   ����   : ż                    */
/************************************/
#ifdef TOI1
static void keisoku_data_sort
( int cnt, int mode )
{
    int     i;                  	/* ���ޯ��      */
    int     j;                  	/* ���ޯ��      */
    struct  KEISOKU_TBL  work;  	/* �ܯ�� ֳ �ر */

    /* �ް� ��� */
    for( i = 0; i < cnt - 1; i++ ) {
        for( j = i + 1; j < cnt; j++ ) {
        	/* If 'mode ' is 1,
        	 * then descending sort
        	 */
        	if(mode == 1) {
        		/* If the current's max_data
        		 * is smaller than the next
        		 * one's, then swap the two
        		 */
				if( sort_keisoku_tbl[ i ].max_data <
					sort_keisoku_tbl[ j ].max_data ) {

					work = sort_keisoku_tbl[ i ];
					sort_keisoku_tbl[ i ] = sort_keisoku_tbl[ j ];
					sort_keisoku_tbl[ j ] = work;
				/* If the current one's max_data
				 * and that of the next one are
				 * equal, then sort according
				 * to kaiin_code
				 */
				} else if( (sort_keisoku_tbl[ i ].max_data ==
					sort_keisoku_tbl[ j ].max_data)
					//&& (sort_keisoku_tbl[ i ].kaiin_code <
					&& (sort_keisoku_tbl[ i ].kaiin_code >
					sort_keisoku_tbl[ j ].kaiin_code)) {

					work = sort_keisoku_tbl[ i ];
					sort_keisoku_tbl[ i ] = sort_keisoku_tbl[ j ];
					sort_keisoku_tbl[ j ] = work;
				}//if( sort_keisoku_tbl[ i ].max_data
			/* If 'mode ' is 0,
			 * then ascending sort
			 */
        	} else if (mode == 0) {//if(mode == 1)
        		/* If the current's max_data
				 * is larger than the next
				 * one's, then swap the two
				 */
				if( sort_keisoku_tbl[ i ].max_data >
					sort_keisoku_tbl[ j ].max_data ) {

					work = sort_keisoku_tbl[ i ];
					sort_keisoku_tbl[ i ] = sort_keisoku_tbl[ j ];
					sort_keisoku_tbl[ j ] = work;
				/* If the current one's max_data
				 * and that of the next one are
				 * equal, then sort according
				 * to kaiin_code
				 */
				} else if( (sort_keisoku_tbl[ i ].max_data ==
					sort_keisoku_tbl[ j ].max_data)
					//&& (sort_keisoku_tbl[ i ].kaiin_code <
					&& (sort_keisoku_tbl[ i ].kaiin_code >
					sort_keisoku_tbl[ j ].kaiin_code)) {

					work = sort_keisoku_tbl[ i ];
					sort_keisoku_tbl[ i ] = sort_keisoku_tbl[ j ];
					sort_keisoku_tbl[ j ] = work;
				}//if( sort_keisoku_tbl[ i ].max_data
        	}//if(mode == 1)
        }//for( j = i + 1; j < cnt; j++ )
    }
	return;
}

#else
static void keisoku_data_sort( int cnt )
{
    int     i;                  	/* ���ޯ��      */
    int     j;                  	/* ���ޯ��      */
    struct  KEISOKU_TBL  work;  	/* �ܯ�� ֳ �ر */

    /* �ް� ��� */
    for( i = 0; i < cnt - 1; i++ ) {
        for( j = i + 1; j < cnt; j++ ) {
            if( sort_keisoku_tbl[ i ].max_data <
                sort_keisoku_tbl[ j ].max_data ) {

				work = sort_keisoku_tbl[ i ];
                sort_keisoku_tbl[ i ] = sort_keisoku_tbl[ j ];
                sort_keisoku_tbl[ j ] = work;
            }
        }
    }
	return;
}
#endif


/************************************/
/* ���ް ��� ��۸���                */
/*  ���� �۸ ƭ�خ� ���             */
/*   ���� ��� ˮ���                 */
/*   ���Ұ� : ���� �ް� �ݽ�        */
/*   ����   : ż                    */
/************************************/
#ifdef TOI1
/***************************
 * 	keisoku_data_disp()
 * <Parameters>
 * 	1. mode => 1 or 0
 * 		1 => Top 5
 * 		0 => Bottom 5
 ***************************/
static void keisoku_sort_disp
( int cnt, int mode )
{
    int     i;  /* ���ޯ��  */

    /* Display labels
     * If 'mode' is 1 => top 5
     * If 'mode' is 0 => bottom 5
     */
    /* mode => 1	*/
    if (mode == 1) {
		printf( "\n\n ** �ޭݲ ˮ��i�ޮ���@5��j **" );
		printf( "\n �ޭݲ ���ݺ���  �����ް�   ��޹" );
	/* mode => 0	*/
    } else if (mode == 0) {
    	printf( "\n\n ** �ޭݲ ˮ��i���@5��j **" );
		printf( "\n �ޭݲ ���ݺ���  �����ް�   ��޹" );
    } else {	//if (mode == 1)
    	printf( "\n\n ** �ޭݲ ˮ� **" );
		printf( "\n �ޭݲ ���ݺ���  �����ް�   ��޹" );
    }//if (mode == 1)

    for( i = 0; i < cnt; i++ ) {

        /* 5� ��� ˮ��� �� */
        if( i >= 5 ) {
            break;
        }
        /* 10� ��� ˮ��� �� */
//		if( i >= 10 ) {
//			break;
//		}

        printf( "\n   %2d   %3d        %4d   %4.4s-%2.2s-%2.2s", i + 1,
            sort_keisoku_tbl[ i ].kaiin_code,
            sort_keisoku_tbl[ i ].max_data,
            &sort_keisoku_tbl[ i ].max_date[ 0 ],
            &sort_keisoku_tbl[ i ].max_date[ 4 ],
            &sort_keisoku_tbl[ i ].max_date[ 6 ] );
    }
	return;
}//static void keisoku_sort_disp( int cnt )
#else
static void keisoku_sort_disp( int cnt )
{
    int     i;  /* ���ޯ��  */

    printf( "\n\n ** �ޭݲ ˮ� **" );
    printf( "\n �ޭݲ ���ݺ���  �����ް�   ��޹" );

    for( i = 0; i < cnt; i++ ) {

        /* 10� ��� ˮ��� �� */
        if( i >= 10 ) {
            break;
        }

        printf( "\n   %2d   %3d        %4d   %4.4s-%2.2s-%2.2s", i + 1,
            sort_keisoku_tbl[ i ].kaiin_code,
            sort_keisoku_tbl[ i ].max_data,
            &sort_keisoku_tbl[ i ].max_date[ 0 ],
            &sort_keisoku_tbl[ i ].max_date[ 4 ],
            &sort_keisoku_tbl[ i ].max_date[ 6 ] );
    }
	return;
}//static void keisoku_sort_disp( int cnt )
#endif
