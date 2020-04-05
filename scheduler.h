#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "common.h"

void *rpi_Scheduler();
void initScheduler();
void setSchedulingPolicy(char policy);
void makeRPiScheduler();
void setUserPolicy(void (*user_schedule_policy)());
void RR();
void FCFS();
void setSchedulerStatus(int status);

#endif