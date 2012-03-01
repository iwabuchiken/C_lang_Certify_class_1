/************************************/
/*  nyuukai.c                       */
/*    ƭ��� ĳ۸ ��� ��۸��� ̧��   */
/************************************/
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "main.h"
#include "nyuukai.h"

extern int akicode_tbl[ MEMBER_MAX + 1 ];			/* ������ ˮ� */
extern int codedata_tbl[ MEMBER_MAX ];				/* �����ް� ����� ˮ� */
extern struct KEISOKU_TBL kojin_keisoku_tbl;			/* ������� ���� �ް�ˮ� */

/***********************************/
/* ���ް ��� ��۸���               */
/*  ƭ��� ĳ۸ ���                 */
/*   Ҳ�                           */
/*   ���Ұ� : ż                   */
/*   ����   : 0:OK                 */
/*           -1:NG                 */
/***********************************/
int nyuukai_touroku( void )
{
#ifdef TOI2
    int    ret;             /* ���� ����        */
    int    kaiin_code;      /* ĳ۸ ���� ����   */
    long   fptr;            /* ̧�� �߲��       */
    char   msg[ 64 ];       /* ү���� �ر       */

    int    i;		/* akicode_tbl[] �p�̃C���f�b�N�X */

    /* �� ���� ˮ� READ -> NG ? */
	if( (ret = akicode_tbl_read( )) == NG ) {
        return ret;
	}

    /* �� ���� �� ? */
    if( akicode_tbl[ 0 ] <= 0 ) {
        printf( "\n �����Ŷ�� ��޲� ���ް � ���� ��Ͼ�\n" );
        ret = OK;
        return ret;
    }

#ifdef DEBUG_NYUUKAI
    /* �󂫃R�[�h�\�̓��e������ */
    show_akicode_tbl();
#endif

    /* akicode_tbl �́A�Y��1�Ԃ���n�߂� */
    i = 1;
    while (1) {
    	/* �L���R�[�h�̔ԍ����I�邩�A
    	 * �Y���ԍ����c�]�̗L���R�[�h�̐���
    	 * ��������A�Y���� i ���P�ɖ߂�
    	 */
    	if (akicode_tbl[i] == 0 ||
    			i > akicode_tbl[0])
    		i = 1;
		/* �� ���� ���� */
		sprintf( msg, "\n ���� ���� � %d �޽. �ۼ� �޽�( Y/N )", akicode_tbl[ i ] );
		if( (ret = kakunin_input( msg )) == OK ) {
			/* ĳ۸ ���� ���� ��� */
			kaiin_code = akicode_tbl[ i ];

			/* �� ���� ˮ� ���� -> OK ? */
			if( (ret = akicode_tbl_update2( i )) == OK ) {
				/* ���� �ް� ˮ� ²� -> OK ? */
				if( (ret = keisoku_tbl_add( &fptr, kaiin_code )) == OK ) {

					/* ���� �ް� ����� ˮ� ���� */
					ret = codedata_tbl_update( kaiin_code, fptr );
				}
			}
			break;
		} else {
		/* kakunin_input() �̖߂�l�� OK
		 * �ł͂Ȃ�������A
		 * �P�D�Y���� i ���P���₷
		 * �Q�Dwhile ���[�v���J��Ԃ�
		 */
			i++;
		}//if( (ret = kakunin_input( msg )) == OK )

    }//while(1)

    if( ret == OK ) {
        printf( "\n ƭ��� ĳ۸ ��� �� ���خ� �ϼ�" );
    }

    return ret;
#else
    int    ret;             /* ���� ����        */
    int    kaiin_code;      /* ĳ۸ ���� ����   */
    long   fptr;            /* ̧�� �߲��       */
    char   msg[ 64 ];       /* ү���� �ر       */

    /* �� ���� ˮ� READ -> NG ? */
	if( (ret = akicode_tbl_read( )) == NG ) {
        return ret;
	}

    /* �� ���� �� ? */
    if( akicode_tbl[ 0 ] <= 0 ) {
        printf( "\n �����Ŷ�� ��޲� ���ް � ���� ��Ͼ�\n" );
        ret = OK;
        return ret;
    }

    while (1) {
		/* �� ���� ���� */
		sprintf( msg, "\n ���� ���� � %d �޽. �ۼ� �޽�( Y/N )", akicode_tbl[ 1 ] );
		if( (ret = kakunin_input( msg )) == OK ) {
			/* ĳ۸ ���� ���� ��� */
			kaiin_code = akicode_tbl[ 1 ];

			/* �� ���� ˮ� ���� -> OK ? */
			if( (ret = akicode_tbl_update( )) == OK ) {
				/* ���� �ް� ˮ� ²� -> OK ? */
				if( (ret = keisoku_tbl_add( &fptr, kaiin_code )) == OK ) {

					/* ���� �ް� ����� ˮ� ���� */
					ret = codedata_tbl_update( kaiin_code, fptr );
				}
			}
		}
		break;
    }//while(1)

    if( ret == OK ) {
        printf( "\n ƭ��� ĳ۸ ��� �� ���خ� �ϼ�" );
    }

    return ret;
#endif
}



