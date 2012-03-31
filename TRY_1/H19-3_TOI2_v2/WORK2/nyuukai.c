/************************************/
/*  nyuukai.c                       */
/*    Æ­³¶² Ä³Û¸ ¼®Ø ÌßÛ¸Þ×Ñ Ì§²Ù   */
/************************************/
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "main.h"
#include "nyuukai.h"

extern int akicode_tbl[ MEMBER_MAX + 1 ];			/* ±·º°ÄÞ Ë®³ */
extern int codedata_tbl[ MEMBER_MAX ];				/* º°ÄÞÃÞ°À À²¼®³ Ë®³ */
extern struct KEISOKU_TBL kojin_keisoku_tbl;			/* º¼ÞÝÍÞÂ ¹²¿¸ ÃÞ°ÀË®³ */

/***********************************/
/* ÒÝÊÞ° ¶ÝØ ÌßÛ¸Þ×Ñ               */
/*  Æ­³¶² Ä³Û¸ ¼®Ø                 */
/*   Ò²Ý                           */
/*   Êß×Ò°À : Å¼                   */
/*   ØÀ°Ý   : 0:OK                 */
/*           -1:NG                 */
/***********************************/
int nyuukai_touroku( void )
{
    int    ret;             /* ØÀ°Ý º°ÄÞ        */
    int    kaiin_code;      /* Ä³Û¸ ¶²²Ý º°ÄÞ   */
    long   fptr;            /* Ì§²Ù Îß²ÝÀ       */
    char   msg[ 64 ];       /* Ò¯¾°¼Þ ´Ø±       */
    
    /* ±· º°ÄÞ Ë®³ READ -> NG ? */
	if( (ret = akicode_tbl_read( )) == NG ) {
        return ret;
	}

    /* ±· º°ÄÞ ±Ø ? */
    if( akicode_tbl[ 0 ] <= 0 ) {
        printf( "\n »ÞÝÈÝÅ¶Þ× ÀÀÞ²Ï ÒÝÊÞ° É ±·¶Þ ±ØÏ¾Ý\n" );
        ret = OK;
        return ret;
    }
    
    /* ±· º°ÄÞ ¶¸ÆÝ */
    /* setup msg variable   */
    sprintf( msg, "\n ¶²²Ý º°ÄÞ Ê %d ÃÞ½. ÖÛ¼² ÃÞ½¶( Y/N )", akicode_tbl[ 1 ] );
    
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
/* ÒÝÊÞ° ¶ÝØ ÌßÛ¸Þ×Ñ                */
/*  Æ­³¶² Ä³Û¸ ¼®Ø                  */
/*   ±· º°ÄÞ Ë®³ Ì§²Ù º³¼Ý          */
/*   Êß×Ò°À : Å¼                    */
/*   ØÀ°Ý   : 0:OK                  */
/*           -1:NG                  */
/************************************/
static int akicode_tbl_update( void )
{
    int     ret;					/* ØÀ°Ý º°ÄÞ        */
    int     i;						/* ²ÝÃÞ¯¸½          */
    int     cnt;					/* ±· º°ÄÞ ½³       */
    FILE    *fp;					/* Ì§²Ù Îß²ÝÀ       */
    char    *fname = AKICODE_TBL_NAME;  		/* ±· º°ÄÞ Ë®³ Ì§²Ù */

    /* ±· º°ÄÞ ¹Ý½³ ¾¯Ä */
    cnt = akicode_tbl[ 0 ];

    /* ±· º°ÄÞ ÍÝ¼­³ */
    for( i = 1; i < cnt; i++ ) {
        if( akicode_tbl[ i + 1 ] == 0 ) {
            break;
        }
        akicode_tbl[ i ] = akicode_tbl[ i + 1 ];
    }

    akicode_tbl[ i ] = 0;

    /* ±· º°ÄÞ ¹Ý½³ ¾¯Ä */
    akicode_tbl[ 0 ] = cnt - 1;

    /* ±· º°ÄÞ Ë®³ Ì§²Ù OPEN -> NULL ? */
    if( (fp = fopen( fname, "w+b" )) == NULL ) {
        printf( "\n ±·º°ÄÞ Ë®³ Ì§²Ù OPEN ´×°" );
        return NG;
    }

    /* ±· º°ÄÞ Ë®³ Ì§²Ù WRITE -> 1²¶Þ² ? */
    if( (ret = fwrite( (char *)akicode_tbl,
               sizeof( int ) * (akicode_tbl[ 0 ] + 1), 1, fp )) != 1 ) {
        printf( "\n ±· º°ÄÞ Ë®³ Ì§²Ù WRITE ´×°" );
        ret = NG;
    }
    else {
        ret = OK;
    }

    /* ±· º°ÄÞ Ë®³ Ì§²Ù CLOSE */
    fclose( fp );

    return ret;
}//static int akicode_tbl_update( void )

/************************************/
/* ÒÝÊÞ° ¶ÝØ ÌßÛ¸Þ×Ñ                */
/*  Æ­³¶² Ä³Û¸ ¼®Ø                  */
/*   ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù Â²¶         */
/*   Êß×Ò°À : ¹²¿¸ ÃÞ°À Îß²ÝÀ       */
/*            Ä³Û¸ ¶²²Ý º°ÄÞ        */
/*   ØÀ°Ý   : 0:OK                  */
/*           -1:NG                  */
/************************************/
static int keisoku_tbl_add( long *fptr, int kaiin_code )
{
    int     ret;					/* ØÀ°Ý º°ÄÞ            */
    FILE    *fp;					/* Ì§²Ù Îß²ÝÀ           */
    char    *fname = KEISOKU_TBL_NAME;			/* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù   */

    /* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù OPEN -> NULL ? */
    if( (fp = fopen( fname, "a+b" )) == NULL ) {
        printf( "\n ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù OPEN ´×°" );
        return NG;
    }

    /* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù SEEK -> OK ÃÞ Å² ? */
    if( (ret = fseek( fp, 0L, SEEK_END )) != OK ) {
        printf( "\n ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù SEEK ´×°" );
        /* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù CLOSE */
        fclose( fp );
        return NG;
    }

    /* Ì§²Ù Îß²ÝÀ ¼­Ä¸ */
    *fptr = ftell( fp );

    /* ¹²¿¸ ÃÞ°À Ë®³ ¸Ø± */
	kojin_keisoku_tbl = init_kojin_keisoku_tbl();

    /* ¶²²Ý º°ÄÞ ¾¯Ä */
    kojin_keisoku_tbl.kaiin_code = kaiin_code;

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
}//static int keisoku_tbl_add( long *fptr, int kaiin_code )

static int codedata_tbl_update( int kaiin_code, long fptr )
{
    int     ret;                        /* ØÀ°Ý º°ÄÞ                */
    FILE    *fp;                        /* Ì§²Ù Îß²ÝÀ               */
    char    *fname = CODEDATA_TBL_NAME;	/* º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù */

    /* º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù OPEN -> NULL ? */
    if( (fp = fopen( fname, "r+b" )) == NULL ) {
        printf( "\n º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù OPEN ´×°" );
        return NG;
    }

    /* º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù READ -> 1²¶Þ² ? */
    if( (ret = fread( (char *)codedata_tbl, sizeof( codedata_tbl ), 1, fp ) )
               != 1 ) {
        printf( "\n º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù READ ´×°" );
        ret = NG;
    }
    else {
        /* ¶Þ²Ä³ ÃÞ°À Îß²ÝÀ ¾¯Ä */
        codedata_tbl[ kaiin_code - 1 ] = 
            (int)( (fptr / sizeof( struct KEISOKU_TBL )) + 1 );

        /* Ì§²Ù Îß²ÝÀ ¦ ¾ÝÄ³ Æ SEEK -> OK ÃÞ Å² ? */
        if( (ret = fseek( fp, 0L, SEEK_SET )) != OK ) {
            printf( "\n º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù SEEK ´×°" );

            /* º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù CLOSE */
            fclose( fp );
            return NG;
        }

        /* º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù WRITE -> 1²¶Þ² ? */
        if( (ret = fwrite( (char *)codedata_tbl, sizeof( codedata_tbl ), 1,
                   fp )) != 1 ) {
            printf( "\n º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù WRITE ´×°" );
            ret = NG;
        }
        else {
            ret = OK;
        }
    }

    /* º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù CLOSE */
    fclose( fp );

    return ret;
}//static int codedata_tbl_update( int kaiin_code, long fptr )
