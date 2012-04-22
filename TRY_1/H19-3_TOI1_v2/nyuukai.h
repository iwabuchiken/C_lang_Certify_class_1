/************************************/
/*  nyuukai.h                       */
/*    Æ­³¶² Ä³Û¸ ¼®Ø Í¯ÀÞ Ì§²Ù      */
/************************************/

int  nyuukai_touroku( void );

#ifdef ADMIN
int akicode_tbl_update( void );
#else
static int akicode_tbl_update( void );
#endif
#ifdef ADMIN
int keisoku_tbl_add( long *fptr, int kaiin_code );
#else
static int keisoku_tbl_add( long *fptr, int kaiin_code );
#endif

#ifdef ADMIN
int codedata_tbl_update( int kaiin_code, long fptr );
#else
static int codedata_tbl_update( int kaiin_code, long fptr );
#endif

