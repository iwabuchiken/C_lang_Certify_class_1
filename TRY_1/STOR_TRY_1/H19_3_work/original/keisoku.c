/**************************************/
/*  keisoku.c                         */
/*  ｹｲｿｸｷﾛｸ ﾆｭｳﾘｮｸ ｼｮﾘ ﾌﾟﾛｸﾞﾗﾑ ﾌｧｲﾙ   */
/**************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "common.h"
#include "main.h"
#include "keisoku.h"

extern int akicode_tbl[ MEMBER_MAX + 1 ];			/* ｱｷｺｰﾄﾞ ﾋｮｳ */
extern int codedata_tbl[ MEMBER_MAX ];				/* ｺｰﾄﾞﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ */
extern struct KEISOKU_TBL kojin_keisoku_tbl;			/* ｺｼﾞﾝﾍﾞﾂ ｹｲｿｸ ﾃﾞｰﾀﾋｮｳ */
extern struct KEISOKU_TBL sort_keisoku_tbl[ MEMBER_MAX ];	/* ｿｰﾄ ﾖｳ ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ */


/* ﾆｭｳﾘｮｸ ｹｲｿｸ ﾃﾞｰﾀ ﾃｰﾌﾞﾙ */
static struct  KEISOKU_INPUT   keisoku_indata[ 5 ];

/************************************/
/* ﾒﾝﾊﾞｰ ｶﾝﾘ ﾌﾟﾛｸﾞﾗﾑ                */
/*  ｹｲｿｸ ｷﾛｸ ﾆｭｳﾘｮｸ ｼｮﾘ             */
/*   ﾒｲﾝ                            */
/*   ﾊﾟﾗﾒｰﾀ : ﾅｼ                    */
/*   ﾘﾀｰﾝ   : 0:OK                  */
/*           -1:NG                  */
/************************************/
int keisoku_input( void )
{
    int     ret;                /* ﾘﾀｰﾝ ｺｰﾄﾞ        */
    int     i;                  /* ｲﾝﾃﾞｯｸｽ          */
    int     kaiin_code;         /* ｹｲｿｸ ｶｲｲﾝ ｺｰﾄﾞ   */
    int     undou_sisuu;        /* ｻﾝｼｭﾂ ｳﾝﾄﾞｳ ｼｽｳ  */
    char    msg[ 64 ];          /* ﾒｯｾｰｼﾞ ｴﾘｱ       */
    char    keisoku_date[ 9 ];  /* ｹｲｿｸ ﾋﾂﾞｹ        */

    /* ｱｷ ｺｰﾄﾞ ﾋｮｳ READ -> NG ? */
    if( (ret = akicode_tbl_read( )) == NG ) {
        return ret;
    }

    /* ﾆｭｳｶｲｼｬ ﾁｪｯｸ */
    if( akicode_tbl[ 0 ] >= MEMBER_MAX ) {
        printf( "\n ｹﾞﾝｻﾞｲ ﾆｭｳｶｲｼｬ ｶﾞ ｲﾏｾﾝ" );
        return NG;
    }

    /* ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ READ -> NG ? */
    if( (ret = codedata_tbl_read( )) == NG ) {
        return ret;
    }

    /* ｹｲｿｸ ｶｲｲﾝ ｺｰﾄﾞ ﾆｭｳﾘｮｸ */
    kaiin_code_input( &kaiin_code );

    /* ｹｲｿｸ ﾋﾂﾞｹ ﾆｭｳﾘｮｸ */
    keisoku_date_input( keisoku_date );

    /* ｹｲｿｸﾁ ﾆｭｳﾘｮｸ ｼｮﾘ */
    for( i = 0; i < 5; i++ ) {
        keisoku_data_input( i );
    }

    /* ﾆｭｳﾘｮｸ ﾃﾞｰﾀ ﾋｮｳｼﾞ */
    keisoku_data_disp( kaiin_code, keisoku_date );

    /* ﾆｭｳﾘｮｸ ｶｸﾆﾝ */
    strcpy( msg, "\n ﾆｭｳﾘｮｸ ﾊ ﾖﾛｼｲ ﾃﾞｽｶ( Y/N )" );

    /* 'N' OR 'n' ﾆｭｳﾘｮｸ -> OK ﾃﾞ ﾅｲ ? */
    if( (ret = kakunin_input( msg )) != OK ) {
        return NG;
    }

    /* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ READ -> NG ? */
    if( (ret = kojin_data_read( kaiin_code )) == NG ) {
        return ret;
    }

    /* ｹｲｿｸﾁ ｹｲｻﾝ ｼｮﾘ */
    undou_sisuu_keisan( &undou_sisuu );

    /* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ SET */
    kojin_data_update( kaiin_code, keisoku_date, undou_sisuu );

    /* ｹｲｿｸ ｹｯｶ ﾃﾞｰﾀ ﾋｮｳｼﾞ */
    kojin_data_disp( kaiin_code, "\n ** ｹｲｿｸ ｹｯｶ ﾃﾞｰﾀ **" );

    /* ｷｰ ﾆｭｳﾘｮｸ ﾏﾁ */
    while( getchar( ) != '\n' ) ;
    printf( "\n ﾘﾀｰﾝ ｷｰ ｦ ｵｼﾃｸﾀﾞｻｲ." );
    getchar( );

    /* ｹｲｿｸ ｹｯｶ ｼﾞｭﾝｲ ｿｰﾄ ﾋｮｳｼﾞ */
    ret = keisoku_rank( );

    return ret;
}



