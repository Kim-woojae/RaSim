#ifndef RASIM_H
#define RASIM_H

#include "common.h"
#include "thing.h"
#include "scheduler.h"
#include "message.h"
#include "link.h"
#include "sensor.h"
#include "location.h"
#include "role.h"
#include "resource.h"

void makeRaspberryPi();
void initRaSim(char location, char *path, char policy, void (*user_policy)());
void connectAroundNode();
void startRaSim();
void exitRaSim();

#endif