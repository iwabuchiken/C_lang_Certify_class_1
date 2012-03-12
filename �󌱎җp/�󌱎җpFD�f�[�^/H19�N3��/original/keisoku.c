/**************************************/
/*  keisoku.c                         */
/*  ¹²¿¸·Û¸ Æ­³Ø®¸ ¼®Ø ÌßÛ¸Þ×Ñ Ì§²Ù   */
/**************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "common.h"
#include "main.h"
#include "keisoku.h"

extern int akicode_tbl[ MEMBER_MAX + 1 ];			/* ±·º°ÄÞ Ë®³ */
extern int codedata_tbl[ MEMBER_MAX ];				/* º°ÄÞÃÞ°À À²¼®³ Ë®³ */
extern struct KEISOKU_TBL kojin_keisoku_tbl;			/* º¼ÞÝÍÞÂ ¹²¿¸ ÃÞ°ÀË®³ */
extern struct KEISOKU_TBL sort_keisoku_tbl[ MEMBER_MAX ];	/* ¿°Ä Ö³ ¹²¿¸ ÃÞ°À Ë®³ */


/* Æ­³Ø®¸ ¹²¿¸ ÃÞ°À Ã°ÌÞÙ */
static struct  KEISOKU_INPUT   keisoku_indata[ 5 ];

/************************************/
/* ÒÝÊÞ° ¶ÝØ ÌßÛ¸Þ×Ñ                */
/*  ¹²¿¸ ·Û¸ Æ­³Ø®¸ ¼®Ø             */
/*   Ò²Ý                            */
/*   Êß×Ò°À : Å¼                    */
/*   ØÀ°Ý   : 0:OK                  */
/*           -1:NG                  */
/************************************/
int keisoku_input( void )
{
    int     ret;                /* ØÀ°Ý º°ÄÞ        */
    int     i;                  /* ²ÝÃÞ¯¸½          */
    int     kaiin_code;         /* ¹²¿¸ ¶²²Ý º°ÄÞ   */
    int     undou_sisuu;        /* »Ý¼­Â ³ÝÄÞ³ ¼½³  */
    char    msg[ 64 ];          /* Ò¯¾°¼Þ ´Ø±       */
    char    keisoku_date[ 9 ];  /* ¹²¿¸ ËÂÞ¹        */

    /* ±· º°ÄÞ Ë®³ READ -> NG ? */
    if( (ret = akicode_tbl_read( )) == NG ) {
        return ret;
    }

    /* Æ­³¶²¼¬ Áª¯¸ */
    if( akicode_tbl[ 0 ] >= MEMBER_MAX ) {
        printf( "\n ¹ÞÝ»Þ² Æ­³¶²¼¬ ¶Þ ²Ï¾Ý" );
        return NG;
    }

    /* º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù READ -> NG ? */
    if( (ret = codedata_tbl_read( )) == NG ) {
        return ret;
    }

    /* ¹²¿¸ ¶²²Ý º°ÄÞ Æ­³Ø®¸ */
    kaiin_code_input( &kaiin_code );

    /* ¹²¿¸ ËÂÞ¹ Æ­³Ø®¸ */
    keisoku_date_input( keisoku_date );

    /* ¹²¿¸Á Æ­³Ø®¸ ¼®Ø */
    for( i = 0; i < 5; i++ ) {
        keisoku_data_input( i );
    }

    /* Æ­³Ø®¸ ÃÞ°À Ë®³¼Þ */
    keisoku_data_disp( kaiin_code, keisoku_date );

    /* Æ­³Ø®¸ ¶¸ÆÝ */
    strcpy( msg, "\n Æ­³Ø®¸ Ê ÖÛ¼² ÃÞ½¶( Y/N )" );

    /* 'N' OR 'n' Æ­³Ø®¸ -> OK ÃÞ Å² ? */
    if( (ret = kakunin_input( msg )) != OK ) {
        return NG;
    }

    /* ¹²¿¸ ÃÞ°À Ë®³ READ -> NG ? */
    if( (ret = kojin_data_read( kaiin_code )) == NG ) {
        return ret;
    }

    /* ¹²¿¸Á ¹²»Ý ¼®Ø */
    undou_sisuu_keisan( &undou_sisuu );

    /* ¹²¿¸ ÃÞ°À Ë®³ SET */
    kojin_data_update( kaiin_code, keisoku_date, undou_sisuu );

    /* ¹²¿¸ ¹¯¶ ÃÞ°À Ë®³¼Þ */
    kojin_data_disp( kaiin_code, "\n ** ¹²¿¸ ¹¯¶ ÃÞ°À **" );

    /* ·° Æ­³Ø®¸ ÏÁ */
    while( getchar( ) != '\n' ) ;
    printf( "\n ØÀ°Ý ·° ¦ µ¼Ã¸ÀÞ»²." );
    getchar( );

    /* ¹²¿¸ ¹¯¶ ¼Þ­Ý² ¿°Ä Ë®³¼Þ */
    ret = keisoku_rank( );

    return ret;
}



/************************************/
/* ÒÝÊÞ° ¶ÝØ ÌßÛ¸Þ×Ñ                */
/*  ¹²¿¸ ·Û¸ Æ­³Ø®¸ ¼®Ø             */
/*   º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù READ  */
/*   Êß×Ò°À : Å¼                    */
/*   ØÀ°Ý   : 0:OK                  */
/*           -1:NG                  */
/************************************/
static int codedata_tbl_read( void )
{
    int     ret;                        /* ØÀ°Ý º°ÄÞ                */
    FILE    *fp;                        /* Ì§²Ù Îß²ÝÀ               */
    char    *fname = CODEDATA_TBL_NAME;	/* º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù */

    /* º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù OPEN -> NULL ? */
    if( (fp = fopen( fname, "rb" )) == NULL ) {
        printf( "\n º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù OPEN ´×°" );
        return NG;
    }

    /* º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù READ -> 1²¶Þ² ? */
    if( (ret = fread( (char *)codedata_tbl, sizeof( codedata_tbl ), 1, fp ))
               != 1 ) {
        printf( "\n º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù READ ´×°" );
        ret = NG;
    }
    else {
        ret = OK;
    }

    /* º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù CLOSE */
    fclose( fp );

    return ret;
}



/************************************/
/* ÒÝÊÞ° ¶ÝØ ÌßÛ¸Þ×Ñ                */
/*  ¹²¿¸ ·Û¸ Æ­³Ø®¸ ¼®Ø             */
/*   ¶²²Ýº°ÄÞ Æ­³Ø®¸                */
/*   Êß×Ò°À : Æ­³Ø®¸ ¶²²Ý º°ÄÞ      */
/*   ØÀ°Ý   : Å¼                    */
/************************************/
static void kaiin_code_input( int *kaiin_code )
{
    int     loop = TRUE;    /* Ù°Ìß Ì×¸Þ    */
    char    work[ 128 ];    /* Æ­³Ø®¸ Ü°¸   */

    while( loop ) {
        printf( "\n ¹²¿¸¼¬ É ¶²²Ý º°ÄÞ ¦ Æ­³Ø®¸ ¼Ã¸ÀÞ»²" );
        printf( "\n ? " );

        /* ¶²²Ý º°ÄÞ Æ­³Ø®¸ */
		work[ 0 ] = '\0';
        scanf( "%s", work );

        /* Æ­°ÒØ¯¸ Áª¯¸ -> ½³Á ²¶Þ² ? */
        if( strspn( work, "1234567890" ) < strlen( work ) ) {
            printf( "\n ½³Á ²¶Þ² ¶Þ Æ­³Ø®¸ »ÚÏ¼À" );
            continue;
        }

        /* Æ­³Ø®¸ ÊÝ² Áª¯¸( 0 < kaiin_code <= MEMBER_MAX ) */
        *kaiin_code = atoi( work );
        if( *kaiin_code > MEMBER_MAX || *kaiin_code <= 0 ) {
            printf( "\n Æ­³Ø®¸ Ð½ ÃÞ½" );
            continue;
        }

        /* ¶²²Ýº°ÄÞ Ä³Û¸ Áª¯¸ -> ÐÄ³Û¸ ? */
        if( codedata_tbl[ *kaiin_code - 1 ] == 0 ) {
            printf( "\n ºÉ ¶²²Ýº°ÄÞ Ê ÐÄ³Û¸ ÃÞ½" );
            continue;
        }
        break;
    }
    return;
}



/************************************/
/* ÒÝÊÞ° ¶ÝØ ÌßÛ¸Þ×Ñ                */
/*  ¹²¿¸ ·Û¸ Æ­³Ø®¸ ¼®Ø             */
/*   ¹²¿¸ ËÂÞ¹ Æ­³Ø®¸               */
/*   Êß×Ò°À : Æ­³Ø®¸ ËÂÞ¹           */
/*   ØÀ°Ý   : Å¼                    */
/************************************/
static void keisoku_date_input( char *keisoku_date )
{
    int     loop = TRUE;    /* Ù°Ìß Ì×¸Þ    */
    int     chk_date;       /* ËÂÞ¹ ½³Á     */
    char    conv[ 3 ];      /* ½³Á ÍÝ¶Ý Ö³  */
    char    work[ 128 ];    /* Æ­³Ø®¸ Ü°¸   */

    while( loop ) {
        printf( "\n ËÂÞ¹ ¦ Æ­³Ø®¸ ¼Ã¸ÀÞ»²( YYYYMMDD )" );
        printf( "\n ? " );

        /* ËÂÞ¹ Æ­³Ø®¸ */
		work[ 0 ] = '\0';
        scanf( "%s", work );

        /* Æ­³Ø®¸ ¹À½³ Áª¯¸ -> 8²¶Þ² ? */
        if( strlen( work ) != 8 ) {
            printf( "\n Æ­³Ø®¸ Ð½ ÃÞ½" );
            continue;
        }

        /* Æ­°ÒØ¯¸ Áª¯¸ -> ½³Á²¶Þ² ? */
        if( strspn( work, "1234567890" ) < strlen( work ) ) {
            printf( "\n ½³Á ²¶Þ² ¶Þ Æ­³Ø®¸ »ÚÏ¼À" );
            continue;
        }

        /* Â· Áª¯¸ */
	conv[0] = work[4];
	conv[1] = work[5];
	conv[2] = '\0';

        chk_date = atoi( conv );
        if( chk_date > 12 || chk_date < 1 ) {
            printf( "\n ËÂÞ¹( Â· ) Æ­³Ø®¸ ´×° ÃÞ½" );
            continue;
        }

        /* Ë Áª¯¸ */
	conv[0] = work[6];
	conv[1] = work[7];
	conv[2] = '\0';
        chk_date = atoi( conv );
        if( chk_date > 31 || chk_date < 1 ) {
            printf( "\n ËÂÞ¹( Ë ) Æ­³Ø®¸ ´×° ÃÞ½" );
            continue;
        }

        break;
    }

    /* Æ­³Ø®¸ ÃÞ°À ¾¯Ä */
    strcpy(keisoku_date, work);
    return;
}



/************************************/
/* ÒÝÊÞ° ¶ÝØ ÌßÛ¸Þ×Ñ                */
/*  ¹²¿¸ ·Û¸ Æ­³Ø®¸ ¼®Ø             */
/*   ¹²¿¸Á Æ­³Ø®¸ ¼®Ø               */
/*   Êß×Ò°À : ²ÝÃÞ¯¸½               */
/*   ØÀ°Ý   : Å¼                    */
/************************************/
static void keisoku_data_input( int idx )
{
    int     i;                  /* ²ÝÃÞ¯¸½      */
    int     loop = TRUE;        /* Ù°Ìß Ì×¸Þ    */
    char    work[ 3 ][ 128 ];   /* Æ­³Ø®¸ Ü°¸   */

    while( loop ) {
        printf( "\n ³ÝÄÞ³ %d É ¹²¿¸ ÃÞ°À ¦ Æ­³Ø®¸ ¼Ã¸ÀÞ»²", idx + 1 );
        printf( "\n   Ì¶(999)  ¾¯Ä(100)  ¶²½³(100)" );
        printf( "\n ? " );

        /* ¹²¿¸ ÃÞ°À Æ­³Ø®¸ */
   	work[ 0 ][ 0 ] = '\0';
	work[ 1 ][ 0 ] = '\0';
	work[ 2 ][ 0 ] = '\0';
        scanf( "%s %s %s", work[ 0 ], work[ 1 ], work[ 2 ] );

        for( i = 0; i < 3; i++ ) {

            /* Æ­³Ø®¸ ¹À½³ Áª¯¸ -> 3ÖØµµ·² ? */
            if( strlen( work[ i ] ) > 3 ) {
                printf( "\n Æ­³Ø®¸ Ð½ ÃÞ½" );
                break;
            }

            /* Æ­°ÒØ¯¸ Áª¯¸ -> ½³Á²¶Þ² ? */
            if( strspn( work[ i ], "1234567890" ) < strlen( work[ i ] ) ) {
                printf( "\n ½³Á ²¶Þ² ¶Þ Æ­³Ø®¸ »ÚÏ¼À" );
                break;
            }

            /* Ì¶ ²¶Þ² É ¼Þ®³¹ÞÝ Áª¯¸ -> 100 ÖØµµ·² ? */
            if( i != 0 ) {
                if( atoi( work[ i ] ) > 100 ) {
                    printf( "\n ¼Þ®³¹ÞÝ(100) ¦ º´Ã²Ï½" );
                    break;
                 }
            }
        }

        if( i < 3 ) {
            continue;
        }

        break;
    }

    /* Æ­³Ø®¸ ÃÞ°À Ã°ÌÞÙ ¾¯Ä */
    keisoku_indata[ idx ].huka = atoi( work[ 0 ] );
    keisoku_indata[ idx ].set = atoi( work[ 1 ] );
    keisoku_indata[ idx ].kaisuu = atoi( work[ 2 ] );

    return;
}



/************************************/
/* ÒÝÊÞ° ¶ÝØ ÌßÛ¸Þ×Ñ                */
/*  ¹²¿¸ ·Û¸ Æ­³Ø®¸ ¼®Ø             */
/*   Æ­³Ø®¸ ¹²¿¸Á Ë®³¼Þ ¼®Ø         */
/*   Êß×Ò°À : ¶²²Ý º°ÄÞ             */
/*            ËÂÞ¹                  */
/*   ØÀ°Ý   : Å¼                    */
/************************************/
static void keisoku_data_disp( int kaiin_code, char *keisoku_date )
{
    int     i;  	/* ²ÝÃÞ¯¸½      */

    printf( "\n ** Æ­³Ø®¸ ¹²¿¸Á ÃÞ°À **" );
    printf( "\n ¶²²Ýº°ÄÞ %3d", kaiin_code );
    printf( "\n ËÂÞ¹     %4.4s-%2.2s-%2.2s", 
        ( keisoku_date + 0 ), ( keisoku_date + 4 ), ( keisoku_date + 6 ) );

    printf( "\n\n ³ÝÄÞ³    Ì¶    ¾¯Ä    ¶²½³" );

    for( i = 0; i < 5; i++ ) {
        printf( "\n   %d     %3d    %3d     %3d", i + 1, 
            keisoku_indata[ i ].huka,
            keisoku_indata[ i ].set,
            keisoku_indata[ i ].kaisuu );
    }

    return;
}



/************************************/
/* ÒÝÊÞ° ¶ÝØ ÌßÛ¸Þ×Ñ                */
/*  ¹²¿¸ ·Û¸ Æ­³Ø®¸ ¼®Ø             */
/*   ³ÝÄÞ³ ¼½³ ¹²»Ý ¼®Ø             */
/*   Êß×Ò°À : ³ÝÄÞ³ ¼½³             */
/*   ØÀ°Ý   : Å¼                    */
/************************************/
static void undou_sisuu_keisan( int *undou_sisuu )
{
    int     i;              /* ²ÝÃÞ¯¸½      */
    double  sisuu;          /* ¹²»Ý Ü°¸     */
    double  sisuu_total;    /* ¹²»ÝÁ ºÞ³¹²  */
    static  double  huka_sisuu[ 5 ] = { 0.24, 0.36, 0.52, 1.05, 2.13 };

    sisuu_total = 0.0;
    for( i = 0; i < 5; i++ ) {

        /* ¶²½³ 1²¶ ? */
        if( keisoku_indata[ i ].kaisuu <= 1 ) {
            continue;
        }

        sisuu = huka_sisuu[ i ] * (double)keisoku_indata[ i ].huka * 
               (double)keisoku_indata[ i ].set *
               ((pow( (double)keisoku_indata[ i ].kaisuu, 2.0 )) /
               ((double)keisoku_indata[ i ].kaisuu - 1.0));

        /* ¼¸ÞÏ(Ù²¹²) É ¹²»Ý */
        sisuu_total += sisuu;
    }

    /* Í²Î³ºÝ É »Ý¼­Â */
    *undou_sisuu = (int)sqrt( sisuu_total );

    return;
}



/************************************/
/* ÒÝÊÞ° ¶ÝØ ÌßÛ¸Þ×Ñ                */
/*  ¹²¿¸ ·Û¸ Æ­³Ø®¸ ¼®Ø             */
/*   ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù º³¼Ý        */
/*   Êß×Ò°À : ¶²²Ý º°ÄÞ             */
/*            ËÂÞ¹                  */
/*            ³ÝÄÞ³ ¼½³             */
/*   ØÀ°Ý   : 0:OK                  */
/*           -1:NG                  */
/************************************/
static int kojin_data_update( int kaiin_code, char *keisoku_date, int undou_sisuu )
{
    int     ret;					/* ØÀ°Ý º°ÄÞ            */
    long    fptr;					/* ¹²¿¸ ÃÞ°À Ì§²Ù Îß²ÝÀ */
    FILE    *fp;					/* Ì§²Ù Îß²ÝÀ           */
    char    *fname = KEISOKU_TBL_NAME;			/* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù   */
    int	    i;						/* ²ÝÃÞ¯¸½		*/

    /* 1¶²Ò ? */
    if( kojin_keisoku_tbl.count <= 0 ) {
		strcpy( kojin_keisoku_tbl.first_date, keisoku_date );
        kojin_keisoku_tbl.first_data = undou_sisuu;

		strcpy( kojin_keisoku_tbl.max_date, keisoku_date );
        kojin_keisoku_tbl.max_data = undou_sisuu;
    }
    else {

        /* »²º³ ·Û¸ ? */
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

    /* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù OPEN -> NULL ? */
    if( (fp = fopen( fname, "r+b" )) == NULL ) {
        printf( "\n ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù OPEN ´×°" );
        return NG;
    }

    /* ¶Þ²Ä³ ÃÞ°À Îß²ÝÀ ¾¯Ä */
    fptr = ( codedata_tbl[ kaiin_code - 1 ] - 1 ) * 
        sizeof( struct KEISOKU_TBL );

    /* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù SEEK -> OK ÃÞ Å² ? */
    if( (ret = fseek( fp, fptr, SEEK_SET )) != OK ) {
        printf( "\n ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù SEEK ´×°" );

        /* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù CLOSE */
        fclose( fp );
        return NG;
    }

    /* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù WRITE -> 1²¶Þ² ? */
    if( (ret = fwrite( (char *)&kojin_keisoku_tbl, sizeof( kojin_keisoku_tbl ),
               1, fp )) != 1 ) {
        printf( "\n ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù WRITE ´×°" );
        ret = NG;
    }
    else {
        ret = OK;
    }

    /* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù CLOSE */
    fclose( fp );

    return ret;
}



/************************************/
/* ÒÝÊÞ° ¶ÝØ ÌßÛ¸Þ×Ñ                */
/*  ¹²¿¸ ·Û¸ Æ­³Ø®¸ ¼®Ø             */
/*   ¹²¿¸ ¹¯¶ ¼Þ­Ý² ¿°Ä Ë®³¼Þ       */
/*   Êß×Ò°À : Å¼                    */
/*   ØÀ°Ý   : 0:OK                  */
/*           -1:NG                  */
/************************************/
static int keisoku_rank( void )
{
    int     ret;						/* ØÀ°Ý º°ÄÞ            */
    int     i;							/* ²ÝÃÞ¯¸½              */
    FILE    *fp;						/* Ì§²Ù Îß²ÝÀ           */
    char    *fname = KEISOKU_TBL_NAME;				/* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù   */

    /* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù OPEN -> NULL ? */
    if( (fp = fopen( fname, "rb" )) == NULL ) {
        printf( "\n ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù OPEN ´×°" );
        return NG;
    }

    i = 0;
    for( ; ; ) {

        /* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù READ -> 1²¶Þ² ? */
        if( (ret = fread( (char *)&sort_keisoku_tbl[ i ],
                   sizeof( struct KEISOKU_TBL ), 1, fp )) != 1 ) {

            /* READ ´×° ? */
            if( ferror( fp ) != 0 ) {
                printf( "\n ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù READ ´×°" );
                ret = NG;
            }
            else {
                /* Ì§²Ù EOF ÃÞ Å² ? */
                if( feof( fp ) == 0 ) {
                    printf( "\n ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù READ ´×°" );
                    ret = NG;
                }
                else {
                    ret = OK;
                }
            }
        }

        /* READ ´×° ? */
        if( ret == NG ) {
            break;
        }

        /* ¹²¿¸ ÃÞ°À ±Ø ? */
        if( sort_keisoku_tbl[ i ].count != 0 ) {
            i++;
        }

        /* eof ? */
        if( ret == OK ) {
            break;
        }
    }

    /* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù CLOSE */
    fclose( fp );

    if( ret == OK ) {
        /* ¹²¿¸ ÃÞ°À ¿°Ä */
        keisoku_data_sort( i );
        /* ¹²¿¸ ÃÞ°À ¿°Ä ¹¯¶ Ë®³¼Þ */
        keisoku_sort_disp( i );
    }

    return ret;
}



/************************************/
/* ÒÝÊÞ° ¶ÝØ ÌßÛ¸Þ×Ñ                */
/*  ¹²¿¸ ·Û¸ Æ­³Ø®¸ ¼®Ø             */
/*   ¹²¿¸ ¹¯¶ ¿°Ä                   */
/*   Êß×Ò°À : ¹²¿¸ ÃÞ°À ¹Ý½³        */
/*   ØÀ°Ý   : Å¼                    */
/************************************/
static void keisoku_data_sort( int cnt )
{
    int     i;                  	/* ²ÝÃÞ¯¸½      */
    int     j;                  	/* ²ÝÃÞ¯¸½      */
    struct  KEISOKU_TBL  work;  	/* ½Ü¯Ìß Ö³ ´Ø± */

    /* ÃÞ°À ¿°Ä */
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



/************************************/
/* ÒÝÊÞ° ¶ÝØ ÌßÛ¸Þ×Ñ                */
/*  ¹²¿¸ ·Û¸ Æ­³Ø®¸ ¼®Ø             */
/*   ¹²¿¸ ¹¯¶ Ë®³¼Þ                 */
/*   Êß×Ò°À : ¹²¿¸ ÃÞ°À ¹Ý½³        */
/*   ØÀ°Ý   : Å¼                    */
/************************************/
static void keisoku_sort_disp( int cnt )
{
    int     i;  /* ²ÝÃÞ¯¸½  */

    printf( "\n\n ** ¼Þ­Ý² Ë®³ **" );
    printf( "\n ¼Þ­Ý² ¶²²Ýº°ÄÞ  »²º³ÃÞ°À   ËÂÞ¹" );

    for( i = 0; i < cnt; i++ ) {

        /* 10² ÏÃÞ Ë®³¼Þ ½Ù */
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
}
