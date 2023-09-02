/*
 * Menu.c
 *
 * Created: 8/22/2023 1:49:04 PM
 *  Author: 20100
 */ 
#include "Menu.h"

/********externed from main************/
extern uint8 Key_Pressed;					//variable will take the read from keypad
extern uint8 show_menu;						//VARIABLE used to know which menu we choose	
/*************************************/

void Menu_Options(const uint8 selected_room,const uint8 selected_mode)//show the menu of the selected room
{

	/************will be sent by spi protocol********/	
	uint8 Status_Code=0;		//variable tell status of room
	uint8 Turn_ON_Code=0;		//variable turn on room
	uint8 Turn_OFF_Code=0;		//variable turn off room
	uint8 Send=0;				//variable to send using SPI protocol
	uint8 Receive=0;			//variable to Receive using SPI protocol
	/***********************************************/
	Key_Pressed=NOTPRESSED;						//remove the last value saved in it 
	do 
	{
		switch(selected_room)
		{
			case ROOM1_MENU:					//if user select Room1 
				Status_Code=ROOM1_STATUS;		//get status of the room
				Turn_ON_Code=ROOM1_TURN_ON;		//turn on the room
				Turn_OFF_Code=ROOM1_TURN_OFF;	//turn off the room
				LCD_Clear_Screen();
				LCD_vSend_String("Room1 S:");//print status of the room
			break;
		
			case ROOM2_MENU:					//if user select Room2
				Status_Code=ROOM2_STATUS;		//get status of the room
				Turn_ON_Code=ROOM2_TURN_ON;		//turn on the room
				Turn_OFF_Code=ROOM2_TURN_OFF;	//turn off the room
				LCD_Clear_Screen();
				LCD_vSend_String("Room2 S:");	//print status of the room
			break;
		
			case ROOM3_MENU:					//if user select Room3
		
				Status_Code=ROOM3_STATUS;		//get status of the room
				Turn_ON_Code=ROOM3_TURN_ON;		//turn on the room
				Turn_OFF_Code=ROOM3_TURN_OFF;	//turn off the room
				LCD_Clear_Screen();
				LCD_vSend_String("Room3 S:");	//print status of the room
			break;
		
			case ROOM4_MENU:					//if user select Room4
		
				Status_Code=ROOM4_STATUS;		//get status of the room
				Turn_ON_Code=ROOM4_TURN_ON;		//turn on the room
				Turn_OFF_Code=ROOM4_TURN_OFF;	//turn off the room
				LCD_Clear_Screen();
				LCD_vSend_String("Room4 S:");	//print status of the room
			break;
			
			case TV_MENU:
				Status_Code=TV_STATUS;			//get status of the TV	
				Turn_ON_Code=TV_TURN_ON;		//turn on the TV
				Turn_OFF_Code=TV_TURN_OFF;		//turn off the TV
				LCD_Clear_Screen();
				LCD_vSend_String("TV  S:");		//print status of the TV
			break;
			
			case AIR_COND_CTRL_MENU:
				Status_Code=AIR_COND_STATUS;			//get status of the AIR_COND	
				Turn_ON_Code=AIR_COND_TURN_ON;			//turn on the  AIR_COND
				Turn_OFF_Code=AIR_COND_TURN_OFF;		//turn off the  AIR_COND
				LCD_Clear_Screen();
				LCD_vSend_String("Air Cond. S:");		//print status of the AIR_COND
				break;
		}//end of switch	
		
		/*********tell status of the room**********/	
			SPI_MasterTransmitchar(Status_Code);		//Send [message] to slvae to know which option we need its status 
			_delay_ms(150);								//to avoide corruption of data
			Receive=SPI_MasterTransmitchar(DUMMY_DATA);//get status [value] of the selected option from slave
			//_delay_ms(100);
			
			if(Receive==ON_STATUS)
			{
				LCD_vSend_String("ON");					//print on in case slave send that the led is already on
			}
			else 
			{
				LCD_vSend_String("OFF");				//print off in case slave send that the led is already off
			}
		/*****************************************/
		
		/**************turn on or off the room****************/
			LCD_Move_Cursor(2,1);
			LCD_vSend_String("1-ON 2-OFF 3-Ret");		//print menu of selected room
		
			do 
			{
				Key_Pressed=KeyPad_u8Check_Pressed('D');
			} while (Key_Pressed==NOTPRESSED);
			_delay_ms(200);								//avoide duplicate press
		
			if(Key_Pressed=='1')						//if user select TURN_ON_LED
			{
				SPI_MasterTransmitchar(Turn_ON_Code);	//send message to slave to know that it will TURN_ON the selected LED
			}
			else if(Key_Pressed=='2')						//if user select TURN_OFF_LED
			{
				SPI_MasterTransmitchar(Turn_OFF_Code);	//send message to slave to know that it will TURN_OFF the selected LED
			}
			else if (Key_Pressed=='3')						//if user select Return 
			{
				show_menu=MAIN_MENU;						//goback to the main menu
			}
			else
			{
				LCD_Clear_Screen();
				LCD_vSend_String("wrong input");
			}
		
	} while ((Key_Pressed<'1') || (Key_Pressed>'3'));	//loop while user didn'y enter any number from 1,2,3
}