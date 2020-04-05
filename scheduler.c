#include <stdlib.h>

#include "thing.h"
#include "scheduler.h"

extern int g_RaSim_status;
void (*userPolicy)();
char schedule_policy;
int *thing_status[NUMBER_OF_THINGS];
int scheduler_status;
pthread_t rpi_scheduler;


void *rpiScheduler(){
	while(g_RaSim_status){
		switch(schedule_policy){
			case SCHED_FCFS:
				FCFS();
				break;
			case SCHED_ROUND_ROBIN:
				RR();
				break;
			case SCHED_USER_POLICY:
				userPolicy();
				break;
		}
		usleep(SECOND);
	}
	//return NULL;
	pthread_exit(NULL);
}

void makeRPiScheduler(){
	pthread_create(&rpi_scheduler, NULL, rpiScheduler, NULL);
}

void initScheduler(){
	int i;

	for(i=0; i<NUMBER_OF_THINGS; i++){
		if(scheduler_status == FALSE)
			break;
		thing_status[i] = getThingStatus(i);
	}
}


void setSchedulingPolicy(char policy){
	schedule_policy = policy;
}

void setUserPolicy(void (*user_schedule_policy)()){
	userPolicy = user_schedule_policy;
}

void RR(){
	int i;
	for(i=0; i<NUMBER_OF_THINGS; i++){
		if(scheduler_status == FALSE)
			break;
		*thing_status[i] = TRUE;
	}
}

void FCFS(){
	//ToDo
}

void setSchedulerStatus(int status){
	scheduler_status = status;
}
