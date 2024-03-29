
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
        printf( "\n  ������ ���� ���ް ��� ��۸���: admin " );
        printf( "\n *************************************" );
        printf( "\n ��� � ���� �ø�޻�" );
        printf( "\n 1: get the akicode_tbl" );
        printf( "\n 2: get the codedata_tbl" );
        printf( "\n 3: get the keisoku_tbl" );
        printf( "\n E:���خ�" );
        printf( "\n ? " );

        /* ��ظ��� ƭ�خ� */
        work[ 0 ] = '\0';
        scanf( "%s", work );

        /* ƭ�خ� ���� ���� -> 1��޲ ? */
        if( strlen( work ) != 1 ) {
            printf( "\n ƭ�خ� н �޽" );
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
				printf( "\n ƭ�خ� н �޽" );
				break;
        }//switch( work[ 0 ] )
	}//while (loop)
}//void start_admin( void )
