#ifndef SENSOR_H
#define SENSOR_H

#include "common.h"

void addSensor(int n, char *sensor_name, int period, int power_consumption, float operating_voltage);
void newSensor(int n, char *sensor_name, int period, int power_consumption, float operating_voltage);
void initSensorList();
struct _sensor* getSensor(int thing_id);
void setName(int thingID, char *sensor_name);
void setPeriod(int thingID, int period);
void setPowerConsumption(int thingID, int power_consumption);
int getSensorValue(int thingID, char *sensor_name);
int operateSensor(struct _sensor *sensor);
struct _sensor* findSensor(struct _sensor *sensor, char *sensor_name);
void freeSensor();

#endif