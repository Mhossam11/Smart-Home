/*
 * Main_macros.h
 *
 * Created: 8/21/2023 8:52:08 PM
 *  Author: 20100
 */ 


#ifndef MAIN_MACROS_H_
#define MAIN_MACROS_H_

#include "STD_Types.h"



#define NOTPRESSED 0xFF			//value indicate that there is nothing here
#define DUMMY_DATA 0xFF			//if we didn't need to send data to slave 

/*************************EEPROM LOCATIONS*************************************/
#define  ADMIN_STATUS_LOCATION 0X20		//TO KNOW IF ADMIN PASS SET BEFOR
//by default stored 0xFF
#define  ADMIN_PASS1		   0X21		//LOCATION of first number in admin password
#define  ADMIN_PASS2		   0X22		//LOCATION of seconde number in admin password
#define  ADMIN_PASS3		   0X23		//LOCATION of third number in admin password
#define  ADMIN_PASS4		   0X24		//LOCATION of fourth number in admin password


#define  GUEST_STATUS_LOCATION 0X30	    //TO KNOW IF GUEST PASS SET BEFOR
//by default stored 0xFF
#define  GUEST_PASS1		   0X31		//LOCATION of first number in GUEST password
#define  GUEST_PASS2		   0X32		//LOCATION of seconde number in GUEST password
#define  GUEST_PASS3		   0X33		//LOCATION of third number in GUEST password
#define  GUEST_PASS4		   0X34		//LOCATION of fourth number in GUEST password
/*****************************************************************************************/


/*****************************system menu Macros_name*************************************/

/********select admin or guest**************/

//#define CHECK_NO_MODE				'0'		//INDICATE THAT USER DIDN'T SELECT ANY MODE
#define CHECK_ADMIN_MODE			'1'		//ASCII CODE THAT THE USER WILL ENTER FROM KEYPAD TO SELCET ADMIN MODE
#define CHECK_GUEST_MODE			'2'		//ASCII CODE THAT THE USER WILL ENTER FROM KEYPAD TO SELCET GUEST MODE
#define CHECK_BLOCK_MODE			'3'		//INDICATE FOR BLOCK MODE
/******************************/

/*******new**************/
#define NO_MODE				(uint8)0		//INDICATE THAT USER DIDN'T SELECT ANY MODE				
#define ADMIN_MODE			(uint8)1		//VALUE SAVED IN login_mode TO KNOW WHICH MODE THE USER CHOOSE
#define GUEST_MODE			(uint8)2		//VALUE SAVED IN login_mode TO KNOW WHICH MODE THE USER CHOOSE
//#define BLOCK_MODE			(uint8)3
	
/*****************************************/

/***************USER select the rooms WITH KEYPAD*******************/

//case main_MENU
#define SELECT_ROOM1		'1'				//ASCII CODE USED IN SWITCH TO KNOW WHICH OPTION THAT THE USER CHOOSE FROM main_menu
#define SELECT_ROOM2		'2'				//ASCII CODE USED IN SWITCH TO KNOW WHICH OPTION THAT THE USER CHOOSE FROM main_menu
#define SELECT_ROOM3		'3'				//ASCII CODE USED IN SWITCH TO KNOW WHICH OPTION THAT THE USER CHOOSE FROM main_menu
#define SELECT_ROOM4		'4'				//ASCII CODE USED IN SWITCH TO KNOW WHICH OPTION THAT THE USER CHOOSE FROM main_menu
#define ADMIN_MORE_OPTION	'4'				//ASCII CODE USED IN SWITCH TO KNOW WHICH OPTION THAT THE USER CHOOSE FROM main_menu
//ROOM4 in case guest mode
//MORE_OPTION case admin mode
/*****************************************/
//admin more menu
#define SELECT_ROOM4_ADMIN	'1'			//ASCII CODE USED IN SWITCH TO KNOW WHICH OPTION THAT THE USER CHOOSE FROM MORE_menu
#define SELECT_TV			'2'			//ASCII CODE USED IN SWITCH TO KNOW WHICH OPTION THAT THE USER CHOOSE FROM MORE_menu
#define SELECT_AIR_COND		'3'			//ASCII CODE USED IN SWITCH TO KNOW WHICH OPTION THAT THE USER CHOOSE FROM MORE_menu
#define ADMIN_RET_OPTION	'4'			//ASCII CODE USED IN SWITCH TO KNOW WHICH OPTION THAT THE USER CHOOSE FROM MORE_menu
/****************************************************************************************/

/***********air cond menu*********/
#define SELECT_SET_TEMP		 '1'			//ASCII CODE USED IN SWITCH TO KNOW WHICH OPTION THAT THE USER CHOOSE FROM temp_menu
#define SELECT_AIR_COND_CTRL '2'			//ASCII CODE USED IN SWITCH TO KNOW WHICH OPTION THAT THE USER CHOOSE FROM temp_menu
#define SELECT_AIR_COND_RET  '3'			//ASCII CODE USED IN SWITCH TO KNOW WHICH OPTION THAT THE USER CHOOSE FROM temp_menu
/*******************************/
/****************/
#define TRUE	(uint8)1					//logic 1
#define FALSE	(uint8)0					//logic 0
/***************/

/***********No. of ticks of timer********************/
#define ADMIN_TIMEOUT (uint16)3000	// ADMIN SESSION TIME = 30sec
#define GUEST_TIMEOUT (uint16)3000	//ADMIN SESSION TIME = 30sec
/*****************************************************************/

/*************************Menu codes IN SWITCH*****************************/
#define MAIN_MENU			(uint8)1		//CASE 1 IN SWITCH OPEN main_menu
#define MORE_MENU			(uint8)2		//CASE 2 IN SWITCH OPEN more_menu
#define ROOM1_MENU			(uint8)3		//CASE 3 IN SWITCH OPEN room1_menu
#define ROOM2_MENU			(uint8)4		//CASE 4 IN SWITCH OPEN room2_menu
#define ROOM3_MENU			(uint8)5		//CASE 5 IN SWITCH OPEN room3_menu
#define ROOM4_MENU			(uint8)6		//CASE 6 IN SWITCH OPEN room4_menu
#define TV_MENU				(uint8)7		//CASE 7 IN SWITCH OPEN tv_menu
#define AIR_COND_MENU		(uint8)8		//CASE 8 IN SWITCH OPEN air_cond_menu
#define AIR_COND_CTRL_MENU	(uint8)9		//CASE 9 IN SWITCH OPEN air_cond_control_menu
#define TEMPREATURE_MENU    (uint8)10		//CASE 10 IN SWITCH OPEN tempreature_menu

/***********************************************************/


#define MAX_PASS_TRIES		3		//MAXIMUM TRIES TO ENTER THE PASSWORD

#define BLOCKED_MODE_TIME	10000	//BLOCKED TIME = 10SEC
/***********************************************/


#endif /* MAIN_MACROS_H_ */