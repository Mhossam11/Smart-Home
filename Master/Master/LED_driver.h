/*
 * LED.h
 *
 * Created: 7/12/2023 4:56:09 PM
 *  Author: 20100
 */ 


#ifndef LED_H_
#define LED_H_

void LED_vInit(unsigned char portname,unsigned char pinnumber);

void LED_vTurnOn(unsigned char portname,unsigned char pinnumber);

void LED_vTurnOFF(unsigned char portname,unsigned char pinnumber);

void LED_vToggle(unsigned char portname,unsigned char pinnumber);


#endif /* LED_H_ */