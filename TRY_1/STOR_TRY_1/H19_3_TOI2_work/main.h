/************************************/
/*  main.h                          */
/*    Ò²Ý ¼®Ø Í¯ÀÞ Ì§²Ù             */
/************************************/

static int  codedata_tbl_create( void );

#ifdef TOI2
int  akicode_tbl_create( void );
#else
static int  akicode_tbl_create( void );
#endif

int  akicode_tbl_read( void );
int  kakunin_input( char *msg );
int  kojin_data_read( int kaiin_code );
void kojin_data_disp( int kaiin_code, char *msg );
struct KEISOKU_TBL init_kojin_keisoku_tbl( void );

#ifdef TOI2
void admin( void );
#endif
