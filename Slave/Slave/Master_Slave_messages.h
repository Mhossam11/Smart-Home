/*
 * Master_Slave_messages.h
 *
 * Created: 8/22/2023 2:39:42 PM
 *  Author: 20100
 */ 


#ifndef MASTER_SLAVE_MESSAGES_H_
#define MASTER_SLAVE_MESSAGES_H_

#define DUMMY_DATA 0xFF					//if we didn't need to send data to slave

/***************************/
#define AIR_COND_ON 0x01				//message to turn_on the AC
#define AIR_COND_OFF 0x00				//message to turn_off the AC
/**************************/

#define ROOM1_STATUS	 0x11			//message to know the status of ROOM1
#define ROOM2_STATUS	 0x12			//message to know the status of ROOM2
#define ROOM3_STATUS	 0x13			//message to know the status of ROOM3
#define ROOM4_STATUS	 0x14			//message to know the status of ROOM4
#define TV_STATUS		 0x15			//message to know the status of TV
#define AIR_COND_STATUS  0x16			//message to know the status of AIR_COND


#define ROOM1_TURN_ON	 0x21			//message to trun_on ROOM1
#define ROOM2_TURN_ON	 0x22			//message to trun_on ROOM2
#define ROOM3_TURN_ON	 0x23			//message to trun_on ROOM3
#define ROOM4_TURN_ON  	 0x24			//message to trun_on ROOM4
#define TV_TURN_ON		 0x25			//message to trun_on TV
#define AIR_COND_TURN_ON 0x26			//message to trun_on AIR_COND


#define ROOM1_TURN_OFF	  0x31			//message to trun_off ROOM1
#define ROOM2_TURN_OFF	  0x32			//message to trun_off ROOM2
#define ROOM3_TURN_OFF	  0x33			//message to trun_off ROOM3
#define ROOM4_TURN_OFF	  0x34			//message to trun_off ROOM4
#define TV_TURN_OFF		  0x35			//message to trun_off TV
#define AIR_COND_TURN_OFF 0x36			//message to trun_off AIR_COND

#define SET_TEMP		  0x40			//message to set the temperature

#define ON_STATUS		  0x01			//message indicate that led is on
#define OFF_STATUS		  0x00			//message indicate that led is oFF

#endif /* MASTER_SLAVE_MESSAGES_H_ */