#ifndef LINK_H
#define LINK_H

#include "common.h"

int connectNode(struct _member *member, int thing_id);
int addNode(struct _member *member, struct _member *around_node);
struct _member* newNode();
struct _member* copyNode(struct _member *around_node);
void initConnectedList(int *connected_list);
int* connectedNodesList(struct _member *member_list);
int getConnectedRandomNode(struct _member *member_list);
int searchNodeByThingID(struct _member *member_list, int thing_id);
int searchNodeBySensor(struct _member *member_list, char *sensor_name);
void freeConnectedNodes(struct _member* member_list);

#endif