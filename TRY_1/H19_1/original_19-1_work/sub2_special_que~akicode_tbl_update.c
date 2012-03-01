/************************************`
 * <Basics>
 *	1. File: sub2_special_que~akicode_tbl_update.c
 *	2. Author: Iwabuchi Ken				*
 *	3. Date: 20120202_075416
 * <Aim>
 *	1. �d�l�i�P�j�A���������邽�߂́A�L���[���
 * <New>
 * 	1. A new function: confirm_yes_no()
 * 		=> �z��� shuffle �𑱂��邩�A�m�F����B
 * <Usage>
 *	1.
 * <Source>
 *	1.
 * <Result>
 * 	1.
 ************************************/
#ifndef INCLUDE_STDIO
#define INCLUDE_STDIO
#include <stdio.h>
#endif
#ifndef INCLUDE_STDLIB
#define INCLUDE_STDLIB
#include <stdlib.h>
#endif
#ifndef INCLUDE_STRING
#define INCLUDE_STRING
#include <string.h>
#endif
#ifndef INCLUDE_TIME
#define INCLUDE_TIME
#include <time.h>
#endif
#ifndef INCLUDE_MATH
#define INCLUDE_MATH
#include <math.h>
#endif

//v=1.0
//created_at=20120202_072802
//project=C:\workspaces\ws_ubuntu_1\G20120202_072802_CExam_class1\main.c
#ifdef MAXNUM
#define MEMBER_MAX	    MAXNUM
#else
#define MEMBER_MAX	    5
#endif

#define AKICODE_TBL_NAME    "akicode.tbl"	/* ������ˮ� ̧�� Ҳ */
#define  TRUE          1    /* ��            */
#define  FALSE         0    /* ��            */
#define  OK            0    /* ���ޮ�        */
#define  CANCEL        1    /* ��� ����      */
#define  NG           -1    /* ��ޮ�         */
#define AKICODE_TBL_NAME    "akicode.tbl"	/* ������ˮ� ̧�� Ҳ */

int akicode_tbl[ MEMBER_MAX + 1 ];

/**********************************************
 * Prototypes
**********************************************/
static int akicode_tbl_create( void );
static int akicode_tbl_update( void );
static void show_akicode_tbl( void );
static int akicode_tbl_shuffle( int number );
static int akicode_tbl_shuffle2( int number );
static int confirm_yes_no( void );

/**********************************************
 * Functions
**********************************************/
/*
 * confirm_yes_no()
 * <Usage>
 * 	int		n;
 * 	n = confirm_yes_no();
 * 	if (n == 1)
 * 		break;
 */
static int confirm_yes_no( void )
{
	char	ch;		/* Receive the input from scanf() */
	char	buf[20]; /* buffer for fgets() */
	int		ret = 2;	/* Return value:
						 * 1. Initially 2
						 * 2. If "no", then 0
						 * 3. If "yes", then 1
						 * 4. None of 2 or 3
						 * 		=> loop continues
	 	 	 	 	 	 */

	while(ret == 2) {
		/* Input the choice */
		printf("Continue?(y/n): ");
		fgets(buf, sizeof(buf), stdin);
		sscanf(buf, "%c", &ch);

		/* Judge the input */
		switch(ch) {
		case 'y':
			ret = 1;
			break;
		case 'n':
			ret = 0;
			break;
		default:
			printf("Your input was: %c\n", ch);
			printf("Please, 'y' or 'n' "
						"(case sensitive)\n");
			break;
		}//switch(ch) {

	}//while(1) {

	return ret;

}//static int confirm_yes_no( void )

