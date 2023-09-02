/*
 * SPI_driver.c
 *
 * Created: 8/8/2023 1:20:30 AM
 *  Author: 20100
 */ 
#include "SPI_driver.h"


void SPI_MasterInit(void)
{
	DIO_set_PINDir('B',4,1);		//set direction SS pin o/p
	DIO_set_PINDir('B',5,1);		//set direction MOSI pin o/p
	DIO_set_PINDir('B',7,1);		//set direction SCK pin o/p
	
	SET_BIT(SPCR,MSTR);				//set direction master bit 
	SET_BIT(SPCR,SPR0);				//set clk: F_CPU/16 fel master bs
	SET_BIT(SPCR,SPE);				//enable SPI hardware for master
	
	DIO_Write('B',4,1);				//write 1 to SS pin to disable transmission 			
}

void SPI_SlaveInit(void)
{
	SET_BIT(SPCR,SPE);				//enable spi hardware for slave
	DIO_set_PINDir('B',6,1);		//set direction MISO pin o/p
}

unsigned char SPI_MasterTransmitchar(unsigned char Data)
{
	DIO_Write('B',4,0);				//write 0 to SS pin to start transmission
	SPDR=Data;						//send data to slave
	while(READ_BIT(SPSR,SPIF)==0);	//wait till interrupt flag be high "serial transmission complete"
	return SPDR;					//return the exchanged data come from slave
}

unsigned char SPI_SlaveReceiverchar(unsigned char Data)
{
	SPDR=Data;						//send data to master
	while(READ_BIT(SPSR,SPIF)==0);	//wait till interrupt flag be high "serial transmission complete"
	return SPDR;					//return the exchanged data come from slave
}	