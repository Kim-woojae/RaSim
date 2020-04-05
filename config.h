#ifndef CONFIG_H
#define CONFIG_H

/*******			Essential configuration				********/
	#define	MAP_SIZE					1
	#define	NUMBER_OF_THINGS			2
	#define	BOUNDARY					10
	#define	PROCESSING_SPEED			1	// Up to 10
	#define	IDLE
	#define	USING_SENSOR
	#define	USING_BLUETOOTH
/*******************************************************************/

#define 	SECOND						4000
#define	RESOURCE_PERIOD			1000 //unit: ms
#define	MAX_MESSAGE_SIZE			513 //125000B>122KB->1Mbit
#define	MAX_TCB_Q_SIZE				64
#define	MAX_Q_SIZE					32

#endif