/*
 * DIO_driver.c
 *
 * Created: 7/11/2023 2:46:16 PM
 *  Author: 20100
 */ 
#include <avr/io.h>
#include "DIO_driver.h"
#include "MACROS.h"

void DIO_set_PINDir(unsigned char portname,unsigned char pinnumber,unsigned char Direction) //EX: ('A',0,1)
{
	switch(portname)
	{
		case 'A':
		case 'a':
		if(Direction==1)
		{
			SET_BIT(DDRA,pinnumber);
		}
		else 
		{
			CLR_BIT(DDRA,pinnumber);
		}
		break;
		
		case 'B':
		case 'b':
		if(Direction==1)
		{
			SET_BIT(DDRB,pinnumber);
		}
		else
		{
			CLR_BIT(DDRB,pinnumber);
		}
		break;
		
		case 'C':
		case 'c':
		if(Direction==1)
		{
			SET_BIT(DDRC,pinnumber);
		}
		else
		{
			CLR_BIT(DDRC,pinnumber);
		}
		break;
		
		case 'D':
		case 'd':
		if(Direction==1)
		{
			SET_BIT(DDRD,pinnumber);
		}
		else
		{
			CLR_BIT(DDRD,pinnumber);
		}
		break;
		
		default:
		break;
	}
}

void DIO_Write(unsigned char portname,unsigned char pinnumber,unsigned char outputvalue)//EX: ('A',0,1)
{
	switch(portname)
	{
		case 'A':
		case 'a':
		if(outputvalue==1)
		{
			SET_BIT(PORTA,pinnumber);
		}
		else 
		{
			CLR_BIT(PORTA,pinnumber);
		}
		break;
		
		case 'B':
		case 'b':
		if(outputvalue==1)
		{
			SET_BIT(PORTB,pinnumber);
		}
		else
		{
			CLR_BIT(PORTB,pinnumber);
		}
		break;
		
		case 'C':
		case 'c':
		if(outputvalue==1)
		{
			SET_BIT(PORTC,pinnumber);
		}
		else 
		{
			CLR_BIT(PORTC,pinnumber);
		}
		break;
		
		case 'D':
		case 'd':
		if(outputvalue==1)
		{
			SET_BIT(PORTD,pinnumber);
		}
		else
		{
			CLR_BIT(PORTD,pinnumber);
		}
		break;
		
		default:
		break;
	}
}

unsigned char DIO_u8read(unsigned char portname,unsigned char pinnumber)//EX: ('A',0)
{
	unsigned char return_value=0;
	switch(portname)
	{
		case 'A':
		case 'a':
		return_value=READ_BIT(PINA,pinnumber);
		break;
		
		case 'B':
		case 'b':
		return_value=READ_BIT(PINB,pinnumber);
		break;
		
		case 'C':
		case 'c':
		return_value=READ_BIT(PINC,pinnumber);
		break;
		
		case 'D':
		case 'd':
		return_value=READ_BIT(PIND,pinnumber);
		break;
		
		default:
		break;
	}
	return return_value;
}

void DIO_Toggle(unsigned char portname,unsigned char pinnumber)//EX: ('A',0)
{
	switch(portname)
	{
		case 'A':
		case 'a':
		TOG_BIT(PORTA,pinnumber);
		break;
		
		case 'B':
		case 'b':
		TOG_BIT(PORTB,pinnumber);
		break;
		
		case 'C':
		case 'c':
		TOG_BIT(PORTC,pinnumber);
		break;
		
		case 'D':
		case 'd':
		TOG_BIT(PORTD,pinnumber);
		break;
	}
}

void DIO_SET_Port_Direction(unsigned char portname,unsigned char direction)//EX: ('A',0xFF)
{
	switch(portname)
	{
		case 'A':
		case 'a':
		DDRA=direction;
		break;
		
		case 'B':
		case 'b':
		DDRB=direction;
		break;
		
		case 'C':
		case 'c':
		DDRC=direction;
		break;
		
		case 'D':
		case 'd':
		DDRD=direction;
		break;
		
		default:
		break;
	}
}

