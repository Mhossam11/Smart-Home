/*
 * DIO_driver.h
 *
 * Created: 7/11/2023 2:46:01 PM
 *  Author: 20100
 */ 


#ifndef DIO_DRIVER_H_
#define DIO_DRIVER_H_

void DIO_set_PINDir(unsigned char portname,unsigned char pinnumber,unsigned char Direction);

void DIO_Write(unsigned char portname,unsigned char pinnumber,unsigned char outputvalue);

unsigned char DIO_u8read(unsigned char portname,unsigned char pinnumber);

void DIO_Toggle(unsigned char portname,unsigned char pinnumber);

void DIO_SET_Port_Direction(unsigned char portname,unsigned char direction);

void DIO_WRITE_PORT(unsigned char portname, unsigned char outputvalue);

unsigned char DIO_Read_PORT(unsigned char portname);

void DIO_vConnectPullup(unsigned char portname,unsigned char pinnumber,unsigned char Connect_PullUp);

void DIO_Write_Low_Nibble(unsigned char portname,unsigned char value);

void DIO_Write_High_Nibble(unsigned char portname,unsigned char value);



#endif /* DIO_DRIVER_H_ */