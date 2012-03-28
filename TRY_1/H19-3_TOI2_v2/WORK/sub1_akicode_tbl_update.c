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

#ifndef TIME_H
#define TIME_H
#include "time.h"
#endif TIME_H

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
int     used_code_tbl[MEMBER_MAX + 1];    /* akicode table        */

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
#ifdef DEBUG
        printf("[%d] ", __LINE__);
#endif

        printf("akicode table initialized\n");
    } else {//if (ret == OK)
        printf("[%d] ", __LINE__);
        printf("initialization error\n");
        exit(1);
    }//if (ret == OK)
    
    /* initialize used_code table */
    ret = init_used_code_tbl();
    if (ret == OK) {
        printf("used_code table initialized\n");
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
        //debug
        //printf("Current time: %s\n", get_time_string(1));
        printf("Current time: %s\n", get_time_string(2));
        printf("*********************\n");
        printf("1. display akicode table\n");
        printf("2. update akicode table\n");
        printf("3. display used_code table\n");
        printf("4. Create dummy data\n");
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
            case '3':
                used_code_tbl_disp();
                break;
            case '4':
                create_dummy_data();
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

/******************************************
 * akicode_tbl_update -- update the akicode table
 * 
 * <Parameters>
 *        - 
 *        - 
 * <Return value>
 *       : 
 * <Notices>
 *      
 ******************************************/
int akicode_tbl_update(void)
{
    /* vars         */
    int     cnt;        /* number of aki codes  */
    int     i;          /* index                */
    int     mode;       /* flag for used_code_tbl_update()
                         *  1   => add
                         *  2   => delete
                         */
    
    /* get the current number of aki codes  */
    cnt = akicode_tbl[0];
    
    /* set the nuber to used_code_tbl[]     */
    mode = 1;
    used_code_tbl_update(1, akicode_tbl[1]);
    //used_code_tbl[MEMBER_MAX - (used_code_tbl[0]) + 1] = akicode_tbl[1];
    
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
/******************************************
 * init_used_code_tbl -- initialize the used_code_tbl[]
 * 
 * <Parameters>
 *        - 
 *        - 
 * <Return value>
 *       : 
 * <Notices>
 *      length => MEMBER_MAX + 1
 ******************************************/
int init_used_code_tbl(void)
{
    /* variables	*/
    //int     used_code_tbl[MEMBER_MAX];    /* used_code table        */
    int     i;                  /* index for 'for' loop */
    
    /* initialize table */
    //used_code_tbl[0]  = (MEMBER_MAX);
    used_code_tbl[0]  = 0;
    for (i = 1; i < MEMBER_MAX + 1; i++) {
        used_code_tbl[i] = 0;
    }//for (i = 0; i < MEMBER_MAX + 1; i++)
    
    return OK;
}//int init_used_code_tbl(void)

/******************************************
 * used_code_disp -- display the used_code table
 * 
 * <Parameters>
 *        - 
 *        - 
 * <Return value>
 *       : 
 * <Notices>
 *      
 ******************************************/
void used_code_tbl_disp(void)
{
    /* vars         */
    int         i;      /* index        */
    
    /* display      */
    for (i = 0; i < MEMBER_MAX + 1; i++) {
        printf("used_code_tbl[%d]=%d\n", i, used_code_tbl[i]);
    }//for (i = 0; i < MEMBER_MAX + 1; i++)
    
}//void used_code_disp(void)

/******************************************
 * used_code_tbl_update -- update the table
 * 
 * <Parameters>
 *        - 
 *        - 
 * <Return value>
 *       : 
 * <Notices>
 *      
 ******************************************/

static int used_code_tbl_update(int mode, int value)
{
    /* vars         */
    int         i;      /* index        */
    
    /* processing   */
    if (mode == 1) {
        /* shift every element      */
        for (i = MEMBER_MAX; i > 1; i--) {
            used_code_tbl[i] = used_code_tbl[i - 1];
        }//for (i = MEMBER_MAX; i < 1; i++)    
        used_code_tbl[1] = value;
        used_code_tbl[0] ++;
    } else {//if (mode == 1)
        //continue;
    }//if (mode == 1)
    
    return OK;
    
}//int used_code_tbl_update(int mode, int value)

static void input_date(char record_date[])
{
    
}//void input_date(char record_date[])

static void create_dummy_data(void)
{
    /* vars         */
    int         i;      /* index        */
    
    /* create dummy codes       */
    for (i = 0; i < 5; i++) {
        akicode_tbl_update();
    }//for (i = 0; i < 5; i++)    
    
    /* create dummy records     */
    
    
    //debug
    //printf("create_dummy_data()\n");
    
}//void create_dummy_data(void)

/******************************************
 * get_time_string -- return a time string
 * 
 * <Parameters>
 *      mode:int  - type of the time string
 *        - 
 * <Return value>
 *      time_str : char*
 * <Notices>
 *  Mode
 *      1   => Wed Mar 28 07:52:18 2012
 *      2   => 20120328_080912
 *      3   => 20120328
 * 
 ******************************************/
static char* get_time_string(int mode)
{
    char    *time_str;  /* time string  */
    time_t  timer;      /* time_t var   */
    struct  tm  *date;  /* tm struct    */
    
    /* alloc time_str   */
    time_str = malloc(sizeof(char) * 30);
    
    /* set timer        */
    timer   = time(NULL);
    /* set localtime    */
    date    = localtime(&timer);
    
    /* prepare time string   */
    //printf("%s\n", asctime(date));
    if (mode == 1) {
        //time_str = asctime(date);
        strcpy(time_str, asctime(date));
    } else if (mode == 2) {//if (mode == 1)
        strftime(time_str, 30, "%Y%m%d_%H%M%S", date);
    } else if (mode == 3) {//if (mode == 1)
        strftime(time_str, 30, "%Y%m%d", date);
    } else {//if (mode == 1)
    }//if (mode == 1)
    //time_str = asctime(date);
    
    /* return           */
    return time_str;
    
}//char* get_time_string(void)


/*
#ifdef D
    printf("[LINE:%d]", __LINE__);
#endif
 */
