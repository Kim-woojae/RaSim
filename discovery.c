#include "discovery.h"
#include "thing.h"

extern float g_distance_table[NUMBER_OF_THINGS][NUMBER_OF_THINGS];

struct _member* findNode(int thing_id, int index){
	if(BOUNDARY >= g_distance_table[thing_id][index]){
		return getMember(index);
	}
	return NULL;
}

