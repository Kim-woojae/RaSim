#ifndef RESOURCE_H
#define RESOURCE_H

#include "common.h"

void makeResourceManager();
void calculateResource(int thing_id, unsigned int sampling_count);
void calculateBattery(int thing_id);
void calculateCPU(int thing_id, unsigned int sampling_count);
void calculateBandwidth(int thing_id);
void setResourceManagerStatus(int status);
void setUptime();
void calculateUptime(int thing_id);
#endif