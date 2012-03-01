/************************************/
/*  common.h                        */
/*    ���³ ͯ�� ̧��               */
/************************************/

#define MEMBER_MAX	    200			/* ���ް�� MAX */
//#define MEMBER_MAX	    10			/* ���ް�� MAX */
#define AKICODE_TBL_NAME    "akicode.tbl"	/* ������ˮ� ̧�� Ҳ */
#define CODEDATA_TBL_NAME   "codedata.tbl"  	/* ���� �ް� ����� ˮ� ̧�� Ҳ */
#define KEISOKU_TBL_NAME    "keisoku.tbl"	/* ���� �ް� ˮ� ̧�� Ҳ */

#define  TRUE          1    /* ��            */
#define  FALSE         0    /* ��            */
#define  OK            0    /* ���ޮ�        */
#define  CANCEL        1    /* ��� ����      */
#define  NG           -1    /* ��ޮ�         */

/* ���� �ް� ð��� */
struct   KEISOKU_TBL {
    int  kaiin_code;       /* ���� ����     */
    int  count;            /* ���� ����     */
    char first_date[ 9 ];  /* ���� ��޹     */
    int  first_data;       /* ���� �ް�     */
    char max_date[ 9 ];    /* ���� �۸ ��޹ */
    int  max_data;         /* ���� �۸ �ް� */
    char soku_date[ 9 ];   /* ���� ��޹     */
    int  soku_data[ 10 ];  /* ���� �ް�     */
};

/* ƭ�خ� ���� �ް� */
struct   KEISOKU_INPUT {
    int  huka;     /* ̶    */
    int  set;      /* ���   */
    int  kaisuu;   /* ����  */
};
