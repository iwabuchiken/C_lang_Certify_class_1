/************************************/
/*  main.h                          */
/*    Ò²Ý ¼®Ø Í¯ÀÞ Ì§²Ù             */
/************************************/

static int  codedata_tbl_create( void );
static int  akicode_tbl_create( void );

int  akicode_tbl_read( void );
int  kakunin_input( char *msg );
int  kojin_data_read( int kaiin_code );
void kojin_data_disp( int kaiin_code, char *msg );
struct KEISOKU_TBL init_kojin_keisoku_tbl( void );

#ifdef TOI2
static int point_rank( void );
int  show_data( void );
static void point_sort( int cnt );
static void point_disp( int cnt );
#endif
