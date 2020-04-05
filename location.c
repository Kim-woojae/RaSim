#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "location.h"

struct _location *g_location_list[NUMBER_OF_THINGS] = {NULL,};
int g_location_list_index = 0;
float g_distance_table[NUMBER_OF_THINGS][NUMBER_OF_THINGS];

void initLocationList(){
	//g_location_list = (struct _location *)malloc(sizeof(struct _location)*NUMBER_OF_THINGS);
}

void initDistanceTable(){
	int i,j;
	float x=0., y=0., distance=0.;

	for(i=0; i<NUMBER_OF_THINGS; i++){
		x = g_location_list[i]->x;
		y = g_location_list[i]->y;
		for(j=0; j<NUMBER_OF_THINGS; j++){
			if(i!=j){
				distance = sqrt(pow(g_location_list[j]->x-x,2)+pow(g_location_list[j]->y-y,2));
				g_distance_table[i][j] = distance;
				g_distance_table[j][i] = distance;
			}
			else
				g_distance_table[i][j] = 999999;
		}
	}
}

int readLocationFile(char *path){
	FILE *location_file;
	int i, x,y;

	if(path == NULL)
		return -1;  // Wrong path || Variable path has NULL
	location_file = fopen(path, "r");
	if(location_file == NULL)
		return -2; // No file
	else{
		for(i=0; i<NUMBER_OF_THINGS; i++){
			fscanf(location_file, "%d %d", &x, &y);
			if(x < 0 || x > MAP_SIZE || y < 0 || y > MAP_SIZE){
					fclose(location_file);
					return -3; // Wrong value
			}
			g_location_list[i]->x = x;
			g_location_list[i]->y = y;
		}
	}
	return 0;
}

int setLocationFromFile(struct _location *location, char *path){
	int result = 0;

	if(location==NULL)
		return -3; 
	
	result = readLocationFile(path);
	if(result < 0)  // Read failure
		return result;
	
	location = g_location_list[g_location_list_index++];

	return 0;
}

void setRandomLocation(struct _location *location){
	location->x = rand()%MAP_SIZE;
	location->y = rand()%MAP_SIZE;
	g_location_list[g_location_list_index++] = location;
}

void setLocation(int thingID, int x, int y){
	g_location_list[thingID]->x = x;
	g_location_list[thingID]->y = y;
}

struct _location getLocation(int thingID){
	return *g_location_list[thingID];
}
