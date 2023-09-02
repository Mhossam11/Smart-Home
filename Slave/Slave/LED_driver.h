/*
 * LED.h
 *
 * Created: 7/12/2023 4:56:09 PM
 *  Author: 20100
 */ 


#ifndef LED_H_
#define LED_H_

#include "STD_Types.h"


void LED_vInit(unsigned char portname,unsigned char pinnumber);

void LED_vTurnOn(unsigned char portname,unsigned char pinnumber);

void LED_vTurnOFF(unsigned char portname,unsigned char pinnumber);

void LED_vToggle(unsigned char portname,unsigned char pinnumber);

uint8 LED_u8ReadStatus(uint8 portname,uint8 pinnumber);

#endif /* LED_H_ */