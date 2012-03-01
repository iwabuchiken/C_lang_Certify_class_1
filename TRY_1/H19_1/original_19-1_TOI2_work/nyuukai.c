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
#ifdef TOI2
    int    ret;             /* ﾘﾀｰﾝ ｺｰﾄﾞ        */
    int    kaiin_code;      /* ﾄｳﾛｸ ｶｲｲﾝ ｺｰﾄﾞ   */
    long   fptr;            /* ﾌｧｲﾙ ﾎﾟｲﾝﾀ       */
    char   msg[ 64 ];       /* ﾒｯｾｰｼﾞ ｴﾘｱ       */

    int    i;		/* akicode_tbl[] 用のインデックス */

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

#ifdef DEBUG_NYUUKAI
    /* 空きコード表の内容を示す */
    show_akicode_tbl();
#endif

    /* akicode_tbl の、添字1番から始める */
    i = 1;
    while (1) {
    	/* 有効コードの番号が終るか、
    	 * 添字番号が残余の有効コードの数を
    	 * 超えたら、添字の i を１に戻す
    	 */
    	if (akicode_tbl[i] == 0 ||
    			i > akicode_tbl[0])
    		i = 1;
		/* ｱｷ ｺｰﾄﾞ ｶｸﾆﾝ */
		sprintf( msg, "\n ｶｲｲﾝ ｺｰﾄﾞ ﾊ %d ﾃﾞｽ. ﾖﾛｼｲ ﾃﾞｽｶ( Y/N )", akicode_tbl[ i ] );
		if( (ret = kakunin_input( msg )) == OK ) {
			/* ﾄｳﾛｸ ｶｲｲﾝ ｺｰﾄﾞ ﾀｲﾋ */
			kaiin_code = akicode_tbl[ i ];

			/* ｱｷ ｺｰﾄﾞ ﾋｮｳ ｺｳｼﾝ -> OK ? */
			if( (ret = akicode_tbl_update2( i )) == OK ) {
				/* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾂｲｶ -> OK ? */
				if( (ret = keisoku_tbl_add( &fptr, kaiin_code )) == OK ) {

					/* ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ｺｳｼﾝ */
					ret = codedata_tbl_update( kaiin_code, fptr );
				}
			}
			break;
		} else {
		/* kakunin_input() の戻り値が OK
		 * ではなかったら、
		 * １．添字の i を１つ増やす
		 * ２．while ループを繰り返す
		 */
			i++;
		}//if( (ret = kakunin_input( msg )) == OK )

    }//while(1)

    if( ret == OK ) {
        printf( "\n ﾆｭｳｶｲ ﾄｳﾛｸ ｼｮﾘ ｶﾞ ｼｭｳﾘｮｳ ｼﾏｼﾀ" );
    }

    return ret;
#else
    int    ret;             /* ﾘﾀｰﾝ ｺｰﾄﾞ        */
    int    kaiin_code;      /* ﾄｳﾛｸ ｶｲｲﾝ ｺｰﾄﾞ   */
    long   fptr;            /* ﾌｧｲﾙ ﾎﾟｲﾝﾀ       */
    char   msg[ 64 ];       /* ﾒｯｾｰｼﾞ ｴﾘｱ       */

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
		sprintf( msg, "\n ｶｲｲﾝ ｺｰﾄﾞ ﾊ %d ﾃﾞｽ. ﾖﾛｼｲ ﾃﾞｽｶ( Y/N )", akicode_tbl[ 1 ] );
		if( (ret = kakunin_input( msg )) == OK ) {
			/* ﾄｳﾛｸ ｶｲｲﾝ ｺｰﾄﾞ ﾀｲﾋ */
			kaiin_code = akicode_tbl[ 1 ];

			/* ｱｷ ｺｰﾄﾞ ﾋｮｳ ｺｳｼﾝ -> OK ? */
			if( (ret = akicode_tbl_update( )) == OK ) {
				/* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾂｲｶ -> OK ? */
				if( (ret = keisoku_tbl_add( &fptr, kaiin_code )) == OK ) {

					/* ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ｺｳｼﾝ */
					ret = codedata_tbl_update( kaiin_code, fptr );
				}
			}
		}
		break;
    }//while(1)

    if( ret == OK ) {
        printf( "\n ﾆｭｳｶｲ ﾄｳﾛｸ ｼｮﾘ ｶﾞ ｼｭｳﾘｮｳ ｼﾏｼﾀ" );
    }

    return ret;
