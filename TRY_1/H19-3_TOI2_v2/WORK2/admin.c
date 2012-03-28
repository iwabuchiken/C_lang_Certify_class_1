
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
        printf( "\n 1: Get the akicode_tbl" );
        printf( "\n 2: Get a record from the akicode_tbl" );
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
            
            /* get a record from the akicode_tbl     */
			case '2':
				get_record_from_akicode_tbl();
				printf("\nget_record_from_akicode_tbl"
						" => complete\n");
				break;
            
            /* get codedata_tbl     */
			
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

static int akicode_tbl_read(void)
{
    int         ret;    /* result       */
    char        *fname = AKICODE_TBL_NAME;  /* file name    */
    FILE        *fp;
    //int         loop;   /* flag for while loop  */
    
    //while (loop) {
    /* open the file    */
    if( (fp = fopen( fname, "rb" )) == NULL ) {
        printf( "\n ±· º°ÄÞË®³ Ì§²Ù OPEN ´×°" );
        return NG;
    }

    /* read data        */
    ret = fread((char*)akicode_tbl, sizeof(akicode_tbl), 1, fp);
    if (ret != 1) {
        printf("Read error\n");
        return NG;
    } else {//if (ret != 1)
        printf("akicode_tbl loaded\n");
        return OK;
    }//if (ret != 1)

    //}//while (loop)

}//static void akicode_tbl_read(void)
