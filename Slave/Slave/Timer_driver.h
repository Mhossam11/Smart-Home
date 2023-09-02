/*
 * Timer_driver.h
 *
 * Created: 7/25/2023 11:37:35 PM
 *  Author: 20100
 */ 


#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_

void Timer_stop_CTC_mode(void);

void Timer_CTC_Init_interrupt(void);

void Timer2_OverFlow_Init_interrupt(void);


#endif /* TIMER_DRIVER_H_ */