/*
 * Master_Slave_messages.h
 *
 * Created: 8/22/2023 2:39:42 PM
 *  Author: 20100
 */ 


#ifndef MASTER_SLAVE_MESSAGES_H_
#define MASTER_SLAVE_MESSAGES_H_

#define ROOM1_STATUS	 0x11
#define ROOM2_STATUS	 0x12
#define ROOM3_STATUS	 0x13
#define ROOM4_STATUS	 0x14
#define TV_STATUS		 0x15
#define AIR_COND_STATUS  0x16


#define ROOM1_TURN_ON	 0x21
#define ROOM2_TURN_ON	 0x22
#define ROOM3_TURN_ON	 0x23
#define ROOM4_TURN_ON  	 0x24
#define TV_TURN_ON		 0x25
#define AIR_COND_TURN_ON 0x26


#define ROOM1_TURN_OFF	  0x31
#define ROOM2_TURN_OFF	  0x32
#define ROOM3_TURN_OFF	  0x33
#define ROOM4_TURN_OFF	  0x34
#define TV_TURN_OFF		  0x35
#define AIR_COND_TURN_OFF 0x36

#define SET_TEMP		  0x40

#define ON_STATUS		  0x01
#define OFF_STATUS		  0x00

#endif /* MASTER_SLAVE_MESSAGES_H_ */