/************************************/
/*  nyuukai.h                       */
/*    Æ­³¶² Ä³Û¸ ¼®Ø Í¯ÀÞ Ì§²Ù      */
/************************************/

int  nyuukai_touroku( void );

#ifdef TOI1
static int  akicode_tbl_update( int touroku_number );
#else
static int  akicode_tbl_update( void );
#endif

static int  keisoku_tbl_add( long *fptr, int kaiin_code );
static int  codedata_tbl_update( int kaiin_code, long fptr );

