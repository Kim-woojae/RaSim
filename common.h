#ifndef COMMON_H
#define COMMON_H

#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include "config.h"

#define TRUE				1
#define FALSE				0
#define DESTROYED			0x01
#define HEADER 			0x02
#define MEMBER			0x03
#define RELAY				0x04
#define SCHED_ROUND_ROBIN		0x20
#define SCHED_FCFS				0x21
#define SCHED_USER_POLICY		0x22
#define BROADCAST			0x30
#define REQUEST			0x31
#define RESPONSE			0x32
#define READ				0x33
#define WRITE				0x34

struct _sensor{
	char *name;
	int value;
	int period;					// Unit: ms(milisecond)
	int action_count;
	float power_consumption;		// Unit: mW
	float operating_voltage;		// Unit: V
	struct _sensor *next;
};

struct _uptime{
	int total;
	int day;
	int hour;
	int minute;
	int second;
	int prev_sec;
};

struct _location{
	int x;
	int y;
};

struct _resource{
	int second;
	float idle_battery;
	float battery;
	float bandwidth;
	float avg_bandwidth;
	float latency;
	float cpu;
	float max_cpu;
	double total_cpu;
	double total_length;
	struct _uptime uptime;
	int number_of_transmissions;
};

struct _message{
	int thing_id;
	int sender_id;
	int receiver_id;
	char send_type;	// Specific node or connected all nodes
	char message_type; //  ( REQUEST || RESPONSE ) + (SENSOR_VALUE, RESOURCE, LOCATION, ...)
	char message[MAX_MESSAGE_SIZE];
	int sensor_value;
	double length;
	int number_of_transmissions;
};

struct _member{
	int thing_id;
	float distance;
	char role;
	struct _location location;
	struct _member *next;
};

typedef struct _TCB{
	int thread_id;
	int thing_id;
	int header_id;
	//int cluster_id;
	int status; // 
	char role;
	struct _location location;
	struct _resource resource;
	struct _message message;
	struct _sensor *sensor;
	struct _member *member_list;

}TCB;

#endif