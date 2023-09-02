/*
 * LCD_driver.h
 *
 * Created: 7/16/2023 11:15:22 PM
 *  Author: 20100
 */ 


#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

#include "DIO_driver.h"
#include "LCD_Config.h"

////////impportant commands///////
#define CLR_SCREEN		0X01	//BYMS7 EL SCREEN WBY7TAG DELAY 10MS
#define RETURN_HOME		0X02	//BYRG3 EL CURSOR AWL 5ANA
#define ENTRY_MODE		0X06	//KOL MA AKTB 7ARF YMSHE EL CURSOR YMEN
#define CURSOR_OFF		0X0C	//BYSHEL CURSOR 5ALS
#define CURSOR_ON		0X0E	//BYZHER EL CURSOR TANY
#define CURSPR_BLINK	0X0F	//TOGGLE CURSOR
#define SHIFT_DISPLAY_LEFT	0X18	//BYMSHE EL DISPLAY SHMAL 
#define SHIFT_DISPLAY_RIGHT	0X1C	//BYMSHE EL DISPLAY YMEN
//////////////////////////////////
#define EN	0
#define RS	1
#define RW	2
/////////////////////////////////
#if defined four_bit_mode
#define FOUR_BIT		0X28	//FOR 4-BIT MODE

#elif defined eight_bit_mode
#define EIGHT_BIT		0X38	//FOR 8-BIT MODE

#endif
//////////////PORT CONTROL///////////////////
#define PORTNAME		'A'
#define CONTROLPORT		'B'

///////////FUNCTIONS/////////////

static void send_falling_edge(void);

void LCD_vSend_Cmd(char cmd);

void LCD_vInit(void);

void LCD_vSend_char(char data);

void LCD_vSend_String(char *data);

void LCD_Clear_Screen(void);

void LCD_Move_Cursor(char row,char coloumn);



#endif /* LCD_DRIVER_H_ */