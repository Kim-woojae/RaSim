#include <stdlib.h>
#include <string.h>

#include "link.h"
#include "discovery.h"
#include "sensor.h"


int connectNode(struct _member *member, int thing_id){
	int i;
	struct _member *around_node;

	for(i=0; i<NUMBER_OF_THINGS; i++){
		around_node = copyNode(findNode(thing_id, i));
		if(around_node != NULL)
			addNode(member, around_node);
	}
	return 0;
}

int addNode(struct _member *member, struct _member *around_node){
	struct _member *temp = member;

	if(temp->next == NULL)
		temp->next = around_node;
	else{
		while(temp->next != NULL)
			temp = temp->next;
		temp->next = around_node;
	}
	return 0;
}

/*int deleteNode(){

}*/

struct _member* newNode(){
	struct _member *new_node;
	new_node = (struct _member*)malloc(sizeof(struct _member));
	return new_node;
}

struct _member* copyNode(struct _member *around_node){
	struct _member *new_node;

	if(around_node == NULL)
		return NULL;
	new_node = newNode();
	new_node->thing_id = around_node->thing_id;
	new_node->distance = around_node->distance;
	new_node->role = around_node->role;
	new_node->location = around_node->location;
	new_node->next = NULL;

	return new_node;
}

void initConnectedList(int *connected_list){
	int i;
	for(i=0; i<NUMBER_OF_THINGS; i++)
		connected_list[i] = -1;
}

int* connectedNodesList(struct _member *member_list){
	static int connected_list[NUMBER_OF_THINGS];
	int i = 0;
	struct _member *temp;

	initConnectedList(connected_list);
	temp = member_list->next;
	while(temp != NULL){
		connected_list[i++] = temp->thing_id;
		temp = temp->next;
	}

	return connected_list;
}

int searchNodeByThingID(struct _member *member_list, int thing_id){
	struct _member *temp = member_list->next;

	while(temp->next != NULL){
		temp = temp->next;
		if(temp->thing_id == thing_id)
			return TRUE;
	}
	return FALSE;
}

int searchNodeBySensor(struct _member *member_list, char *sensor_name){
	struct _member *temp = member_list->next;
	struct _sensor *sensor;

	while(temp != NULL){
		sensor = getSensor(temp->thing_id);
		while(sensor!=NULL){
			if(strcmp(sensor->name, sensor_name)==0)
				return temp->thing_id;
			sensor = sensor->next;
		}
		temp = temp->next;
	}
	return -1;
}

int getConnectedRandomNode(struct _member *member_list){
	int result = -1, index = 0;
	int *connected_list;

	if(NUMBER_OF_THINGS == 1)
		return -1;
	while(result < 0){
		connected_list = connectedNodesList(member_list);
		for(index=0; connected_list[index]!=-1; index++);
		if(index == 1){
			return connected_list[index-1];
		}
		result = connected_list[rand()%(index-1)];
	}
	return result;
}

void freeConnectedNodes(struct _member* member_list){
	// Initialize member of TCB
	struct _member *temp = member_list;
	struct _member *prev;
	while(temp->next != NULL){
		prev = temp;
		temp = temp->next;
		free(prev);
	}
}