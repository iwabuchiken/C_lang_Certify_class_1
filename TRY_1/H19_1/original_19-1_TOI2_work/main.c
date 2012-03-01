/***********************************/
/*  main.c                         */
/*   ������ ���� ���ް ��� ��۸��� */
/***********************************/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "common.h"
#include "main.h"
#include "nyuukai.h"
#include "keisoku.h"
#include "sakujyo.h"

/***********************************/
/* ���³ �ް�                      */
/***********************************/

/* ������ ˮ� */
int akicode_tbl[ MEMBER_MAX + 1 ];

/* �����ް� ����� ˮ� */
int codedata_tbl[ MEMBER_MAX ];

/* ������� ���� �ް�ˮ� */
struct KEISOKU_TBL kojin_keisoku_tbl;

/* ��� ֳ ���� �ް� ˮ� */
struct KEISOKU_TBL sort_keisoku_tbl[ MEMBER_MAX ];


/***********************************/
/* ���ް ��� ��۸���               */
/*  Ҳ�                            */
/*   ���Ұ� : ż                   */
/*   ����   : ż                   */
/***********************************/
int main( void )
#ifdef TOI2
{
    int    loop = TRUE;			/* ٰ�� �׸�                */
    char   work[ 128 ];			/* ƭ�خ� ܰ�               */
    FILE   *fp;				/* ̧�� �߲��               */
    char   *fname1 = AKICODE_TBL_NAME;	/* �� ���� ˮ� ̧��         */
    char   *fname2 = CODEDATA_TBL_NAME;	/* ���� �ް� ����� ˮ� ̧�� */
    int	   i;				/* ���ޯ��		    */

    /* �� ���� ˮ� ̧�� OPEN -> NULL ? */
    if( (fp = fopen( fname1, "rb" )) == NULL ) {
        printf( "\n �� ���� ˮ� ̧�� � ���� �òϽ�" );

        /* �� ���� ˮ� ̧�� ���� */
        akicode_tbl_create( );
    }
    else {
        /* �� ���� ˮ� ̧�� CLOSE */
        fclose( fp );
    }

    /* ���� �ް� ����� ˮ� ̧�� OPEN -> NULL ? */
    if( (fp = fopen( fname2, "rb" )) == NULL ) {
        printf( "\n ���� �ް� ����� ˮ� ̧�� � ���� �òϽ�" );

        /* ���� �ް� ����� ˮ� ̧�� ���� */
        codedata_tbl_create( );
    }
    else {
        /* ���� �ް� ����� ˮ� ̧�� CLOSE */
        fclose( fp );
    }

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
        printf( "\n 2:���� �۸ ƭ�خ�" );
        printf( "\n 3:ĳ۸ ���ޮ" );
        printf( "\n 4:�߲��ˮ���");
        printf( "\n 5:�ް��ˮ���");
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

            case '2':       /* ���� �۸ ����� */
                keisoku_input( );
                break;

            case '3':       /* ĳ۸ ���ޮ     */
                touroku_sakujyo( );
                break;

            case '4':       /* �߲��ˮ���     */
                point_rank( );
                break;

            case '5':       /* �ް�ˮ���     */
                show_data( );
                break;

            case 'e':       /* ���خ�         */
            case 'E':
                loop = FALSE;
                break;

            default:
                printf( "\n ƭ�خ� н �޽" );
                break;
        }
    }
    return OK;
}
#else
{
	int    loop = TRUE;			/* ٰ�� �׸�                */
	char   work[ 128 ];			/* ƭ�خ� ܰ�               */
	FILE   *fp;				/* ̧�� �߲��               */
	char   *fname1 = AKICODE_TBL_NAME;	/* �� ���� ˮ� ̧��         */
	char   *fname2 = CODEDATA_TBL_NAME;	/* ���� �ް� ����� ˮ� ̧�� */
	int	   i;				/* ���ޯ��		    */

	/* �� ���� ˮ� ̧�� OPEN -> NULL ? */
	if( (fp = fopen( fname1, "rb" )) == NULL ) {
		printf( "\n �� ���� ˮ� ̧�� � ���� �òϽ�" );

		/* �� ���� ˮ� ̧�� ���� */
		akicode_tbl_create( );
	}
	else {
		/* �� ���� ˮ� ̧�� CLOSE */
		fclose( fp );
	}

	/* ���� �ް� ����� ˮ� ̧�� OPEN -> NULL ? */
	if( (fp = fopen( fname2, "rb" )) == NULL ) {
		printf( "\n ���� �ް� ����� ˮ� ̧�� � ���� �òϽ�" );

		/* ���� �ް� ����� ˮ� ̧�� ���� */
		codedata_tbl_create( );
	}
	else {
		/* ���� �ް� ����� ˮ� ̧�� CLOSE */
		fclose( fp );
	}

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
		printf( "\n 2:���� �۸ ƭ�خ�" );
		printf( "\n 3:ĳ۸ ���ޮ" );
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

			case '2':       /* ���� �۸ ����� */
				keisoku_input( );
				break;

			case '3':       /* ĳ۸ ���ޮ     */
				touroku_sakujyo( );
				break;

			case 'e':       /* ���خ�         */
			case 'E':
				loop = FALSE;
				break;

			default:
				printf( "\n ƭ�خ� н �޽" );
				break;
		}
	}
	return OK;
}
#endif

