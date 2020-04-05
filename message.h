#ifndef MESSAGE_H
#define MESSAGE_H

#include "common.h"

int sendMessageToAllMember(struct _message *message);
int sendMessageToMember(struct _message *message);
int sendMessage(struct _message *message, char send_type);
int messageLength(char *message);
int isEmpty(int thing_id);
int isFull(int thing_id);
int push(struct _message *message, int thing_id);
int receiveMessage(int thing_id, struct _message *message);
struct _message *pop(int thing_id);
void printMessage(struct _message *message);

#endif