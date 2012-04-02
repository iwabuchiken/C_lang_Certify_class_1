#include <stdio.h>
#include "common.h"
#include "main.h"

//#define KEISOKU_TBL_NAME "keisoku.tbl"

struct KEISOKU_TBL kojin_keisoku_tbl;

static int kojin_data_delete( int kaiin_code )
{
    /* vars         */
    int     ret;				/* ØÀ°Ý º°ÄÞ                */
    int     i;					/* ²ÝÃÞ¯¸½                  */
    FILE    *fp;				/* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù Îß²ÝÀ */
    FILE    *tmp;				/* ÃÝÎß×Ø Ì§²Ù Îß²ÝÀ        */
    char    *fname = KEISOKU_TBL_NAME;		/* ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù       */
    char    *tmpfl = "keisoku.tmp";		/* ÃÝÎß×Ø Ì§²Ù              */

    /* Open the table file          */
    if( (fp = fopen( fname, "rb" )) == NULL ) {
        printf( "\n ¹²¿¸ ÃÞ°À Ë®³ Ì§²Ù OPEN ´×°" );
        return NG;
    }
    
    /* Read data: kojin_keisoku         */
    ret = fread( (char *)&kojin_keisoku_tbl,
            sizeof( kojin_keisoku_tbl ), 1, fp );
    
    //debug
    printf("\n[%s:%d]\n", __FILE__, __LINE__);
    printf("ret=%d\n", ret);
    
    /* Close the table file             */
    fclose(fp);
    
    return 0;
}//static int kojin_data_delete( int kaiin_code )

int main( int argc, char* argv[] )
{
    /* vars             */
    int     code;   /* kaiin_code       */
    
    /* Set values       */
    if (argc < 2) {
        code = 1;
    } else {//if (argc < 2)
        code = atoi(argv[0]);
    }//if (argc )
    //debug
    //printf("argc=%d\n", argc);
    
    kojin_data_delete(code);

    /* Show data            */
    printf("kojin_keisoku_tbl.kaiin_code=%d\n", kojin_keisoku_tbl.kaiin_code);
    
    /* return       */
    return 0;
}//int main( void )
