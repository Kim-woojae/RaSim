#include <stdlib.h>
#include <sys/time.h>

#include "resource.h"
#include "sensor.h"
#include "thing.h"

#define MICROSECOND				1000000
extern int g_RaSim_status;
pthread_t resource_manager;
int previous_second, previous_microsecond;
int resource_manager_status = TRUE;


void *resourceManager(){
	int i;
	unsigned int sampling_count = 0;
	setUptime();
	while(g_RaSim_status){
		sampling_count++;
		for(i=0; i<NUMBER_OF_THINGS; i++)
			calculateResource(i, sampling_count);
		usleep(1000000);
	}
	//return NULL;
	pthread_exit(NULL);
}

void makeResourceManager(){
	pthread_create(&resource_manager, NULL, resourceManager, NULL);
}

void calculateResource(int thing_id, unsigned int sampling_count){
	if(resource_manager_status != FALSE){
		calculateUptime(thing_id);
		calculateCPU(thing_id, sampling_count);
		calculateBandwidth(thing_id); // Max 1Mbps
		calculateBattery(thing_id);
	}
}

void calculateBattery(int thing_id){
	struct _resource *thing_resource;
	struct timeval current_timer;

	thing_resource = getResource(thing_id);

#ifdef IDLE
	// case: IDLE
	// Elapsed time(s) * 390mA / 3600 = x mAh
	int sec=0;
	gettimeofday(&current_timer, NULL);
	sec = current_timer.tv_sec - thing_resource->uptime.prev_sec;
	thing_resource->idle_battery = sec*390/3600;
#endif
#ifdef USING_SENSOR
	// case: Use sensor
	/*	Critical section start 	*/
	struct _sensor *sensor, *temp;
	sensor = getSensor(thing_id);
	temp = sensor;

	while(temp != NULL){
		float sensor_operating_current;		// Unit: mA
		sensor_operating_current = temp->power_consumption/temp->operating_voltage;
		thing_resource->battery += temp->action_count*(sensor_operating_current*\
															temp->period/3600);
		temp->action_count = 0;
		temp = temp->next;
	}
	/*	Critical section end 	*/
#endif
#ifdef USING_BLUETOOTH
	// case: Send/Receive message
	float transmission_time;
	float mA = 2.5;				// 10mW / 4V
	transmission_time = thing_resource->avg_bandwidth;
	thing_resource->battery += thing_resource->number_of_transmissions*\
													mA*transmission_time/3600;
	thing_resource->number_of_transmissions = 0;
#endif
	// TODO case: According to use CPU...?


}

void calculateCPU(int thing_id, unsigned int sampling_count){
	int thread_id;
	char command[64] = {0,};
	char data[20] = {0,};
	struct _resource *thing_resource;
	FILE *pipe;
	float cpu=0;
	char *ptr3;

	thing_resource = getResource(thing_id);
	thread_id = getThreadID(thing_id);
	sprintf(command, "top -n 1 -H -p %d | grep %d | awk '{print $10}'", thread_id, thread_id);
	pipe = popen(command, "r");
	fread(data, 1, 19, pipe);
	cpu = atof(data);
	thing_resource->total_cpu += cpu;
	thing_resource->cpu = (float)(thing_resource->total_cpu/(double)sampling_count);
	if(thing_resource->cpu == 0.0)
		thing_resource->max_cpu = 0.001;
	if(thing_resource->max_cpu < cpu)
	 	thing_resource->max_cpu = cpu;
	if(thing_id==1)
		printf("%.2f\n",thing_resource->cpu);
	pclose(pipe);
}

void calculateBandwidth(int thing_id){
	struct _resource *thing_resource;
	struct _message *thing_message;
	float length;

	thing_resource = getResource(thing_id);
	thing_message = getMessage(thing_id);
	length = (float)thing_message->length; // n*Byte -> n*(8 bit)
	if(thing_resource->uptime.total == 0)
		thing_resource->uptime.total = 1;
	thing_resource->avg_bandwidth = length/thing_resource->uptime.total/1250;
}

void setResourceManagerStatus(int status){
	resource_manager_status = status;
}

void setUptime(){
	struct _resource *resource;
	struct timeval current_timer;
	int i;

	for(i=0; i<NUMBER_OF_THINGS; i++){
		resource = getResource(i);
		gettimeofday(&current_timer, NULL);
		resource->uptime.prev_sec = current_timer.tv_sec;
	}
}

void calculateUptime(int thing_id){
	struct _resource *resource;
	struct timeval current_timer;
	int sec;
	
	resource = getResource(thing_id);
	gettimeofday(&current_timer, NULL);

	sec = current_timer.tv_sec - resource->uptime.prev_sec;
	resource->uptime.total = sec;
	resource->uptime.day = sec/(3600*24);
	sec %= (3600*24);
	resource->uptime.hour = sec/3600;
	sec %= 3600;
	resource->uptime.minute = sec/60;
	sec %= 60;
	resource->uptime.second = sec;
}