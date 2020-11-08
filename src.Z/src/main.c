#include <stdio.h>
#include <stdio.h>
#include <time.h>

#include "aloha.h"

int main(int argv, char** args) {
    char type_rand = 'u';
    int nb_stations = 10;
    int nb_slots = 1;
    float proba = 0.01;
    int k = 4;
    Results result;

    srand(time(NULL));

    if (argv != 5 && argv != 6) {
        printf("argument 1: type de tirage (u(niforme)/b(eb)\n");
        printf("argument 2: nb slots\n");
        printf("argument 3: nb stations\n");
        printf("argument 4: proba\n");
        printf("argument 5: k\n ");
        return 0;
    }
    if (argv >= 5) {
        type_rand = args[1][0];
        nb_slots = atoi(args[2]);
        nb_stations = atoi(args[3]);
        proba = atof(args[4]);
        k = 0;
    }
    if (argv == 6) {
        k = atoi(args[5]);
    }
    if (DEBUG) {
        fprintf(stderr, "type de choix de relance : %c\n", type_rand);
        fprintf(stderr, "nb_slots : %d\n", nb_slots);
        fprintf(stderr, "nb_stations : %d\n", nb_stations);
        fprintf(stderr, "proba : %f\n", proba);
        if (argv == 6) fprintf(stderr, "k : %d\n", k);
    }
    
    
    if (type_rand == 'u') {
        result = test_uniform(0, proba, nb_stations, nb_slots, k);
    }
    else if (type_rand == 'b') {
        result = test_beb(0, proba, nb_stations, nb_slots);
    }
    printf("%f\t%u\t%u\t%u\t%u\t%u\n", proba, k, nb_stations, nb_slots, result.useful_slots, result.tot_queued_msgs[nb_slots-1]);
    exit(EXIT_SUCCESS);
}