static int akicode_tbl_shuffle2( int number )
{
    int     ret;					/* ���� ����        */
    int     i;						/* ���ޯ��          */
    int     cnt;					/* �� ���� ��       */
    FILE    *fp;					/* ̧�� �߲��       */
    char    *fname = AKICODE_TBL_NAME;  		/* �� ���� ˮ� ̧�� */

    int		akicode_tbl_tmp[MEMBER_MAX + 1];	/* ��Ɨp */
    int		j;			/* index for akicode_tbl */
    int		k;			/* index for akicode_tbl_tmp */

#ifdef DEBUG
    printf("[%s:%d]", __FILE__, __LINE__);
    printf("Enter: %s\n", "akicode_tbl_shuffle2()");
    printf("number=%d\n", number);
#endif

    /* Set the element to zero */
    akicode_tbl[number] = 0;

#ifdef DEBUG
    printf("[%s:%d]\n", __FILE__, __LINE__);

    show_akicode_tbl();

#endif

    /*
     * 1. Copy from akicode_tbl[] to
     * 		akicode_tbl_tmp[]
     * 2. Skip copying if the value is 0
     * 3. The last element of akicode_tbl_tmp[]
     * 		=> To zero
     */
    //for(j = 0, k = 0; i < MEMBER_MAX + 1; j++) {
	//for(j = 0, k = 0; j < MEMBER_MAX + 1; j++) {
	for(j = 0, k = 0; j <= akicode_tbl[0]; j++) {
    	if(akicode_tbl[j] != 0) {
    		akicode_tbl_tmp[k] = akicode_tbl[j];
    		++k;
    	}//if(akicode_tbl[i] != 0) {
    }//for(i = 0; i < MEMBER_MAX + 1; i++) {

#ifdef DEBUG
	printf("[%s:%d] ", __FILE__, __LINE__);
	printf("j=%d k=%d\n", j, k);
#endif

    akicode_tbl_tmp[k] = 0;

    /*
     * Copy the data section of akicode_tbl_tmp[]
     * 	to the data section of akicode_tbl[]
     */
    //for(i = 1; i < MEMBER_MAX + 1; i++) {
	//for(i = 1; i < akicode_tbl[0]; i++) {
    //for(i = 1; i <= MEMBER_MAX; i++) {
    for(i = 1; i <= akicode_tbl[0]; i++) {
    	akicode_tbl[i] = akicode_tbl_tmp[i];
    }//for(i = 1; i < MEMBER_MAX + 1; i++) {

    /*
     * Decrement the value of the max number
     * 	section of akicode_tbl[]
     */
    --akicode_tbl[0];

#ifdef DEBUG
    printf("[%s:%d]", __FILE__, __LINE__);
    printf("Exit: %s\n", "akicode_tbl_shuffle2()");
#endif

    //return 0;
    return 0;

}//static int akicode_tbl_shuffle2( int number )

static void show_akicode_tbl( void )
{
	int		i;		/* index */

	for(i = 0; i < MEMBER_MAX + 1; i++) {
		printf("akicode_tbl[%d]=%d\n",
					i, akicode_tbl[i]);
	}
}//static void show_akicode_tbl( void )

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
}//static int akicode_tbl_create( void )

static int akicode_tbl_update( void )
{
    int     ret;					/* ���� ����        */
    int     i;						/* ���ޯ��          */
    int     cnt;					/* �� ���� ��       */
    FILE    *fp;					/* ̧�� �߲��       */
    char    *fname = AKICODE_TBL_NAME;  		/* �� ���� ˮ� ̧�� */

    /* �� ���� �ݽ� ��� */
    cnt = akicode_tbl[ 0 ];

    //return 0;

#ifdef DEBUG
    printf("[%s:%d]\n", __FILE__, __LINE__);
    printf("�󂫃R�[�h����(cnt)�F %d\n", cnt);
    printf("\n");
#endif

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
}//static int akicode_tbl_update( void )

/*
 * akicode_tbl_shuffle()
 * <Parameter>
 * 	1. number:int =>
 * <Return>
 */