/************************************/
/* ���ް ��� ��۸���                */
/*  ƭ��� ĳ۸ ���                  */
/*   �� ���� ˮ� ̧�� ����          */
/*   ���Ұ� : ż                    */
/*   ����   : 0:OK                  */
/*           -1:NG                  */
/************************************/
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

    return ret;
}



/************************************/
/* ���ް ��� ��۸���                */
/*  ƭ��� ĳ۸ ���                  */
/*   ���� �ް� ����� ˮ� ̧�� ����  */
/*   ���Ұ� : ż                    */
/*   ����   : 0:OK                  */
/*           -1:NG                  */
/************************************/
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

    return ret;
}



/************************************/
/* ���³ ٰ��                       */
/************************************/


/************************************/
/* ���ް ��� ��۸���                */
/*  ƭ��� ĳ۸ ���                  */
/*   �� ���� ˮ� ̧�� READ          */
/*   ���Ұ� : ż                    */
/*   ����   : 0:OK                  */
/*           -1:NG                  */
/************************************/
int akicode_tbl_read( void )
{
    int     ret;				/* ���� ����        */
    int     i;					/* ���ޯ��          */
    FILE    *fp;				/* ̧�� �߲��       */
    char    *fname = AKICODE_TBL_NAME;		/* �� ���� ˮ� ̧�� */

    /* �� ���� ˮ� ̧�� OPEN -> NULL ? */
    if( (fp = fopen( fname, "rb" )) == NULL ) {
        printf( "\n �� ���� ˮ� ̧�� OPEN �װ" );
        return NG;
    }

    for( i = 0; i < MEMBER_MAX + 1; i++ ) {
        /* �� ���� ˮ� ̧�� READ -> 1��޲ ? */
        if( (ret = fread( (char *)&akicode_tbl[ i ], sizeof( int ), 1, fp ) )
                   != 1 ) {
            /* READ �װ �� ? */
            if( ferror( fp ) != 0 ) {
                printf( "\n �� ���� ˮ� ̧�� READ �װ" );
                ret = NG;
            }
            else {
                /* ̧�� EOF �� Ų ? */
                if( feof( fp ) == 0 ) {
                    printf( "\n �� ���� ˮ� ̧�� READ �װ" );
                    ret = NG;
                }
                else {
                    ret = OK;
                }
            }
            break;
        }
#ifdef DEBUG
        printf("[%s:%d]\n", __FILE__, __LINE__);
        printf("akicode_tbl[%d]=%d\n",
        			i, akicode_tbl[i]);
        printf("\n");
#endif
    }

#ifdef DEBUG
    /* Show a part of akicode_tbl[] */
    printf("[%s:%d]\n", __FILE__, __LINE__);
    printf("akicode_tbl[]\n");
    for(i = 0; i < 10; i++) {
    	printf("akicode_tbl[%d]=%c(%%d=%d)\n",
    			i, akicode_tbl[i], akicode_tbl[i]);

    }
    printf("\n");
#endif

    /* �� ���� ˮ� ̧�� CLOSE */
    fclose( fp );

    return ret;
}



