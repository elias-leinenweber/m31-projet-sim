#include <stdio.h>
#include <stdlib.h>

#include "aloha.h"

Results test(Aloha_test aloha_test, void* random_params) {
    Results ans;
    init_results(&ans, aloha_test.nb_stations, aloha_test.nb_slots);
    //print_stations(aloha_test.stations, aloha_test.nb_stations);
    for (unsigned int slot = 0; slot < aloha_test.nb_slots; slot++) {
        int nb_msgs = 0;
        //print_results(ans, i, aloha_test.nb_stations);
        // les stations veulent-elles emettre un nouveau message?
        for (unsigned int j = 0; j < aloha_test.nb_stations; j++) {            
            Station* st = &aloha_test.stations[j];
            if (rand() / (float) RAND_MAX < aloha_test.prob) {
                st->queued_msgs++;
            }
            ans.tot_queued_msgs[slot]+=st->queued_msgs;
        }
        // y a-t-il collision?
        for (unsigned int j = 0; j < aloha_test.nb_stations && nb_msgs < 2; j++) {                      
            Station* st = &aloha_test.stations[j];
            if (st->queued_msgs > 0
                &&
                st->next_try == 0) {
                nb_msgs++;
            }
        }
        // calcul de l'attente si collision
        if (nb_msgs > 1) {
            //printf("collision\n");
            for (unsigned int j = 0; j < aloha_test.nb_stations; j++) {            
                Station* st = &aloha_test.stations[j];
                if (st->queued_msgs > 0
                    &&
                    st->next_try == 0) {
                        st->next_try = aloha_test.random(st->nb_retries, random_params);
                        st->nb_retries+=1;
                        ans.msgs_sent[slot]++;
                        if(DEBUG) printf("%u \n", st->next_try);
                }
            }
        }
        // envoi du message
        else if (nb_msgs == 1) {
            unsigned int j = 0;
            ans.msgs_sent[slot] = 1;
            ans.useful_slots++;
            while(j < aloha_test.nb_stations) {
                if (aloha_test.stations[j].queued_msgs > 0
                    &&
                    aloha_test.stations[j].next_try == 0) {
                        aloha_test.stations[j].queued_msgs --;
                        j = aloha_test.nb_stations;
                        ans.tot_queued_msgs[slot]--;
                }
                j++;
            }
        }
        // affichage
        if (aloha_test.verbose) {
            debug(ans, aloha_test, slot);
        }
        if (DEBUG) debug(ans, aloha_test, slot);
        // mise a jour du next_try
        for (unsigned int j = 0; j < aloha_test.nb_stations; j++) {            
            Station* st = &aloha_test.stations[j];
            if (st->next_try>0) st->next_try--;
        }
    }


    return ans;
}

Results test_uniform(char verbose, float prob, unsigned int nb_stations, unsigned int nb_slots, int k) {
    Aloha_test aloha_test;
    int params = k;
    init_aloha_test(&aloha_test, verbose, prob, nb_stations, nb_slots, &uniform);
    return test(aloha_test, &params);
}

Results test_beb(char verbose, float prob, unsigned int nb_stations, unsigned int nb_slots) {
    Aloha_test aloha_test;
    void* params = 0;
    init_aloha_test(&aloha_test, verbose, prob, nb_stations, nb_slots, &beb_rand);
    return test(aloha_test, params);
}