void DIO_WRITE_PORT(unsigned char portname, unsigned char outputvalue)//EX: ('A',0xFF)
{
	switch(portname)
	{
		case 'A':
		case 'a':
		PORTA=outputvalue;
		break;
		
		case 'B':
		case 'b':
		PORTB=outputvalue;
		break;
		
		case 'C':
		case 'c':
		PORTC=outputvalue;
		break;
		
		case 'D':
		case 'd':
		PORTD=outputvalue;
		break;
		
		default:
		break;
	}
}

unsigned char DIO_Read_PORT(unsigned char portname)
{
	unsigned char return_value=0;
	switch(portname)
	{
		case 'A':
		case 'a':
		return_value=PINA;
		break;
		
		case 'B':
		case 'b':
		return_value=PINB;
		break;
		
		case 'C':
		case 'c':
		return_value=PINC;
		break;
		
		case 'D':
		case 'd':
		return_value=PIND;
		break;
		
		default:
		break;
		
	}
	return return_value;
}

void DIO_vConnectPullup(unsigned char portname,unsigned char pinnumber,unsigned char Connect_PullUp)
{
	switch(portname)
	{
		case 'A':
		case 'a':
		if (Connect_PullUp==1)
		{
			SET_BIT(PORTA,pinnumber);
		}
		else
		{
			CLR_BIT(PORTA,pinnumber);
		}
		break;
		
		
		case 'B':
		case 'b':
		if(Connect_PullUp==1)
		{
			SET_BIT(PORTB,pinnumber);
		}
		else
		{
			CLR_BIT(PORTB,pinnumber);
		}
		break;
		
		
		case 'C':
		case 'c':
		if(Connect_PullUp==1)
		{
			SET_BIT(PORTC,pinnumber);
		}
		else
		{
			CLR_BIT(PORTC,pinnumber);
		}
		break;
		
		
		case 'D':
		case 'd':
		if(Connect_PullUp==1)
		{
			SET_BIT(PORTD,pinnumber);
		}
		else
		{
			CLR_BIT(PORTD,pinnumber);
		}
		break;
		
		default:
		break;
	}
}


void DIO_Write_Low_Nibble(unsigned char portname,unsigned char value)////EX: ('B',0x08)
{
	value &=0x0F;	//b7me nfse mn 8ba2 el user 3shan law da5l value akbr mn 9
	
	switch(portname)
	{
		case 'A':
		case 'a':
		PORTA &=0xF0;	//basfr el low nibble fel port da
		PORTA |=value;	//btl3 el value bt3te
		break;
		
		case 'B':
		case 'b':
		PORTB &=0xF0;	//bsfr low nibble fel port da
		PORTB |=value;
		break;
		
		case 'C':
		case 'c':
		PORTC &=0xF0;
		PORTC |=value;
		break;
		
		case 'D':
		case 'd':
		PORTD &=0xF0;
		PORTD |=value;
		break;
		
		default:
		break;
	}
}

void DIO_Write_High_Nibble(unsigned char portname,unsigned char value)  //EX: ('a',0x02)
{
	value<<=4;		//ba7me nafse mn 8ba2 el user
	
	switch(portname)
	{
		case 'A':
		case 'a':
		PORTA &=0x0F;	//basfr el high nibble 3shan law fe value adema
		PORTA |=value;	//btl3 el value bt3te
		break;
		
		case 'B':
		case'b':
		PORTB &=0x0F;	//basfr el high nibble
		PORTB |=value;	//btl3 el value bt3te
		break;
		
		case 'C':
		case 'c':
		PORTC &=0x0F;
		PORTC |=value;
		break;
		
		case 'D':
		case 'd':
		PORTD &=0x0F;
		PORTD |=value;
		break;
		
		default:
		break;
		
	}
}
