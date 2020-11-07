#ifndef __ALOHA__

#define __ALOHA__

#include "utils.h"
#include "structs.h"

#define DEBUG 0


Results test(Aloha_test aloha_test, void* random_params);

Results test_uniform(char verbose, float prob, unsigned int nb_stations, unsigned int nb_slots, int k);

Results test_beb(char verbose, float prob, unsigned int nb_stations, unsigned int nb_slots);

#endif