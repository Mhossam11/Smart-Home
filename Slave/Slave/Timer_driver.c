/*
 * Timer_driver.c
 *
 * Created: 7/25/2023 11:37:23 PM
 *  Author: 20100
 */ 
#include "MACROS.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "MACROS.h"

void Timer_stop_CTC_mode(void)
{
	/*CLR_BIT(TCCR0,CS00);
	CLR_BIT(TCCR0,CS01);
	CLR_BIT(TCCR0,CS02);*/
	//disable the clock to stop the counter
	CLR_BIT(TCCR0, CS00);
	CLR_BIT(TCCR0, CS01);
	CLR_BIT(TCCR0, CS02);
}

void Timer_CTC_Init_interrupt(void)
{
	/*OCR0=78;						//load 80 in OCR0 80*0.125*(10^-4)-> byro7 lel ISR kol 10msec

	SET_BIT(TCCR0,WGM01);			//enable CTC mode WGM01=1,WGM00=0
	CLR_BIT(TCCR0, WGM00);
	
		
	SET_BIT(TCCR0,CS00);			//let the prescaler=1024
	CLR_BIT(TCCR0,CS01);
	SET_BIT(TCCR0,CS02); 
	
	sei();							//enable I-bet
	SET_BIT(TIMSK,OCIE0);			//enable ctc inttterupt bit */
	
	//Config OCR0
	//OCR0 = the value to compare with
	OCR0 = 78; //to achieve tick equal to 10 msec
	
	//Set timer mode
	//Set the mode as Compare match
	SET_BIT(TCCR0, WGM01);
	CLR_BIT(TCCR0, WGM00);
	
	//Configure clock
	//set as clk/1024
	SET_BIT(TCCR0, CS00);
	CLR_BIT(TCCR0, CS01);
	SET_BIT(TCCR0, CS02);
	
	//Enable global interrupts
	sei();
	
	//Enable timer 0 interrupt for compare match
	SET_BIT(TIMSK, OCIE0);
}

void Timer2_OverFlow_Init_interrupt(void)
{
	SET_BIT(ASSR,AS2);				//3SHAN YA5OD EL CLOCK MN EXTERNAL CRYSTAL 
	
	SET_BIT(TCCR2,CS22);			//SELECT PRESCALER 128 3shan yro7 el ISR kol sanya bzbt
	SET_BIT(TCCR2,CS20);
	
	sei();
	SET_BIT(TIMSK,TOIE2);			//enable interrupt
}