/***********************************/
/* ���ް ��� ��۸���               */
/*  ƭ�خ� ����                    */
/*   ���Ұ� : ���� ү����          */
/*   ����   : 0:OK                 */
/*           -1:NG                 */
/***********************************/
int kakunin_input( char *msg )
{
    int     ret;            /* ���� ����    */
    int     loop = TRUE;    /* ٰ�� �׸�    */
    char    work[ 128 ];    /* ƭ�خ� ܰ�   */

    while( loop ) {
        /* ���� ˮ��� */
        printf( msg );
        printf( "\n ? " );

        /* Y/N ƭ�خ� */
        work[ 0 ] = '\0';
        scanf( "%s", work );

        /* ƭ�خ� ���� ���� -> 1��޲ ? */
        if( strlen( work ) != 1 ) {
            printf( "\n ƭ�خ� н �޽" );
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
                printf( "\n ƭ�خ� н �޽" );
                break;
        }
    }

    return ret;
}



/************************************/
/* ���ް ��� ��۸���                */
/*   ���� ���� �ް� ˮ� ̧�� READ   */
/*   ���Ұ� : ���ݺ���              */
/*   ����   : 0:OK                  */
/*           -1:NG                  */
/************************************/
int kojin_data_read( int kaiin_code )
{
    int     ret;				/* ���� ����                */
    FILE    *fp;				/* ���� �ް� ˮ� ̧�� �߲�� */
    long    fptr;				/* ���� �ް� ̧�� �߲��     */
    char    *fname = KEISOKU_TBL_NAME;		/* ���� �ް� ˮ� ̧��       */

    /* ���� �ް� ˮ� ̧�� OPEN -> NULL ? */
    if( (fp = fopen( fname, "rb" )) == NULL ) {
        printf( "\n ���� �ް� ˮ� ̧�� OPEN �װ" );
        return NG;
    }

    /* �޲ĳ �ް� �߲�� ��� */
    fptr = ( codedata_tbl[ kaiin_code - 1 ] - 1 ) *
             sizeof( struct KEISOKU_TBL );

    /* ���� �ް� ˮ� ̧�� � ����� � �� ��� SEEK -> OK ? */
    if( (ret = fseek( fp, fptr, SEEK_SET )) != OK ) {
        printf( "\n ���� �ް� ˮ� ̧�� SEEK �װ" );

        /* ���� �ް�  ˮ� ̧�� CLOSE */
        fclose( fp );
        return NG;
    }

    /* ���� �ް� ˮ� ̧�� READ -> 1��޲ ? */
    if( (ret = fread( (char *)&kojin_keisoku_tbl, sizeof( kojin_keisoku_tbl ),
               1, fp )) != 1 ) {
        printf( "\n ���� �ް� ˮ� READ �װ" );
        ret = NG;
    }
    else {
        ret = OK;
    }

    /* ���� �ް�  ˮ� ̧�� CLOSE */
    fclose( fp );

    return ret;
}



/************************************/
/* ���ް ��� ��۸���                */
/*   ���� �ް� ˮ���                */
/*   ���Ұ� : ���ݺ���              */
/*            ˮ��� ү����          */
/*   ����   : ż                    */
/************************************/
#ifdef TOI2
void kojin_data_disp( int kaiin_code, char *msg )
{
    printf( msg );
    printf( "\n ���ݺ��� %3d", kaiin_code );

    /* �|�C���g�̕\�� */
    printf( "\n\n    �߲�� " );
    printf( "%3d", kojin_keisoku_tbl.point);

    if( kojin_keisoku_tbl.count != 0 ) {
        printf( "\n\n ��������   ���� ��޹   �ް�     " );
        printf( "���� ��޹   �ް�     ���� ��޹   �ް�" );

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

        printf( "\n\n    1��ϴ   2��ϴ   3��ϴ   4��ϴ   ");
        printf( "5��ϴ   6��ϴ   7��ϴ   8��ϴ   9��ϴ" );

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
        printf( "    ���� �ް� �� ��Ͼ�" );
	return;
	}
    return;
}//void kojin_data_disp( int kaiin_code, char *msg )
#else
void kojin_data_disp( int kaiin_code, char *msg )
{
    printf( msg );
    printf( "\n ���ݺ��� %3d", kaiin_code );

    if( kojin_keisoku_tbl.count != 0 ) {
        printf( "\n\n ��������   ���� ��޹   �ް�     " );
        printf( "���� ��޹   �ް�     ���� ��޹   �ް�" );

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

        printf( "\n\n    1��ϴ   2��ϴ   3��ϴ   4��ϴ   ");
        printf( "5��ϴ   6��ϴ   7��ϴ   8��ϴ   9��ϴ" );

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
        printf( "    ���� �ް� �� ��Ͼ�" );
	return;
	}
    return;
}//void kojin_data_disp( int kaiin_code, char *msg )
#endif


