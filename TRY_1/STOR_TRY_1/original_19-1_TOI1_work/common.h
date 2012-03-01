/************************************/
/*  common.h                        */
/*    ·®³Â³ Í¯ÀÞ Ì§²Ù               */
/************************************/

#define MEMBER_MAX	    200			/* ÒÝÊÞ°½³ MAX */
//#define MEMBER_MAX	    10			/* ÒÝÊÞ°½³ MAX */
#define AKICODE_TBL_NAME    "akicode.tbl"	/* ±·º°ÄÞË®³ Ì§²Ù Ò² */
#define CODEDATA_TBL_NAME   "codedata.tbl"  	/* º°ÄÞ ÃÞ°À À²¼®³ Ë®³ Ì§²Ù Ò² */
#define KEISOKU_TBL_NAME    "keisoku.tbl"	/* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù Ò² */

#define  TRUE          1    /* ¼Ý            */
#define  FALSE         0    /* ·Þ            */
#define  OK            0    /* ¾²¼Þ®³        */
#define  CANCEL        1    /* ¼®Ø Á­³¼      */
#define  NG           -1    /* ²¼Þ®³         */

/* ¹²¿¸ ÃÞ°À Ã°ÌÞÙ */
struct   KEISOKU_TBL {
    int  kaiin_code;       /* ¶²²Ý º°ÄÞ     */
    int  count;            /* ¹²¿¸ ¶²½³     */
    char first_date[ 9 ];  /* ¼®¶² ËÂÞ¹     */
    int  first_data;       /* ¼®¶² ÃÞ°À     */
    char max_date[ 9 ];    /* »²º³ ·Û¸ ËÂÞ¹ */
    int  max_data;         /* »²º³ ·Û¸ ÃÞ°À */
    char soku_date[ 9 ];   /* ¹²¿¸ ËÂÞ¹     */
    int  soku_data[ 10 ];  /* ¹²¿¸ ÃÞ°À     */
};

/* Æ­³Ø®¸ ¹²¿¸ ÃÞ°À */
struct   KEISOKU_INPUT {
    int  huka;     /* Ì¶    */
    int  set;      /* ¾¯Ä   */
    int  kaisuu;   /* ¶²½³  */
};
