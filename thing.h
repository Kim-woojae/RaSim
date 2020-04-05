#ifndef THING_H
#define THING_H

#include "common.h"

void *thingManager(TCB *tcb);
TCB* createThings(char location, char *path);
void initTCB(TCB* tcb, int thing_id, char location, char *path);
void initDestroyedThingsList();
void destroyThing(int thing_id);
void freeDestroyedTCB();
void freeTCB();
struct _member* getMember(int thing_id);
struct _resource* getResource(int thing_id);
struct _message* getMessage(int thing_id);
int getThreadID(int thing_id);
int* getThingStatus(int thing_id);
void printThings();

#endif