#endif
}



/************************************/
/* ﾒﾝﾊﾞｰ ｶﾝﾘ ﾌﾟﾛｸﾞﾗﾑ                */
/*  ﾆｭｳｶｲ ﾄｳﾛｸ ｼｮﾘ                  */
/*   ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ ｺｳｼﾝ          */
/*   ﾊﾟﾗﾒｰﾀ : ﾅｼ                    */
/*   ﾘﾀｰﾝ   : 0:OK                  */
/*           -1:NG                  */
/************************************/
#ifdef TOI2
static int akicode_tbl_update2( int number )
{
    int     ret;					/* ﾘﾀｰﾝ ｺｰﾄﾞ        */
    int     i;						/* ｲﾝﾃﾞｯｸｽ          */
    int     cnt;					/* ｱｷ ｺｰﾄﾞ ｽｳ       */
    FILE    *fp;					/* ﾌｧｲﾙ ﾎﾟｲﾝﾀ       */
    char    *fname = AKICODE_TBL_NAME;  		/* ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ */

    int     akicode_tbl_tmp[ MEMBER_MAX + 1 ]; /* update 時の、作業配列 */
    int     j;		/* akicode_tbl[] 用のインデックス */
    int     k;		/* akicode_tbl_tmp[] 用のインデックス */

    /* ｱｷ ｺｰﾄﾞ ｹﾝｽｳ ｾｯﾄ */
    cnt = akicode_tbl[ 0 ];

    /* ターゲットの要素をゼロにする */
    akicode_tbl[number] = 0;

    /* akicode_tbl[] を並べ替える
     * １．akicode_tbl_tmp[] に、akicode_tbl[] の
     * 		要素のうち、０出ないものを、akicode_tbl_tmp[] の
     * 		先頭（添字=０）から、代入する
     * ２．akicode_tbl_tmp に入れた数値列の末尾の
     * 		要素に、０を代入する
     * ３．akicode_tbl_tmp から akicode_tbl へ、
     * 		残余データの数（akicode_tbl[0]）だけ、
     * 		akicode_tbl の添字１番から順に、コピーする
     */

    /* 1 */
    for(j = 0, k = 0; j <= akicode_tbl[0]; j++) {
		if(akicode_tbl[j] != 0) {
			akicode_tbl_tmp[k] = akicode_tbl[j];
			++k;
		}//if(akicode_tbl[i] != 0) {
	}//for(i = 0; i < MEMBER_MAX + 1; i++) {

    /* 2 */
    akicode_tbl_tmp[k] = 0;

    /* 3 */
    for(i = 1; i <= akicode_tbl[0]; i++) {
		akicode_tbl[i] = akicode_tbl_tmp[i];
	}//for(i = 1; i < MEMBER_MAX + 1; i++) {

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
#endif

static int akicode_tbl_update( void )
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
        akicode_tbl[ i ] = akicode_tbl[ i + 1 ];
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

    /* 入会時ポイント　=>　設定 */
    kojin_keisoku_tbl.point = 100;

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

        //debug
        printf("[%s:%d]\n", __FILE__, __LINE__);
        printf("codedata_tbl[ kaiin_code - 1 ]=%d\n\n",
        			codedata_tbl[ kaiin_code - 1 ]);

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

static void show_akicode_tbl( void )
{
	int		i;	/* インデックス */

	printf("akicode_tbl[]= ");
	for (i = 0; i < MEMBER_MAX + 1; i++) {
		printf("%3d", akicode_tbl[i]);
	}
	printf("\n\n");
}//static int  show_akicode_tbl( void )
