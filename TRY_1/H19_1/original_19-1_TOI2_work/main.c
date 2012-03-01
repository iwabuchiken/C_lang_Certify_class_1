/***********************************/
/*  main.c                         */
/*   ｱｽﾚﾁｯｸ ｸﾗﾌﾞ ﾒﾝﾊﾞｰ ｶﾝﾘ ﾌﾟﾛｸﾞﾗﾑ */
/***********************************/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "common.h"
#include "main.h"
#include "nyuukai.h"
#include "keisoku.h"
#include "sakujyo.h"

/***********************************/
/* ｷｮｳﾂｳ ﾃﾞｰﾀ                      */
/***********************************/

/* ｱｷｺｰﾄﾞ ﾋｮｳ */
int akicode_tbl[ MEMBER_MAX + 1 ];

/* ｺｰﾄﾞﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ */
int codedata_tbl[ MEMBER_MAX ];

/* ｺｼﾞﾝﾍﾞﾂ ｹｲｿｸ ﾃﾞｰﾀﾋｮｳ */
struct KEISOKU_TBL kojin_keisoku_tbl;

/* ｿｰﾄ ﾖｳ ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ */
struct KEISOKU_TBL sort_keisoku_tbl[ MEMBER_MAX ];


/***********************************/
/* ﾒﾝﾊﾞｰ ｶﾝﾘ ﾌﾟﾛｸﾞﾗﾑ               */
/*  ﾒｲﾝ                            */
/*   ﾊﾟﾗﾒｰﾀ : ﾅｼ                   */
/*   ﾘﾀｰﾝ   : ﾅｼ                   */
/***********************************/
int main( void )
#ifdef TOI2
{
    int    loop = TRUE;			/* ﾙｰﾌﾟ ﾌﾗｸﾞ                */
    char   work[ 128 ];			/* ﾆｭｳﾘｮｸ ﾜｰｸ               */
    FILE   *fp;				/* ﾌｧｲﾙ ﾎﾟｲﾝﾀ               */
    char   *fname1 = AKICODE_TBL_NAME;	/* ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ         */
    char   *fname2 = CODEDATA_TBL_NAME;	/* ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ */
    int	   i;				/* ｲﾝﾃﾞｯｸｽ		    */

    /* ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ OPEN -> NULL ? */
    if( (fp = fopen( fname1, "rb" )) == NULL ) {
        printf( "\n ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ ｦ ｻｸｾｲ ｼﾃｲﾏｽ｡" );

        /* ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ ｻｸｾｲ */
        akicode_tbl_create( );
    }
    else {
        /* ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ CLOSE */
        fclose( fp );
    }

    /* ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ OPEN -> NULL ? */
    if( (fp = fopen( fname2, "rb" )) == NULL ) {
        printf( "\n ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ ｦ ｻｸｾｲ ｼﾃｲﾏｽ｡" );

        /* ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ ｻｸｾｲ */
        codedata_tbl_create( );
    }
    else {
        /* ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ CLOSE */
        fclose( fp );
    }

    while( loop ) {
        /* ﾃｰﾌﾞﾙ ｼｮｷ ｸﾘｱ */
		akicode_tbl[ 0 ] = 0;
		for( i = 0; i < MEMBER_MAX; i++) {
			akicode_tbl[ i + 1 ] = 0;
			codedata_tbl[ i ] = 0;
			sort_keisoku_tbl[ i ] = init_kojin_keisoku_tbl();
		}
		kojin_keisoku_tbl = init_kojin_keisoku_tbl();

        printf( "\n" );
        printf( "\n *******************************" );
        printf( "\n  ｱｽﾚﾁｯｸ ｸﾗﾌﾞ ﾒﾝﾊﾞｰ ｶﾝﾘ ﾌﾟﾛｸﾞﾗﾑ " );
        printf( "\n *******************************" );
        printf( "\n ｼｮﾘ ｦ ｾﾝﾀｸ ｼﾃｸﾀﾞｻｲ" );
        printf( "\n 1:ﾆｭｳｶｲ ﾄｳﾛｸ" );
        printf( "\n 2:ｹｲｿｸ ｷﾛｸ ﾆｭｳﾘｮｸ" );
        printf( "\n 3:ﾄｳﾛｸ ｻｸｼﾞｮ" );
        printf( "\n 4:ﾎﾟｲﾝﾄﾋｮｳｼﾞ");
        printf( "\n 5:ﾃﾞｰﾀﾉﾋｮｳｼﾞ");
        printf( "\n E:ｼｭｳﾘｮｳ" );
        printf( "\n ? " );

        /* ｼｮﾘｸﾌﾞﾝ ﾆｭｳﾘｮｸ */
        work[ 0 ] = '\0';
        scanf( "%s", work );

        /* ﾆｭｳﾘｮｸ ｹﾀｽｳ ﾁｪｯｸ -> 1ｲｶﾞｲ ? */
        if( strlen( work ) != 1 ) {
            printf( "\n ﾆｭｳﾘｮｸ ﾐｽ ﾃﾞｽ" );
            continue;
        }

        switch( work[ 0 ] ) {
            case '1':       /* ﾆｭｳｶｲ ﾄｳﾛｸ     */
                nyuukai_touroku( );
                break;

            case '2':       /* ｹｲｿｸ ｷﾛｸ ｼｭｳｹｲ */
                keisoku_input( );
                break;

            case '3':       /* ﾄｳﾛｸ ｻｸｼﾞｮ     */
                touroku_sakujyo( );
                break;

            case '4':       /* ﾎﾟｲﾝﾄﾋｮｳｼﾞ     */
                point_rank( );
                break;

            case '5':       /* ﾃﾞｰﾀﾋｮｳｼﾞ     */
                show_data( );
                break;

            case 'e':       /* ｼｭｳﾘｮｳ         */
            case 'E':
                loop = FALSE;
                break;

            default:
                printf( "\n ﾆｭｳﾘｮｸ ﾐｽ ﾃﾞｽ" );
                break;
        }
    }
    return OK;
}
#else
{
	int    loop = TRUE;			/* ﾙｰﾌﾟ ﾌﾗｸﾞ                */
	char   work[ 128 ];			/* ﾆｭｳﾘｮｸ ﾜｰｸ               */
	FILE   *fp;				/* ﾌｧｲﾙ ﾎﾟｲﾝﾀ               */
	char   *fname1 = AKICODE_TBL_NAME;	/* ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ         */
	char   *fname2 = CODEDATA_TBL_NAME;	/* ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ */
	int	   i;				/* ｲﾝﾃﾞｯｸｽ		    */

	/* ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ OPEN -> NULL ? */
	if( (fp = fopen( fname1, "rb" )) == NULL ) {
		printf( "\n ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ ｦ ｻｸｾｲ ｼﾃｲﾏｽ｡" );

		/* ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ ｻｸｾｲ */
		akicode_tbl_create( );
	}
	else {
		/* ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ CLOSE */
		fclose( fp );
	}

	/* ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ OPEN -> NULL ? */
	if( (fp = fopen( fname2, "rb" )) == NULL ) {
		printf( "\n ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ ｦ ｻｸｾｲ ｼﾃｲﾏｽ｡" );

		/* ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ ｻｸｾｲ */
		codedata_tbl_create( );
	}
	else {
		/* ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ CLOSE */
		fclose( fp );
	}

	while( loop ) {
		/* ﾃｰﾌﾞﾙ ｼｮｷ ｸﾘｱ */
		akicode_tbl[ 0 ] = 0;
		for( i = 0; i < MEMBER_MAX; i++) {
			akicode_tbl[ i + 1 ] = 0;
			codedata_tbl[ i ] = 0;
			sort_keisoku_tbl[ i ] = init_kojin_keisoku_tbl();
		}
		kojin_keisoku_tbl = init_kojin_keisoku_tbl();

		printf( "\n" );
		printf( "\n *******************************" );
		printf( "\n  ｱｽﾚﾁｯｸ ｸﾗﾌﾞ ﾒﾝﾊﾞｰ ｶﾝﾘ ﾌﾟﾛｸﾞﾗﾑ " );
		printf( "\n *******************************" );
		printf( "\n ｼｮﾘ ｦ ｾﾝﾀｸ ｼﾃｸﾀﾞｻｲ" );
		printf( "\n 1:ﾆｭｳｶｲ ﾄｳﾛｸ" );
		printf( "\n 2:ｹｲｿｸ ｷﾛｸ ﾆｭｳﾘｮｸ" );
		printf( "\n 3:ﾄｳﾛｸ ｻｸｼﾞｮ" );
		printf( "\n E:ｼｭｳﾘｮｳ" );
		printf( "\n ? " );

		/* ｼｮﾘｸﾌﾞﾝ ﾆｭｳﾘｮｸ */
		work[ 0 ] = '\0';
		scanf( "%s", work );

		/* ﾆｭｳﾘｮｸ ｹﾀｽｳ ﾁｪｯｸ -> 1ｲｶﾞｲ ? */
		if( strlen( work ) != 1 ) {
			printf( "\n ﾆｭｳﾘｮｸ ﾐｽ ﾃﾞｽ" );
			continue;
		}

		switch( work[ 0 ] ) {
			case '1':       /* ﾆｭｳｶｲ ﾄｳﾛｸ     */
				nyuukai_touroku( );
				break;

			case '2':       /* ｹｲｿｸ ｷﾛｸ ｼｭｳｹｲ */
				keisoku_input( );
				break;

			case '3':       /* ﾄｳﾛｸ ｻｸｼﾞｮ     */
				touroku_sakujyo( );
				break;

			case 'e':       /* ｼｭｳﾘｮｳ         */
			case 'E':
				loop = FALSE;
				break;

			default:
				printf( "\n ﾆｭｳﾘｮｸ ﾐｽ ﾃﾞｽ" );
				break;
		}
	}
	return OK;
}
#endif

