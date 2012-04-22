/************************************/
/*  sakujyo.c                       */
/*    Ä³Û¸ »¸¼Þ® ¼®Ø ÌßÛ¸Þ×Ñ Ì§²Ù   */
/************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "common.h"
#include "main.h"
#include "sakujyo.h"

extern int akicode_tbl[ MEMBER_MAX + 1 ];		/* ±·º°ÄÞ Ë®³ */
extern int codedata_tbl[ MEMBER_MAX ];			/* º°ÄÞÃÞ°À À²¼®³ Ë®³ */
extern struct KEISOKU_TBL kojin_keisoku_tbl;		/* º¼ÞÝÍÞÂ ¹²¿¸ ÃÞ°ÀË®³ */

/************************************/
/* ÒÝÊÞ° ¶ÝØ ÌßÛ¸Þ×Ñ                */
/*  Ä³Û¸ »¸¼Þ® ¼®Ø                  */
/*   Ò²Ý                            */
/*   Êß×Ò°À : Å¼                    */
/*   ØÀ°Ý   : 0:OK                  */
/*           -1:NG                  */
/************************************/
int touroku_sakujyo( void )
{
    int     ret;            /* ØÀ°Ý º°ÄÞ        */
    int     loop = TRUE;    /* Ù°Ìß Ì×¸Þ        */
    int     kaiin_code;     /* »¸¼Þ® ¶²²Ý º°ÄÞ  */
    char    work[ 128 ];    /* Æ­³Ø®¸ Ü°¸       */

    while( loop ) {
        printf( "\n À²¶²¼¬ É ¶²²Ý º°ÄÞ ¦ Æ­³Ø®¸ ¼Ã¸ÀÞ»²" );
        printf( "\n ? " );

        /* ¶²²Ý º°ÄÞ Æ­³Ø®¸ */
        work[ 0 ] = '\0';
        scanf( "%s", work );

        /* Æ­°ÒØ¯¸ Áª¯¸ -> ½³Á²¶Þ² ? */
        if( strspn( work, "1234567890" ) < strlen( work ) ) {
            printf( "\n ½³Á ²¶Þ² ¶Þ Æ­³Ø®¸ »ÚÏ¼À" );
            continue;
        }

        /* Æ­°Ø®¸ ÊÝ² Áª¯¸ -> ( 0 < kaiin_code <= MEMBER_MAX ) ? */
        kaiin_code = atoi( work );
        if( kaiin_code > MEMBER_MAX || kaiin_code <= 0 ) {
            printf( "\n Æ­³Ø®¸ Ð½ ÃÞ½" );
            continue;
        }

        /* º°ÄÞ ÃÞ°À À²¼®³ Ë®³ »¸¼Þ® -> OK ? */
        if( (ret = codedata_tbl_delete( kaiin_code )) == OK ) {
            /* ±· º°ÄÞ Ë®³ Â²¶ -> OK ? */
            if( (ret = akicode_tbl_add( kaiin_code )) == OK ) {
                /* Ò²Ý Æ ÓÄÞÙ */
                loop = FALSE;
            }
        }
        else {
            /* Ò²Ý Æ ÓÄÞÙ */
            loop = FALSE;
        }//if( (ret = codedata_tbl_delete( kaiin_code )) == OK )
    }//while( loop )

    if( ret == OK ) {
        printf( "\n Æ­³¶² Ä³Û¸ »¸¼Þ® ¼®Ø ¶Þ ¼­³Ø®³ ¼Ï¼À" );
    }

    return ret;
}//int touroku_sakujyo( void )



