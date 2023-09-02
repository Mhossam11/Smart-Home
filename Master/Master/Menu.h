/*
 * Menu.h
 *
 * Created: 8/22/2023 1:48:55 PM
 *  Author: 20100
 */ 


#ifndef MENU_H_
#define MENU_H_

#include "Master_Slave_messages.h"
#include "STD_Types.h"
#include "SPI_driver.h"
#include "LCD_driver.h"
#include "Main_macros.h"

#define F_CPU 8000000ul
#include <util/delay.h>

void Menu_Options(const uint8 selected_room,const uint8 selected_mode);


#endif /* MENU_H_ */