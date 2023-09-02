/*
 * EEPROM_driver.c
 *
 * Created: 7/15/2023 12:05:20 AM
 *  Author: 20100
 */ 
#include <avr/io.h>
#include "MACROS.h"
void EEPROM_Write(unsigned short address,unsigned char data)	//dayman el write ykon bara el while 1
{
	EEARL=(char)address;	//awl 8-bit mn el address
	EEARH=(char)(address>>8);	//tany 8-bit mn el address
	
	EEDR=data;		//save data that you entered in data register
	
	SET_BIT(EECR,EEMWE);	//set master enable 3shan yebd2 ye3ml write
	SET_BIT(EECR,EEWE);		//set write enable to start writing 
	
	while(READ_BIT(EECR,EEMWE));	//loop yfdl feha tol mahowa lsa by3ml writing 
}


unsigned char EEPROM_Read(unsigned short address)
{
	EEARL=(char)address;
	EEARH=(char)(address>>8);
	
	SET_BIT(EECR,EERE);
	
	return EEDR;
}