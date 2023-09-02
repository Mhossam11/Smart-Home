/*
 * Slave.c
 *
 * Created: 8/22/2023 8:33:50 PM
 *  Author: 20100
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000ul
#include <util/delay.h>

#include "ADC_driver.h"
#include "LED_driver.h"
#include "STD_Types.h"
#include "Main_macros.h"
#include "SPI_driver.h"
#include "Master_Slave_messages.h"

volatile uint8 counter=0;								//counter that count the ticks
volatile uint16 Required_Temp=24;						//Temp that user will input and INITIALY by 24
volatile uint16 Temp_Sensor_Reading=0;					//Temp that will read from temp sensor
volatile uint8 Last_Air_Cond_Value=AIR_COND_OFF;		//save the last status of the air_cond

int main(void)
{
	/*************INITIALIZATION************/
	LED_vInit('D',0);									//init Room1 led
	LED_vInit('D',1);									//init Room2 led
	LED_vInit('D',2);									//init Room3 led
	LED_vInit('D',3);									//init Room4 led
	LED_vInit('D',4);									//init TV led
	LED_vInit('D',5);									//init air_cond led
	
	ADC_vInit();										//initialize ADC
	SPI_SlaveInit();									//initialize SPI protocol
	_delay_ms(500);										//delay used in slave to wait the master LCD delay
	/**************************/
	
	/***************variable to send and receive using spi**********/
	uint8 Send=0;										//variable to send using SPI protocol
	uint8 receive=0;									//variable to RECEIVE using SPI protocol
	/*************************************************************/
    while(1)
    {
         receive=SPI_SlaveReceiverchar(DUMMY_DATA);		//exchanging data=> receive the message from master to know which action to perform
		 
		 switch(receive)//switch on the message that come from the master
		 {
			 /***********status of ROOMS**************/
			 case ROOM1_STATUS:							//case master send message ask about status of room1
					if(LED_u8ReadStatus('D',0)==1)		//read the value of the led
					{
						Send=ON_STATUS;					//send message to indicate that the led is ON
					}
					else if(LED_u8ReadStatus('D',0)==0)	//read the value of the led
					{
						Send=OFF_STATUS;				//send message to indicate that the led is OFF
					}
					else{}
					SPI_SlaveReceiverchar(Send);		//send the status of room1
				break;
				
				
			case ROOM2_STATUS:							//case master send message ask about status of room2
					if(LED_u8ReadStatus('D',1)==1)		//read the value of the led
					{
						Send=ON_STATUS;					//send message to indicate that the led is ON
					}
					else if(LED_u8ReadStatus('D',1)==0)	//read the value of the led
					{
						Send=OFF_STATUS;				//send message to indicate that the led is OFF
					}
				else{}
				SPI_SlaveReceiverchar(Send);			//send the status of room2
			break;
				
				
			case ROOM3_STATUS:							//case master send message ask about status of room3
				if(LED_u8ReadStatus('D',2)==1)			//read the value of the led
				{
					Send=ON_STATUS;						//send message to indicate that the led is ON
				}
				else if(LED_u8ReadStatus('D',2)==0)		//read the value of the led
				{
					Send=OFF_STATUS;					//send message to indicate that the led is OFF
				}
				
				else{}
				SPI_SlaveReceiverchar(Send);		//send the status of room3
			break;
					
			case ROOM4_STATUS:							//case master send message ask about status of room4
				if(LED_u8ReadStatus('D',3)==1)			//read the value of the led
				{
					Send=ON_STATUS;						//send message to indicate that the led is ON
				}
				else if(LED_u8ReadStatus('D',3)==0)		//read the value of the led
				{
					Send=OFF_STATUS;					//send message to indicate that the led is OFF
				}
				else{}
				SPI_SlaveReceiverchar(Send);			//send the status of room4
			break;
				
			case TV_STATUS:								//case master send message ask about status of TV
				if(LED_u8ReadStatus('D',4)==1)			//read the value of the led
				{
					Send=ON_STATUS;						//send message to indicate that the led is ON
				}
				else if(LED_u8ReadStatus('D',4)==0)		//read the value of the led
				{
					Send=OFF_STATUS;					//send message to indicate that the led is OFF
				}
				else{}
				SPI_SlaveReceiverchar(Send);			//send the status of TV
			break;
			
			case AIR_COND_STATUS:						//case master send message ask about status of AIR_COND
				if(LED_u8ReadStatus('D',5)==1)			//read the value of the led
				{
					Send=ON_STATUS;						//send message to indicate that the led is ON
				}
				else if(LED_u8ReadStatus('D',5)==0)		//read the value of the led
				{
					Send=OFF_STATUS;					//send message to indicate that the led is OFF
				}
			else{}
			SPI_SlaveReceiverchar(Send);				//send the status of AIR_COND
			break;
			/******************************************************************/
			
			/**************on and off commands*************/
			case ROOM1_TURN_ON:							//case master send message to turn_ON room1
				LED_vTurnOn('D',0);
				break;
			case ROOM1_TURN_OFF:						//case master send message to turn_Off room1
				LED_vTurnOFF('D',0);
				break; 
				
			case ROOM2_TURN_ON:							//case master send message to turn_ON room2
				LED_vTurnOn('D',1);
				break;
			case ROOM2_TURN_OFF:						//case master send message to turn_OFF room2
				LED_vTurnOFF('D',1);
				break;
						
				case ROOM3_TURN_ON:						//case master send message to turn_ON room3
				LED_vTurnOn('D',2);
				break;
			case ROOM3_TURN_OFF:						//case master send message to turn_OFF room4
				LED_vTurnOFF('D',2);
				break;
				
			case ROOM4_TURN_ON:							//case master send message to turn_ON room4
				LED_vTurnOn('D',3);
				break;
			case ROOM4_TURN_OFF:						//case master send message to turn_OFF room4
				LED_vTurnOFF('D',3);
				break;
				
			case TV_TURN_ON:							//case master send message to turn_ON TV
				LED_vTurnOn('D',4);
				break;
			case TV_TURN_OFF:							//case master send message to turn_OFF TV
				LED_vTurnOFF('D',4);
				break;		
				
			case AIR_COND_TURN_ON:						//case master send message to turn_ON AIR_COND
				Timer_CTC_Init_interrupt();				//start timer0 to start count ticks case air_cond on
				LED_vTurnOn('D',5);
				break;
			case AIR_COND_TURN_OFF:						//case master send message to turn_OFF AIR_COND
				Timer_stop_CTC_mode();					//stop timer0 case air_cond off
				LED_vTurnOFF('D',5);
			break;		
				/**************************************************/
				
			/****************set temp*****************/
			case SET_TEMP:								//case master send message to set Tempreature
			
				Required_Temp=SPI_SlaveReceiverchar(DUMMY_DATA);	//take the tempreature value from master
			
			break;
		/*********************************************/
		 }			 
    }
}

