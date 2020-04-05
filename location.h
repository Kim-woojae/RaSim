#ifndef LOCATION_H
#define LOCATION_H

#include "common.h"

#define RANDOM_LOCATION		0x00
#define SET_FROM_FILE			0x01

void initLocationList();
void initDistanceTable();
int readLocationFile(char *path);
int setLocationFromFile(struct _location *location, char *path);
void setRandomLocation(struct _location *location);
void setLocation(int thingID, int x, int y);
struct _location getLocation(int thingID);

#endif