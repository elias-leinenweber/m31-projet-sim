#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "aloha.h"
#include "randutils.h"

/*
 * Effectue une simulation.
 *
 * Paramètres :
 * - `p` : probabilité de commencer une émission au début d'un slot
 * - `k` : nombre de slots suivants parmi lesquels choisir le slot de réémission
 * - `n` : nombre de stations
 * - `slots` : durée de la simulation en slots
 * - `beb` : si le mode "binary exponential backoff" est activé ou non
 */
struct result
slotted_aloha(double p, uint32_t k, uint32_t n, uint32_t slots, bool beb)
{
	struct result res;			/* résultats de la simulation */
	uint32_t i, nb_senders, *next_slot, *senders, slot, station, *tries;
	bool is_slot_occupied;

	/* Initialisation des variables */
	res.useful_slots = 0;
	res.queued_msgs = 0;
	nb_senders = 0;
	next_slot = calloc(n + 1, sizeof(uint32_t));
	senders = calloc(n + 1, sizeof(uint32_t));
	tries = beb ? calloc(n + 1, sizeof(uint32_t)) : NULL;

	/* Pour chaque slot (représentant chacun une unité de temps) : */
	for (slot = 1; slot <= slots; ++slot) {
		/* On débute un nouveau slot : il n'est pas occupé. */
		is_slot_occupied = false;

		/* On réinitialise les transmetteurs. */
		for (i = 0; i < nb_senders; ++i)
			senders[i] = 0;
		nb_senders = 0;

		/* Pour toutes les stations : */
		for (station = 1; station <= n; ++station)
			/*
			 * Soit elle a déjà tenté (et échoué) de transmettre un
			 * message : dans ce cas-là, si elle a choisi le slot
			 * courant pour ré-émettre son message, on tente à
			 * nouveau de transmettre le message.
			 * Sinon, elle tente de transmettre un nouveau message
			 * avec une probabilité égale à `p`.
			 */
			if (slot == next_slot[station] ||
			    (randbool(p) && ++res.queued_msgs))
				senders[nb_senders++] = station;

		if (nb_senders == 1) {
			/* Pas de collision, envoi du message. */
			next_slot[senders[0]] = 0;
			is_slot_occupied = true;
			--res.queued_msgs;
		} else if (nb_senders > 1)
			/*
			 * Collision : toutes les stations ayant tenté de
			 * transmettre pendant ce slot, choisissent un slot
			 * parmi les `k` suivants pour retransmettre leur
			 * message.
			 */
			for (i = 0; i < nb_senders; ++i)
				next_slot[senders[i]] = slot +
				    (beb ? beb_rand(tries[senders[i]]++) :
				    uniform(1, k));

		/*
		 * Si le slot est occupé, c'est-à-dire si une station a effectué
		 * une transmission au cours de ce slot, on le considère comme
		 * "utile".
		 */
		if (is_slot_occupied)
			++res.useful_slots;

		/* Sortie d'état. */
		fprintf(stderr,
		    "Slot#%u: %suseful, queued_msgs=%u\n",
		    slot, is_slot_occupied ? "" : "not ", res.queued_msgs);
	}

	if (tries)
		free(tries);
	free(senders);
	free(next_slot);
	return res;
}
