#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <errno.h>
#include "rasim.h"
#include "event.h"

TCB *g_tcb;
int g_RaSim_status = TRUE;
pthread_t raspberry_pi[NUMBER_OF_THINGS];

void handler(){
	static int called = 0;
	if(called == 1)
		return;
	called = 1;
	g_RaSim_status = FALSE;
	usleep(100000);
	exitRaSim();
}

void *raspberryPi(void *arg){
	TCB *tcb = (TCB*)arg;
	tcb->thread_id = syscall(SYS_gettid);
	while(g_RaSim_status){
		if(tcb->status){
			switch(tcb->role){
				case HEADER:
					header(tcb); break;
				case MEMBER:
					// if(tcb->thing_id==0)
					// 	receiveMessage(tcb->thing_id, &tcb->message);

					member(tcb); break;
				case RELAY:
					relay(tcb); break;
			}
		}
		tcb->status = FALSE;
		usleep(SECOND);
	}
	//return NULL;
	pthread_exit(NULL);
}

void makeRaspberryPi(){
	int i;
	for(i=0; i<NUMBER_OF_THINGS; i++){
		newSensor(i, "temp", 10, 10, 10);
		g_tcb[i].sensor = getSensor(i);
		pthread_create(&raspberry_pi[i], NULL, raspberryPi, (void *)&g_tcb[i]);
	}
}

void initRaSim(char location, char *path, char policy, void (*user_policy)()){
	signal(SIGINT, handler);
	g_tcb = createThings(location, path);
	//initSensorList();
	//initLocationList();
	initDistanceTable();
	initDestroyedThingsList();
	setSchedulerStatus(TRUE);
	setResourceManagerStatus(TRUE);
	initScheduler();
	//printThings();
	switch(policy){
		case SCHED_USER_POLICY:
			setUserPolicy(user_policy);
		default:
			setSchedulingPolicy(policy);
	}
	srand((unsigned)time(NULL));
}

void connectAroundNode(){
	int i;

	for(i=0; i<NUMBER_OF_THINGS; i++){
		if(0 > connectNode(g_tcb[i].member_list, g_tcb[i].thing_id)){
			printf("Connect Fail\n");
		}
	}
}

void startRaSim(){
	int i;
	
	makeRaspberryPi();
	makeResourceManager();
	makeRPiScheduler();
	for(i=0; i<NUMBER_OF_THINGS; i++)
		//pthread_join(raspberry_pi[i], NULL);
		pthread_detach(raspberry_pi[i]);
	pause();
}

void exitRaSim(){
	int i;
	
	fflush(stdout);
	setSchedulerStatus(FALSE);
	setResourceManagerStatus(FALSE);
	usleep(1000);

	for(i=0; i<NUMBER_OF_THINGS; i++)
		freeConnectedNodes(g_tcb[i].member_list);
	usleep(1000000);
	freeSensor();
	freeDestroyedTCB();
	freeTCB(g_tcb);
	printf("Exit RaSim\n");
}

