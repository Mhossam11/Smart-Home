/*
 * EEPROM_driver.h
 *
 * Created: 7/15/2023 12:05:40 AM
 *  Author: 20100
 */ 


#ifndef EEPROM_DRIVER_H_
#define EEPROM_DRIVER_H_

void EEPROM_Write(unsigned short address,unsigned char data);

unsigned char EEPROM_Read(unsigned short address);



#endif /* EEPROM_DRIVER_H_ */