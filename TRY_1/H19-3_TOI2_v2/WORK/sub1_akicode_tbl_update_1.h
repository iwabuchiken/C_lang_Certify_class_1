/************************************`
 * <Basics>
 *	1. File: sub1_akicode_tbl_update.h
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
// prototypes ============================
void akicode_tbl_disp(void);
int init_akicode_tbl(void);
int akicode_tbl_update(void);
int init_used_code_tbl(void);
void used_code_tbl_disp(void);
static int used_code_tbl_update(int mode, int value);
static void create_dummy_data(void);
static void input_date(char record_date[]);
static char* get_time_string(int mode);

//================EOF================================