/************************************/
/* ���ް ��� ��۸���                */
/*  ƭ��� ĳ۸ ���                  */
/*   �� ���� ˮ� ̧�� ����          */
/*   ���Ұ� : ż                    */
/*   ����   : 0:OK                  */
/*           -1:NG                  */
/************************************/
#ifdef TOI2
static int akicode_tbl_update2( int number )
{
    int     ret;					/* ���� ����        */
    int     i;						/* ���ޯ��          */
    int     cnt;					/* �� ���� ��       */
    FILE    *fp;					/* ̧�� �߲��       */
    char    *fname = AKICODE_TBL_NAME;  		/* �� ���� ˮ� ̧�� */

    int     akicode_tbl_tmp[ MEMBER_MAX + 1 ]; /* update ���́A��Ɣz�� */
    int     j;		/* akicode_tbl[] �p�̃C���f�b�N�X */
    int     k;		/* akicode_tbl_tmp[] �p�̃C���f�b�N�X */

    /* �� ���� �ݽ� ��� */
    cnt = akicode_tbl[ 0 ];

    /* �^�[�Q�b�g�̗v�f���[���ɂ��� */
    akicode_tbl[number] = 0;

    /* akicode_tbl[] ����בւ���
     * �P�Dakicode_tbl_tmp[] �ɁAakicode_tbl[] ��
     * 		�v�f�̂����A�O�o�Ȃ����̂��Aakicode_tbl_tmp[] ��
     * 		�擪�i�Y��=�O�j����A�������
     * �Q�Dakicode_tbl_tmp �ɓ��ꂽ���l��̖�����
     * 		�v�f�ɁA�O��������
     * �R�Dakicode_tbl_tmp ���� akicode_tbl �ցA
     * 		�c�]�f�[�^�̐��iakicode_tbl[0]�j�����A
     * 		akicode_tbl �̓Y���P�Ԃ��珇�ɁA�R�s�[����
     */

    /* 1 */
    for(j = 0, k = 0; j <= akicode_tbl[0]; j++) {
		if(akicode_tbl[j] != 0) {
			akicode_tbl_tmp[k] = akicode_tbl[j];
			++k;
		}//if(akicode_tbl[i] != 0) {
	}//for(i = 0; i < MEMBER_MAX + 1; i++) {

    /* 2 */
    akicode_tbl_tmp[k] = 0;

    /* 3 */
    for(i = 1; i <= akicode_tbl[0]; i++) {
		akicode_tbl[i] = akicode_tbl_tmp[i];
	}//for(i = 1; i < MEMBER_MAX + 1; i++) {

    /* �� ���� �ݽ� ��� */
    akicode_tbl[ 0 ] = cnt - 1;

    /* �� ���� ˮ� ̧�� OPEN -> NULL ? */
    if( (fp = fopen( fname, "w+b" )) == NULL ) {
        printf( "\n ������ ˮ� ̧�� OPEN �װ" );
        return NG;
    }

    /* �� ���� ˮ� ̧�� WRITE -> 1��޲ ? */
    if( (ret = fwrite( (char *)akicode_tbl,
               sizeof( int ) * (akicode_tbl[ 0 ] + 1), 1, fp )) != 1 ) {
        printf( "\n �� ���� ˮ� ̧�� WRITE �װ" );
        ret = NG;
    }
    else {
        ret = OK;
    }

    /* �� ���� ˮ� ̧�� CLOSE */
    fclose( fp );

    return ret;
}
#endif

