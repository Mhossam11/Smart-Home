/*
 * LED.c
 *
 * Created: 7/12/2023 4:55:59 PM
 *  Author: 20100
 */ 
#include "DIO_driver.h"

void LED_vInit(unsigned char portname,unsigned char pinnumber)//EX:  ('A',0)
{
	DIO_set_PINDir(portname,pinnumber,1);
}

void LED_vTurnOn(unsigned char portname,unsigned char pinnumber)//EX:  ('A',7)
{
	DIO_Write(portname,pinnumber,1);
}

void LED_vTurnOFF(unsigned char portname,unsigned char pinnumber)//EX:  ('A',4)
{
	DIO_Write(portname,pinnumber,0);
}

void LED_vToggle(unsigned char portname,unsigned char pinnumber)//EX:  ('A',3)
{
	DIO_Toggle(portname,pinnumber);
}

