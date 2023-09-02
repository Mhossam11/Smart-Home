/*
 * Keypad_driver.c
 *
 * Created: 7/18/2023 4:45:02 PM
 *  Author: 20100
 */ 
#include "Keypad_driver.h"

void KeyPad_vInit(unsigned char portname)
{
	DIO_set_PINDir(portname,0,1);			//mtwslen bel row
	DIO_set_PINDir(portname,1,1);			//
	DIO_set_PINDir(portname,2,1);
	DIO_set_PINDir(portname,3,1);
	
	DIO_set_PINDir(portname,4,0);			//mtwslen bel col bab3t 0 3la kol row bel tarteb wlama ytdas 3la ay button hla2e 3la el col wsl zero w a2dr a3rf da ane button el etdas
	DIO_set_PINDir(portname,5,0);
	DIO_set_PINDir(portname,6,0);
	DIO_set_PINDir(portname,7,0);
	
	DIO_vConnectPullup(portname,4,1);
	DIO_vConnectPullup(portname,5,1);
	DIO_vConnectPullup(portname,6,1);
	DIO_vConnectPullup(portname,7,1);
}

unsigned char KeyPad_u8Check_Pressed(unsigned char portname)		//dymn gowa while 1
{
	unsigned char arr[4][4]={ {'7','8','9','-'}, {'4','5','6','*'} , {'1','2','3','/'} , {'A','0','=','+'} };
	unsigned char col,row,x;
	unsigned char return_value=NOTPRESSED;
	for(row=0;row<=3;row++)
	{
		DIO_Write(portname,0,1);			//write 1 to the first four pins
		DIO_Write(portname,1,1);
		DIO_Write(portname,2,1);
		DIO_Write(portname,3,1);
		DIO_Write(portname,row,0);			//write 0 3la kol row bel trteb 3shan lma button ytdas a2dr a7dd 3la el col ane wa7d bzbt el etdas
		
		for(col=0;col<=3;col++)
		{
			x=DIO_u8read(portname,(col+4));//b3ml read mn awl pin 4 bel trteb lel coloumn kolhom 
			
			if(x==0)						//law fe button etdas hyzhr 3la el col
			{
				return_value=arr[row][col];
				break;
			}
		}
		if(x==0)
		{
			break;
		}
	}
	return return_value;
}