/************************************/
/* ﾒﾝﾊﾞｰ ｶﾝﾘ ﾌﾟﾛｸﾞﾗﾑ                */
/*  ｹｲｿｸ ｷﾛｸ ﾆｭｳﾘｮｸ ｼｮﾘ             */
/*   ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ READ  */
/*   ﾊﾟﾗﾒｰﾀ : ﾅｼ                    */
/*   ﾘﾀｰﾝ   : 0:OK                  */
/*           -1:NG                  */
/************************************/
static int codedata_tbl_read( void )
{
    int     ret;                        /* ﾘﾀｰﾝ ｺｰﾄﾞ                */
    FILE    *fp;                        /* ﾌｧｲﾙ ﾎﾟｲﾝﾀ               */
    char    *fname = CODEDATA_TBL_NAME;	/* ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ */

    /* ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ OPEN -> NULL ? */
    if( (fp = fopen( fname, "rb" )) == NULL ) {
        printf( "\n ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ OPEN ｴﾗｰ" );
        return NG;
    }

    /* ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ READ -> 1ｲｶﾞｲ ? */
    if( (ret = fread( (char *)codedata_tbl, sizeof( codedata_tbl ), 1, fp ))
               != 1 ) {
        printf( "\n ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ READ ｴﾗｰ" );
        ret = NG;
    }
    else {
        ret = OK;
    }

    /* ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ CLOSE */
    fclose( fp );

    return ret;
}



