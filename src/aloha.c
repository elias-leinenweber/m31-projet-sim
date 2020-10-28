#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "aloha.h"
#include "randutils.h"

static void	attempt_send(uint32_t, uint32_t *, uint32_t, uint32_t, bool *);

/*
 * Effectue une simulation.
 *
 * Paramètres :
 * - p : probabilité de commencer une émission au début d'un slot
 * - k : nombre de slots suivants parmi lesquels choisir le slot de réémission
 * - n : nombre de stations
 */
struct result
slotted_aloha(float p, uint32_t k, uint32_t n)
{
	struct result res;			/* Résultats de la simulation */
	uint32_t *next_slot, slot, station;
	bool is_slot_occupied;

	/* Initialisation des variables */
	res.useful_slots = 0;
	res.queued_msgs = 0;
	next_slot = calloc(n, sizeof(uint32_t));

	reset_seed();
	/* Pour chaque slot (représentant chacun une unité de temps) : */
	for (slot = 0; slot < SLOTS; ++slot) {
		/* On débute un nouveau slot : il n'est pas occupé. */
		is_slot_occupied = false;

		/* Pour toutes les stations : */
		for (station = 0; station < n; ++station) {
			/*
			 * Soit elle a déjà tenté (et échoué) de transmettre un
			 * message : dans ce cas-là, si elle a choisi le slot
			 * courant pour ré-émettre son message, on tente à
			 * nouveau de transmettre le message.
			 * Sinon, elle tente de transmettre un nouveau message
			 * avec une probabilité égale à `p`.
			 */
			if ((!next_slot[station] && slot == next_slot[station]) || randbool(p))
				attempt_send(k, next_slot, slot, station, &is_slot_occupied);
		}

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

	free(next_slot);
	return res;
}

/*
 * Routine permettant de tenter l'émission d'un message.
 */
static void
attempt_send(uint32_t k, uint32_t *next_slot, uint32_t slot, uint32_t station,
    bool *is_slot_occupied)
{
	if (!*is_slot_occupied) {
		/*
		 * Si le slot n'est pas occupé, on transmet le message,
		 * réinitialise la variable `next_slot` (au cas où elle serait
		 * initialisée, si la tentative précédente de transmission avait
		 * échouée) et marque le slot courant comme occupé.
		 */
		next_slot[station] = 0;
		*is_slot_occupied = true;
	} else {
		/*
		 * Sinon il y a collision, et dans ce cas, la station doit
		 * ré-émettre son message ultérieurement. Pour déterminer le
		 * moment de la ré-émission, la station choisit un slot au
		 * hasard uniformément parmi les `k` slots suivants.
		 */
		next_slot[station] = randint(slot, slot + k) + 1;
	}
}
