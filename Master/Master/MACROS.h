/*
 * MACROS.h
 *
 * Created: 7/11/2023 2:23:32 PM
 *  Author: 20100
 */ 


#ifndef MACROS_H_
#define MACROS_H_

#define SET_BIT(reg,bit)	reg|=(1<<bit)
#define CLR_BIT(reg,bit)	reg&=(~(1<<bit))
#define TOG_BIT(reg,bit)	reg^=(1<<bit)
#define READ_BIT(reg,bit)	((reg&(1<<bit))>>bit)
#define ROR(reg,num)		reg=((reg<<(8-num))|(reg>>num))		//num is number of rotations 
#define ROL(reg,num)		reg=((reg>>(8-num))|(reg<<num))


#endif /* MACROS_H_ */