/************************************/
/* ﾒﾝﾊﾞｰ ｶﾝﾘ ﾌﾟﾛｸﾞﾗﾑ                */
/*  ｹｲｿｸ ｷﾛｸ ﾆｭｳﾘｮｸ ｼｮﾘ             */
/*   ｶｲｲﾝｺｰﾄﾞ ﾆｭｳﾘｮｸ                */
/*   ﾊﾟﾗﾒｰﾀ : ﾆｭｳﾘｮｸ ｶｲｲﾝ ｺｰﾄﾞ      */
/*   ﾘﾀｰﾝ   : ﾅｼ                    */
/************************************/
static void kaiin_code_input( int *kaiin_code )
{
    int     loop = TRUE;    /* ﾙｰﾌﾟ ﾌﾗｸﾞ    */
    char    work[ 128 ];    /* ﾆｭｳﾘｮｸ ﾜｰｸ   */

    while( loop ) {
        printf( "\n ｹｲｿｸｼｬ ﾉ ｶｲｲﾝ ｺｰﾄﾞ ｦ ﾆｭｳﾘｮｸ ｼﾃｸﾀﾞｻｲ" );
        printf( "\n ? " );

        /* ｶｲｲﾝ ｺｰﾄﾞ ﾆｭｳﾘｮｸ */
		work[ 0 ] = '\0';
        scanf( "%s", work );

        /* ﾆｭｰﾒﾘｯｸ ﾁｪｯｸ -> ｽｳﾁ ｲｶﾞｲ ? */
        if( strspn( work, "1234567890" ) < strlen( work ) ) {
            printf( "\n ｽｳﾁ ｲｶﾞｲ ｶﾞ ﾆｭｳﾘｮｸ ｻﾚﾏｼﾀ" );
            continue;
        }

        /* ﾆｭｳﾘｮｸ ﾊﾝｲ ﾁｪｯｸ( 0 < kaiin_code <= MEMBER_MAX ) */
        *kaiin_code = atoi( work );
        if( *kaiin_code > MEMBER_MAX || *kaiin_code <= 0 ) {
            printf( "\n ﾆｭｳﾘｮｸ ﾐｽ ﾃﾞｽ" );
            continue;
        }

        /* ｶｲｲﾝｺｰﾄﾞ ﾄｳﾛｸ ﾁｪｯｸ -> ﾐﾄｳﾛｸ ? */
        if( codedata_tbl[ *kaiin_code - 1 ] == 0 ) {
            printf( "\n ｺﾉ ｶｲｲﾝｺｰﾄﾞ ﾊ ﾐﾄｳﾛｸ ﾃﾞｽ" );
            continue;
        }
        break;
    }
    return;
}



/************************************/
/* ﾒﾝﾊﾞｰ ｶﾝﾘ ﾌﾟﾛｸﾞﾗﾑ                */
/*  ｹｲｿｸ ｷﾛｸ ﾆｭｳﾘｮｸ ｼｮﾘ             */
/*   ｹｲｿｸ ﾋﾂﾞｹ ﾆｭｳﾘｮｸ               */
/*   ﾊﾟﾗﾒｰﾀ : ﾆｭｳﾘｮｸ ﾋﾂﾞｹ           */
/*   ﾘﾀｰﾝ   : ﾅｼ                    */
/************************************/
static void keisoku_date_input( char *keisoku_date )
{
    int     loop = TRUE;    /* ﾙｰﾌﾟ ﾌﾗｸﾞ    */
    int     chk_date;       /* ﾋﾂﾞｹ ｽｳﾁ     */
    char    conv[ 3 ];      /* ｽｳﾁ ﾍﾝｶﾝ ﾖｳ  */
    char    work[ 128 ];    /* ﾆｭｳﾘｮｸ ﾜｰｸ   */

    while( loop ) {
        printf( "\n ﾋﾂﾞｹ ｦ ﾆｭｳﾘｮｸ ｼﾃｸﾀﾞｻｲ( YYYYMMDD )" );
        printf( "\n ? " );

        /* ﾋﾂﾞｹ ﾆｭｳﾘｮｸ */
		work[ 0 ] = '\0';
        scanf( "%s", work );

        /* ﾆｭｳﾘｮｸ ｹﾀｽｳ ﾁｪｯｸ -> 8ｲｶﾞｲ ? */
        if( strlen( work ) != 8 ) {
            printf( "\n ﾆｭｳﾘｮｸ ﾐｽ ﾃﾞｽ" );
            continue;
        }

        /* ﾆｭｰﾒﾘｯｸ ﾁｪｯｸ -> ｽｳﾁｲｶﾞｲ ? */
        if( strspn( work, "1234567890" ) < strlen( work ) ) {
            printf( "\n ｽｳﾁ ｲｶﾞｲ ｶﾞ ﾆｭｳﾘｮｸ ｻﾚﾏｼﾀ" );
            continue;
        }

        /* ﾂｷ ﾁｪｯｸ */
	conv[0] = work[4];
	conv[1] = work[5];
	conv[2] = '\0';

        chk_date = atoi( conv );
        if( chk_date > 12 || chk_date < 1 ) {
            printf( "\n ﾋﾂﾞｹ( ﾂｷ ) ﾆｭｳﾘｮｸ ｴﾗｰ ﾃﾞｽ" );
            continue;
        }

        /* ﾋ ﾁｪｯｸ */
	conv[0] = work[6];
	conv[1] = work[7];
	conv[2] = '\0';
        chk_date = atoi( conv );
        if( chk_date > 31 || chk_date < 1 ) {
            printf( "\n ﾋﾂﾞｹ( ﾋ ) ﾆｭｳﾘｮｸ ｴﾗｰ ﾃﾞｽ" );
            continue;
        }

        break;
    }

    /* ﾆｭｳﾘｮｸ ﾃﾞｰﾀ ｾｯﾄ */
    strcpy(keisoku_date, work);
    return;
}



