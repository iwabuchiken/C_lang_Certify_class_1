
// prototypes ================================
/*
static void get_keisoku_tbl(void);
 * static void keisoku_tbl_read(void);
*/

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
        printf( "\n 1: get the akicode_tbl" );
        printf( "\n 2: get the codedata_tbl" );
        printf( "\n 3: get the keisoku_tbl" );
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

        /* switching
         * 1    => get_akicode_tbl
         * E    => quit
         */
        switch( work[ 0 ] ) {
            /* get akicode_tbl     */
			case '1':
				get_akicode_tbl();
				printf("\nShow the akicode_tbl"
						" => complete\n");
				break;
            
            /* get codedata_tbl     */
			case '2':
				get_codedata_tbl();
				printf("\nget the codedata_tbl"
						" => complete\n");
				break;
                
            /* get keisoku_tbl     */
			case '3':
				get_keisoku_tbl();
				printf("\nget the keisoku_tbl"
						" => complete\n");
				break;
            /* quit         */
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
/******************************************
 * get_akicode_tbl -- get akicode_tbl, and show
 * 
 * <Parameters>
 *      
 * <Return value>
 *      return void
 * <Notices>
 * ***
 ******************************************/
static void get_akicode_tbl( void )
{
    /* vars
     * 
     */
    int     i;          /* index        */
    int     res;        /* return value of each function    */
    
    /* read akicode_tbl[]   */
    res = akicode_tbl_read();
    
    /* show akicode_tbl     */
    /* show: column numbers */
    printf("   ");
    for (i = 0; i < 10; i++) {
        printf("%3d", i);
    }//for (i = 0; i < 10; i++)
    printf("\n");
    
    /* show data            */
    for (i = 0; i < MEMBER_MAX; i++) {
        if (i % 10 == 0) {
            printf("\n%3d", i);
        }//if (i % 10 == 0)
        
        printf("%3d", akicode_tbl[i]);
        //printf("akicode_tbl[%d]=%d\n", i, akicode_tbl[i]);
    }//for (i = 0; i < MEMBER_MAX; i++)
    printf("\n");
    
    //printf("get_akicode_tbl( void )\n");
}//get_akicode_tbl( void )

/******************************************
 * get_codedata_tbl -- show codedata_tbl
 * 
 * <Parameters>
 *        - 
 *        - 
 * <Return value>
 *       : 
 * <Notices>
 *      **
 ******************************************/
static void get_codedata_tbl(void)
{
    /* vars             */
    int         i;      /* index        */
    
    /* prepare codedata_tbl[]       */
    codedata_tbl_read();
    
    /* show data        */
    for (i = 0; i < MEMBER_MAX; i++) {
        if (i % 10 == 0) {
            printf("\n%3d", i);
        }//if (i % 10 == 0)
        
        printf("%3d", codedata_tbl[i]);
    }//for (i = 0; i < MEMBER_MAX; i++)
    printf("\n");
    
}//static void get_codedata_tbl(void)


/******************************************
 * update_akicode_tbl -- update akicode_tbl
 * 
 * <Parameters>
 *        - 
 *        - 
 * <Return value>
 *      void : 
 * <Notices>
 *      ***
 ******************************************/
static void update_akicode_tbl(void)
{
    //printf("update_akicode_tbl(void)\n");
    
}//static void update_akicode_tbl(void)

/******************************************
 * get_keisoku_tbl -- obtain keisoku_tbl data and display
 * 
 * <Parameters>
 *        - 
 *        - 
 * <Return value>
 *       : 
 * <Notices>
 *      
 ******************************************/
static void get_keisoku_tbl(void)
{
    /* vars             */
    int     i;          /* index for 'for' loop     */
    int     cnt;        /* number of tbl data       */
    
    /* prepare keisoku_tbl      */
    cnt     = keisoku_tbl_read();
#ifdef DEBUG
	printf("[%d]\n", __LINE__);
    printf("keisoku_tbl prepared\n");
#endif
    
    /* show sort_keisoku_tbl data    */
/*
    for (i = 0; i < 10; i++) {
        printf("sort_keisoku_tbl[%d].kaiin_code=%d\n",
                i, sort_keisoku_tbl[i].kaiin_code);
    }//for (i = 0; i < 3; i++)
*/
    
    
}//static get_keisoku_tbl(void)

static int keisoku_tbl_read(void)
{
    /* vars             */
    int     ret;						/* ØÀ°Ý º°ÄÞ            */
    int     i      = 0;					/* ²ÝÃÞ¯¸½              */
    FILE    *fp;						/* Ì§²Ù Îß²ÝÀ           */
    char    *fname = KEISOKU_TBL_NAME;				/* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù   */
    
    /* open the file    */
    /* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù OPEN -> NULL ? */
    if( (fp = fopen( fname, "rb" )) == NULL ) {
        printf( "\n ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù OPEN ´×°" );
        return NG;
    }
#ifdef DEBUG
	printf("[%d]\n", __LINE__);
    printf("File opened: %s\n", KEISOKU_TBL_NAME);
#endif
    
    /* close file       */
    fclose(fp);
#ifdef DEBUG
	printf("[%d]\n", __LINE__);
    printf("File closed: %s\n", KEISOKU_TBL_NAME);
#endif
    
    /* read keisoku_tbl data    */
    if( (ret = fread( (char *)&sort_keisoku_tbl[ i ],
                   sizeof( struct KEISOKU_TBL ), 1, fp )) != 1 ) {
#ifdef DEBUG
        printf("[%d]\n", __LINE__);
        printf("fread() returned non-1 value: %d\n", ret);
#endif

        return NULL;
    } else {
        i ++;
    }
        
    
#ifdef DEBUG
	printf("[%d]\n", __LINE__);
    printf("sort_keisoku_tbl[%d].kaiin_code=%d\n",
                i, sort_keisoku_tbl[i].kaiin_code);
#endif

    /* return           */
    return i;
    
}//static void keisoku_tbl_read(void)
