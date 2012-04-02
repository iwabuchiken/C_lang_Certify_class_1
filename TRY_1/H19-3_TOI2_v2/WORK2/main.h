/************************************/
/*  main.h                          */
/*    Ò²Ý ¼®Ø Í¯ÀÞ Ì§²Ù             */
/************************************/
struct DUMMY {
    int     num;
    char    string[10];
};

//prototypes: static =========================
static int akicode_tbl_create( void );
static int codedata_tbl_create( void );

//prototypes: non-static =========================
int akicode_tbl_read( void );
int kakunin_input( char *msg );
int kojin_data_read( int kaiin_code );
//int main( void );
struct KEISOKU_TBL init_kojin_keisoku_tbl( void );
void dummy_func( void );
void dummy_func2( int n1, char string[]);
void kojin_data_disp( int kaiin_code, char *msg );