/************************************/
/* ﾒﾝﾊﾞｰ ｶﾝﾘ ﾌﾟﾛｸﾞﾗﾑ                */
/*  ｹｲｿｸ ｷﾛｸ ﾆｭｳﾘｮｸ ｼｮﾘ             */
/*   ｹｲｿｸﾁ ﾆｭｳﾘｮｸ ｼｮﾘ               */
/*   ﾊﾟﾗﾒｰﾀ : ｲﾝﾃﾞｯｸｽ               */
/*   ﾘﾀｰﾝ   : ﾅｼ                    */
/************************************/
static void keisoku_data_input( int idx )
{
    int     i;                  /* ｲﾝﾃﾞｯｸｽ      */
    int     loop = TRUE;        /* ﾙｰﾌﾟ ﾌﾗｸﾞ    */
    char    work[ 3 ][ 128 ];   /* ﾆｭｳﾘｮｸ ﾜｰｸ   */

    while( loop ) {
        printf( "\n ｳﾝﾄﾞｳ %d ﾉ ｹｲｿｸ ﾃﾞｰﾀ ｦ ﾆｭｳﾘｮｸ ｼﾃｸﾀﾞｻｲ", idx + 1 );
        printf( "\n   ﾌｶ(999)  ｾｯﾄ(100)  ｶｲｽｳ(100)" );
        printf( "\n ? " );

        /* ｹｲｿｸ ﾃﾞｰﾀ ﾆｭｳﾘｮｸ */
   	work[ 0 ][ 0 ] = '\0';
	work[ 1 ][ 0 ] = '\0';
	work[ 2 ][ 0 ] = '\0';
        scanf( "%s %s %s", work[ 0 ], work[ 1 ], work[ 2 ] );

        for( i = 0; i < 3; i++ ) {

            /* ﾆｭｳﾘｮｸ ｹﾀｽｳ ﾁｪｯｸ -> 3ﾖﾘｵｵｷｲ ? */
            if( strlen( work[ i ] ) > 3 ) {
                printf( "\n ﾆｭｳﾘｮｸ ﾐｽ ﾃﾞｽ" );
                break;
            }

            /* ﾆｭｰﾒﾘｯｸ ﾁｪｯｸ -> ｽｳﾁｲｶﾞｲ ? */
            if( strspn( work[ i ], "1234567890" ) < strlen( work[ i ] ) ) {
                printf( "\n ｽｳﾁ ｲｶﾞｲ ｶﾞ ﾆｭｳﾘｮｸ ｻﾚﾏｼﾀ" );
                break;
            }

            /* ﾌｶ ｲｶﾞｲ ﾉ ｼﾞｮｳｹﾞﾝ ﾁｪｯｸ -> 100 ﾖﾘｵｵｷｲ ? */
            if( i != 0 ) {
                if( atoi( work[ i ] ) > 100 ) {
                    printf( "\n ｼﾞｮｳｹﾞﾝ(100) ｦ ｺｴﾃｲﾏｽ" );
                    break;
                 }
            }
        }

        if( i < 3 ) {
            continue;
        }

        break;
    }

    /* ﾆｭｳﾘｮｸ ﾃﾞｰﾀ ﾃｰﾌﾞﾙ ｾｯﾄ */
    keisoku_indata[ idx ].huka = atoi( work[ 0 ] );
    keisoku_indata[ idx ].set = atoi( work[ 1 ] );
    keisoku_indata[ idx ].kaisuu = atoi( work[ 2 ] );

    return;
}



