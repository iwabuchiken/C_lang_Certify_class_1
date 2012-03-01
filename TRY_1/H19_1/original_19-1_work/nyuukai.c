/************************************/
/*  nyuukai.c                       */
/*    ﾆｭｳｶｲ ﾄｳﾛｸ ｼｮﾘ ﾌﾟﾛｸﾞﾗﾑ ﾌｧｲﾙ   */
/************************************/
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "main.h"
#include "nyuukai.h"

extern int akicode_tbl[ MEMBER_MAX + 1 ];			/* ｱｷｺｰﾄﾞ ﾋｮｳ */
extern int codedata_tbl[ MEMBER_MAX ];				/* ｺｰﾄﾞﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ */
extern struct KEISOKU_TBL kojin_keisoku_tbl;			/* ｺｼﾞﾝﾍﾞﾂ ｹｲｿｸ ﾃﾞｰﾀﾋｮｳ */

/***********************************/
/* ﾒﾝﾊﾞｰ ｶﾝﾘ ﾌﾟﾛｸﾞﾗﾑ               */
/*  ﾆｭｳｶｲ ﾄｳﾛｸ ｼｮﾘ                 */
/*   ﾒｲﾝ                           */
/*   ﾊﾟﾗﾒｰﾀ : ﾅｼ                   */
/*   ﾘﾀｰﾝ   : 0:OK                 */
/*           -1:NG                 */
/***********************************/
int nyuukai_touroku( void )
{
    int    ret;             /* ﾘﾀｰﾝ ｺｰﾄﾞ        */
    int    kaiin_code;      /* ﾄｳﾛｸ ｶｲｲﾝ ｺｰﾄﾞ   */
    long   fptr;            /* ﾌｧｲﾙ ﾎﾟｲﾝﾀ       */
    char   msg[ 64 ];       /* ﾒｯｾｰｼﾞ ｴﾘｱ       */

#ifdef TOI1
    int    i = 1;				/*　インデックス　*/
#endif

    /* ｱｷ ｺｰﾄﾞ ﾋｮｳ READ -> NG ? */
	if( (ret = akicode_tbl_read( )) == NG ) {
        return ret;
	}

    /* ｱｷ ｺｰﾄﾞ ｱﾘ ? */
    if( akicode_tbl[ 0 ] <= 0 ) {
        printf( "\n ｻﾞﾝﾈﾝﾅｶﾞﾗ ﾀﾀﾞｲﾏ ﾒﾝﾊﾞｰ ﾉ ｱｷｶﾞ ｱﾘﾏｾﾝ\n" );
        ret = OK;
        return ret;
    }

    while (1) {
		/* ｱｷ ｺｰﾄﾞ ｶｸﾆﾝ */
#ifdef TOI1
    	printf("[LINE:%d]\n", __LINE__);
    	printf("i=%d akicode_tbl=%d\n",
    				i, akicode_tbl[i]);
		sprintf( msg, "\n ｶｲｲﾝ ｺｰﾄﾞ ﾊ %d ﾃﾞｽ. ﾖﾛｼｲ ﾃﾞｽｶ( Y/N )", akicode_tbl[ i ] );
#else
		sprintf( msg, "\n ｶｲｲﾝ ｺｰﾄﾞ ﾊ %d ﾃﾞｽ. ﾖﾛｼｲ ﾃﾞｽｶ( Y/N )", akicode_tbl[ 1 ] );
#endif
		if( (ret = kakunin_input( msg )) == OK ) {
			/* ﾄｳﾛｸ ｶｲｲﾝ ｺｰﾄﾞ ﾀｲﾋ */
#ifdef TOI1
			kaiin_code = akicode_tbl[ i ];
#else
			kaiin_code = akicode_tbl[ 1 ];
#endif
			/* ｱｷ ｺｰﾄﾞ ﾋｮｳ ｺｳｼﾝ -> OK ? */
#ifdef TOI1
			if( (ret = akicode_tbl_update( kaiin_code + 1 )) == OK ) {
#else
			if( (ret = akicode_tbl_update( )) == OK ) {
#endif

				/* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾂｲｶ -> OK ? */
				if( (ret = keisoku_tbl_add( &fptr, kaiin_code )) == OK ) {

					/* ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ｺｳｼﾝ */
					ret = codedata_tbl_update( kaiin_code, fptr );
				}
			}
		}
#ifdef TOI1
		if( ret == OK )
			break;
		else
			i += 1;
#else
		break;
#endif
    }//while(1)

    if( ret == OK ) {
        printf( "\n ﾆｭｳｶｲ ﾄｳﾛｸ ｼｮﾘ ｶﾞ ｼｭｳﾘｮｳ ｼﾏｼﾀ" );
    }

    return ret;
}



/************************************/
/* ﾒﾝﾊﾞｰ ｶﾝﾘ ﾌﾟﾛｸﾞﾗﾑ                */
/*  ﾆｭｳｶｲ ﾄｳﾛｸ ｼｮﾘ                  */
/*   ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ ｺｳｼﾝ          */
/*   ﾊﾟﾗﾒｰﾀ : ﾅｼ                    */
/*   ﾘﾀｰﾝ   : 0:OK                  */
/*           -1:NG                  */
/************************************/
#ifdef TOI1
static int akicode_tbl_update( int touroku_number )
#else
static int akicode_tbl_update( void )
#endif
{
    int     ret;					/* ﾘﾀｰﾝ ｺｰﾄﾞ        */
    int     i;						/* ｲﾝﾃﾞｯｸｽ          */
    int     cnt;					/* ｱｷ ｺｰﾄﾞ ｽｳ       */
    FILE    *fp;					/* ﾌｧｲﾙ ﾎﾟｲﾝﾀ       */
    char    *fname = AKICODE_TBL_NAME;  		/* ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ */

    /* ｱｷ ｺｰﾄﾞ ｹﾝｽｳ ｾｯﾄ */
    cnt = akicode_tbl[ 0 ];

    /* ｱｷ ｺｰﾄﾞ ﾍﾝｼｭｳ */
    for( i = 1; i < cnt; i++ ) {
        if( akicode_tbl[ i + 1 ] == 0 ) {
            break;
        }
#ifdef TOI1
        akicode_tbl[ i ] = akicode_tbl[ touroku_number ];
        touroku_number += 1;
#else
        akicode_tbl[ i ] = akicode_tbl[ i + 1 ];
#endif
    }

    akicode_tbl[ i ] = 0;

    /* ｱｷ ｺｰﾄﾞ ｹﾝｽｳ ｾｯﾄ */
    akicode_tbl[ 0 ] = cnt - 1;

    /* ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ OPEN -> NULL ? */
    if( (fp = fopen( fname, "w+b" )) == NULL ) {
        printf( "\n ｱｷｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ OPEN ｴﾗｰ" );
        return NG;
    }

    /* ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ WRITE -> 1ｲｶﾞｲ ? */
    if( (ret = fwrite( (char *)akicode_tbl,
               sizeof( int ) * (akicode_tbl[ 0 ] + 1), 1, fp )) != 1 ) {
        printf( "\n ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ WRITE ｴﾗｰ" );
        ret = NG;
    }
    else {
        ret = OK;
    }

    /* ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ CLOSE */
    fclose( fp );

    return ret;
}



/************************************/
/* ﾒﾝﾊﾞｰ ｶﾝﾘ ﾌﾟﾛｸﾞﾗﾑ                */
/*  ﾆｭｳｶｲ ﾄｳﾛｸ ｼｮﾘ                  */
/*   ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ ﾂｲｶ         */
/*   ﾊﾟﾗﾒｰﾀ : ｹｲｿｸ ﾃﾞｰﾀ ﾎﾟｲﾝﾀ       */
/*            ﾄｳﾛｸ ｶｲｲﾝ ｺｰﾄﾞ        */
/*   ﾘﾀｰﾝ   : 0:OK                  */
/*           -1:NG                  */
/************************************/
static int keisoku_tbl_add( long *fptr, int kaiin_code )
{
    int     ret;					/* ﾘﾀｰﾝ ｺｰﾄﾞ            */
    FILE    *fp;					/* ﾌｧｲﾙ ﾎﾟｲﾝﾀ           */
    char    *fname = KEISOKU_TBL_NAME;			/* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ   */

    /* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ OPEN -> NULL ? */
    if( (fp = fopen( fname, "a+b" )) == NULL ) {
        printf( "\n ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ OPEN ｴﾗｰ" );
        return NG;
    }

    /* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ SEEK -> OK ﾃﾞ ﾅｲ ? */
    if( (ret = fseek( fp, 0L, SEEK_END )) != OK ) {
        printf( "\n ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ SEEK ｴﾗｰ" );
        /* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ CLOSE */
        fclose( fp );
        return NG;
    }

    /* ﾌｧｲﾙ ﾎﾟｲﾝﾀ ｼｭﾄｸ */
    *fptr = ftell( fp );

    /* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ｸﾘｱ */
	kojin_keisoku_tbl = init_kojin_keisoku_tbl();

    /* ｶｲｲﾝ ｺｰﾄﾞ ｾｯﾄ */
    kojin_keisoku_tbl.kaiin_code = kaiin_code;

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
/*  ﾆｭｳｶｲ ﾄｳﾛｸ ｼｮﾘ                  */
/*   ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ ｺｳｼﾝ  */
/*   ﾊﾟﾗﾒｰﾀ : ﾄｳﾛｸ ｶｲｲﾝ ｺｰﾄﾞ        */
/*            ｹｲｿｸ ﾃﾞｰﾀ ﾎﾟｲﾝﾀ       */
/*   ﾘﾀｰﾝ   : 0:OK                  */
/*           -1:NG                  */
/************************************/
static int codedata_tbl_update( int kaiin_code, long fptr )
{
    int     ret;                        /* ﾘﾀｰﾝ ｺｰﾄﾞ                */
    FILE    *fp;                        /* ﾌｧｲﾙ ﾎﾟｲﾝﾀ               */
    char    *fname = CODEDATA_TBL_NAME;	/* ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ */

    /* ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ OPEN -> NULL ? */
    if( (fp = fopen( fname, "r+b" )) == NULL ) {
        printf( "\n ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ OPEN ｴﾗｰ" );
        return NG;
    }

    /* ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ READ -> 1ｲｶﾞｲ ? */
    if( (ret = fread( (char *)codedata_tbl, sizeof( codedata_tbl ), 1, fp ) )
               != 1 ) {
        printf( "\n ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ READ ｴﾗｰ" );
        ret = NG;
    }
    else {
        /* ｶﾞｲﾄｳ ﾃﾞｰﾀ ﾎﾟｲﾝﾀ ｾｯﾄ */
        codedata_tbl[ kaiin_code - 1 ] =
            (int)( (fptr / sizeof( struct KEISOKU_TBL )) + 1 );

        /* ﾌｧｲﾙ ﾎﾟｲﾝﾀ ｦ ｾﾝﾄｳ ﾆ SEEK -> OK ﾃﾞ ﾅｲ ? */
        if( (ret = fseek( fp, 0L, SEEK_SET )) != OK ) {
            printf( "\n ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ SEEK ｴﾗｰ" );

            /* ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ CLOSE */
            fclose( fp );
            return NG;
        }

        /* ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ WRITE -> 1ｲｶﾞｲ ? */
        if( (ret = fwrite( (char *)codedata_tbl, sizeof( codedata_tbl ), 1,
                   fp )) != 1 ) {
            printf( "\n ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ WRITE ｴﾗｰ" );
            ret = NG;
        }
        else {
            ret = OK;
        }
    }

    /* ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ CLOSE */
    fclose( fp );

    return ret;
}
