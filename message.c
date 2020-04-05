#include <stdlib.h>
#include <string.h>

#include "message.h"
#include "link.h"
#include "thing.h"

struct _message msgQ[NUMBER_OF_THINGS][MAX_Q_SIZE];
int front[NUMBER_OF_THINGS], rear[NUMBER_OF_THINGS];

struct _message *copy_message(struct _message *message){
	struct _message *copy;

	copy = (struct _message*)malloc(sizeof(struct _message));
	memcpy(copy, message, sizeof(struct _message));
	return copy;
}

int sendMessageToAllMember(struct _message *message){
	int *connected_nodes, i;
	struct _member *member_list = getMember(message->sender_id);
	struct _message *copy;
	int length;

	if(member_list==NULL)
		return -2;

	copy = copy_message(message);	
	connected_nodes = connectedNodesList(member_list);
	for(i=0; connected_nodes[i]!=-1; i++){
		if(!isFull(connected_nodes[i])){
			message->number_of_transmissions++;
			length = messageLength(message->message);
			message->length += length;
			copy->receiver_id = connected_nodes[i];
			//calculateBandwidth(message->sender_id, length);
			push(copy, connected_nodes[i]);
		}
		else // 연결된 모든 노드 중 하나의 노드에서 실패
			return -2;
	}
	return 0;
}

int sendMessageToMember(struct _message *message){
	struct _message *copy;
	int length;

	copy = copy_message(message);
	if(!isFull(message->receiver_id)){
		message->number_of_transmissions++;
		length = messageLength(message->message);
		//printf("%lf\n",message->length);
		message->length += length;
		//calculateBandwidth(message->sender_id, length);
		return push(copy, message->receiver_id);
	}
	else
		return -2;
}

// If rand() result is higher than 2 then send
int sendMessage(struct _message *message, char send_type){
	message->send_type = send_type;
	message->sender_id = message->thing_id;
	if(rand()%10 > 2){
		switch(message->send_type){
			case BROADCAST: 
				return sendMessageToAllMember(message); 
			default: 
				return sendMessageToMember(message); 
		}
	}
	else
		return -1;		// Just failure;
}

int messageLength(char *message){
	int i=0;
	for(i=0; message[i]!=0; i++);
	return i;
}

int isEmpty(int thing_id){
	if(rear[thing_id] == front[thing_id])
		return TRUE;
	else
		return FALSE;
}

int isFull(int thing_id){
	if((rear[thing_id]+1)%MAX_Q_SIZE == front[thing_id]){
		//printf("%d FULL!!!!!\n",thing_id);
		return TRUE;
	}
	else
		return FALSE;
}

int push(struct _message *message, int thing_id){
	msgQ[thing_id][rear[thing_id]] = *message;
	rear[thing_id] = (rear[thing_id]+1)%MAX_Q_SIZE;
	return 0;
}

int receiveMessage(int thing_id, struct _message *message){
	struct _message *recv_meesage;
	int length;

	if(!isEmpty(thing_id)){
		recv_meesage = pop(thing_id);
		message->number_of_transmissions++;
		length = messageLength(recv_meesage->message);
		message->length += length;
		//calculateBandwidth(thing_id, length);
		message->sender_id = recv_meesage->sender_id;
		message->receiver_id = recv_meesage->receiver_id;
		message->send_type = recv_meesage->send_type;
		message->message_type = recv_meesage->message_type;
		strcpy(message->message, recv_meesage->message);
		message->sensor_value = recv_meesage->sensor_value;
		return 1;
	}
	else
		return 0;
}

struct _message *pop(int thing_id){
	//struct _message *received_message;
	int temp_front = front[thing_id];
	//received_message = &msgQ[thing_id][front[thing_id]];
	front[thing_id] = (front[thing_id]+1)%MAX_Q_SIZE;
	//return received_message;
	return &msgQ[thing_id][temp_front];
}

void printMessage(struct _message *message){
	printf("----------------------------------\n");
	printf("Sender: %d -----> Receiver: %d\n", message->sender_id, message->receiver_id);
	printf("Payload: %s\n", message->message);
	printf("----------------------------------\n");
}