/************************************/
/* ÒÝÊÞ° ¶ÝØ ÌßÛ¸Þ×Ñ                */
/*  Ä³Û¸ »¸¼Þ® ¼®Ø                  */
/*   º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù º³¼Ý  */
/*   Êß×Ò°À : »¸¼Þ® ¶²²Ý º°ÄÞ       */
/*   ØÀ°Ý   : 0:OK                  */
/*            1:CANCEL              */
/*           -1:NG                  */
/************************************/
static int codedata_tbl_delete( int kaiin_code )
{
    int     ret;                        /* ØÀ°Ý º°ÄÞ                */
    int     i;                          /* ²ÝÃÞ¯¸½                  */
    char    msg[ 64 ];                  /* Ò¯¾°¼Þ ´Ø±               */
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
        /* READ ´×° */
        printf( "\n º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù READ ´×°" );

        /* º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù CLOSE */
        fclose( fp );
        return NG;
    }

    /* ¶²²Ý Ä³Û¸ Áª¯¸ -> ÐÄ³Û¸ ? */
    if( codedata_tbl[ kaiin_code - 1 ] == 0 ) {
        printf( "\n ºÉ ¶²²Ý º°ÄÞ Ê ÐÄ³Û¸ ÃÞ½" );

        /* º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù CLOSE */
        fclose( fp );
        return CANCEL;
    }

    /* ¹²¿¸ ÃÞ°À Ë®³ READ -> NG ? */
    if( (ret = kojin_data_read( kaiin_code )) == NG ) {
        /* º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù CLOSE */
        fclose( fp );
        return ret;
    }

    /* ¹²¿¸ ÃÞ°À Ë®³¼Þ */
    kojin_data_disp( kaiin_code, "\n ** »¸¼Þ® ÃÞ°À **" );

    /* ¹²¿¸ ÃÞ°À Ë®³ »¸¼Þ® ¶¸ÆÝ */
    sprintf( msg, "\n\n ³´ É ÃÞ°À ¦ »¸¼Þ® ¼Ï½. ÖÛ¼² ÃÞ½¶( Y/N )" );

    if( (ret = kakunin_input( msg )) == OK ) {

        /* ¹²¿¸ ÃÞ°À Ë®³ »¸¼Þ® -> OK ? */
        if( (ret = kojin_data_delete( kaiin_code )) == OK ) {

            /* ¹²¿¸ ÃÞ°À Îß²ÝÀ º³¼Ý */
            for( i = 0; i < MEMBER_MAX; i++ ) {
                if( codedata_tbl[ i ] > codedata_tbl[ kaiin_code - 1 ] ) {
                    codedata_tbl[ i ]--;
                }
            }

            /* ¹²¿¸ ÃÞ°À Îß²ÝÀ ¸Ø± */
            codedata_tbl[ kaiin_code - 1 ] = 0;

            /* º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù É ¾ÝÄ³²Á Æ SEEK -> OK ? */
            if( (ret = fseek( fp, 0L, SEEK_SET )) == OK ) {

                /* º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù WRITE -> 1²¶Þ² ? */
                if( (ret = fwrite( (char *)codedata_tbl,
                           sizeof( codedata_tbl ),1, fp )) != 1 ) {
                    printf( "\n º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù WRITE ´×°" );
                    ret = NG;
                }
                else {
                    ret = OK;
                }
            }
            else {
                printf( "\n º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù SEEK ´×°" );
                ret = NG;
            }
        }
    }
    else {
        /* ¼®Ø Á­³¼ */
        ret = CANCEL;
    }

    /* º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù CLOSE */
    fclose( fp );

    return ret;
}