/************************************/
/* ﾒﾝﾊﾞｰ ｶﾝﾘ ﾌﾟﾛｸﾞﾗﾑ                */
/*  ﾆｭｳｶｲ ﾄｳﾛｸ ｼｮﾘ                  */
/*   ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ ｻｸｾｲ          */
/*   ﾊﾟﾗﾒｰﾀ : ﾅｼ                    */
/*   ﾘﾀｰﾝ   : 0:OK                  */
/*           -1:NG                  */
/************************************/
static int akicode_tbl_create( void )
{
    int     ret;				/* ﾘﾀｰﾝ ｺｰﾄﾞ        */
    int     i;					/* ｲﾝﾃﾞｯｸｽ          */
    FILE    *fp;				/* ﾌｧｲﾙ ﾎﾟｲﾝﾀ       */
    char    *fname = AKICODE_TBL_NAME;		/* ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ */

    /* ｱｷ ｺｰﾄﾞ ﾍﾝｼｭｳ */
    akicode_tbl[ 0 ] = MEMBER_MAX;
    for( i = 1; i < MEMBER_MAX + 1; i++ ) {
        akicode_tbl[ i ] = i;
    }

    /* ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ OPEN -> NULL ? */
    if( (fp = fopen( fname, "w+b" )) == NULL ) {
        printf( "\n ｱｷ ｺｰﾄﾞﾋｮｳ ﾌｧｲﾙ OPEN ｴﾗｰ" );
        return NG;
    }

    /* ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ WRITE -> 1ｲｶﾞｲ ? */
    if( (ret = fwrite( (char *)akicode_tbl, sizeof( akicode_tbl ), 1, fp ) )
               != 1 ) {
        printf( "\n ｱｷ ｺｰﾄﾞﾋｮｳ ﾌｧｲﾙ WRITE ｴﾗｰ" );
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
/*   ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ ｻｸｾｲ  */
/*   ﾊﾟﾗﾒｰﾀ : ﾅｼ                    */
/*   ﾘﾀｰﾝ   : 0:OK                  */
/*           -1:NG                  */
/************************************/
static int codedata_tbl_create( void )
{
    int     ret;                        	/* ﾘﾀｰﾝ ｺｰﾄﾞ                */
    FILE    *fp;                        	/* ﾌｧｲﾙ ﾎﾟｲﾝﾀ               */
    char    *fname = CODEDATA_TBL_NAME;		/* ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ */
    int	    i;					/* ｲﾝﾃﾞｯｸｽ		    */

    /* ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ OPEN -> NULL ? */
    if( (fp = fopen( fname, "w+b" )) == NULL ) {
        printf( "\n ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ OPEN ｴﾗｰ" );
        return NG;
    }

	for( i = 0; i < MEMBER_MAX; i++ )
		codedata_tbl[ i ] = 0;

    /* ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ WRITE -> 1ｲｶﾞｲ ? */
    if( (ret = fwrite( (char *)codedata_tbl, sizeof( codedata_tbl ), 1, fp ) )
               != 1 ) {
        /* WRITE ｴﾗｰ */
        printf( "\n ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ WRITE ｴﾗｰ" );
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
/* ｷｮｳﾂｳ ﾙｰﾁﾝ                       */
/************************************/


/************************************/
/* ﾒﾝﾊﾞｰ ｶﾝﾘ ﾌﾟﾛｸﾞﾗﾑ                */
/*  ﾆｭｳｶｲ ﾄｳﾛｸ ｼｮﾘ                  */
/*   ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ READ          */
/*   ﾊﾟﾗﾒｰﾀ : ﾅｼ                    */
/*   ﾘﾀｰﾝ   : 0:OK                  */
/*           -1:NG                  */
/************************************/
int akicode_tbl_read( void )
{
    int     ret;				/* ﾘﾀｰﾝ ｺｰﾄﾞ        */
    int     i;					/* ｲﾝﾃﾞｯｸｽ          */
    FILE    *fp;				/* ﾌｧｲﾙ ﾎﾟｲﾝﾀ       */
    char    *fname = AKICODE_TBL_NAME;		/* ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ */

    /* ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ OPEN -> NULL ? */
    if( (fp = fopen( fname, "rb" )) == NULL ) {
        printf( "\n ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ OPEN ｴﾗｰ" );
        return NG;
    }

    for( i = 0; i < MEMBER_MAX + 1; i++ ) {
        /* ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ READ -> 1ｲｶﾞｲ ? */
        if( (ret = fread( (char *)&akicode_tbl[ i ], sizeof( int ), 1, fp ) )
                   != 1 ) {
            /* READ ｴﾗｰ ｱﾘ ? */
            if( ferror( fp ) != 0 ) {
                printf( "\n ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ READ ｴﾗｰ" );
                ret = NG;
            }
            else {
                /* ﾌｧｲﾙ EOF ﾃﾞ ﾅｲ ? */
                if( feof( fp ) == 0 ) {
                    printf( "\n ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ READ ｴﾗｰ" );
                    ret = NG;
                }
                else {
                    ret = OK;
                }
            }
            break;
        }
#ifdef DEBUG
        printf("[%s:%d]\n", __FILE__, __LINE__);
        printf("akicode_tbl[%d]=%d\n",
        			i, akicode_tbl[i]);
        printf("\n");
#endif
    }

#ifdef DEBUG
    /* Show a part of akicode_tbl[] */
    printf("[%s:%d]\n", __FILE__, __LINE__);
    printf("akicode_tbl[]\n");
    for(i = 0; i < 10; i++) {
    	printf("akicode_tbl[%d]=%c(%%d=%d)\n",
    			i, akicode_tbl[i], akicode_tbl[i]);

    }
    printf("\n");
#endif

    /* ｱｷ ｺｰﾄﾞ ﾋｮｳ ﾌｧｲﾙ CLOSE */
    fclose( fp );

    return ret;
}



/***********************************/
/* ﾒﾝﾊﾞｰ ｶﾝﾘ ﾌﾟﾛｸﾞﾗﾑ               */
/*  ﾆｭｳﾘｮｸ ｶｸﾆﾝ                    */
/*   ﾊﾟﾗﾒｰﾀ : ｶｸﾆﾝ ﾒｯｾｰｼﾞ          */
/*   ﾘﾀｰﾝ   : 0:OK                 */
/*           -1:NG                 */
/***********************************/
int kakunin_input( char *msg )
{
    int     ret;            /* ﾘﾀｰﾝ ｺｰﾄﾞ    */
    int     loop = TRUE;    /* ﾙｰﾌﾟ ﾌﾗｸﾞ    */
    char    work[ 128 ];    /* ﾆｭｳﾘｮｸ ﾜｰｸ   */

    while( loop ) {
        /* ｶｸﾆﾝ ﾋｮｳｼﾞ */
        printf( msg );
        printf( "\n ? " );

        /* Y/N ﾆｭｳﾘｮｸ */
        work[ 0 ] = '\0';
        scanf( "%s", work );

        /* ﾆｭｳﾘｮｸ ｹﾀｽｳ ﾁｪｯｸ -> 1ｲｶﾞｲ ? */
        if( strlen( work ) != 1 ) {
            printf( "\n ﾆｭｳﾘｮｸ ﾐｽ ﾃﾞｽ" );
            continue;
        }

        switch( work[ 0 ] ) {
            case 'Y':   /* Yes */
            case 'y':
                ret  = OK;
                loop = FALSE;
                break;

            case 'N':   /* No */
            case 'n':
                ret  = NG;
                loop = FALSE;
                break;

            default:
                printf( "\n ﾆｭｳﾘｮｸ ﾐｽ ﾃﾞｽ" );
                break;
        }
    }

    return ret;
}



/************************************/
/* ﾒﾝﾊﾞｰ ｶﾝﾘ ﾌﾟﾛｸﾞﾗﾑ                */
/*   ｺｼﾞﾝ ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ READ   */
/*   ﾊﾟﾗﾒｰﾀ : ｶｲｲﾝｺｰﾄﾞ              */
/*   ﾘﾀｰﾝ   : 0:OK                  */
/*           -1:NG                  */
/************************************/
int kojin_data_read( int kaiin_code )
{
    int     ret;				/* ﾘﾀｰﾝ ｺｰﾄﾞ                */
    FILE    *fp;				/* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ ﾎﾟｲﾝﾀ */
    long    fptr;				/* ｹｲｿｸ ﾃﾞｰﾀ ﾌｧｲﾙ ﾎﾟｲﾝﾀ     */
    char    *fname = KEISOKU_TBL_NAME;		/* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ       */

    /* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ OPEN -> NULL ? */
    if( (fp = fopen( fname, "rb" )) == NULL ) {
        printf( "\n ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ OPEN ｴﾗｰ" );
        return NG;
    }

    /* ｶﾞｲﾄｳ ﾃﾞｰﾀ ﾎﾟｲﾝﾀ ｾｯﾄ */
    fptr = ( codedata_tbl[ kaiin_code - 1 ] - 1 ) *
             sizeof( struct KEISOKU_TBL );

    /* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ ｦ ﾀｲｼｮｳ ﾉ ｲﾁ ﾏﾃﾞ SEEK -> OK ? */
    if( (ret = fseek( fp, fptr, SEEK_SET )) != OK ) {
        printf( "\n ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ SEEK ｴﾗｰ" );

        /* ｹｲｿｸ ﾃﾞｰﾀ  ﾋｮｳ ﾌｧｲﾙ CLOSE */
        fclose( fp );
        return NG;
    }

    /* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ READ -> 1ｲｶﾞｲ ? */
    if( (ret = fread( (char *)&kojin_keisoku_tbl, sizeof( kojin_keisoku_tbl ),
               1, fp )) != 1 ) {
        printf( "\n ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ READ ｴﾗｰ" );
        ret = NG;
    }
    else {
        ret = OK;
    }

    /* ｹｲｿｸ ﾃﾞｰﾀ  ﾋｮｳ ﾌｧｲﾙ CLOSE */
    fclose( fp );

    return ret;
}



/************************************/
/* ﾒﾝﾊﾞｰ ｶﾝﾘ ﾌﾟﾛｸﾞﾗﾑ                */
/*   ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳｼﾞ                */
/*   ﾊﾟﾗﾒｰﾀ : ｶｲｲﾝｺｰﾄﾞ              */
/*            ﾋｮｳｼﾞ ﾒｯｾｰｼﾞ          */
/*   ﾘﾀｰﾝ   : ﾅｼ                    */
/************************************/
#ifdef TOI2
void kojin_data_disp( int kaiin_code, char *msg )
{
    printf( msg );
    printf( "\n ｶｲｲﾝｺｰﾄﾞ %3d", kaiin_code );

    /* ポイントの表示 */
    printf( "\n\n    ﾎﾟｲﾝﾄ " );
    printf( "%3d", kojin_keisoku_tbl.point);

    if( kojin_keisoku_tbl.count != 0 ) {
        printf( "\n\n ｹｲｿｸｶｲｽｳ   ｼｮｶｲ ﾋﾂﾞｹ   ﾃﾞｰﾀ     " );
        printf( "ｻｲｺｳ ﾋﾂﾞｹ   ﾃﾞｰﾀ     ｻｲｼﾝ ﾋﾂﾞｹ   ﾃﾞｰﾀ" );

        printf( "\n    %3d", kojin_keisoku_tbl.count );

        printf( "    %4.4s-%2.2s-%2.2s",
            &kojin_keisoku_tbl.first_date[ 0 ],
            &kojin_keisoku_tbl.first_date[ 4 ],
            &kojin_keisoku_tbl.first_date[ 6 ] );

        printf( "   %4d", kojin_keisoku_tbl.first_data );

		printf( "    %4.4s-%2.2s-%2.2s",
            &kojin_keisoku_tbl.max_date[ 0 ],
            &kojin_keisoku_tbl.max_date[ 4 ],
            &kojin_keisoku_tbl.max_date[ 6 ] );

        printf( "   %4d", kojin_keisoku_tbl.max_data );

        printf( "    %4.4s-%2.2s-%2.2s",
            &kojin_keisoku_tbl.soku_date[ 0 ],
            &kojin_keisoku_tbl.soku_date[ 4 ],
            &kojin_keisoku_tbl.soku_date[ 6 ] );

        printf( "   %4d", kojin_keisoku_tbl.soku_data[ 0 ] );

        printf( "\n\n    1ｶｲﾏｴ   2ｶｲﾏｴ   3ｶｲﾏｴ   4ｶｲﾏｴ   ");
        printf( "5ｶｲﾏｴ   6ｶｲﾏｴ   7ｶｲﾏｴ   8ｶｲﾏｴ   9ｶｲﾏｴ" );

        printf( "\n " );
        printf( "    %4d", kojin_keisoku_tbl.soku_data[ 1 ] );
        printf( "    %4d", kojin_keisoku_tbl.soku_data[ 2 ] );
        printf( "    %4d", kojin_keisoku_tbl.soku_data[ 3 ] );
        printf( "    %4d", kojin_keisoku_tbl.soku_data[ 4 ] );
        printf( "    %4d", kojin_keisoku_tbl.soku_data[ 5 ] );
        printf( "    %4d", kojin_keisoku_tbl.soku_data[ 6 ] );
        printf( "    %4d", kojin_keisoku_tbl.soku_data[ 7 ] );
        printf( "    %4d", kojin_keisoku_tbl.soku_data[ 8 ] );
        printf( "    %4d", kojin_keisoku_tbl.soku_data[ 9 ] );

    }
	else {
        printf( "    ｹｲｿｸ ﾃﾞｰﾀ ｶﾞ ｱﾘﾏｾﾝ" );
	return;
	}
    return;
}//void kojin_data_disp( int kaiin_code, char *msg )
#else
void kojin_data_disp( int kaiin_code, char *msg )
{
    printf( msg );
    printf( "\n ｶｲｲﾝｺｰﾄﾞ %3d", kaiin_code );

    if( kojin_keisoku_tbl.count != 0 ) {
        printf( "\n\n ｹｲｿｸｶｲｽｳ   ｼｮｶｲ ﾋﾂﾞｹ   ﾃﾞｰﾀ     " );
        printf( "ｻｲｺｳ ﾋﾂﾞｹ   ﾃﾞｰﾀ     ｻｲｼﾝ ﾋﾂﾞｹ   ﾃﾞｰﾀ" );

        printf( "\n    %3d", kojin_keisoku_tbl.count );

        printf( "    %4.4s-%2.2s-%2.2s",
            &kojin_keisoku_tbl.first_date[ 0 ],
            &kojin_keisoku_tbl.first_date[ 4 ],
            &kojin_keisoku_tbl.first_date[ 6 ] );

        printf( "   %4d", kojin_keisoku_tbl.first_data );

		printf( "    %4.4s-%2.2s-%2.2s",
            &kojin_keisoku_tbl.max_date[ 0 ],
            &kojin_keisoku_tbl.max_date[ 4 ],
            &kojin_keisoku_tbl.max_date[ 6 ] );

        printf( "   %4d", kojin_keisoku_tbl.max_data );

        printf( "    %4.4s-%2.2s-%2.2s",
            &kojin_keisoku_tbl.soku_date[ 0 ],
            &kojin_keisoku_tbl.soku_date[ 4 ],
            &kojin_keisoku_tbl.soku_date[ 6 ] );

        printf( "   %4d", kojin_keisoku_tbl.soku_data[ 0 ] );

        printf( "\n\n    1ｶｲﾏｴ   2ｶｲﾏｴ   3ｶｲﾏｴ   4ｶｲﾏｴ   ");
        printf( "5ｶｲﾏｴ   6ｶｲﾏｴ   7ｶｲﾏｴ   8ｶｲﾏｴ   9ｶｲﾏｴ" );

        printf( "\n " );
        printf( "    %4d", kojin_keisoku_tbl.soku_data[ 1 ] );
        printf( "    %4d", kojin_keisoku_tbl.soku_data[ 2 ] );
        printf( "    %4d", kojin_keisoku_tbl.soku_data[ 3 ] );
        printf( "    %4d", kojin_keisoku_tbl.soku_data[ 4 ] );
        printf( "    %4d", kojin_keisoku_tbl.soku_data[ 5 ] );
        printf( "    %4d", kojin_keisoku_tbl.soku_data[ 6 ] );
        printf( "    %4d", kojin_keisoku_tbl.soku_data[ 7 ] );
        printf( "    %4d", kojin_keisoku_tbl.soku_data[ 8 ] );
        printf( "    %4d", kojin_keisoku_tbl.soku_data[ 9 ] );
    }
	else {
        printf( "    ｹｲｿｸ ﾃﾞｰﾀ ｶﾞ ｱﾘﾏｾﾝ" );
	return;
	}
    return;
}//void kojin_data_disp( int kaiin_code, char *msg )
#endif


/************************************/
/* ﾒﾝﾊﾞｰ ｶﾝﾘ ﾌﾟﾛｸﾞﾗﾑ                */
/*   ｹｲｿｸ ﾃﾞｰﾀ ｼｮｷｶ                 */
/*   ﾊﾟﾗﾒｰﾀ : ﾅｼ                    */
/*   ﾘﾀｰﾝ   : ｹｲｿｸ ﾃﾞｰﾀ             */
/************************************/
#ifdef TOI2
struct KEISOKU_TBL init_kojin_keisoku_tbl( void )
{
	static struct KEISOKU_TBL tbl = {
		0, 0, "        ", 0, "        ", 0, "        ", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0
	};
	return tbl;
}
#else
struct KEISOKU_TBL init_kojin_keisoku_tbl( void )
{
	static struct KEISOKU_TBL tbl = {
		0, 0, "        ", 0, "        ", 0, "        ", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
	return tbl;
}
#endif

#ifdef TOI2
/************************************/
/* ﾒﾝﾊﾞｰ ｶﾝﾘ ﾌﾟﾛｸﾞﾗﾑ                */
/*   ポイントデータの作成           */
/*   ﾊﾟﾗﾒｰﾀ :                     */
/*   ﾘﾀｰﾝ   :              */
/************************************/

/************************************/
/* ﾒﾝﾊﾞｰ ｶﾝﾘ ﾌﾟﾛｸﾞﾗﾑ                */
/*   個人データの表示                 */
/*   ﾊﾟﾗﾒｰﾀ : 会員ID（kaiin_code）                    */
/*   ﾘﾀｰﾝ   : -1 => No entry with the id             */
/*			  1  => Display successful */
/************************************/
int  show_data( void )
{
	char	buf[10];	/* scanする文字列のために、１次バッファー */
	int		kaiin_code;	/* 会員コード */

	int		i;			/* インデックス */

    int     ret;				/* ﾘﾀｰﾝ ｺｰﾄﾞ                */
    FILE    *fp;				/* ｺｰﾄﾞ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ ﾎﾟｲﾝﾀ */
    long    fptr;				/* ｺｰﾄﾞ ﾃﾞｰﾀ ﾌｧｲﾙ ﾎﾟｲﾝﾀ     */
    char    *fname = CODEDATA_TBL_NAME;		/* ｺｰﾄﾞ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ       */

    /* ｺｰﾄﾞ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ OPEN -> NULL ? */
    if( (fp = fopen( fname, "rb" )) == NULL ) {
        printf( "\n ｺｰﾄﾞ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ OPEN ｴﾗｰ" );
        return NG;
    }

    /* コード表データ　=>　読み込み */
    if( (ret = fread( (char *)codedata_tbl,
    		sizeof( codedata_tbl ), 1, fp ) ) != 1 ) {
		printf( "\n ｺｰﾄﾞ ﾃﾞｰﾀ ﾀｲｼｮｳ ﾋｮｳ ﾌｧｲﾙ READ ｴﾗｰ" );
		ret = NG;
	}

	/* バッファーをフラッシュしておく */
	fflush(stdin);

	while (1) {
		/* コード番号の入力 */
		printf("会員コードを入力してください：");
		fgets(buf, sizeof(buf), stdin);

		/* buf を表示 */
		printf("[%s:%d]\n", __FILE__, __LINE__);
		printf("buf=%s(%d)\n", buf, *buf);

		/* 数値文字かどうか検証 */
		buf[strlen(buf) - 1] = '\0';
		if( strspn( buf, "1234567890" )
				< strlen( buf ) ) {
			printf( "\n ｽｳﾁ ｲｶﾞｲ ｶﾞ ﾆｭｳﾘｮｸ ｻﾚﾏｼﾀ" );
			continue;
		}
		else
			break;
		/*
		if (isdigit(buf))
			break;

		else
			printf("数値以外の文字です => %s\n", buf);
*/
	}//while (1) {

	/* 入力された番号が、すでに登録されているか検証 */
	//if (codedata_tbl[atoi(buf)] == 0) {
	if (codedata_tbl[atoi(buf) - 1] == 0) {
		printf("codedata_tbl[atoi(buf) - 1]=%d\n",
					codedata_tbl[atoi(buf) - 1]);
		printf("atoi(buf) - 1 = %d\n", atoi(buf) - 1);
		printf("The id %d is not registered yet.\n",
				atoi(buf));
		return -1;
	}

	/* 登録データ　=>　表示 */
	printf("<Showing the data for ID %d ...>\n",
					atoi(buf));

	/* 個人データ　=>　読み込み */
	kojin_data_read(atoi(buf));

	/* 表示 */
	kojin_data_disp(atoi(buf), "Data\n");

/*
	printf("Showing the data for Kaiin ID %d ...\n",
				atoi(buf));
	printf("\tNow building the program. Sorry.\n");
*/
	return 0;

}//int  show_data(int kaiin_code)

static int point_rank( void )
{
    int     ret;						/* ﾘﾀｰﾝ ｺｰﾄﾞ            */
    int     i;							/* ｲﾝﾃﾞｯｸｽ              */
    FILE    *fp;						/* ﾌｧｲﾙ ﾎﾟｲﾝﾀ           */
    char    *fname = KEISOKU_TBL_NAME;				/* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ   */

    //debug
    printf("[%s:%d]\n", __FILE__, __LINE__);
    printf("Start point rank\n");

    /* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ OPEN -> NULL ? */
    if( (fp = fopen( fname, "rb" )) == NULL ) {
        printf( "\n ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ OPEN ｴﾗｰ" );
        return NG;
    }

    /* sort_keisoku_tbl[] => set */
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
    }//for( ; ; ) {

    /* ｹｲｿｸ ﾃﾞｰﾀ ﾋｮｳ ﾌｧｲﾙ CLOSE */
    fclose( fp );

    if( ret == OK ) {
        /* ｹｲｿｸ ﾃﾞｰﾀ ｿｰﾄ */
    	point_sort( i );
        /* ｹｲｿｸ ﾃﾞｰﾀ ｿｰﾄ ｹｯｶ ﾋｮｳｼﾞ */
    	point_disp( i );
    }

    //debug
    printf("\n\n[%s:%d]\n", __FILE__, __LINE__);
    printf("[Exit: point_rank()\n]");

    return ret;
}//static int point_rank( int cnt )

static void point_sort( int cnt )
{
    int     i;                  	/* ｲﾝﾃﾞｯｸｽ      */
    int     j;                  	/* ｲﾝﾃﾞｯｸｽ      */
    struct  KEISOKU_TBL  work;  	/* ｽﾜｯﾌﾟ ﾖｳ ｴﾘｱ */

    /* ﾃﾞｰﾀ ｿｰﾄ */
    for( i = 0; i < cnt - 1; i++ ) {
        for( j = i + 1; j < cnt; j++ ) {
            if( sort_keisoku_tbl[ i ].point <
                sort_keisoku_tbl[ j ].point ) {

				work = sort_keisoku_tbl[ i ];
                sort_keisoku_tbl[ i ] = sort_keisoku_tbl[ j ];
                sort_keisoku_tbl[ j ] = work;
            }
        }
    }
	return;
}//static void point_sort( int cnt )

static void point_disp( int cnt )
{
    int     i;  /* ｲﾝﾃﾞｯｸｽ  */

    printf( "\n\n ** ｼﾞｭﾝｲ ﾋｮｳ (ﾎﾟｲﾝﾄｼﾞｭﾝ) **" );
    printf( "\n ｼﾞｭﾝｲ ｶｲｲﾝｺｰﾄﾞ  ﾎﾟｲﾝﾄ" );

    for( i = 0; i < cnt; i++ ) {

        /* 10ｲ ﾏﾃﾞ ﾋｮｳｼﾞ ｽﾙ */
        if( i >= 10 ) {
            break;
        }

        printf( "\n   %2d   %3d        %4d",
        	i + 1,
            sort_keisoku_tbl[ i ].kaiin_code,
            sort_keisoku_tbl[ i ].point );
    }
	return;
}//static void point_disp( int cnt )

#endif//#ifdef TOI2

/*
 * printf("[%s:%d]\n", __FILE__, __LINE__);
 */