static int akicode_tbl_shuffle( int number )
{
    int     ret;					/* ���� ����        */
    int     i;						/* ���ޯ��          */
    int     cnt;					/* �� ���� ��       */
    FILE    *fp;					/* ̧�� �߲��       */
    char    *fname = AKICODE_TBL_NAME;  		/* �� ���� ˮ� ̧�� */

    int		akicode_tbl_tmp[MEMBER_MAX + 1];	/* ��Ɨp */
    int		j;			/* index for akicode_tbl */
    int		k;			/* index for akicode_tbl_tmp */

#ifdef DEBUG
    printf("[%s:%d]", __FILE__, __LINE__);
    printf("Enter: %s\n", "akicode_tbl_shuffle()");
    printf("number=%d\n", number);
#endif

    /* Copy: From number to tail */
    for(j = number, k = 1; j <= akicode_tbl[0]; j++, k++) {
    	akicode_tbl_tmp[k] = akicode_tbl[j];
    }//for(j = number, k = 1; j <= akicode_tbl[0]; j++, k++) {

    /* Copy: From head to (number - 1) */
    for(j = 1; j < number; j++, k++) {
    	akicode_tbl_tmp[k] = akicode_tbl[j];
    }

    /* Copy: akicode_tbl_tmp[] to akicode_tbl[] */
    for(j = 1; j <= akicode_tbl[0]; j++) {
    	akicode_tbl[j] = akicode_tbl_tmp[j];
    }

#ifdef DEBUG
    printf("[%s:%d]", __FILE__, __LINE__);
    printf("Exit: %s\n", "akicode_tbl_shuffle()");
#endif

    //return 0;
    return 0;

}//static int akicode_tbl_shuffle( void )

int main( int argc, char *argv[] )
{
#ifdef NUM
	int		shuffle_num = NUM;
#else
	int		shuffle_num = 2;	/* akicode_tbl_shuffle() */
#endif

    //char	ans;		/* whlie���́A���s�̑��ۂ̓��͂��󂯂� */
    char	ans[10];		/* whlie���́A���s�̑��ۂ̓��͂��󂯂� */
    char	buf[10];	/* ans �ɑ�����邽�߂̃o�b�t�@�[ */
    int		i_ans;		/* Receive confirm_yes_no() */

    /* Create akicode_tbl[] */
	akicode_tbl_create();

	/* Show akicode_tbl[] */
	show_akicode_tbl();

	/* Update akicode_tbl[] */
	//akicode_tbl_update();

	/* �󂫃R�[�h���� */
	printf("[%s:%d]", __FILE__, __LINE__);
	printf("akicode_tbl[0]=%d\n", akicode_tbl[0]);

	/* �󂫃R�[�h�\�F���בւ� */
	//akicode_tbl_shuffle(2);
	//akicode_tbl_shuffle(shuffle_num);

	/* �󂫃R�[�h�\�F���בւ�: ���̂Q
	 * akicode_tbl_shuffle2()
	 */
	while(1) {
		akicode_tbl_shuffle2(shuffle_num);

		/* Show akicode_tbl[] */
		show_akicode_tbl();

		/* Ask whether to continue */
		i_ans = confirm_yes_no();
//		printf("Continue?(y/n): ");
//		scanf("%s", ans);
		//fgets(buf, sizeof(char), stdin);
		//fgets(buf, sizeof(buf), stdin);
		//sscanf(buf, "%c", ans);
		//scanf("%c", &ans);

		if(i_ans == 0)
			break;
		else if(i_ans == 1) {
			printf("\tLet's continue\n");
			//shuffle_num -= 2;
		}

/*		//if(ans == 'n')
		if(ans[0] == 'n')
			break;
		else if(ans[0] == 'y') {
			printf("\tLet's continue\n");
			//shuffle_num -= 2;
		}
		else
			printf
				("Unknown input. Program ends\n");
*/
	}//while(1) {
    return 0;
}//int main( int argc, char *argv[] )

/*
#ifdef D
    printf("[%s:%d]", __FILE__, __LINE__);
#endif

    printf("Content-Type: text/html;charset=shift-jis\n\n");
    printf(__FILE__); printf("<br>\n");
    printf(CREATED_AT); printf("<br>\n");
*/
