/***********************************/
/*  main.c                         */
/*   ������ ���� ���ް ��� ��۸��� */
/***********************************/
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "main.h"
#include "admin.h"
#include "nyuukai.h"

/***********************************/
/* ���³ �ް�                      */
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
/* ���ް ��� ��۸���               */
/*  Ҳ�                            */
/*   ���Ұ� : ż                   */
/*   ����   : ż                   */
/***********************************/
int main( void )
{
    /* vars         */
    int         work[128];  /* input line       */
    int         loop    = TRUE; /* flag         */
    int         i;          /* index            */
    FILE   *fp;				/* ̧�� �߲��               */
    char   *fname1 = AKICODE_TBL_NAME;	/* �� ���� ˮ� ̧��         */
    char   *fname2 = CODEDATA_TBL_NAME;	/* ���� �ް� ����� ˮ� ̧�� */
    
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
        printf( "\n �� ���� ˮ� ̧�� � ���� �òϽ�" );

        /* �� ���� ˮ� ̧�� ���� */
        akicode_tbl_create( );
    }else {
        /* �� ���� ˮ� ̧�� CLOSE */
        fclose( fp );
    }
    
    /* Create: codedata_tbl.tbl     
     * 1. The processes are same as that in akicode_tbl.tbl above
     */
    if( (fp = fopen( fname2, "rb" )) == NULL ) {
        printf( "\n ���� �ް� ����� ˮ� ̧�� � ���� �òϽ�" );

        /* ���� �ް� ����� ˮ� ̧�� ���� */
        codedata_tbl_create( );
    }
    else {
        /* ���� �ް� ����� ˮ� ̧�� CLOSE */
        fclose( fp );
    }
    
    /* loop         */
    while( loop ) {
        /* ð��� ��� �ر */
		akicode_tbl[ 0 ] = 0;
		for( i = 0; i < MEMBER_MAX; i++) {
			akicode_tbl[ i + 1 ] = 0;
			codedata_tbl[ i ] = 0;
			sort_keisoku_tbl[ i ] = init_kojin_keisoku_tbl();
		}
		kojin_keisoku_tbl = init_kojin_keisoku_tbl();

        printf( "\n" );
        printf( "\n *******************************" );
        printf( "\n  ������ ���� ���ް ��� ��۸��� " );
        printf( "\n *******************************" );
        printf( "\n ��� � ���� �ø�޻�" );
        printf( "\n 1:ƭ��� ĳ۸" );
#ifdef ADMIN        
        printf( "\n 9:admin" );
#endif
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

        switch( work[ 0 ] ) {
            case '1':       /* ƭ��� ĳ۸     */
                nyuukai_touroku( );
                break;

            case '9':       /* admin     */
                start_admin( );
                break;

            case 'e':       /* ���خ�         */
            case 'E':
                loop = FALSE;
                break;

            default:
                printf( "\n ƭ�خ� н �޽" );
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
    int     ret;				/* ���� ����        */
    int     i;					/* ���ޯ��          */
    FILE    *fp;				/* ̧�� �߲��       */
    char    *fname = AKICODE_TBL_NAME;		/* �� ���� ˮ� ̧�� */

    /* �� ���� �ݼ�� */
    akicode_tbl[ 0 ] = MEMBER_MAX;
    for( i = 1; i < MEMBER_MAX + 1; i++ ) {
        akicode_tbl[ i ] = i;
    }

    /* �� ���� ˮ� ̧�� OPEN -> NULL ? */
    if( (fp = fopen( fname, "w+b" )) == NULL ) {
        printf( "\n �� ����ˮ� ̧�� OPEN �װ" );
        return NG;
    }

    /* �� ���� ˮ� ̧�� WRITE -> 1��޲ ? */
    if( (ret = fwrite( (char *)akicode_tbl, sizeof( akicode_tbl ), 1, fp ) )
               != 1 ) {
        printf( "\n �� ����ˮ� ̧�� WRITE �װ" );
        ret = NG;
    }
    else {
        ret = OK;
    }

    /* �� ���� ˮ� ̧�� CLOSE */
    fclose( fp );

    //debug
    printf("File created: %s\n", AKICODE_TBL_NAME);

    return ret;

    //debug
    //printf("static int akicode_tbl_create( void )\n");
}//static int akicode_tbl_create( void )

static int codedata_tbl_create( void )
{
    int     ret;                        	/* ���� ����                */
    FILE    *fp;                        	/* ̧�� �߲��               */
    char    *fname = CODEDATA_TBL_NAME;		/* ���� �ް� ����� ˮ� ̧�� */
    int	    i;					/* ���ޯ��		    */

    /* ���� �ް� ����� ˮ� ̧�� OPEN -> NULL ? */
    if( (fp = fopen( fname, "w+b" )) == NULL ) {
        printf( "\n ���� �ް� ����� ˮ� ̧�� OPEN �װ" );
        return NG;
    }

	for( i = 0; i < MEMBER_MAX; i++ )
		codedata_tbl[ i ] = 0;

    /* ���� �ް� ����� ˮ� ̧�� WRITE -> 1��޲ ? */
    if( (ret = fwrite( (char *)codedata_tbl, sizeof( codedata_tbl ), 1, fp ) )
               != 1 ) {
        /* WRITE �װ */
        printf( "\n ���� �ް� ����� ˮ� ̧�� WRITE �װ" );
        ret = NG;
    }
    else {
        ret = OK;
    }

    /* ���� �ް� ����� ˮ� ̧�� CLOSE */
    fclose( fp );

    //debug
    printf("File created: %s\n", CODEDATA_TBL_NAME);
    
    return ret;
}//static int codedata_tbl_create( void )
