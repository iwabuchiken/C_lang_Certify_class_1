/************************************`
 * <Basics>
 *	1. File: sub1_akicode_tbl_update.c
 *	2. Author: Iwabuchi Ken				*
 *	3. Date: 20120314_085559
 *	4. Dependencies:
 *		1)
 * <Aim>
 * 	1.
 * <Usage>
 *	1. Execute the program			*
 * <Source>
 * 	1. 
 * <Related>
 * 	1.
 * <Others>
 * <Description of the program>
 * 	1. 
 ************************************/

#ifndef COMMON_H
#define COMMON_H
#include "common.h"
#endif COMMON_H

#ifndef AKICODE_TBL_UPDATE
#define AKICODE_TBL_UPDATE
#include "sub1_akicode_tbl_update_1.h"
#endif AKICODE_TBL_UPDATE

// global vars ============================
int     akicode_tbl[MEMBER_MAX + 1];    /* akicode table        */

// functions ============================
/******************************************
 * akicode_tbl_disp -- show every element in the table
 * 
 * <Parameters>
 *        - 
 *        - 
 * <Return value>
 *       : 
 * <Notices>
 *  1. index value is from 0 to MEMBER_MAX + 1, 
 *      for the index 0 is used for the total sum of
 *      empty codes
 ******************************************/
void akicode_tbl_disp(void)
{
    /* vars         */
    int         i;      /* index        */
    
    /* display      */
    for (i = 0; i < MEMBER_MAX + 1; i++) {
        printf("akicode_tbl[%d]=%d\n", i, akicode_tbl[i]);
    }//for (i = 0; i < MEMBER_MAX + 1; i++)
    
}//void akicode_tbl_disp(void)

int main(int argc, char* argv[])
{
	/* vars             */
    int         ret;        /* return value of each function    */
    char        input[10];  /* choice from the menu             */
    int         loop;       /* flag for 'while' loop            */
    
    /* initialize akicode table */
    ret = init_akicode_tbl();
    if (ret == OK) {
        printf("akicode table initialized\n");
    } else {//if (ret == OK)
        printf("initialization error\n");
        exit(1);
    }//if (ret == OK)
    
    /* show table       */
    //akicode_tbl_disp();
    
    /* menu             */
    loop = TRUE;
    while (loop) {
        /* display menu     */
        printf("*********************\n");
        printf("1. display akicode table\n");
        printf("2. update akicode table\n");
        printf("Q. Quit\n");
        printf("*********************\n");
        printf("Enter your choice: ");
        
        /* enter input      */
        fgets(input, sizeof(input), stdin);
        input[strlen(input) - 1] = '\0';
        
        /* validation       */
        if (strlen(input) != 1) {
            printf("length of input not proper: length=%d\n",
                            strlen(input));
            continue;            
        }//if (strlen(input) != 1)
        
        /* switching        */
        switch (input[0]) {
            case '1':
                akicode_tbl_disp();
                break;
            case '2':
                akicode_tbl_update();
                break;
            case 'Q':
            case 'q':
                loop = FALSE;
                break;

        }//switch (condition)
    }//while (loop)

	return (0);
}//int main(int argc, char* argv[])
/******************************************
 * init_akicode_tbl -- initialize the akicode table
 * 
 * <Parameters>
 *        - 
 *        - 
 * <Return value>
 *       : 
 * <Notices>
 *      
 ******************************************/
int init_akicode_tbl(void)
{
    /* variables	*/
    //int     akicode_tbl[MEMBER_MAX];    /* akicode table        */
    int     i;                  /* index for 'for' loop */
    
    /* initialize table */
    akicode_tbl[0]  = (MEMBER_MAX);
    for (i = 1; i < MEMBER_MAX + 1; i++) {
        akicode_tbl[i] = i;
    }//for (i = 0; i < MEMBER_MAX + 1; i++)
    
    return OK;
}//int init_akicode_tbl(void)

int akicode_tbl_update(void)
{
    /* vars         */
    int     cnt;        /* number of aki codes  */
    int     i;          /* index                */
    
    /* get the current number of aki codes  */
    cnt = akicode_tbl[0];
    
    /* update data          */
    for (i = 1; i < cnt; i++) {
        akicode_tbl[i] = akicode_tbl[i + 1];
    }//for (i = 1; i < cnt; i++)
    
    /* 0-fy the unused element in akicode_tbl   */
    akicode_tbl[i] = 0;
    
    /* renew number of aki codes    */
    akicode_tbl[0] = cnt - 1;
    
#ifdef DEBUG
    printf("[%d]\n", __LINE__);
    akicode_tbl_disp();
    printf("\n");
    printf("i=%d\n", i);
#endif

/*
#ifdef DEBUG
    printf("[%d]\n", __LINE__);
    printf("akicode_tbl[0]=%d\n", akicode_tbl[0]);
#endif
*/

    /* return           */
    return OK;
    
}//int akicode_tbl_update(void)

/*
#ifdef D
    printf("[LINE:%d]", __LINE__);
#endif
 */
