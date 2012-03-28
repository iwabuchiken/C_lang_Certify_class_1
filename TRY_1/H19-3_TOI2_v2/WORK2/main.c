/***********************************/
/*  main.c                         */
/*   ±½ÚÁ¯¸ ¸×ÌÞ ÒÝÊÞ° ¶ÝØ ÌßÛ¸Þ×Ñ */
/***********************************/
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "main.h"
#include "admin.h"
#include "nyuukai.h"

/***********************************/
/* ·®³Â³ ÃÞ°À                      */
/***********************************/
/* empty codes table    */
int akicode_tbl[ MEMBER_MAX + 1 ];
/* code-data-location reference table   */
int codedata_tbl[ MEMBER_MAX ];
/* record table for a single member     */
struct KEISOKU_TBL kojin_keisoku_tbl;
/* record table for all the registered members  */
struct KEISOKU_TBL sort_keisoku_tbl[ MEMBER_MAX ];

/***********************************/
/* ÒÝÊÞ° ¶ÝØ ÌßÛ¸Þ×Ñ               */
/*  Ò²Ý                            */
/*   Êß×Ò°À : Å¼                   */
/*   ØÀ°Ý   : Å¼                   */
/***********************************/
int main( void )
{
    /* vars         */
    int         work[128];  /* input line       */
    int         loop    = TRUE; /* flag         */
    int         i;          /* index            */
    FILE   *fp;				/* Ì§²Ù Îß²ÝÀ               */
    char   *fname1 = AKICODE_TBL_NAME;	/* ±· º°ÄÞ Ë®³ Ì§²Ù         */
    char   *fname2 = CODEDATA_TBL_NAME;	/* º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù */
    
    /*   create: akicode_tbl.tbl
     *  1. Open the file
     *  2. If the file doesn't exist, the return value will be
     *      "NULL" => then, create a new file using the function
     *      "akicode_tbl_create( )"
     *      => In this case, in the function "main", the file is not
     *          opened yet, so that closing operation is not necessary.
     *  3. If the return value is not "NULL", meaning the file exists,
     *      then close the file.
     */
    if( (fp = fopen( fname1, "rb" )) == NULL ) {
        printf( "\n ±· º°ÄÞ Ë®³ Ì§²Ù ¦ »¸¾² ¼Ã²Ï½¡" );

        /* ±· º°ÄÞ Ë®³ Ì§²Ù »¸¾² */
        akicode_tbl_create( );
    }else {
        /* ±· º°ÄÞ Ë®³ Ì§²Ù CLOSE */
        fclose( fp );
    }
    
    /* Create: codedata_tbl.tbl     
     * 1. The processes are same as that in akicode_tbl.tbl above
     */
    if( (fp = fopen( fname2, "rb" )) == NULL ) {
        printf( "\n º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù ¦ »¸¾² ¼Ã²Ï½¡" );

        /* º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù »¸¾² */
        codedata_tbl_create( );
    }
    else {
        /* º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù CLOSE */
        fclose( fp );
    }
    
    /* loop         */
    while( loop ) {
        /* Ã°ÌÞÙ ¼®· ¸Ø± */
		akicode_tbl[ 0 ] = 0;
		for( i = 0; i < MEMBER_MAX; i++) {
			akicode_tbl[ i + 1 ] = 0;
			codedata_tbl[ i ] = 0;
			sort_keisoku_tbl[ i ] = init_kojin_keisoku_tbl();
		}
		kojin_keisoku_tbl = init_kojin_keisoku_tbl();

        printf( "\n" );
        printf( "\n *******************************" );
        printf( "\n  ±½ÚÁ¯¸ ¸×ÌÞ ÒÝÊÞ° ¶ÝØ ÌßÛ¸Þ×Ñ " );
        printf( "\n *******************************" );
        printf( "\n ¼®Ø ¦ ¾ÝÀ¸ ¼Ã¸ÀÞ»²" );
        printf( "\n 1:Æ­³¶² Ä³Û¸" );
#ifdef ADMIN        
        printf( "\n 9:admin" );
#endif
        printf( "\n E:¼­³Ø®³" );
        printf( "\n ? " );

        /* ¼®Ø¸ÌÞÝ Æ­³Ø®¸ */
        work[ 0 ] = '\0';
        scanf( "%s", work );

        /* Æ­³Ø®¸ ¹À½³ Áª¯¸ -> 1²¶Þ² ? */
        if( strlen( work ) != 1 ) {
            printf( "\n Æ­³Ø®¸ Ð½ ÃÞ½" );
            continue;
        }

        switch( work[ 0 ] ) {
            case '1':       /* Æ­³¶² Ä³Û¸     */
                nyuukai_touroku( );
                break;

            case '9':       /* admin     */
                start_admin( );
                break;

            case 'e':       /* ¼­³Ø®³         */
            case 'E':
                loop = FALSE;
                break;

            default:
                printf( "\n Æ­³Ø®¸ Ð½ ÃÞ½" );
                break;
        }//switch( work[ 0 ] )
    }//while( loop )
    return OK;
}

