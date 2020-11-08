#include "utils.h"

unsigned int uniform(unsigned int try, void* params) {
    // params : int* k pour un entier entre  et k
    int k = *((int*) params);
    return rand() % (k - 1) + 1;
}

unsigned int beb_rand(unsigned int try, void* params) {
    // params osef
    unsigned int max = 1;
    max <<= (try + 1);
    if (max == 0) max = 1;
    return rand() % max + 1;
}

void init_aloha_test(Aloha_test* aloha_test, char verbose, float prob, unsigned int nb_stations, unsigned int nb_slots, ptr_next_slot random) {
    aloha_test->verbose = verbose;
    aloha_test->prob = prob;
    aloha_test->nb_stations = nb_stations;
    aloha_test->stations = calloc(nb_stations, sizeof(Station));
    aloha_test->nb_slots = nb_slots;
    aloha_test->random = random;
}

void init_results(Results* results, unsigned int nb_stations, unsigned int nb_slots) {
    results->queued_msgs = malloc(nb_slots * sizeof(unsigned int*));
    for (size_t i = 0; i < nb_slots; i++) {
        results->queued_msgs[i] = calloc(nb_stations, sizeof(unsigned int));
    }
    results->tot_queued_msgs = calloc(nb_slots, sizeof(unsigned int));
    results->useful_slots = 0;
    results->msgs_sent = calloc(nb_slots, sizeof(unsigned int));
}

void print_results(Results results, size_t slot, size_t nb_stations) {
    printf("Slot : %lu\n", slot);
    printf("\tqueued_msgs\n");
    for (size_t i = 0; i < nb_stations; i++) {
        printf("\t\t[%lu]: %u\n", i, results.queued_msgs[slot][i]);
    }
    printf("\t\ttot: %u\n", results.tot_queued_msgs[slot]);
    printf("\tuseful_slots: %u\n", results.useful_slots);
    printf("\tmessages sent: %u\n", results.msgs_sent[slot]);
}

void debug(Results results, Aloha_test test, size_t slot) {
    size_t nb_stations = test.nb_stations;
    fprintf(stderr, "Slot : %lu\n", slot);
    fprintf(stderr, "\tqueued_msgs [nxt try][nb_retries]\n");
    for (size_t i = 0; i < nb_stations; i++) {
        Station st = test.stations[i];
        fprintf(stderr, "\t\t[%lu]: %u[%u][%u]\n", i, st.queued_msgs, st.next_try, st.nb_retries);
    }
    fprintf(stderr, "\t\ttot: %u\n", results.tot_queued_msgs[slot]);
    fprintf(stderr, "\tuseful_slots: %u\n", results.useful_slots);
    fprintf(stderr, "\tmessages sent: %u\n", results.msgs_sent[slot]);
}

void print_stations(Station* stations, size_t nb_stations) {
    for(size_t i = 0; i < nb_stations; i++) {
        Station st = stations[i];
        printf("Station %lu :\n", i);
        printf("\tqueued_msgs, next_try, nb_retries : %u %u %u\n", st.queued_msgs, st.next_try, st.nb_retries);

    }
}