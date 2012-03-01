/************************************/
/*  keisoku.h                       */
/*    ¹²¿¸·Û¸ Æ­³Ø®¸ ¼®Ø Í¯ÀÞ Ì§²Ù  */
/************************************/

int  keisoku_input( void );

#ifdef TOI2
int  codedata_tbl_read( void );
#else
static int  codedata_tbl_read( void );
#endif

static void kaiin_code_input( int *kaiin_code );
static void keisoku_date_input( char *keisoku_date );
static void keisoku_data_input( int idx );
static void keisoku_data_disp( int kaiin_code, char *keisoku_date );
static void undou_sisuu_keisan( int *undou_sisuu );
static int  kojin_data_update( int kaiin_code, char *keisoku_date, int undou_sisuu );
static int  keisoku_rank( void );
static void keisoku_data_sort( int cnt );
static void keisoku_sort_disp( int cnt );