/************************************/
/* ﾒﾝﾊﾞｰ ｶﾝﾘ ﾌﾟﾛｸﾞﾗﾑ                */
/*  ｹｲｿｸ ｷﾛｸ ﾆｭｳﾘｮｸ ｼｮﾘ             */
/*   ﾆｭｳﾘｮｸ ｹｲｿｸﾁ ﾋｮｳｼﾞ ｼｮﾘ         */
/*   ﾊﾟﾗﾒｰﾀ : ｶｲｲﾝ ｺｰﾄﾞ             */
/*            ﾋﾂﾞｹ                  */
/*   ﾘﾀｰﾝ   : ﾅｼ                    */
/************************************/
static void keisoku_data_disp( int kaiin_code, char *keisoku_date )
{
    int     i;  	/* ｲﾝﾃﾞｯｸｽ      */

    printf( "\n ** ﾆｭｳﾘｮｸ ｹｲｿｸﾁ ﾃﾞｰﾀ **" );
    printf( "\n ｶｲｲﾝｺｰﾄﾞ %3d", kaiin_code );
    printf( "\n ﾋﾂﾞｹ     %4.4s-%2.2s-%2.2s", 
        ( keisoku_date + 0 ), ( keisoku_date + 4 ), ( keisoku_date + 6 ) );

    printf( "\n\n ｳﾝﾄﾞｳ    ﾌｶ    ｾｯﾄ    ｶｲｽｳ" );

    for( i = 0; i < 5; i++ ) {
        printf( "\n   %d     %3d    %3d     %3d", i + 1, 
            keisoku_indata[ i ].huka,
            keisoku_indata[ i ].set,
            keisoku_indata[ i ].kaisuu );
    }

    return;
}



/************************************/
/* ﾒﾝﾊﾞｰ ｶﾝﾘ ﾌﾟﾛｸﾞﾗﾑ                */
/*  ｹｲｿｸ ｷﾛｸ ﾆｭｳﾘｮｸ ｼｮﾘ             */
/*   ｳﾝﾄﾞｳ ｼｽｳ ｹｲｻﾝ ｼｮﾘ             */
/*   ﾊﾟﾗﾒｰﾀ : ｳﾝﾄﾞｳ ｼｽｳ             */
/*   ﾘﾀｰﾝ   : ﾅｼ                    */
/************************************/
static void undou_sisuu_keisan( int *undou_sisuu )
{
    int     i;              /* ｲﾝﾃﾞｯｸｽ      */
    double  sisuu;          /* ｹｲｻﾝ ﾜｰｸ     */
    double  sisuu_total;    /* ｹｲｻﾝﾁ ｺﾞｳｹｲ  */
    static  double  huka_sisuu[ 5 ] = { 0.24, 0.36, 0.52, 1.05, 2.13 };

    sisuu_total = 0.0;
    for( i = 0; i < 5; i++ ) {

        /* ｶｲｽｳ 1ｲｶ ? */
        if( keisoku_indata[ i ].kaisuu <= 1 ) {
            continue;
        }

        sisuu = huka_sisuu[ i ] * (double)keisoku_indata[ i ].huka * 
               (double)keisoku_indata[ i ].set *
               ((pow( (double)keisoku_indata[ i ].kaisuu, 2.0 )) /
               ((double)keisoku_indata[ i ].kaisuu - 1.0));

        /* ｼｸﾞﾏ(ﾙｲｹｲ) ﾉ ｹｲｻﾝ */
        sisuu_total += sisuu;
    }

    /* ﾍｲﾎｳｺﾝ ﾉ ｻﾝｼｭﾂ */
    *undou_sisuu = (int)sqrt( sisuu_total );

    return;
}



