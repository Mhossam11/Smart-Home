/*
 * Keypad_driver.h
 *
 * Created: 7/18/2023 4:45:17 PM
 *  Author: 20100
 */ 


#ifndef KEYPAD_DRIVER_H_
#define KEYPAD_DRIVER_H_

#include "DIO_driver.h"

#define NOTPRESSED 0xFF

void KeyPad_vInit(unsigned char portname);
unsigned char KeyPad_u8Check_Pressed(unsigned char portname);




#endif /* KEYPAD_DRIVER_H_ */