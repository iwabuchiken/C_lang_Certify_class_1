/************************************/
/*  admin.c                       */
/*          */
/************************************/
#ifndef INCLUDE_STDIO_H
#define INCLUDE_STDIO_H
#include <stdio.h>
#endif

#ifndef INCLUDE_STRING_H
#define INCLUDE_STRING_H
#include <string.h>
#endif

#include "common.h"
#include "main.h"
#include "admin.h"
#include "nyuukai.h"
#include "keisoku.h"

/*****************************
 *	global variables
 ****************************/
extern int akicode_tbl[ MEMBER_MAX + 1 ];
extern struct
KEISOKU_TBL sort_keisoku_tbl[ MEMBER_MAX ];
extern int codedata_tbl[ MEMBER_MAX ];
extern struct KEISOKU_TBL keisoku_tbl_data[ MEMBER_MAX ];

/****************************
 * functions
 ****************************/
void start_admin( void )
{
//	printf("[%s:%d]\n", __FILE__, __LINE__);
//	printf("*** Under construction ***\n");

	/* variables
	 * 1. work:char[]
	 * 	=> choice number:		undefined
	 * 2. loop:int
	 * 	=> flag for while loop:	1
	 * 3. ret:int
	 * 	=> return of a function
	 */
	char		work[128];
	int			loop = 1;
	int			ret;

	/* loop: choince input	*/
	while (loop) {
        printf( "\n" );
        printf( "\n *************************************" );
        printf( "\n  ±½ÚÁ¯¸ ¸×ÌÞ ÒÝÊÞ° ¶ÝØ ÌßÛ¸Þ×Ñ: admin " );
        printf( "\n *************************************" );
        printf( "\n ¼®Ø ¦ ¾ÝÀ¸ ¼Ã¸ÀÞ»²" );
        printf( "\n 1: Show the akicode_tbl" );
        printf( "\n 2: Update the akicode_tbl" );
        printf( "\n 3: Show individual datum" );
        printf( "\n 4: Read keisoku table (all)" );
        printf( "\n 5: Get codedata table" );
        printf( "\n 6: Show codedata table" );
        printf( "\n 7: Show keisoku table" );
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

        /* switching	*/
        switch( work[ 0 ] ) {
			case '1':
				get_akicode_tbl();
				printf("\nShow the akicode_tbl"
						" => complete\n");
				break;
			case '2':
				akicode_tbl_update();
				/* show message	*/
				printf("Update the aki_code"
						" => complete\n");
				break;
			case '3':
				show_individual_datum();
				/* show message	*/
				printf("Show individual datum"
						" => complete\n");
				break;
			case '4':
				ret = keisoku_tbl_read_all();
				/* show message	*/
				printf("Read keisoku table\n");
				printf("\tResult=%d", ret);
				printf(" => complete\n");
				break;
			case '5':
				codedata_tbl_read();
				/* show message	*/
				printf("Get codedata table\n");
				//printf("\tResult=%d", ret);
				printf(" => complete\n");
				break;
			case '6':
				show_codedata_tbl();
				/* show message	*/
				printf("Show codedata table\n");
				//printf("\tResult=%d", ret);
				printf(" => complete\n");
				break;
			case '7':
				show_keisoku_tbl();
				/* show message	*/
				printf("Show keisoku table\n");
				//printf("\tResult=%d", ret);
				printf(" => complete\n");
				break;

			case 'E':
			case 'e':
				/* show message	*/
				printf("\n\tLeave the admin\n");
				loop = FALSE;
				break;

			default:
				printf( "\n Æ­³Ø®¸ Ð½ ÃÞ½" );
				break;
        }//switch( work[ 0 ] )
	}//while (loop)
}//void start_admin( void )

static void get_akicode_tbl( void )
{
	/* variables
	 *
	 */

	char    *fname = AKICODE_TBL_NAME;		/* ±· º°ÄÞ Ë®³ Ì§²Ù */
	FILE    *fp;				/* Ì§²Ù Îß²ÝÀ       */
	int     ret;				/* ØÀ°Ý º°ÄÞ        */
	int     i;					/* ²ÝÃÞ¯¸½          */

	/* Processes
	 * 1. open the file
	 * 2. read akicode_tbl into akicode_tbl[]
	 * 3. display value for each
	 * 		akicode_tbl[] element
	 */

	/* open the file */
	fp = fopen( fname, "rb" );
	if( fp == NULL ) {
		printf( "\n Can't open the file: %s\n",
				fname);
		printf("Create a file: %s\n", fname);
		ret = akicode_tbl_create();
		if (ret == NG) {
			printf("Can't create a file: %s\n",
					fname);
			return;
		}//if (ret == NG)
		//return NG;
	}//if( fp == NULL )

	printf("File opened: %s\n", fname);

	/* 2. read akicode_tbl into akicode_tbl[] */
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
        }//if( (ret = fread( (char *)&akicode_tbl[ i ], sizeof( int ), 1, fp ) )
    }//for( i = 0; i < MEMBER_MAX + 1; i++ )

    	/* report	*/
    printf("Read akicode_tbl => complete\n");

    /* 3. display value	*/
    printf("\nShowing akicode_tbl[] values\n");
    for( i = 0; i < MEMBER_MAX + 1; i++ ) {
    	if (akicode_tbl[i] < 100) {
    		printf("%3d", akicode_tbl[i]);
    	} else {
			printf("%4d", akicode_tbl[i]);
		}
    }//for( i = 0; i < MEMBER_MAX + 1; i++ )

	/* close the file	*/
	fclose(fp);