struct KEISOKU_TBL init_kojin_keisoku_tbl( void )
{
	static struct KEISOKU_TBL tbl = {
		0, 0, "        ", 0, "        ", 0, "        ", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
	return tbl;
}//struct KEISOKU_TBL init_kojin_keisoku_tbl( void )

static int akicode_tbl_create( void )
{
    int     ret;				/* ØÀ°Ý º°ÄÞ        */
    int     i;					/* ²ÝÃÞ¯¸½          */
    FILE    *fp;				/* Ì§²Ù Îß²ÝÀ       */
    char    *fname = AKICODE_TBL_NAME;		/* ±· º°ÄÞ Ë®³ Ì§²Ù */

    /* ±· º°ÄÞ ÍÝ¼­³ */
    akicode_tbl[ 0 ] = MEMBER_MAX;
    for( i = 1; i < MEMBER_MAX + 1; i++ ) {
        akicode_tbl[ i ] = i;
    }

    /* ±· º°ÄÞ Ë®³ Ì§²Ù OPEN -> NULL ? */
    if( (fp = fopen( fname, "w+b" )) == NULL ) {
        printf( "\n ±· º°ÄÞË®³ Ì§²Ù OPEN ´×°" );
        return NG;
    }

    /* ±· º°ÄÞ Ë®³ Ì§²Ù WRITE -> 1²¶Þ² ? */
    if( (ret = fwrite( (char *)akicode_tbl, sizeof( akicode_tbl ), 1, fp ) )
               != 1 ) {
        printf( "\n ±· º°ÄÞË®³ Ì§²Ù WRITE ´×°" );
        ret = NG;
    }
    else {
        ret = OK;
    }

    /* ±· º°ÄÞ Ë®³ Ì§²Ù CLOSE */
    fclose( fp );

    //debug
    printf("File created: %s\n", AKICODE_TBL_NAME);

    return ret;

    //debug
    //printf("static int akicode_tbl_create( void )\n");
}//static int akicode_tbl_create( void )

static int codedata_tbl_create( void )
{
    int     ret;                        	/* ØÀ°Ý º°ÄÞ                */
    FILE    *fp;                        	/* Ì§²Ù Îß²ÝÀ               */
    char    *fname = CODEDATA_TBL_NAME;		/* º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù */
    int	    i;					/* ²ÝÃÞ¯¸½		    */

    /* º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù OPEN -> NULL ? */
    if( (fp = fopen( fname, "w+b" )) == NULL ) {
        printf( "\n º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù OPEN ´×°" );
        return NG;
    }

	for( i = 0; i < MEMBER_MAX; i++ )
		codedata_tbl[ i ] = 0;

    /* º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù WRITE -> 1²¶Þ² ? */
    if( (ret = fwrite( (char *)codedata_tbl, sizeof( codedata_tbl ), 1, fp ) )
               != 1 ) {
        /* WRITE ´×° */
        printf( "\n º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù WRITE ´×°" );
        ret = NG;
    }
    else {
        ret = OK;
    }

    /* º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù CLOSE */
    fclose( fp );

    //debug
    printf("File created: %s\n", CODEDATA_TBL_NAME);
    
    return ret;
}//static int codedata_tbl_create( void )
