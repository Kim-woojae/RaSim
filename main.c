#include "rasim.h"

int main(){
	initRaSim(RANDOM_LOCATION, NULL, SCHED_ROUND_ROBIN, NULL);
	connectAroundNode();
	startRaSim();
}