#ifndef __STRUCTS__

#define __STRUCTS__

typedef struct {
    unsigned int queued_msgs;
    unsigned int next_try;
    unsigned int nb_retries;
} Station;

typedef unsigned int (*ptr_next_slot)(unsigned int try, void* params);

typedef struct {
    char verbose;
    float prob;
    unsigned int nb_stations;
    Station* stations;
    unsigned int nb_slots;
    ptr_next_slot random;
} Aloha_test;

typedef struct {
    unsigned int** queued_msgs;
    unsigned int* tot_queued_msgs;
    unsigned int useful_slots;
    unsigned int* msgs_sent;
} Results;

#endif