/************************************/
/* ÒÝÊÞ° ¶ÝØ ÌßÛ¸Þ×Ñ                */
/*  Ä³Û¸ »¸¼Þ® ¼®Ø                  */
/*   ¹²¿¸ ÃÞ°À Ë®³ »¸¼Þ®            */
/*   Êß×Ò°À : »¸¼Þ® ¶²²Ý º°ÄÞ       */
/*   ØÀ°Ý   : 0:OK                  */
/*           -1:NG                  */
/************************************/
static int kojin_data_delete( int kaiin_code )
{
    int     ret;				/* ØÀ°Ý º°ÄÞ                */
    int     i;					/* ²ÝÃÞ¯¸½                  */
    FILE    *fp;				/* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù Îß²ÝÀ */
    FILE    *tmp;				/* ÃÝÎß×Ø Ì§²Ù Îß²ÝÀ        */
    char    *fname = KEISOKU_TBL_NAME;		/* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù       */
    char    *tmpfl = "keisoku.tmp";		/* ÃÝÎß×Ø Ì§²Ù              */

    /* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù OPEN -> NULL ? */
    if( (fp = fopen( fname, "rb" )) == NULL ) {
        printf( "\n ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù OPEN ´×°" );
        return NG;
    }

    /* ÃÝÎß×Ø Ì§²Ù OPEN -> NULL ? */
    if( (tmp = fopen( tmpfl, "w+b" )) == NULL ) {
        printf( "\n ÃÝÎß×Ø Ì§²Ù OPEN ´×°" );
        fclose( fp );
        return NG;
    }

    i = 0;
    for( ; ; ) {

        /* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù READ -> 1²¶Þ² ? */
        if( (ret = fread( (char *)&kojin_keisoku_tbl,
                   sizeof( kojin_keisoku_tbl ), 1, fp )) != 1 ) {

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
            break;
        }

        /* »¸¼Þ® ÃÞ°À ? */
        if( kaiin_code == kojin_keisoku_tbl.kaiin_code ) {
            continue;
        }

        /* ÃÝÎß×Ø Ì§²Ù WRITE -> 1²¶Þ² ? */
        if( (ret = fwrite( (char *)&kojin_keisoku_tbl,
                   sizeof( kojin_keisoku_tbl ), 1, tmp )) != 1 ) {
            printf( "\n ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù WRITE ´×°" );
            ret = NG;
            break;
        }
        i++;
    }

    /* ÃÝÎß×Ø Ì§²Ù CLOSE */
    fclose( tmp );

    /* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù CLOSE */
    fclose( fp );

    /* ¾²¼Þ®³ ¼­³Ø®³ ? */
    if( ret == OK ) {

        /* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù DELETE -> 0²¶Þ² ? */
        if( (ret = remove( fname )) != 0 ) {
            printf( "\n ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù »¸¼Þ® ´×°" );
            ret = NG;
        }
        else {
            /* ¶·ºÐ ÃÞ°À ±Ø ? */
            if( i > 0 ) {

                /* ÃÝÎß×Ø Ì§²Ù ¦ ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù Æ ØÈ°Ñ ½Ù -> 0²¶Þ² ? */
                if( (ret = rename( tmpfl, fname )) != 0 ) {
                    printf( "\n ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù ØÈ°Ñ ´×°" );
                    ret = NG;
                }
            }
            else {
                /* ÃÝÎß×Ø Ì§²Ù »¸¼Þ® */
                remove( tmpfl );
            }
        }
    }
    else {
        /* ÃÝÎß×Ø Ì§²Ù »¸¼Þ® */
        remove( tmpfl );
    }

    return ret;
}



/************************************/
/* ÒÝÊÞ° ¶ÝØ ÌßÛ¸Þ×Ñ                */
/*  Ä³Û¸ »¸¼Þ® ¼®Ø                  */
/*   ±· º°ÄÞ Ë®³ Ì§²Ù Â²¶           */
/*   Êß×Ò°À : »¸¼Þ® ¶²²Ý º°ÄÞ       */
/*   ØÀ°Ý   : 0:OK                  */
/*           -1:NG                  */
/************************************/
static int akicode_tbl_add( int kaiin_code )
{
    int     ret;				/* ØÀ°Ý º°ÄÞ        */
    int     cnt;				/* ±· º°ÄÞ¹Ý½³      */
    FILE    *fp;				/* Ì§²Ù Îß²ÝÀ       */
    char    *fname = AKICODE_TBL_NAME;		/* ±· º°ÄÞ Ë®³ Ì§²Ù */

    /* ±· º°ÄÞ Ë®³ READ -> NG ? */
    if( (ret = akicode_tbl_read( )) == NG ) {
        return ret;
    }

    /* ±· º°ÄÞ ¹Ý½³ ¾¯Ä */
    cnt = akicode_tbl[ 0 ];

    /* ±· º°ÄÞ Ã°ÌÞÙ ¾¯Ä */
    akicode_tbl[ cnt + 1 ] = kaiin_code;

    /* ±· º°ÄÞ ¹Ý½³ ¾¯Ä */
    akicode_tbl[ 0 ] = cnt + 1;

    /* ±· º°ÄÞ Ë®³ Ì§²Ù OPEN -> NULL ? */
    if( (fp = fopen( fname, "w+b" )) == NULL ) {
        printf( "\n ±· º°ÄÞË®³ Ì§²Ù OPEN ´×°" );
        return NG;
    }

    /* ±· º°ÄÞ Ë®³ Ì§²Ù WRITE -> 1²¶Þ² ? */
    if( (ret = fwrite( (char *)akicode_tbl,
               sizeof( int ) * ( akicode_tbl[ 0 ] + 1 ), 1, fp )) != 1 ) {
        printf( "\n ±· º°ÄÞ Ë®³ Ì§²Ù WRITE ´×°" );
        ret = NG;
    }
    else {
        ret = OK;
    }

    /* ±·º°ÄÞ Ë®³ Ì§²Ù CLOSE */
    fclose( fp );

    return ret;
}
