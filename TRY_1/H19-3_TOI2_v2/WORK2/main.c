/***********************************/
/*  main.c                         */
/*   ±½ÚÁ¯¸ ¸×ÌÞ ÒÝÊÞ° ¶ÝØ ÌßÛ¸Þ×Ñ */
/*   C:\WORKS\WORKSPACES\C_lang_Certify_class_1\TRY_1\H19-3_TOI2_v2\WORK2\main.c */
/***********************************/
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "main.h"
#include "admin.h"
#include "nyuukai.h"
#include "sakujyo.h"

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
        printf( "\n 3:Ä³Û¸ »¸¼Þ®" );
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

            case '3':       /* Ä³Û¸ »¸¼Þ®     */
                touroku_sakujyo( );
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

int akicode_tbl_read( void )
{
    int     ret;				/* ØÀ°Ý º°ÄÞ        */
    int     i;					/* ²ÝÃÞ¯¸½          */
    FILE    *fp;				/* Ì§²Ù Îß²ÝÀ       */
    char    *fname = AKICODE_TBL_NAME;		/* ±· º°ÄÞ Ë®³ Ì§²Ù */

    /* ±· º°ÄÞ Ë®³ Ì§²Ù OPEN -> NULL ? */
    if( (fp = fopen( fname, "rb" )) == NULL ) {
        printf( "\n ±· º°ÄÞ Ë®³ Ì§²Ù OPEN ´×°" );
        return NG;
    }

    for( i = 0; i < MEMBER_MAX + 1; i++ ) {
        /* ±· º°ÄÞ Ë®³ Ì§²Ù READ -> 1²¶Þ² ? */
        if( (ret = fread( (char *)&akicode_tbl[ i ], sizeof( int ), 1, fp ) )
                   != 1 ) {
            /* READ ´×° ±Ø ? */
            if( ferror( fp ) != 0 ) {
                printf( "\n ±· º°ÄÞ Ë®³ Ì§²Ù READ ´×°" );
                ret = NG;
            }
            else {
                /* Ì§²Ù EOF ÃÞ Å² ? */
                if( feof( fp ) == 0 ) {
                    printf( "\n ±· º°ÄÞ Ë®³ Ì§²Ù READ ´×°" );
                    ret = NG;
                }
                else {
                    ret = OK;
                }
            }
            break;
        }
    }

    /* ±· º°ÄÞ Ë®³ Ì§²Ù CLOSE */
    fclose( fp );

    return ret;
}//int akicode_tbl_read( void )

int kakunin_input( char *msg )
{
    int     ret;            /* ØÀ°Ý º°ÄÞ    */
    int     loop = TRUE;    /* Ù°Ìß Ì×¸Þ    */
    char    work[ 128 ];    /* Æ­³Ø®¸ Ü°¸   */

    while( loop ) {
        /* ¶¸ÆÝ Ë®³¼Þ */
        printf( msg );
        printf( "\n ? " );

        /* Y/N Æ­³Ø®¸ */
        work[ 0 ] = '\0';
        scanf( "%s", work );

        /* Æ­³Ø®¸ ¹À½³ Áª¯¸ -> 1²¶Þ² ? */
        if( strlen( work ) != 1 ) {
            printf( "\n Æ­³Ø®¸ Ð½ ÃÞ½" );
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
                printf( "\n Æ­³Ø®¸ Ð½ ÃÞ½" );
                break;
        }
    }

    return ret;
}//int kakunin_input( char *msg )

/************************************/
/* ÒÝÊÞ° ¶ÝØ ÌßÛ¸Þ×Ñ                */
/*   º¼ÞÝ ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù READ   */
/*   Êß×Ò°À : ¶²²Ýº°ÄÞ              */
/*   ØÀ°Ý   : 0:OK                  */
/*           -1:NG                  */
/************************************/
int kojin_data_read( int kaiin_code )
{
    int     ret;				/* ØÀ°Ý º°ÄÞ                */
    FILE    *fp;				/* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù Îß²ÝÀ */
    long    fptr;				/* ¹²¿¸ ÃÞ°À Ì§²Ù Îß²ÝÀ     */
    char    *fname = KEISOKU_TBL_NAME;		/* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù       */

    /* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù OPEN -> NULL ? */
    if( (fp = fopen( fname, "rb" )) == NULL ) {
        printf( "\n ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù OPEN ´×°" );
        return NG;
    }

    /* ¶Þ²Ä³ ÃÞ°À Îß²ÝÀ ¾¯Ä */
    fptr = ( codedata_tbl[ kaiin_code - 1 ] - 1 ) *
             sizeof( struct KEISOKU_TBL );

    /* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù ¦ À²¼®³ É ²Á ÏÃÞ SEEK -> OK ? */
    if( (ret = fseek( fp, fptr, SEEK_SET )) != OK ) {
        printf( "\n ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù SEEK ´×°" );

        /* ¹²¿¸ ÃÞ°À  Ë®³ Ì§²Ù CLOSE */
        fclose( fp );
        return NG;
    }

    /* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù READ -> 1²¶Þ² ? */
    if( (ret = fread( (char *)&kojin_keisoku_tbl, sizeof( kojin_keisoku_tbl ),
               1, fp )) != 1 ) {
        printf( "\n ¹²¿¸ ÃÞ°À Ë®³ READ ´×°" );
        ret = NG;
    }
    else {
        ret = OK;
    }

    /* ¹²¿¸ ÃÞ°À  Ë®³ Ì§²Ù CLOSE */
    fclose( fp );

    return ret;
}//int kojin_data_read( int kaiin_code )

/************************************/
/* ÒÝÊÞ° ¶ÝØ ÌßÛ¸Þ×Ñ                */
/*   ¹²¿¸ ÃÞ°À Ë®³¼Þ                */
/*   Êß×Ò°À : ¶²²Ýº°ÄÞ              */
/*            Ë®³¼Þ Ò¯¾°¼Þ          */
/*   ØÀ°Ý   : Å¼                    */
/************************************/
void kojin_data_disp( int kaiin_code, char *msg )
{
    printf( msg );
    printf( "\n ¶²²Ýº°ÄÞ %3d", kaiin_code );

    if( kojin_keisoku_tbl.count != 0 ) {
        printf( "\n\n ¹²¿¸¶²½³   ¼®¶² ËÂÞ¹   ÃÞ°À     " );
        printf( "»²º³ ËÂÞ¹   ÃÞ°À     »²¼Ý ËÂÞ¹   ÃÞ°À" );

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

        printf( "\n\n    1¶²Ï´   2¶²Ï´   3¶²Ï´   4¶²Ï´   ");
        printf( "5¶²Ï´   6¶²Ï´   7¶²Ï´   8¶²Ï´   9¶²Ï´" );

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
        printf( "    ¹²¿¸ ÃÞ°À ¶Þ ±ØÏ¾Ý" );
	return;
	}
    return;
}//void kojin_data_disp( int kaiin_code, char *msg )

void dummy_func( void )
{
    printf("hi.\n");
}//void dummy_func( void )

struct KEISOKU_TBL dummy_tbl;
