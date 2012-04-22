/************************************/
/*  keisoku.h                       */
/*    ¹²¿¸·Û¸ Æ­³Ø®¸ ¼®Ø Í¯ÀÞ Ì§²Ù  */
/************************************/

int  keisoku_input( void );

static int  codedata_tbl_read( void );
static void kaiin_code_input( int *kaiin_code );
static void keisoku_date_input( char *keisoku_date );
static void keisoku_data_input( int idx );

static void keisoku_data_disp( int kaiin_code, char *keisoku_date );
static void undou_sisuu_keisan( int *undou_sisuu );
static int  kojin_data_update( int kaiin_code, char *keisoku_date, int undou_sisuu );

#ifdef TOI1
int  keisoku_rank( void );
#else
static int  keisoku_rank( void );
#endif

#ifdef TOI1
/* 	keisoku_data_sort()
 * <Parameters>
 * 	1. mode => 1 or 0
 * 		1 => descending sort
 * 		0 => ascending sort
 */
static void keisoku_data_sort
			( int cnt, int mode );
#else
static void keisoku_data_sort( int cnt );
#endif

/***************************
 * 	keisoku_data_disp()
 * <Parameters>
 * 	1. mode => 1 or 0
 * 		1 => Top 5
 * 		0 => Bottom 5
 ***************************/
#ifdef TOI1
static void keisoku_sort_disp
( int cnt, int mode );
#else
static void keisoku_sort_disp( int cnt );
#endif
