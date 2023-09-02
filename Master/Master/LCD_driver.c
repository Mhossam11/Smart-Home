/*
 * LCD_driver.c
 *
 * Created: 7/16/2023 11:15:08 PM
 *  Author: 20100
 */ 
#include "LCD_driver.h"
#define F_CPU 8000000UL
#include <util/delay.h>

static void send_falling_edge(void)
{
	DIO_Write(CONTROLPORT,EN,1);				//write 1 to enable pin
	_delay_ms(2);
	DIO_Write(CONTROLPORT,EN,0);
	_delay_ms(2);
}

void LCD_vSend_Cmd(char cmd)					//take the commands
{
	#if defined eight_bit_mode
	DIO_WRITE_PORT(PORTNAME,cmd);
	DIO_Write(CONTROLPORT,RS,0);				//write 0 to Rs 3shan da command
	send_falling_edge();
	_delay_ms(1);
	
	#elif defined four_bit_mode
	DIO_Write_High_Nibble(PORTNAME,cmd>>4);		//bab3t el hight 4 bit bto3 el cmd 3shan ana bb3t el command 3la marten
	DIO_Write(CONTROLPORT,RS,0);				//3shan da command 
	send_falling_edge();
	DIO_Write_High_Nibble(PORTNAME,cmd);		//send least 4 bit of command
	DIO_Write(CONTROLPORT,RS,0);				//3shan da command
	send_falling_edge();
	_delay_ms(1);
	
	#endif
}

void LCD_vInit(void)
{
	_delay_ms(200);								//step 1 delay 200ms estna el hardware
	////////eight bits mode/////////
	#if defined eight_bit_mode
	DIO_SET_Port_Direction(PORTNAME,1);			//set direction of data port
	
	DIO_set_PINDir(CONTROLPORT,EN,1);			//set direction of control bits 
	DIO_set_PINDir(CONTROLPORT,RW,1);
	DIO_set_PINDir(CONTROLPORT,RS,1);
	
	DIO_Write(CONTROLPORT,RW,0);				//write 0 to RW pin to write data
	
	LCD_vSend_Cmd(RETURN_HOME);					//by7ot el cursor 3nd awl 5ana
	_delay_ms(10);
	LCD_vSend_Cmd(EIGHT_BIT);					//config the 8 bits mode command
	_delay_ms(1);
	LCD_vSend_Cmd(CURSOR_ON);					//make cursor on
	_delay_ms(1);
	LCD_vSend_Cmd(CLR_SCREEN);					//clear screen if there is old data
	_delay_ms(10);
	LCD_vSend_Cmd(ENTRY_MODE);					//make cursor move right when i write
	_delay_ms(1);
	
	////////four bits mode/////////
	
	#elif defined four_bit_mode
	DIO_set_PINDir(PORTNAME,4,1);				//set direction of data port
	DIO_set_PINDir(PORTNAME,5,1);
	DIO_set_PINDir(PORTNAME,6,1);
	DIO_set_PINDir(PORTNAME,7,1);
	
	DIO_set_PINDir(CONTROLPORT,EN,1);			//set direction of command port
	DIO_set_PINDir(CONTROLPORT,RW,1);
	DIO_set_PINDir(CONTROLPORT,RS,1);
	
	DIO_Write(CONTROLPORT,RW,0);				//write 0 to RW pin as it data not command
	
	LCD_vSend_Cmd(RETURN_HOME);					//by7ot el cursor 3nd awl 5ana
	_delay_ms(10);
	LCD_vSend_Cmd(FOUR_BIT);
	_delay_ms(1);
	LCD_vSend_Cmd(CURSOR_ON);
	_delay_ms(1);
	LCD_vSend_Cmd(CLR_SCREEN);
	_delay_ms(10);
	LCD_vSend_Cmd(ENTRY_MODE);
	_delay_ms(1);
	
	#endif
}

void LCD_vSend_char(char data)
{
	#if defined eight_bit_mode
	DIO_WRITE_PORT(PORTNAME,data);			//baktb el charcter el ana 3ayzo 3la el port el 7addto
	DIO_Write(CONTROLPORT,RS,1);				//write 1 3la RS 3shan de data
	send_falling_edge();					//lazm da 3shan el enable
	_delay_ms(1);
	
	#elif defined four_bit_mode
	DIO_Write_High_Nibble(PORTNAME,data>>4);			//bab3t el 4 highest bits 3shan bb3t el data 3la marten
	DIO_Write(CONTROLPORT,RS,1);
	send_falling_edge();
	DIO_Write_High_Nibble(PORTNAME,data);
	DIO_Write(CONTROLPORT,RS,1);
	send_falling_edge();
	_delay_ms(1);
	
	#endif
}

void LCD_vSend_String(char *data)
{
	while((*data)!='\0')								//tol ma howa mwslsh lel NULL
	{
		LCD_vSend_char(*data);							//eb3t 7arf 7arf
		data++;
	}
}

void LCD_Clear_Screen(void)
{
	LCD_vSend_Cmd(CLR_SCREEN);
	_delay_ms(10);
}

void LCD_Move_Cursor(char row,char coloumn)
{
	char Cursor;
	if((row<1) || (row>2) ||(coloumn>16) || (coloumn<1))
	{
		Cursor=0x80;									//b7me nfse mn el 8ba2 fa brg3o 3and awl 5ana
	}
	else if(row==1)
	{
		Cursor=0x80+(coloumn-1);						//byw2f el cursor mkan mana 3awz fe row 1
	}
	else if(row==2)
	{
		Cursor=0xC0+(coloumn-1);						//byw2f el cursor mkan mana 3awz fe row 2
	}
	LCD_vSend_Cmd(Cursor);
	_delay_ms(1);
}