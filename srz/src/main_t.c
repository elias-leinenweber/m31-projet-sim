#include <stdio.h>
#include <stdio.h>
#include <time.h>

#include "aloha.h"

#define NB_TESTS 1000

int main(int argv, char** args) {
    char type_rand = 'u';
    int nb_stations = 10;
    int nb_slots = 1;
    float proba = 0.01;
    float pn_min, pn_max, pas;
    int k = 4;
    Results result;

    srand(time(NULL));


    if (argv != 8) {
        printf("argument 1: type de tirage (u(niforme)/b(eb)\n");
        printf("argument 2: nb slots\n");
        printf("argument 3: nb stations\n");
        printf("argument 4: pn min\n");
        printf("argument 5: pn max\n");
        printf("argument 6: pas\n");
        printf("argument 7: k\n ");
        return 0;
    }
    else {
        type_rand = args[1][0];
        nb_slots = atoi(args[2]);
        nb_stations = atoi(args[3]);
        pn_min = atof(args[4]);
        pn_max = atof(args[5]);
        pas = atof(args[6]);
        k = atof(args[7]);
    }
    if (DEBUG) {
        fprintf(stderr, "type de choix de relance : %c\n", type_rand);
        fprintf(stderr, "nb_slots : %d\n", nb_slots);
        fprintf(stderr, "nb_stations : %d\n", nb_stations);
        fprintf(stderr, "pn_min : %f\n", pn_min);
        fprintf(stderr, "pn_max : %f\n", pn_max);
        fprintf(stderr, "pas : %f\n", pas);
        fprintf(stderr, "k : %d\n", k);
    }
    
    for (proba=pn_min/nb_stations; proba <= pn_max/nb_stations; proba+=pas/nb_stations) {
        if (DEBUG) {
        fprintf(stderr, "proba : %f\n", proba);
    }
        for (int count = 0; count < NB_TESTS; count++) {
            if (type_rand == 'u') {
                result = test_uniform(1, proba, nb_stations, nb_slots, k);
            }
            else if (type_rand == 'b') {
                result = test_beb(1, proba, nb_stations, nb_slots);
            }
        }
    }
    exit(EXIT_SUCCESS);
}