#include <stdlib.h>
#include <string.h>

#include "sensor.h"

struct _sensor *sensor_list[NUMBER_OF_THINGS] = {NULL,};
int sensor_list_index = 0;

void newSensor(int n, char *sensor_name, int period, int power_consumption, float operating_voltage){
	if(sensor_list[n] == NULL){
		sensor_list[n] = (struct _sensor *)malloc(sizeof(struct _sensor));
		sensor_list[n]->name = sensor_name;
		sensor_list[n]->period= period;
		sensor_list[n]->power_consumption = power_consumption;
		sensor_list[n]->operating_voltage = operating_voltage;
		sensor_list[n]->next = NULL;
	}
	else{
		addSensor(n, sensor_name, period, power_consumption, operating_voltage);
	}
}
void addSensor(int n, char *sensor_name, int period, int power_consumption, float operating_voltage){
	struct _sensor *temp, *new_sensor;
	
	temp = sensor_list[n];
	while(temp->next!=NULL)
		temp = temp->next;

	new_sensor = (struct _sensor *)malloc(sizeof(struct _sensor));
	new_sensor->name = sensor_name;
	new_sensor->period = period;
	new_sensor->power_consumption = power_consumption;
	new_sensor->operating_voltage = operating_voltage;
	new_sensor->next = NULL;
	temp->next = new_sensor;
}

void initSensorList(){
	//sensor_list = (struct _sensor *)malloc(sizeof(struct _sensor)*NUMBER_OF_THINGS);
	printf("%s TODO\n", __func__);
}

struct _sensor* getSensor(int thing_id){
	return sensor_list[thing_id];
}

void setName(int thing_id, char *sensor_name){
	sensor_list[thing_id]->name = sensor_name;
}

char* getSensorName(int thing_id){
	return sensor_list[thing_id]->name;
}

void setPeriod(int thing_id, int period){
	sensor_list[thing_id]->period = period;
}

int getPeriod(int thing_id){
	return sensor_list[thing_id]->period;
}

void setPowerConsumption(int thing_id, int power_consumption){
	sensor_list[thing_id]->power_consumption = power_consumption;
}

int getPowerConsumption(int thing_id){
	return sensor_list[thing_id]->power_consumption;
}

int getSensorValue(int thing_id, char *sensor_name){
	return operateSensor(findSensor(sensor_list[thing_id], sensor_name));
}

int operateSensor(struct _sensor *sensor){
	int value;

	if(sensor==NULL){
		//sensorNotFoundException();
		return -1;
	}

	value = rand();
	sensor->value = value;
	sensor->action_count++;
	usleep(sensor->period*1000);
	return value;
}

struct _sensor* findSensor(struct _sensor *sensor, char *sensor_name){
	struct _sensor *temp;

	temp = sensor;
	while(temp != NULL){
		if(strcmp(temp->name, sensor_name)==0)
			return temp;
		else
			temp = temp->next;
	}

	return NULL;
}

void freeSensor(){
	int i;
	struct _sensor *prev, *temp;

	for(i=0; i<NUMBER_OF_THINGS; i++){
		temp = sensor_list[i];
		while(temp != NULL){
			prev = temp;
			temp = temp->next;
			free(prev);
		}
	}
}