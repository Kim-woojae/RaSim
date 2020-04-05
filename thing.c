#include <stdlib.h>
#include <string.h>
#include "thing.h"
#include "location.h"
#include "link.h"

extern int g_RaSim_status;
int *g_destroyed_things_list;
int g_destroyed_things_list_index;

TCB *g_tcb;

void *thingManager(TCB *tcb){
	tcb->thread_id = syscall(SYS_gettid);
	while(g_RaSim_status){
		if(tcb->status){
			
		}
		usleep(SECOND);
	}

	return NULL;
}

TCB* createThings(char location, char *path){
	TCB *tcb;
	int i;

	tcb = (TCB *)malloc(sizeof(TCB)*NUMBER_OF_THINGS);
	initDestroyedThingsList();
	for(i=0; i<NUMBER_OF_THINGS; i++)
		initTCB(&tcb[i], i, location, path);
	g_tcb = tcb;

	return tcb;
}

void initTCB(TCB* tcb, int thing_id, char location, char *path){
	memset(tcb, 0, sizeof(struct _TCB));
	tcb->thing_id = thing_id;
	tcb->role = MEMBER;
	tcb->status = FALSE;
	if(location==RANDOM_LOCATION)
		setRandomLocation(&tcb->location);
	else if(location==SET_FROM_FILE)
		setLocationFromFile(&tcb->location, path);
	tcb->member_list = newNode();
	tcb->sensor = (struct _sensor *)malloc(sizeof(struct _sensor));
	tcb->member_list->thing_id = tcb->thing_id;
	tcb->member_list->role = tcb->role;
	tcb->member_list->location = tcb->location;
	tcb->member_list->next = NULL;
	tcb->message.thing_id = tcb->thing_id;
}

void initDestroyedThingsList(){
	int i;

	g_destroyed_things_list_index = 0;
	g_destroyed_things_list = (int *)malloc(sizeof(int)*NUMBER_OF_THINGS);
	for(i=0; i<NUMBER_OF_THINGS; i++)
		g_destroyed_things_list[i] = -1;
}

void destroyThing(int thing_id){
	g_tcb[thing_id].role = DESTROYED;
	g_destroyed_things_list[g_destroyed_things_list_index++] = thing_id;
}

void freeDestroyedTCB(){
	int i;

	for(i=0; g_destroyed_things_list[i]>0; i++)
		free(&g_tcb[i]);
	free(g_destroyed_things_list);
}

void freeTCB(){
	free(g_tcb);
}

void printThings(){
	int i;

	for(i=0; i<NUMBER_OF_THINGS; i++){
		printf("thing ID: %d \n",g_tcb[i].thing_id);
	}
}

struct _member* getMember(int thing_id){
	return g_tcb[thing_id].member_list;
}

struct _resource* getResource(int thing_id){
	return &g_tcb[thing_id].resource;
}

struct _message* getMessage(int thing_id){
	return &g_tcb[thing_id].message;
}

int getThreadID(int thing_id){
	return g_tcb[thing_id].thread_id;
}

int* getThingStatus(int thing_id){
	return &g_tcb[thing_id].status;
}