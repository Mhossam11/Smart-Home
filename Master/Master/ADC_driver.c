/*
 * CFile1.c
 *
 * Created: 7/21/2023 11:59:30 PM
 *  Author: 20100
 */ 
#include "MACROS.h"
#include <avr/io.h>

void ADC_vInit(void)	//by default bysht8l 3la pin 0 port A ela law 8ayrtha mn ADMUX
{
	SET_BIT(ADMUX,REFS0);		//Vref howa el volt el internal  bas lazm a7ot capacitor ma3 pin AREF
	SET_BIT(ADMUX,REFS1);
	
	SET_BIT(ADCSRA,ADEN);		//ENABLE ADC
	
	SET_BIT(ADCSRA,ADPS2);		//DIVISION FACTOR IS 64
	SET_BIT(ADCSRA,ADPS1);
}

unsigned short ADC_u16Read(void)
{
	unsigned short return_value;
	SET_BIT(ADCSRA,ADSC);
	while(READ_BIT(ADCSRA,ADSC)==1);		//loop yfdl mkano tol ma el ADSC=1 hya msh htrg3 0 8er lma el conversion ttem 5als
	SET_BIT(ADCSRA,ADIF);					//clear el interrupt flag 
	
	return_value=(ADCL);
	return_value|=(ADCH<<8);
	
	return return_value;
}