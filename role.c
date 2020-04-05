#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "role.h"
#include "message.h"
#include "sensor.h"
#include "link.h"

int k = 10485760;
void header(TCB *tcb){
	printf("[%d]bandwidth:%.1f, cpu:%.1f\n",tcb->thing_id,tcb->resource.bandwidth, tcb->resource.cpu);
}

void member(TCB *tcb){
	int i;
	int ran, t=0;

	ran = rand()%512;
	//if(rand()%10>1 && tcb->thing_id==1){ 
		// char c[MAX_MESSAGE_SIZE+1]={0};
		// int n = getConnectedRandomNode(tcb->member_list);
		// if(n > -1){
		// 	tcb->message.receiver_id = n;
		// 	//getSensorValue(tcb->thing_id, "temp");
		// 	if(ran/MAX_MESSAGE_SIZE>0){
		// 		t = ran/MAX_MESSAGE_SIZE;
		// 		ran -= t*MAX_MESSAGE_SIZE;
		// 	}
		// 	else{
		// 		t = ran;
		// 		ran = 0;
		// 	}
		// 	if(ran==0){
		// 		for(i=0; i<t; i++)
		// 			strcat(c,"a");
		// 		strcpy(tcb->message.message, c);
		// 		tcb->message.message_type = REQUEST;
		// 		tcb->message.sensor_value = tcb->sensor->value;
		// 		sendMessage(&tcb->message, 0);
		// 	}
		// 	else{
		// 		for(i=0; i<MAX_MESSAGE_SIZE; i++)
		// 			strcat(c,"a");
		// 		for(i=0; i<t; i++){
		// 			strcpy(tcb->message.message, c);
		// 			tcb->message.message_type = REQUEST;
		// 			tcb->message.sensor_value = tcb->sensor->value;
		// 			sendMessage(&tcb->message, 0);
		// 		}
		// 		memset(c,0,sizeof(c));
		// 		for(i=0; i<ran; i++)
		// 			strcat(c,"a");
		// 		strcpy(tcb->message.message, c);
		// 		tcb->message.message_type = REQUEST;
			// 	tcb->message.sensor_value = tcb->sensor->value;
			// 	sendMessage(&tcb->message, 0);

			// }
		//}
		//for(i=0; i<10000000; i++);
			
	//}
	/*	i=0;
		extern int g_RaSim_status;
		srand((unsigned)time(NULL));
		int data[20000]={0,};
		int j=0;
		for(i=0; i<20000; i++){
			data[i] = rand()%1000000;
		}
		int tmp=0;
		for(i=0; i<20000-1; i++){
			for(j=i+1; j<20000-1; j++){
				if(data[i]>data[j]){
					tmp = data[i];
					data[i] = data[j];
					data[j] = tmp;
				}
			}
		}
		g_RaSim_status = FALSE;*/
		/*while(i<10000000000){
			i++;
			usleep(rand()%1);
		}*/
	/*if(tcb->thing_id == 1){
		char buf[512]={0,};
		memset(buf, 'q', 511);
		strcpy(tcb->message.message, buf);
		tcb->message.receiver_id = 0;
		tcb->message.message_type = REQUEST;
		sendMessage(&tcb->message,0);
	}*/
	//if(tcb->thing_id>=0){
		static int don=0;
		extern int g_RaSim_status;
		static int prev=0;
	if(tcb->thing_id == 1){
		char buff[513]={0,};
		
			memset(buff, 'a', sizeof(buff));
			strcpy(tcb->message.message, buff);
			tcb->message.receiver_id = 0;
			tcb->message.message_type = REQUEST;
			sendMessage(&tcb->message,0);
		k -= 512;
		if(k <= 0){
			strcpy(tcb->message.message, "end");
			tcb->message.receiver_id = 0;
			tcb->message.message_type = REQUEST;
			sendMessage(&tcb->message,0);
			printf("Bandwidth: %.2f%%\n",tcb->resource.avg_bandwidth);
			printf("Battery: %.2f\n", tcb->resource.battery+tcb->resource.idle_battery);
			printf("Done!!\n");
			don=1;
		}
	}
	if(tcb->thing_id==0){
		while(1){
		receiveMessage(tcb->thing_id, &tcb->message);
		if(strcmp(tcb->message.message,"end")==0){
			printf("Received\n");
			tcb->thing_id = 1;
			break;
		}
		usleep(messageLength(tcb->message.message));
		}
	}
	if(tcb->thing_id == 1 && don == 1){
		/*printf("Bandwidth: %.2f%%\n",tcb->resource.avg_bandwidth);
		printf("Battery: %.2f\n", tcb->resource.battery+tcb->resource.idle_battery);
		printf("Done!!\n");*/
		g_RaSim_status = FALSE;
		usleep(100000000);
	}
	// if(tcb->thing_id==0){
	// printf("[%d] Bandwidth: %.2f%%, \t",tcb->thing_id,\
	// 									tcb->resource.avg_bandwidth);
	// printf("%.2f%%, ", tcb->resource.cpu);
	// if(tcb->resource.cpu == 0.0)
	// 	tcb->resource.max_cpu = 0.001;
	// printf("normCPU: %.2f%%, ", tcb->resource.cpu/tcb->resource.max_cpu);
	// printf("Battery: %.2f, ", tcb->resource.battery+tcb->resource.idle_battery);
	// printf("Uptime: %02d : %02d : %02d\n", tcb->resource.uptime.hour,\
	// 										  tcb->resource.uptime.minute,\
	// 										  tcb->resource.uptime.second);
	// }
	//}
	// FILE *fp = fopen("cpuTEST.txt","a");
	// fprintf(fp,"%.2f, %.2f, %f\n",tcb->resource.cpu, tcb->resource.cpu/tcb->resource.max_cpu,tcb->resource.cpu2);
	// fclose(fp);
}

void relay(TCB *tcb){
	printf("[%d]bandwidth:%.1f, cpu:%.1f\n",tcb->thing_id,tcb->resource.bandwidth, tcb->resource.cpu);
}