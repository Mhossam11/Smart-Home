/*
 * SPI_driver.h
 *
 * Created: 8/8/2023 1:21:25 AM
 *  Author: 20100
 */ 


#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_

#include "DIO_driver.h"
#include "MACROS.h"

#include <avr/io.h>

void SPI_MasterInit(void);

void SPI_SlaveInit(void);

unsigned char SPI_MasterTransmitchar(unsigned char Data);

unsigned char SPI_SlaveReceiverchar(unsigned char Data);

#endif /* SPI_DRIVER_H_ */