/*
 * Master.c
 *
 * Created: 8/21/2023 8:36:16 PM
 *  Author: 20100
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000ul
#include <util/delay.h>

#include "Main_macros.h"		//Master Macros
#include "LCD_driver.h"			//LCD FILE.h
#include "Keypad_driver.h"		//KeyPad FILE.h
#include "EEPROM_driver.h"		//EEPROM FILE.h
#include "LED_driver.h"			//LED FILE.h
#include "SPI_driver.h"			//SPI protocol FILE.h
#include "Menu.h"				//MORE FUNCTION USED INT MAIN 
#include "Timer_driver.h"		//TIMERS FILE.h
#include "ADC_driver.h"			//ADC FILE.h



uint8 show_menu=MAIN_MENU;						//VARIABLE used to know which menu we choose	
volatile uint16 session_counter=0;				//timer counter to know the session expired or not
uint8 TIME_OUT_FLAG=FALSE;						//flag to detect if session expired
uint8 Key_Pressed=NOTPRESSED;					//variable will take the read from keypad
int main(void)
{
	/*********INITIALIZATION************/
	LED_vInit('C',0);		//BLOCK_mode LEd INIT
	LED_vInit('C',1);		//ADMIN_mode LED INIT
	LED_vInit('C',2);		//GUEST_mode LEd INIT
	
	LCD_vInit();			//initialize LCD
	KeyPad_vInit('D');		//initialize KeyPad
	SPI_MasterInit();		//SPI protocol intialization for master
	ADC_vInit();			//initialize ADC
	/**********************************/
	
	/*******interning message**********/
	LCD_vSend_String("Welcome to Smart");
	LCD_Move_Cursor(2,1);
	LCD_vSend_String("Home System");
	_delay_ms(1000);
	LCD_Clear_Screen();
	/*************************************/
	
	/***************SOME VARIABLES*****************/
	//uint8 Key_Pressed=NOTPRESSED;									//variable will take the read from keypad
	uint8 i=0;														//counter for loops
	uint8 PASS_FLAG=0;												//flag to know if the password entered correct
	uint8 Tries_allowed=MAX_PASS_TRIES;								//maximum tries  to enter the password
	uint8 pass_tries_count=0;										//COUNTER for how many times we entered the password 

	uint8 login_mode=NO_MODE;										//to know the status of choosen mode(admin or guest)
	uint8 BLOCKED_MODE_FLAG;										//Flag to know if we entered the blocked mode
	uint8 pass[4]={NOTPRESSED,NOTPRESSED,NOTPRESSED,NOTPRESSED};	//to store the password that we will check
	
	uint8 tempreature=0;											//to save temp that user will enter
	uint8 temp_tens=0xFF;											//save the tens number when user set tempreature
	uint8 temp_ones=0xFF;											//save the ones number when user set tempreature
	/**********************************************/
	
	/******************if this is the first time to use the system*************************/
	if((EEPROM_Read(ADMIN_STATUS_LOCATION)==NOTPRESSED) && (EEPROM_Read(GUEST_STATUS_LOCATION)==NOTPRESSED))	//NO PASSWORD IS SET YET
	{																											//by default in EEPROM address saved 0xFF
		LCD_vSend_String("Login For");
		LCD_Move_Cursor(2,1);
		LCD_vSend_String("First time");
		_delay_ms(1000);
		LCD_Clear_Screen();
		
		/*******************take and save the admin password*******************/
		LCD_vSend_String("Set Admin Pass");					//message for the user
		LCD_Move_Cursor(2,1);
		LCD_vSend_String("Admin pass:");
		
		for(i=0;i<4;i++)									//for loop with 4 iterations to take the password
		{
			Key_Pressed=NOTPRESSED;							//remove the last value saved in it 
			do 
			{
				Key_Pressed=KeyPad_u8Check_Pressed('D');	//take the admin password from the keypad
			} while (Key_Pressed==NOTPRESSED);				//wait until user put the password
			
			LCD_vSend_char(Key_Pressed);					//print the number to the lcd
			_delay_ms(250);									//delay to avoide corruption 
			LCD_Move_Cursor(2,12+i);
			LCD_vSend_char('*');							//print pass sympol to lcd
			EEPROM_Write(ADMIN_PASS1+i,Key_Pressed);		//copy the Admin password to EEPROM location
			_delay_ms(100);									//wait to write in EEPROM
		}
		
		i=0;												//reset the counter again
		EEPROM_Write(ADMIN_STATUS_LOCATION,0x00);			//WRITE 0 TO ADMIN STATUS LOCATION TO TELL MC THAT PASS IS SAVED
		_delay_ms(100);										//wait to write in EEPROM
		/***************************************************************/
		
		/**************print that password saved************************/
		LCD_Clear_Screen();
		LCD_vSend_String("Pass saved");
		_delay_ms(500);
		LCD_Clear_Screen();
		/***************************************************************/
		
		/*******************take and save the Guest password*******************/
		LCD_vSend_String("Set Guest Pass");					//message for the user
		LCD_Move_Cursor(2,1);
		LCD_vSend_String("Guest Pass:");
		for(i=0;i<4;i++)									//for loop with 4 iterations to take the password
		{
			Key_Pressed=NOTPRESSED;							//remove the last value saved in it 
			do 
			{
				Key_Pressed=KeyPad_u8Check_Pressed('D');	//SAVE GUEST PASS
			} while (Key_Pressed==NOTPRESSED);
			
			LCD_vSend_char(Key_Pressed);					//print the number to the lcd
			_delay_ms(250);									//delay to avoide corruption 
			LCD_Move_Cursor(2,12+i);
			LCD_vSend_char('*');							//print pass sympol to lcd
			EEPROM_Write(GUEST_PASS1+i,Key_Pressed);		//copy guest pass to guest EEPROM pass location
			_delay_ms(100);									//wait to write in EEPROM
		}
		
		i=0;												//reset the counter again
		EEPROM_Write(GUEST_STATUS_LOCATION,0x00);			//WRITE 0 TO GUEST STATUS LOCATION TO TELL MC THAT PASS IS SAVED
		_delay_ms(100);										//wait to write in EEPROM
		/******************************************************************/
		
		/**************print that password saved************************/
		LCD_Clear_Screen();
		LCD_vSend_String("Pass saved");
		_delay_ms(500);
		LCD_Clear_Screen();
		/***************************************************************/
	}//end of (if this is the first time to use the system)
	/************************************************************************************/	
			
    while(1)
    {	
		/**********************Case session timeout*****************/
		Key_Pressed=NOTPRESSED;						//remove the last value saved in it 
		
		while(TIME_OUT_FLAG==TRUE)					//loop whole session expired 
		{
			Timer_stop_CTC_mode();					//stop timer
			
			session_counter=0;						//remove the value saved in session counter to recount 
			TIME_OUT_FLAG=FALSE;					//write 0 to this flagh to know that the session didn't expired
			login_mode=NO_MODE;						//select no mode to logout from the current mode
			Key_Pressed=NOTPRESSED;					//remove the last value saved in it 				
			show_menu=MAIN_MENU;					//go back to Main menu
			
			LED_vTurnOFF('C',1);					//turn off admin mode led 
			LED_vTurnOFF('C',2);					//turn off guest mode led 
			
			LCD_Clear_Screen();
			LCD_vSend_String("Session TimeOut");	//message for user
			_delay_ms(1000);
		}
		/*********************************************************/
		while(login_mode==NO_MODE)					//loop while there is no mode selected
		{
			if(BLOCKED_MODE_FLAG==TRUE)				//if program enter Block mode
			{
				LCD_Clear_Screen();
				LCD_vSend_String("Login Blocked");	//message for the user
				LCD_Move_Cursor(2,1);
				LCD_vSend_String("Wait 10 Sec");
				LED_vTurnOn('C',0);
				_delay_ms(BLOCKED_MODE_TIME);		//wait for BLOCKED MODE time
				pass_tries_count=0;					//clear the pass tries counter
				Tries_allowed=MAX_PASS_TRIES;		
				BLOCKED_MODE_FLAG=FALSE;			//logout from Blocked mode
				LED_vTurnOFF('C',0);				//turnoff blocked mode LED
			}
			
			/*************select mode***********************/
			Key_Pressed=NOTPRESSED;						//remove the last value saved in it
			LCD_Clear_Screen();
			LCD_vSend_String("Select mode:");			//message for the user
			LCD_Move_Cursor(2,1);
			LCD_vSend_String("1:Admin  2:Guest");
		/***************************************************/
			
			do /*************user choose if he want admin or guest mode***************/
			{
				Key_Pressed=KeyPad_u8Check_Pressed('D');				//take number from PORTD
			
			} while (Key_Pressed==NOTPRESSED);
		
			if((Key_Pressed != CHECK_ADMIN_MODE) && (Key_Pressed != CHECK_GUEST_MODE) )		//CASE OF ANOTHER INPUT
			{
				LCD_Clear_Screen();
				LCD_vSend_String("Wrong input");						//message for user
				_delay_ms(1000);
				LCD_Clear_Screen();
				Key_Pressed=NOTPRESSED;									//remove the last value saved in it
				continue;												//backagain to the above menu to select admin or guest
			}
		
			/***************************switch on main menu**************************/
			switch(Key_Pressed)
			{
				case CHECK_ADMIN_MODE:									//IF USER SELECT ADMIN MODE
			
					while(login_mode!=ADMIN_MODE)						//Loop till password entered correctly  
					{
						Key_Pressed=NOTPRESSED;							//erase the last value entered
						i=0;											//erase the last counts
						
						LCD_Clear_Screen();
						LCD_vSend_String("Admin Mode");					//message for the user
						LCD_Move_Cursor(2,1);
						LCD_vSend_String("Admin Pass:");
						/*****take admin pass********/
						
						for(i=0;i<4;i++)								//for loop with 4 iterations to take the password
						{
							do 
							{
								pass[i]=KeyPad_u8Check_Pressed('D');
							} while (pass[i]==NOTPRESSED);				//Take ADMIN PASS
					
							LCD_vSend_char(pass[i]);					//print the number that user entered on LCD
							_delay_ms(250);								//delay to prevent corruption 
							LCD_Move_Cursor(2,12+i);					//move cursor to the number that user entered location
							LCD_vSend_char('*');						//Print pass symbol to LCD
						}//end of for loop 
						/*****************************/
				
						/************COMPARE ADMIN PASS*************/
						if((EEPROM_Read(ADMIN_PASS1) == pass[0]) && (EEPROM_Read(ADMIN_PASS2)== pass[1]) && (EEPROM_Read(ADMIN_PASS3)== pass[2]) && (EEPROM_Read(ADMIN_PASS4)== pass[3]))//if user entered password correct
						{
							login_mode=ADMIN_MODE;						//flag to know which mode we are in
							PASS_FLAG=1;								//to know that pass enterd correct befor
							pass_tries_count=0;							//start the counter from 0 again since the password is correct
							Tries_allowed=MAX_PASS_TRIES;
							LCD_Clear_Screen();
							LCD_vSend_String("Right Password");
							LED_vTurnOn('c',1);							//turn on admin led
							_delay_ms(500);
							Timer_CTC_Init_interrupt();					//enable timer to start counting the session time
							LCD_Clear_Screen();
						}
						else
						{
							pass_tries_count++;							//count the number of tries
							Tries_allowed--;							//decrement the counter of avilable tries
							login_mode=NO_MODE;							//select no mode to back again
							
							LCD_Clear_Screen();
							LCD_vSend_String("Wrong password");
							LCD_Move_Cursor(2,1);
							LCD_vSend_String("tries allowed:");
							LCD_vSend_char(Tries_allowed+48);			//print number of avilable tries
							_delay_ms(500);
						
							if(pass_tries_count>2)						//user enter the wrong password three times 
							{
								LCD_Clear_Screen();
								LCD_vSend_String("No tries allowed");	//message for the user
								LCD_Move_Cursor(2,1);
								LCD_vSend_String("Blocked Mode");
								BLOCKED_MODE_FLAG=TRUE;					//write 1 to this fkag login to BLOCKED MODE
								_delay_ms(1000);
								break;
							}
						}
						/*********************************************/
					}//end of while loop
					break;												//break from admin check pass
			
				case CHECK_GUEST_MODE:
					while(login_mode!=GUEST_MODE)						//Loop till password entered correctly 
					{
							Key_Pressed=NOTPRESSED;						//erase the last value entered
							i=0;										//erase the last counts
					
							LCD_Clear_Screen();
							LCD_vSend_String("Guest Mode");
							LCD_Move_Cursor(2,1);
							LCD_vSend_String("Guest Pass:");
						
							/*****take guest pass********/
							for(i=0;i<4;i++)								//for loop with 4 iterations to take the passwor
							{
								do 
								{
									pass[i]=KeyPad_u8Check_Pressed('D');
					
								} while (pass[i]==NOTPRESSED);
								LCD_vSend_char(pass[i]);					//print the number that user entered on LCD
								_delay_ms(250);								//delay to prevent corruption 
								LCD_Move_Cursor(2,12+i);					//move cursor to the number that user entered location
								LCD_vSend_char('*');						//Print pass symbol to LCD
							}//end of for loop	
							/********************************/
						
						/********compare guest pass*************/
							if((EEPROM_Read(GUEST_PASS1)==pass[0]) && (EEPROM_Read(GUEST_PASS2)==pass[1]) && (EEPROM_Read(GUEST_PASS3)==pass[2]) && (EEPROM_Read(GUEST_PASS4)==pass[3]))//if user entered password correct
							{
								login_mode=GUEST_MODE;						//flag to know which mode we are in
								PASS_FLAG=1;								//to know that pass enterd correct befor
								pass_tries_count=0;							//start the counter from 0 again since the password is correct
								Tries_allowed=MAX_PASS_TRIES;
								
								LCD_Clear_Screen();
								LCD_vSend_String("Right pass");
								LED_vTurnOn('c',2);
								_delay_ms(500);
								Timer_CTC_Init_interrupt();					//enable timer to start counting session time
								LCD_Clear_Screen();
							}
							else
							{
								pass_tries_count++;							//count the number of tries
								Tries_allowed--;							//decrement the counter of avilable tries
								LCD_Clear_Screen();
								LCD_vSend_String("Wrong Password");
								LCD_Move_Cursor(2,1);
								LCD_vSend_String("Tries Allowed:");
								LCD_vSend_char(Tries_allowed+48);			//print number of avilable tries
								_delay_ms(500);
								
								if(pass_tries_count>2)						//user enter the wrong password three times 
								{
									LCD_Clear_Screen();
									LCD_vSend_String("No Tries Left");
									LCD_Move_Cursor(2,1);
									LCD_vSend_String("Blocked mode");
									BLOCKED_MODE_FLAG=TRUE;					//write 1 to this fkag login to BLOCKED MODE
									_delay_ms(1000);
									break;
								}
							}
							
						}//end of while				
					break;	
				/************************************************************/	
					default:
					break;		
				
				}//end of switch
			}			
			/**************************************************************************************/
			
		
		/***************CHOOSE THE MENU INSIDE GUEST OR ADMIN MODE****************/
		//uint8 show_menu=MAIN_MENU;//3shan yfdl yrg3 lel main menu
		//show_menu=MAIN_MENU;
		
			while(TIME_OUT_FLAG!=TRUE)									//loop while session did not expired
			{
				Key_Pressed=NOTPRESSED;									//remove the last value saved in it
			
				switch(show_menu)
				{
					/***********main menu admin and guest*************/
					case MAIN_MENU:		
						
						Key_Pressed=NOTPRESSED;									//remove the last value saved in it
						do 
						{
							LCD_Clear_Screen();
							LCD_vSend_String("1-Room1  2-Room2");
							LCD_Move_Cursor(2,1);
							if(login_mode==ADMIN_MODE)							//if user choose admin mode
							{
								LCD_vSend_String("3-Room3  4-MORE");
							}
							else if(login_mode==GUEST_MODE)						//if user choose guest mode
							{
								LCD_vSend_String("3-Room3  4-Room4");
							}
							
							do 
							{
								if((session_counter>=ADMIN_TIMEOUT && login_mode==ADMIN_MODE) || (session_counter>=GUEST_TIMEOUT && login_mode==GUEST_MODE))//check if session expired or not
								{
									TIME_OUT_FLAG=TRUE;							//in case that session expired write 1 to timout FLAG
									break;
								}
								Key_Pressed=KeyPad_u8Check_Pressed('D');		//wait tell user choose from menu
							
							} while (Key_Pressed==NOTPRESSED);
							_delay_ms(100);
							/***************user select room***************/
							
							if(Key_Pressed==SELECT_ROOM1)						//case user enter 1 
							{
								show_menu=ROOM1_MENU;						//goto ROOM1 menu in switch
							}
							else if(Key_Pressed==SELECT_ROOM2)					//case user enter 2
							{
								show_menu=ROOM2_MENU;						//goto ROOM2 menu in switch
							}
							else if(Key_Pressed==SELECT_ROOM3)					//case user enter 3 
							{
								show_menu=ROOM3_MENU;						//goto ROOM3 menu in switch
							}
							else if((Key_Pressed==SELECT_ROOM4) && (login_mode==GUEST_MODE) )//case user enter 4 and guest mode selected
							{
								show_menu=ROOM4_MENU;						//goto ROOM4 menu in switch
							}
							else if((Key_Pressed==ADMIN_MORE_OPTION) && (login_mode==ADMIN_MODE))//case user enter 4 and guest mode selected
							{
								show_menu=MORE_MENU;						//goto MORE menu in switch
							}
							else if(Key_Pressed != NOTPRESSED)					//case user did not enter (1or2or3or4)
							{
								LCD_Clear_Screen();
								LCD_vSend_String("wrong input!");
								_delay_ms(500);
							}
						} while (((Key_Pressed<'1') || (Key_Pressed>'4')) && TIME_OUT_FLAG==FALSE);//loop while user did not enter an number from (1,2,3,4) and session did not expired
										
					break;//end of main menu case
					
					/**********case more menu in admin mode***********/
					case MORE_MENU:
						Key_Pressed=NOTPRESSED;									//remove the last value saved in it
						do 
						{
						LCD_Clear_Screen();
						LCD_vSend_String("1-ROOM4  2-TV");
						LCD_Move_Cursor(2,1);
						LCD_vSend_String("3-Air Cond.4-Ret");
						do 
						{
							if((session_counter>=ADMIN_TIMEOUT && login_mode==ADMIN_MODE) || (session_counter>=GUEST_TIMEOUT && login_mode==GUEST_MODE))//check if session ecpired or not
								{
									TIME_OUT_FLAG=TRUE;							//in case that session expired write 1 to timout FLAG
									break;
								}
							Key_Pressed=KeyPad_u8Check_Pressed('D');			//wait till user choose from menu
						} while (Key_Pressed==NOTPRESSED);
						_delay_ms(250);
						
						if(Key_Pressed==SELECT_ROOM4_ADMIN)						//case user enter 1 
						{
							show_menu=ROOM4_MENU;						//goto ROOM4 menu in switch
						}
						else if(Key_Pressed==SELECT_TV)							//case user enter 2
						{
							show_menu=TV_MENU;						//goto TV menu in switch		
						}
						else if(Key_Pressed==SELECT_AIR_COND)					//case user enter 3 
						{
							show_menu=AIR_COND_MENU;					//goto AIR_cond. menu in switch
						}
						else if(Key_Pressed==ADMIN_RET_OPTION)					//case user enter 4 
						{
							show_menu=MAIN_MENU;						//goto MAIN_menu in switch
						}
						
						}while(((Key_Pressed<'1') || (Key_Pressed>'4')) && TIME_OUT_FLAG==FALSE);//loop while user did not enter an number from (1,2,3,4) and session did not expired
					break;
					
					/**********case AIR_cond. MENU***********/	
					case AIR_COND_MENU:
						do
						{
							Key_Pressed=NOTPRESSED;									//remove the last value saved in it
							LCD_Clear_Screen();
							LCD_vSend_String("1-Set Temp.");
							LCD_Move_Cursor(2,1);
							LCD_vSend_String("2-Control 3-Ret");
							do
							{
								if((session_counter>ADMIN_TIMEOUT) && (login_mode==ADMIN_MODE))			//check if session expired
								{
									TIME_OUT_FLAG=TRUE;								//in case that session expired write 1 to timout FLAG
									break;
								}
								Key_Pressed=KeyPad_u8Check_Pressed('D');
							} while (Key_Pressed==NOTPRESSED);						//wait till user choose from menu
							_delay_ms(250);
							
							if(Key_Pressed == SELECT_SET_TEMP)						//case user enter 1 
							{
								show_menu=TEMPREATURE_MENU;						//goto Tempreature menu in switch
							}
							else if(Key_Pressed == SELECT_AIR_COND_CTRL)			//case user enter 2
							{
								show_menu=AIR_COND_CTRL_MENU;					//goto control Air cond. menu in switch
							}
							else if(Key_Pressed == SELECT_AIR_COND_RET)				//case user enter 3 
							{
								show_menu=MORE_MENU;							//goto more menu in switch
							}
							
							else//in case user press anything except 1,2,3
							{
								LCD_Clear_Screen();
								LCD_vSend_String("Wrong input!");
								_delay_ms(500);
							}
						} while (Key_Pressed<'1' && Key_Pressed>'3' && TIME_OUT_FLAG==FALSE);//loop while user did not enter any of this (1,2,3) and the session didn't expired
					break;	
					/*********************menu that user select befor*****************/	
					case ROOM1_MENU:
						Menu_Options(ROOM1_MENU,login_mode);			//function shows the menu of selected option
						show_menu=MAIN_MENU;							//goto MAIN_MENU in switch
					break;
					
					case ROOM2_MENU:
						Menu_Options(ROOM2_MENU,login_mode);			//function shows the menu of selected option
						show_menu=MAIN_MENU;							//goto MAIN_MENU in switch
					break;
					
					case ROOM3_MENU:
						Menu_Options(ROOM3_MENU,login_mode);			//function shows the menu of selected option
						show_menu=MAIN_MENU;							//goto MAIN_MENU in switch
					break;
					
					case ROOM4_MENU:
						Menu_Options(ROOM4_MENU,login_mode);			//function shows the menu of selected option
						show_menu=MAIN_MENU;							//goto MAIN_MENU in switch
					break;
						
					case TV_MENU:
						Menu_Options(TV_MENU,login_mode);				//function shows the menu of selected option
						show_menu=MORE_MENU;							//goto MORE_MENU in switch
					break;	
						
					case AIR_COND_CTRL_MENU:
						Menu_Options(AIR_COND_CTRL_MENU,login_mode);		//function shows the menu of selected option
						show_menu=AIR_COND_MENU;							//goto AIR_COND_MENU in switch
					break;
						
					case TEMPREATURE_MENU:
						while(tempreature==0 && TIME_OUT_FLAG==FALSE)		//loop while user didn't enter tempreature and session didn't expired
						{
							tempreature=0;
							Key_Pressed=NOTPRESSED;
							LCD_Clear_Screen();
							LCD_vSend_String("Set Temp.:__");
							LCD_vSend_char(0xDF);							//print degree symbol
							LCD_vSend_char('C');							//print celsius 
							LCD_Move_Cursor(1,11);						
							/************ //get first number**************/
							do
							{
								if((session_counter>ADMIN_TIMEOUT) && (login_mode==ADMIN_MODE))//check if Admin session Expired or Not
								{
									TIME_OUT_FLAG=TRUE;				//case session expired write 1 to timeout_Flag
									break;
								}
								Key_Pressed=KeyPad_u8Check_Pressed('D');
							} while (Key_Pressed==NOTPRESSED);
							_delay_ms(250);							//avoide duplicate press
							
							if(TIME_OUT_FLAG==TRUE)				
							{
								break;								//break from loop that ask about temp
							}
							
							if(Key_Pressed<'0' || Key_Pressed>'9')	//print message in case user enter anything not from (0 to 9)
							{
								LCD_Clear_Screen();
								LCD_vSend_String("wrong input!");
								_delay_ms(500);
							}
						else
							{
								LCD_vSend_char(Key_Pressed);
								temp_tens=(Key_Pressed-48);			//save the ascii code of tens number
								Key_Pressed=NOTPRESSED;				//remove the last value saved in it
							}
							/*******************************************************/
							/************** //get seconde number********************/
							do
							{
								if((session_counter>ADMIN_TIMEOUT) && (login_mode==ADMIN_MODE))//check if Admin session Expired or Not
								{
									TIME_OUT_FLAG=TRUE;				//case session expired write 1 to timeout_Flag
									break;
								}
								Key_Pressed=KeyPad_u8Check_Pressed('D');
							} while (Key_Pressed==NOTPRESSED);
							_delay_ms(250);							//avoide duplicate press
						
							if(TIME_OUT_FLAG==TRUE)
							{
								break;								//break from loop that ask about temp
							}
							
							if(Key_Pressed<'0' || Key_Pressed>'9')	//print message in case user enter anything not from (0 to 9)
							{
								LCD_Clear_Screen();
								LCD_vSend_String("wrong input!");
								_delay_ms(500);
							}
							else
							{
								LCD_vSend_char(Key_Pressed);
								temp_ones=(Key_Pressed-48);			//save ASCII OF ones NUMBER
								Key_Pressed=NOTPRESSED;				//remove the last value saved in it
							}
							/*************************************************************/
							tempreature=(temp_tens*10)+temp_ones;	//save the value of tempreature that user enters
							//(*10)=>to get the tens , then add it to temo_ones to get the whole tempreature value
							
							SPI_MasterTransmitchar(SET_TEMP);		//send message to slave to know that we will set the tempreature 
							_delay_ms(200);							//avoide data corruption
							SPI_MasterTransmitchar(tempreature);	//send the tempreature value
						
							LCD_Clear_Screen();
							LCD_vSend_String("Temp. Sent");			//message for user to know that tempreature set
							_delay_ms(500);
						}
						
						show_menu=AIR_COND_MENU;							//goto AIR_COND_MENU in switch						
					break;	
					/***********************************************************/
					
					default:
					break;			
			}//end of 2nd switch
			
		}							
    }//end of while 1
}//end of int main

ISR(TIMER0_COMP_vect)
{
	session_counter++;//Timer/counter to count the time of session expiration 
}