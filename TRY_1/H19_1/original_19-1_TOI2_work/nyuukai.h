/************************************/
/*  nyuukai.h                       */
/*    Æ­³¶² Ä³Û¸ ¼®Ø Í¯ÀÞ Ì§²Ù      */
/************************************/

int  nyuukai_touroku( void );

static int  akicode_tbl_update( void );

#ifdef TOI2
static int akicode_tbl_update2( int number );
#endif

static int  keisoku_tbl_add( long *fptr, int kaiin_code );
static int  codedata_tbl_update( int kaiin_code, long fptr );
static void show_akicode_tbl( void );
