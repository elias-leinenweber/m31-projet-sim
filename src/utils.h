#ifndef __UTILS__

#define __UTILS__

#include <stdlib.h>
#include <stdio.h>
#include "structs.h"

void init_aloha_test(Aloha_test* aloha_test, char verbose, float prob, unsigned int nb_stations, unsigned int nb_slots, ptr_next_slot random);

void init_results(Results* results, unsigned int nb_stations, unsigned int nb_slots);

unsigned int uniform(unsigned int try, void* params);

unsigned int beb_rand(unsigned int try, void* params);

void print_results(Results results, size_t slot, size_t nb_stations);

void debug(Results results, Aloha_test test, size_t slot);

void print_stations(Station* stations, size_t nb_stations);

#endif