/************************************/
/* ���ް ��� ��۸���                */
/*   ���� �ް� ����                 */
/*   ���Ұ� : ż                    */
/*   ����   : ���� �ް�             */
/************************************/
#ifdef TOI2
struct KEISOKU_TBL init_kojin_keisoku_tbl( void )
{
	static struct KEISOKU_TBL tbl = {
		0, 0, "        ", 0, "        ", 0, "        ", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0
	};
	return tbl;
}
#else
struct KEISOKU_TBL init_kojin_keisoku_tbl( void )
{
	static struct KEISOKU_TBL tbl = {
		0, 0, "        ", 0, "        ", 0, "        ", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
	return tbl;
}
#endif

#ifdef TOI2
/************************************/
/* ���ް ��� ��۸���                */
/*   �|�C���g�f�[�^�̍쐬           */
/*   ���Ұ� :                     */
/*   ����   :              */
/************************************/

/************************************/
/* ���ް ��� ��۸���                */
/*   �l�f�[�^�̕\��                 */
/*   ���Ұ� : ���ID�ikaiin_code�j                    */
/*   ����   : -1 => No entry with the id             */
/*			  1  => Display successful */
/************************************/
int  show_data( void )
{
	char	buf[10];	/* scan���镶����̂��߂ɁA�P���o�b�t�@�[ */
	int		kaiin_code;	/* ����R�[�h */

	int		i;			/* �C���f�b�N�X */

    int     ret;				/* ���� ����                */
    FILE    *fp;				/* ���� �ް� ˮ� ̧�� �߲�� */
    long    fptr;				/* ���� �ް� ̧�� �߲��     */
    char    *fname = CODEDATA_TBL_NAME;		/* ���� �ް� ˮ� ̧��       */

    /* ���� �ް� ˮ� ̧�� OPEN -> NULL ? */
    if( (fp = fopen( fname, "rb" )) == NULL ) {
        printf( "\n ���� �ް� ˮ� ̧�� OPEN �װ" );
        return NG;
    }

    /* �R�[�h�\�f�[�^�@=>�@�ǂݍ��� */
    if( (ret = fread( (char *)codedata_tbl,
    		sizeof( codedata_tbl ), 1, fp ) ) != 1 ) {
		printf( "\n ���� �ް� ����� ˮ� ̧�� READ �װ" );
		ret = NG;
	}

	/* �o�b�t�@�[���t���b�V�����Ă��� */
	fflush(stdin);

	while (1) {
		/* �R�[�h�ԍ��̓��� */
		printf("����R�[�h����͂��Ă��������F");
		fgets(buf, sizeof(buf), stdin);

		/* buf ��\�� */
		printf("[%s:%d]\n", __FILE__, __LINE__);
		printf("buf=%s(%d)\n", buf, *buf);

		/* ���l�������ǂ������� */
		buf[strlen(buf) - 1] = '\0';
		if( strspn( buf, "1234567890" )
				< strlen( buf ) ) {
			printf( "\n ��� ��޲ �� ƭ�خ� ��ϼ�" );
			continue;
		}
		else
			break;
		/*
		if (isdigit(buf))
			break;

		else
			printf("���l�ȊO�̕����ł� => %s\n", buf);
*/
	}//while (1) {

	/* ���͂��ꂽ�ԍ����A���łɓo�^����Ă��邩���� */
	//if (codedata_tbl[atoi(buf)] == 0) {
	if (codedata_tbl[atoi(buf) - 1] == 0) {
		printf("codedata_tbl[atoi(buf) - 1]=%d\n",
					codedata_tbl[atoi(buf) - 1]);
		printf("atoi(buf) - 1 = %d\n", atoi(buf) - 1);
		printf("The id %d is not registered yet.\n",
				atoi(buf));
		return -1;
	}

	/* �o�^�f�[�^�@=>�@�\�� */
	printf("<Showing the data for ID %d ...>\n",
					atoi(buf));

	/* �l�f�[�^�@=>�@�ǂݍ��� */
	kojin_data_read(atoi(buf));

	/* �\�� */
	kojin_data_disp(atoi(buf), "Data\n");

/*
	printf("Showing the data for Kaiin ID %d ...\n",
				atoi(buf));
	printf("\tNow building the program. Sorry.\n");
*/
	return 0;

}//int  show_data(int kaiin_code)

static int point_rank( void )
{
    int     ret;						/* ���� ����            */
    int     i;							/* ���ޯ��              */
    FILE    *fp;						/* ̧�� �߲��           */
    char    *fname = KEISOKU_TBL_NAME;				/* ���� �ް� ˮ� ̧��   */

    //debug
    printf("[%s:%d]\n", __FILE__, __LINE__);
    printf("Start point rank\n");

    /* ���� �ް� ˮ� ̧�� OPEN -> NULL ? */
    if( (fp = fopen( fname, "rb" )) == NULL ) {
        printf( "\n ���� �ް� ˮ� ̧�� OPEN �װ" );
        return NG;
    }

    /* sort_keisoku_tbl[] => set */
    i = 0;
    for( ; ; ) {

        /* ���� �ް� ˮ� ̧�� READ -> 1��޲ ? */
        if( (ret = fread( (char *)&sort_keisoku_tbl[ i ],
                   sizeof( struct KEISOKU_TBL ), 1, fp )) != 1 ) {

            /* READ �װ ? */
            if( ferror( fp ) != 0 ) {
                printf( "\n ���� �ް� ˮ� ̧�� READ �װ" );
                ret = NG;
            }
            else {
                /* ̧�� EOF �� Ų ? */
                if( feof( fp ) == 0 ) {
                    printf( "\n ���� �ް� ˮ� ̧�� READ �װ" );
                    ret = NG;
                }
                else {
                    ret = OK;
                }
            }
        }

        /* READ �װ ? */
        if( ret == NG ) {
            break;
        }

        /* ���� �ް� �� ? */
        if( sort_keisoku_tbl[ i ].count != 0 ) {
            i++;
        }

        /* eof ? */
        if( ret == OK ) {
            break;
        }
    }//for( ; ; ) {

    /* ���� �ް� ˮ� ̧�� CLOSE */
    fclose( fp );

    if( ret == OK ) {
        /* ���� �ް� ��� */
    	point_sort( i );
        /* ���� �ް� ��� ��� ˮ��� */
    	point_disp( i );
    }

    //debug
    printf("\n\n[%s:%d]\n", __FILE__, __LINE__);
    printf("[Exit: point_rank()\n]");

    return ret;
}//static int point_rank( int cnt )

static void point_sort( int cnt )
{
    int     i;                  	/* ���ޯ��      */
    int     j;                  	/* ���ޯ��      */
    struct  KEISOKU_TBL  work;  	/* �ܯ�� ֳ �ر */

    /* �ް� ��� */
    for( i = 0; i < cnt - 1; i++ ) {
        for( j = i + 1; j < cnt; j++ ) {
            if( sort_keisoku_tbl[ i ].point <
                sort_keisoku_tbl[ j ].point ) {

				work = sort_keisoku_tbl[ i ];
                sort_keisoku_tbl[ i ] = sort_keisoku_tbl[ j ];
                sort_keisoku_tbl[ j ] = work;
            }
        }
    }
	return;
}//static void point_sort( int cnt )

static void point_disp( int cnt )
{
    int     i;  /* ���ޯ��  */

    printf( "\n\n ** �ޭݲ ˮ� (�߲�ļޭ�) **" );
    printf( "\n �ޭݲ ���ݺ���  �߲��" );

    for( i = 0; i < cnt; i++ ) {

        /* 10� ��� ˮ��� �� */
        if( i >= 10 ) {
            break;
        }

        printf( "\n   %2d   %3d        %4d",
        	i + 1,
            sort_keisoku_tbl[ i ].kaiin_code,
            sort_keisoku_tbl[ i ].point );
    }
	return;
}//static void point_disp( int cnt )

#endif//#ifdef TOI2

/*
 * printf("[%s:%d]\n", __FILE__, __LINE__);
 */
