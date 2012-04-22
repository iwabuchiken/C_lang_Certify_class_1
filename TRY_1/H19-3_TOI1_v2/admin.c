
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

#ifndef INCLUDE_STDLIB_H
#define INCLUDE_STDLIB_H
#include <stdlib.h>
#endif

#include "common.h"
#include "main.h"
#include "admin.h"
#include "nyuukai.h"

extern int akicode_tbl[ MEMBER_MAX + 1 ];			/* ±·º°ÄÞ Ë®³ */
extern int codedata_tbl[ MEMBER_MAX ];				/* º°ÄÞÃÞ°À À²¼®³ Ë®³ */

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
//	printf("7[%s:%d]\n", __FILE__, __LINE__);
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
        printf( "\n 2: Show the codedata_tbl" );
        printf( "\n 3: Delete a record" );
        //printf( "\n 3: Get a record from the akicode_tbl" );
        printf( "\n 4: Create dummy data" );
        printf( "\n E: Back to the main menu" );
        printf( "\n Q: Quit the program" );
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
				akicode_tbl_disp();
				printf("\nShow the akicode_tbl"
						" => complete\n");
				break;
            
            /* get a record from the akicode_tbl     */
			case '2':
				codedata_tbl_disp();
				printf("\nget_record_from_akicode_tbl"
						" => complete\n");
				break;
            
            /* get a record from the akicode_tbl     */
			case '3':
				touroku_sakujyo();
				printf("\nget_record_from_akicode_tbl"
						" => complete\n");
				break;
            
            /* get a record from the akicode_tbl     */
			case '4':
				create_dummy_data();
				printf("\nget_record_from_akicode_tbl"
						" => complete\n");
				break;
            
            /* get codedata_tbl     */
			
            /* back to main         */
			case 'E':
			case 'e':
				/* show message	*/
				printf("\n\tLeave the admin\n");
				loop = FALSE;
				break;
                
            /* Quit             */
			case 'Q':
			case 'q':
				/* show message	*/
				printf("\n\tQuit\n");
                exit(0);

			default:
				printf( "\n Æ­³Ø®¸ Ð½ ÃÞ½" );
				break;
        }//switch( work[ 0 ] )
	}//while (loop)
}//void start_admin( void )

static void get_akicode_tbl( void )
{
    //debug
    printf("static void get_akicode_tbl( void )\n");
}//static void get_akicode_tbl( void )

static void get_record_from_akicode_tbl(void)
{
    /* vars         */
    int         ret;    /* result       */
    char        *fname = AKICODE_TBL_NAME;  /* file name    */
    FILE        *fp;
    int         value;  /* value of the record in the akicode_tbl   */
    char        line[10];  /* input line   */
    int         index;  /* index for fseek  */
    
    
    /* setup the table      */
    /* open the file    */
    if( (fp = fopen( fname, "rb" )) == NULL ) {
        printf( "\n ±· º°ÄÞË®³ Ì§²Ù OPEN ´×°" );
        exit(1);
    }

    /* input the number     */
    printf("Input number: ");
    fflush(stdin);
    fgets(line, sizeof(line), stdin);
    line[strlen(line) - 1] = '\0';
    //debug
    printf("line=%s\n", line);
    index = atoi(line);
    //debug
    printf("index=%d\n", index);
    
    /* seek the location    */
    //ret = fseek(fp, 10 * sizeof(akicode_tbl[0]), SEEK_SET);
    ret = fseek(fp, index * sizeof(akicode_tbl[0]), SEEK_SET);
    if (ret != OK) {
        printf("[%d] File seek error\n", __LINE__);
        fclose(fp);        
        exit(1);
    } else {//if (ret != OK)
    }//if (ret != OK)
    
    /* read the data        */
    //ret = fread((char*)value, sizeof(akicode_tbl[0]), 1, fp);
    ret = fread((char*)&value, sizeof(akicode_tbl[0]), 1, fp);
    if (ret != 1) {
        printf("[%d] Read error\n", __LINE__);
        exit(1);
    } else {//if (ret != 1)
        printf("A record loaded\n");
    }//if (ret != 1)
    
    /* show: data           */
    printf("value(record: %d)=%d\n", index, value);
    
}//static void get_record_from_akicode_tbl(void)

static int create_dummy_data( void )
{
    /* vars         */
    int         ret;    /* result       */
    char        *fname = AKICODE_TBL_NAME;  /* file name    */
    FILE        *fp;
    int         value;  /* value of the record in the akicode_tbl   */
    char        line[10];  /* input line   */
    int         index;  /* index for fseek  */
    long        fptr;   /* file pointer     */
    int         kaiin_code;
    
    /* Processes
     * 1. Read akicode_tbl
     * 2. Update akicode_tbl
     * 3. keisoku_tbl_add()
     * 4. codedata_tbl_update()
     */
    /* Read: akicode_tbl        */
//    ret = akicode_tbl_read();
    ret = akicode_tbl_read();
    
    /* 2. Update akicode_tbl    */
    ret = akicode_tbl_update();
    
    kaiin_code = akicode_tbl[1] - 1;
    printf("New code registered: %d\n", kaiin_code);
    
    /* 3. keisoku_tbl_add()     */
    ret = keisoku_tbl_add(&fptr, kaiin_code);
    printf("A new keisoku_tbl record added\n");
    
    /* 4. codedata_tbl_update() */
    ret = codedata_tbl_update( kaiin_code, fptr );
    printf("codedata_tbl updated\n");
    
    //debug
    
    printf("\n[%s:%d]\n", __FILE__, __LINE__);
    printf("ret=%d\n", ret);
    
    /* Return       */
    return ret;
    
}//static int create_dummy_data( void )

static int akicode_tbl_disp( void )
{
    /* Processes
     * 1. Read akicode_tbl
     * 2. Show akicode_tbl
     */
    /* vars             */
    int         ret;    /* return value     */
    int         i;      /* index            */
    
    /* 1. Read akicode_tbl      */
    ret = akicode_tbl_read();
    
    /* 2. Show akicode_tbl      */
    for (i = 0; i < 10; i++) {
        printf("akicode_tbl[%d]=%d\n", i, akicode_tbl[i]);
    }//for (i = 0; i < 10; i++)
    
    /* Return           */
    return ret;
}//static int akicode_tbl_disp( void )

static int codedata_tbl_disp( void )
{
    /* Processes
     * 1. Read codedata_tbl
     * 2. Show codedata_tbl
     */
    /* vars             */
    int         ret;    /* return value     */
    int         i;      /* index            */
    
    /* 1. Read codedata_tbl      */
    ret = codedata_tbl_read();
    
    /* 2. Show codedata_tbl      */
    for (i = 0; i < 10; i++) {
        printf("codedata_tbl[%d]=%d\n", i, codedata_tbl[i]);
    }//for (i = 0; i < 10; i++)
    
    /* Return           */
    return ret;
}//static int codedata_tbl_disp( void )

static int codedata_tbl_read( void )
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
    
    /* return       */
    return ret;
}//static codedata_tbl_read( void )

/*
printf("\n[%s:%d]\n", __FILE__, __LINE__);
*/