static int akicode_tbl_update( void )
{
    int     ret;					/* ���� ����        */
    int     i;						/* ���ޯ��          */
    int     cnt;					/* �� ���� ��       */
    FILE    *fp;					/* ̧�� �߲��       */
    char    *fname = AKICODE_TBL_NAME;  		/* �� ���� ˮ� ̧�� */

    /* �� ���� �ݽ� ��� */
    cnt = akicode_tbl[ 0 ];

    /* �� ���� �ݼ�� */
    for( i = 1; i < cnt; i++ ) {
        if( akicode_tbl[ i + 1 ] == 0 ) {
            break;
        }
        akicode_tbl[ i ] = akicode_tbl[ i + 1 ];
    }

    akicode_tbl[ i ] = 0;

    /* �� ���� �ݽ� ��� */
    akicode_tbl[ 0 ] = cnt - 1;

    /* �� ���� ˮ� ̧�� OPEN -> NULL ? */
    if( (fp = fopen( fname, "w+b" )) == NULL ) {
        printf( "\n ������ ˮ� ̧�� OPEN �װ" );
        return NG;
    }

    /* �� ���� ˮ� ̧�� WRITE -> 1��޲ ? */
    if( (ret = fwrite( (char *)akicode_tbl,
               sizeof( int ) * (akicode_tbl[ 0 ] + 1), 1, fp )) != 1 ) {
        printf( "\n �� ���� ˮ� ̧�� WRITE �װ" );
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
/*   ���� �ް� ˮ� ̧�� ²�         */
/*   ���Ұ� : ���� �ް� �߲��       */
/*            ĳ۸ ���� ����        */
/*   ����   : 0:OK                  */
/*           -1:NG                  */
/************************************/
static int keisoku_tbl_add( long *fptr, int kaiin_code )
{
    int     ret;					/* ���� ����            */
    FILE    *fp;					/* ̧�� �߲��           */
    char    *fname = KEISOKU_TBL_NAME;			/* ���� �ް� ˮ� ̧��   */

    /* ���� �ް� ˮ� ̧�� OPEN -> NULL ? */
    if( (fp = fopen( fname, "a+b" )) == NULL ) {
        printf( "\n ���� �ް� ˮ� ̧�� OPEN �װ" );
        return NG;
    }

    /* ���� �ް� ˮ� ̧�� SEEK -> OK �� Ų ? */
    if( (ret = fseek( fp, 0L, SEEK_END )) != OK ) {
        printf( "\n ���� �ް� ˮ� ̧�� SEEK �װ" );
        /* ���� �ް� ˮ� ̧�� CLOSE */
        fclose( fp );
        return NG;
    }

    /* ̧�� �߲�� ��ĸ */
    *fptr = ftell( fp );

    /* ���� �ް� ˮ� �ر */
	kojin_keisoku_tbl = init_kojin_keisoku_tbl();

    /* ���� ���� ��� */
    kojin_keisoku_tbl.kaiin_code = kaiin_code;

    /* ����|�C���g�@=>�@�ݒ� */
    kojin_keisoku_tbl.point = 100;

    /* ���� �ް� ˮ� ̧�� WRITE -> 1��޲ ? */
    if( (ret = fwrite( (char *)&kojin_keisoku_tbl, sizeof( kojin_keisoku_tbl ),
               1, fp )) != 1 ) {
        printf( "\n ���� �ް� ˮ� ̧�� WRITE �װ" );
        ret = NG;
    }
    else {
        ret = OK;
    }

    /* ���� �ް� ˮ� ̧�� CLOSE */
    fclose( fp );

    return ret;
}



/************************************/
/* ���ް ��� ��۸���                */
/*  ƭ��� ĳ۸ ���                  */
/*   ���� �ް� ����� ˮ� ̧�� ����  */
/*   ���Ұ� : ĳ۸ ���� ����        */
/*            ���� �ް� �߲��       */
/*   ����   : 0:OK                  */
/*           -1:NG                  */
/************************************/
static int codedata_tbl_update( int kaiin_code, long fptr )
{
    int     ret;                        /* ���� ����                */
    FILE    *fp;                        /* ̧�� �߲��               */
    char    *fname = CODEDATA_TBL_NAME;	/* ���� �ް� ����� ˮ� ̧�� */

    /* ���� �ް� ����� ˮ� ̧�� OPEN -> NULL ? */
    if( (fp = fopen( fname, "r+b" )) == NULL ) {
        printf( "\n ���� �ް� ����� ˮ� ̧�� OPEN �װ" );
        return NG;
    }

    /* ���� �ް� ����� ˮ� ̧�� READ -> 1��޲ ? */
    if( (ret = fread( (char *)codedata_tbl, sizeof( codedata_tbl ), 1, fp ) )
               != 1 ) {
        printf( "\n ���� �ް� ����� ˮ� ̧�� READ �װ" );
        ret = NG;
    }
    else {
        /* �޲ĳ �ް� �߲�� ��� */
        codedata_tbl[ kaiin_code - 1 ] =
            (int)( (fptr / sizeof( struct KEISOKU_TBL )) + 1 );

        //debug
        printf("[%s:%d]\n", __FILE__, __LINE__);
        printf("codedata_tbl[ kaiin_code - 1 ]=%d\n\n",
        			codedata_tbl[ kaiin_code - 1 ]);

        /* ̧�� �߲�� � ��ĳ � SEEK -> OK �� Ų ? */
        if( (ret = fseek( fp, 0L, SEEK_SET )) != OK ) {
            printf( "\n ���� �ް� ����� ˮ� ̧�� SEEK �װ" );

            /* ���� �ް� ����� ˮ� ̧�� CLOSE */
            fclose( fp );
            return NG;
        }

        /* ���� �ް� ����� ˮ� ̧�� WRITE -> 1��޲ ? */
        if( (ret = fwrite( (char *)codedata_tbl, sizeof( codedata_tbl ), 1,
                   fp )) != 1 ) {
            printf( "\n ���� �ް� ����� ˮ� ̧�� WRITE �װ" );
            ret = NG;
        }
        else {
            ret = OK;
        }
    }

    /* ���� �ް� ����� ˮ� ̧�� CLOSE */
    fclose( fp );

    return ret;
}

static void show_akicode_tbl( void )
{
	int		i;	/* �C���f�b�N�X */

	printf("akicode_tbl[]= ");
	for (i = 0; i < MEMBER_MAX + 1; i++) {
		printf("%3d", akicode_tbl[i]);
	}
	printf("\n\n");
}//static int  show_akicode_tbl( void )