//	printf("[%s:%d]\n", __FILE__, __LINE__);
//	printf("*** get_akicode_tbl() ***\n");
//	printf("*** Under construction ***\n");
}//get_akicode_tbl( void )

void show_individual_datum( void )
{

//	printf("[%s:%d]\n", __FILE__, __LINE__);
//	printf("*** show_individual_datum() ***\n");
//	printf("*** Under construction ***\n");
}//void show_individual_datum( void )

static int keisoku_tbl_read( void )
{
    int     ret;						/* ØÀ°Ý º°ÄÞ            */
    int     i;							/* ²ÝÃÞ¯¸½              */
    FILE    *fp;						/* Ì§²Ù Îß²ÝÀ           */
    char    *fname = KEISOKU_TBL_NAME;				/* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù   */

    /* processes
     * 1. open the table
     * 2. read data
     */
    /* 1. open the table	*/
    if( (fp = fopen( fname, "rb" )) == NULL ) {
        printf( "Can't open the file: %s\n",
        			fname);
        return -1;
    }

    /* 2. read data	*/
    i = 0;
    for( ; ; ) {
        /* read 1 unit of data	*/
    	ret = fread(
    		//(char *)&sort_keisoku_tbl[ i ],
			(char *)&keisoku_tbl_data[ i ],
    		sizeof( struct KEISOKU_TBL ), 1,
    		fp );
        if( ret != 1 ) {
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
        }//if( ret != 1 )

        /* READ ´×° ? */
        if( ret == NG ) {
            break;
        }

        /* ¹²¿¸ ÃÞ°À ±Ø ? */
        //if( sort_keisoku_tbl[ i ].count != 0 ) {
        if( keisoku_tbl_data[ i ].count != 0 ) {
            i++;
        }

        /* eof ? */
        if( ret == OK ) {
            break;
        }
    }//for( ; ; )

    /* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù CLOSE */
    fclose( fp );

    /* return	*/
    return i;
//	printf("[%s:%d]\n", __FILE__, __LINE__);
//	printf("*** keisoku_tbl_read() ***\n");
//	printf("*** Under construction ***\n");
}//void keisoku_tbl_read( void )

static int keisoku_tbl_read_all( void )
{
    int     ret;						/* ØÀ°Ý º°ÄÞ            */
    int     i;							/* ²ÝÃÞ¯¸½              */
    FILE    *fp;						/* Ì§²Ù Îß²ÝÀ           */
    char    *fname = KEISOKU_TBL_NAME;				/* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù   */

    /* processes
     * 1. open the table
     * 2. read data
     */
    /* 1. open the table	*/
    if( (fp = fopen( fname, "rb" )) == NULL ) {
        printf( "Can't open the file: %s\n",
        			fname);
        return -1;
    }

    /* 2. read data	*/
    //i = 0;
    for( i = 0; i < MEMBER_MAX + 1; i++ ) {
        /* read 1 unit of data	*/
    	ret = fread(
    		//(char *)&sort_keisoku_tbl[ i ],
			(char *)&keisoku_tbl_data[ i ],
    		sizeof( struct KEISOKU_TBL ), 1,
    		fp );
        if( ret != 1 ) {
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
        }//if( ret != 1 )

        /* READ ´×° ? */
        if( ret == NG ) { /* NG = -1	*/
            break;
        }

        /* ¹²¿¸ ÃÞ°À ±Ø ? */
        //if( sort_keisoku_tbl[ i ].count != 0 ) {
//        if( keisoku_tbl_data[ i ].count != 0 ) {
//            i++;
//        }

        /* eof ? */
        if( ret == OK ) { /* OK = 0	*/
            break;
        }
    }//for( ; ; )

    /* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù CLOSE */
    fclose( fp );

    /* return	*/
    return i;
//	printf("[%s:%d]\n", __FILE__, __LINE__);
//	printf("*** keisoku_tbl_read() ***\n");
//	printf("*** Under construction ***\n");
}//void keisoku_tbl_read_all( void )

static void show_codedata_tbl( void )
{
	/* variables
	 * 1. ret:int	=> return of codedata_tbl_read()
	 * 2. i:int		=> index
	 */
	int		ret;
	int		i;

	/* processes
	 * 1. Read codedata_tbl
	 */

	/* 1. Read codedata_tbl	 */
	ret = codedata_tbl_read();
	if (ret == OK) {
		for( i = 0;
				i < MEMBER_MAX + 1; i++ ) {
			printf("%d:%d ",
					i, codedata_tbl[i]);
		}//for( i = 0; i < MEMBER_MAX + 1; i++ )
		printf("\n");
	} else {
		printf("[%s:%d\n]",
				__FILE__, __LINE__);
		printf("Error: codedata_tbl_read()");
		return;
	}//if (ret == OK)

//	printf("[%s:%d]\n", __FILE__, __LINE__);
//	printf("*** show_codedata_tbl() ***\n");
//	printf("*** Under construction ***\n");
}//static void show_codedata_tbl( void )

static void show_keisoku_tbl( void )
{
	/* variables
	 * 1. i:int	=> index
	 */
	int		i;

	for( i = 0; i < MEMBER_MAX + 1; i++ ) {
		if (keisoku_tbl_data[i].kaiin_code
				!= 0) {
			//printf("%d:%d\n", i, sort_keisoku_tbl[i].kaiin_code);
			printf("keisoku_tbl_data[%d]."
				"kaiin_code=%d\n",
				i, keisoku_tbl_data[i].kaiin_code);
//		} else {
//			printf("%d:%d ", i, sort_keisoku_tbl[i].kaiin_code);
		}
	}//for( i = 0; i < MEMBER_MAX + 1; i++ )
}//static void show_keisoku_tbl( void )