ISR(TIMER0_COMP_vect)
{
	counter++;													//start counting 
	if(counter>=10)												//repeat every 10msec
	{
		counter=0;												//remove the value saved in counter to repeat the loop
		
		Temp_Sensor_Reading=(0.25*ADC_u16Read());				//0.25=>((2.56*1000*x)/(10*1024))
		//calculate the value that the sensor reads 
		
		if(Temp_Sensor_Reading>=(Required_Temp+1))				//if the reading of the sensor MORE than the value of temp that the user set
		{
			LED_vTurnOn('D',5);									//OPEN the AIR_COND
			Last_Air_Cond_Value=AIR_COND_ON;					//save the last status of the Air_cond
		}
		else if(Temp_Sensor_Reading<=(Required_Temp-1))			//if the reading of the sensor LESS than the value of temp that the user set
		{
			LED_vTurnOFF('D',5);								//CLOSE the AIR_COND
			Last_Air_Cond_Value=AIR_COND_OFF;
		}
		else if (Temp_Sensor_Reading==Required_Temp)			//if the reading of the sensor EQUAL than the value of temp that the user set
		{//follow the last status of Air_cond
			if(Last_Air_Cond_Value==AIR_COND_ON)
			{
				LED_vTurnOn('D',5);
			}
			else if(Last_Air_Cond_Value==AIR_COND_OFF)
			{
				LED_vTurnOFF('D',5);
			}
		}
	}
}