/************************************/
/* ﾒﾝﾊﾞｰ ｶﾝﾘ ﾌﾟﾛｸﾞﾗﾑ                */
/*  ｹｲｿｸ ｷﾛｸ ﾆｭｳﾘｮｸ ｼｮﾘ             */
/*   ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ ｺｳｼﾝ        */
/*   ﾊﾟﾗﾒｰﾀ : ｶｲｲﾝ ｺｰﾄﾞ             */
/*            ﾋﾂﾞｹ                  */
/*            ｳﾝﾄﾞｳ ｼｽｳ             */
/*   ﾘﾀｰﾝ   : 0:OK                  */
/*           -1:NG                  */
/************************************/
static int kojin_data_update( int kaiin_code, char *keisoku_date, int undou_sisuu )
{
    int     ret;					/* ﾘﾀｰﾝ ｺｰﾄﾞ            */
    long    fptr;					/* ｹｲｿｸ ﾃﾞｰﾀ ﾌｧｲﾙ ﾎﾟｲﾝﾀ */
    FILE    *fp;					/* ﾌｧｲﾙ ﾎﾟｲﾝﾀ           */
    char    *fname = KEISOKU_TBL_NAME;			/* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ   */
    int	    i;						/* ｲﾝﾃﾞｯｸｽ		*/

    /* 1ｶｲﾒ ? */
    if( kojin_keisoku_tbl.count <= 0 ) {
		strcpy( kojin_keisoku_tbl.first_date, keisoku_date );
        kojin_keisoku_tbl.first_data = undou_sisuu;

		strcpy( kojin_keisoku_tbl.max_date, keisoku_date );
        kojin_keisoku_tbl.max_data = undou_sisuu;
    }
    else {

        /* ｻｲｺｳ ｷﾛｸ ? */
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

    /* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ OPEN -> NULL ? */
    if( (fp = fopen( fname, "r+b" )) == NULL ) {
        printf( "\n ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ OPEN ｴﾗｰ" );
        return NG;
    }

    /* ｶﾞｲﾄｳ ﾃﾞｰﾀ ﾎﾟｲﾝﾀ ｾｯﾄ */
    fptr = ( codedata_tbl[ kaiin_code - 1 ] - 1 ) * 
        sizeof( struct KEISOKU_TBL );

    /* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ SEEK -> OK ﾃﾞ ﾅｲ ? */
    if( (ret = fseek( fp, fptr, SEEK_SET )) != OK ) {
        printf( "\n ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ SEEK ｴﾗｰ" );

        /* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ CLOSE */
        fclose( fp );
        return NG;
    }

    /* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ WRITE -> 1ｲｶﾞｲ ? */
    if( (ret = fwrite( (char *)&kojin_keisoku_tbl, sizeof( kojin_keisoku_tbl ),
               1, fp )) != 1 ) {
        printf( "\n ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ WRITE ｴﾗｰ" );
        ret = NG;
    }
    else {
        ret = OK;
    }

    /* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ CLOSE */
    fclose( fp );

    return ret;
}



/************************************/
/* ﾒﾝﾊﾞｰ ｶﾝﾘ ﾌﾟﾛｸﾞﾗﾑ                */
/*  ｹｲｿｸ ｷﾛｸ ﾆｭｳﾘｮｸ ｼｮﾘ             */
/*   ｹｲｿｸ ｹｯｶ ｼﾞｭﾝｲ ｿｰﾄ ﾋｮｳｼﾞ       */
/*   ﾊﾟﾗﾒｰﾀ : ﾅｼ                    */
/*   ﾘﾀｰﾝ   : 0:OK                  */
/*           -1:NG                  */
/************************************/
#ifdef TOI1
int keisoku_rank( void )
{
    int     ret;						/* ﾘﾀｰﾝ ｺｰﾄﾞ            */
    int     i;							/* ｲﾝﾃﾞｯｸｽ              */
    FILE    *fp;						/* ﾌｧｲﾙ ﾎﾟｲﾝﾀ           */
    char    *fname = KEISOKU_TBL_NAME;				/* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ   */

    /* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ OPEN -> NULL ? */
    if( (fp = fopen( fname, "rb" )) == NULL ) {
        printf( "\n ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ OPEN ｴﾗｰ" );
        return NG;
    }

    i = 0;
    for( ; ; ) {

        /* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ READ -> 1ｲｶﾞｲ ? */
        if( (ret = fread( (char *)&sort_keisoku_tbl[ i ],
                   sizeof( struct KEISOKU_TBL ), 1, fp )) != 1 ) {

            /* READ ｴﾗｰ ? */
            if( ferror( fp ) != 0 ) {
                printf( "\n ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ READ ｴﾗｰ" );
                ret = NG;
            }
            else {
                /* ﾌｧｲﾙ EOF ﾃﾞ ﾅｲ ? */
                if( feof( fp ) == 0 ) {
                    printf( "\n ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ READ ｴﾗｰ" );
                    ret = NG;
                }
                else {
                    ret = OK;
                }
            }
        }

        /* READ ｴﾗｰ ? */
        if( ret == NG ) {
            break;
        }

        /* ｹｲｿｸ ﾃﾞｰﾀ ｱﾘ ? */
        if( sort_keisoku_tbl[ i ].count != 0 ) {
            i++;
        }

        /* eof ? */
        if( ret == OK ) {
            break;
        }
    }

    /* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ CLOSE */
    fclose( fp );

    if( ret == OK ) {
    	/* descending	*/
    	/* ｹｲｿｸ ﾃﾞｰﾀ ｿｰﾄ */
		keisoku_data_sort( i, 1 );

		/* ｹｲｿｸ ﾃﾞｰﾀ ｿｰﾄ ｹｯｶ ﾋｮｳｼﾞ */
		keisoku_sort_disp( i, 1 );

    	/* ascending	*/
        /* ｹｲｿｸ ﾃﾞｰﾀ ｿｰﾄ */
        //keisoku_data_sort( i );
    	/* sort => ascednd = 0	*/
    	keisoku_data_sort( i, 0 );
        /* ｹｲｿｸ ﾃﾞｰﾀ ｿｰﾄ ｹｯｶ ﾋｮｳｼﾞ */
        //keisoku_sort_disp( i );
    	keisoku_sort_disp( i, 0 );
    }

    return ret;
}//int keisoku_rank( void )
#else
static int keisoku_rank( void )
{
    int     ret;						/* ﾘﾀｰﾝ ｺｰﾄﾞ            */
    int     i;							/* ｲﾝﾃﾞｯｸｽ              */
    FILE    *fp;						/* ﾌｧｲﾙ ﾎﾟｲﾝﾀ           */
    char    *fname = KEISOKU_TBL_NAME;				/* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ   */

    /* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ OPEN -> NULL ? */
    if( (fp = fopen( fname, "rb" )) == NULL ) {
        printf( "\n ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ OPEN ｴﾗｰ" );
        return NG;
    }

    i = 0;
    for( ; ; ) {

        /* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ READ -> 1ｲｶﾞｲ ? */
        if( (ret = fread( (char *)&sort_keisoku_tbl[ i ],
                   sizeof( struct KEISOKU_TBL ), 1, fp )) != 1 ) {

            /* READ ｴﾗｰ ? */
            if( ferror( fp ) != 0 ) {
                printf( "\n ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ READ ｴﾗｰ" );
                ret = NG;
            }
            else {
                /* ﾌｧｲﾙ EOF ﾃﾞ ﾅｲ ? */
                if( feof( fp ) == 0 ) {
                    printf( "\n ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ READ ｴﾗｰ" );
                    ret = NG;
                }
                else {
                    ret = OK;
                }
            }
        }

        /* READ ｴﾗｰ ? */
        if( ret == NG ) {
            break;
        }

        /* ｹｲｿｸ ﾃﾞｰﾀ ｱﾘ ? */
        if( sort_keisoku_tbl[ i ].count != 0 ) {
            i++;
        }

        /* eof ? */
        if( ret == OK ) {
            break;
        }
    }

    /* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ CLOSE */
    fclose( fp );

    if( ret == OK ) {
        /* ｹｲｿｸ ﾃﾞｰﾀ ｿｰﾄ */
        keisoku_data_sort( i );
        /* ｹｲｿｸ ﾃﾞｰﾀ ｿｰﾄ ｹｯｶ ﾋｮｳｼﾞ */
        keisoku_sort_disp( i );
    }

    return ret;
}//static int keisoku_rank( void )
#endif


/************************************/
/* ﾒﾝﾊﾞｰ ｶﾝﾘ ﾌﾟﾛｸﾞﾗﾑ                */
/*  ｹｲｿｸ ｷﾛｸ ﾆｭｳﾘｮｸ ｼｮﾘ             */
/*   ｹｲｿｸ ｹｯｶ ｿｰﾄ                   */
/*   ﾊﾟﾗﾒｰﾀ : ｹｲｿｸ ﾃﾞｰﾀ ｹﾝｽｳ        */
/*   ﾘﾀｰﾝ   : ﾅｼ                    */
/************************************/
#ifdef TOI1
static void keisoku_data_sort
( int cnt, int mode )
{
    int     i;                  	/* ｲﾝﾃﾞｯｸｽ      */
    int     j;                  	/* ｲﾝﾃﾞｯｸｽ      */
    struct  KEISOKU_TBL  work;  	/* ｽﾜｯﾌﾟ ﾖｳ ｴﾘｱ */

    /* ﾃﾞｰﾀ ｿｰﾄ */
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
    int     i;                  	/* ｲﾝﾃﾞｯｸｽ      */
    int     j;                  	/* ｲﾝﾃﾞｯｸｽ      */
    struct  KEISOKU_TBL  work;  	/* ｽﾜｯﾌﾟ ﾖｳ ｴﾘｱ */

    /* ﾃﾞｰﾀ ｿｰﾄ */
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
/* ﾒﾝﾊﾞｰ ｶﾝﾘ ﾌﾟﾛｸﾞﾗﾑ                */
/*  ｹｲｿｸ ｷﾛｸ ﾆｭｳﾘｮｸ ｼｮﾘ             */
/*   ｹｲｿｸ ｹｯｶ ﾋｮｳｼﾞ                 */
/*   ﾊﾟﾗﾒｰﾀ : ｹｲｿｸ ﾃﾞｰﾀ ｹﾝｽｳ        */
/*   ﾘﾀｰﾝ   : ﾅｼ                    */
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
    int     i;  /* ｲﾝﾃﾞｯｸｽ  */

    /* Display labels
     * If 'mode' is 1 => top 5
     * If 'mode' is 0 => bottom 5
     */
    /* mode => 1	*/
    if (mode == 1) {
		printf( "\n\n ** ｼﾞｭﾝｲ ﾋｮｳ（ｼﾞｮｳｲ　5ｲ） **" );
		printf( "\n ｼﾞｭﾝｲ ｶｲｲﾝｺｰﾄﾞ  ｻｲｺｳﾃﾞｰﾀ   ﾋﾂﾞｹ" );
	/* mode => 0	*/
    } else if (mode == 0) {
    	printf( "\n\n ** ｼﾞｭﾝｲ ﾋｮｳ（ｶｲ　5ｲ） **" );
		printf( "\n ｼﾞｭﾝｲ ｶｲｲﾝｺｰﾄﾞ  ｻｲｺｳﾃﾞｰﾀ   ﾋﾂﾞｹ" );
    } else {	//if (mode == 1)
    	printf( "\n\n ** ｼﾞｭﾝｲ ﾋｮｳ **" );
		printf( "\n ｼﾞｭﾝｲ ｶｲｲﾝｺｰﾄﾞ  ｻｲｺｳﾃﾞｰﾀ   ﾋﾂﾞｹ" );
    }//if (mode == 1)

    for( i = 0; i < cnt; i++ ) {

        /* 5ｲ ﾏﾃﾞ ﾋｮｳｼﾞ ｽﾙ */
        if( i >= 5 ) {
            break;
        }
        /* 10ｲ ﾏﾃﾞ ﾋｮｳｼﾞ ｽﾙ */
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
    int     i;  /* ｲﾝﾃﾞｯｸｽ  */

    printf( "\n\n ** ｼﾞｭﾝｲ ﾋｮｳ **" );
    printf( "\n ｼﾞｭﾝｲ ｶｲｲﾝｺｰﾄﾞ  ｻｲｺｳﾃﾞｰﾀ   ﾋﾂﾞｹ" );

    for( i = 0; i < cnt; i++ ) {

        /* 10ｲ ﾏﾃﾞ ﾋｮｳｼﾞ ｽﾙ */
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
