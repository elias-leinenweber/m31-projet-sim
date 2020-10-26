#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "aloha.h"
#include "randutils.h"

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
	struct result res;
	uint32_t *next_slot, slot, station;
	bool is_slot_occupied;

	res.useful_slots = 0;
	res.queued_msgs = 0;
	next_slot = calloc(n, sizeof(uint32_t));

	reset_seed();
	for (slot = 0; slot < SLOTS; ++slot) {
		is_slot_occupied = false;
		for (station = 0; station < n; ++station)
			if (!next_slot[station]) {
				if (slot == next_slot[station])
					attempt_send(k, next_slot, slot,
					    station, &is_slot_occupied);
			} else if (randbool(p))
				attempt_send(k, next_slot, slot, station,
				    &is_slot_occupied);
		if (!is_slot_occupied)
			++res.useful_slots;
	}

	free(next_slot);
	return res;
}

void
attempt_send(uint32_t k, uint32_t *next_slot, uint32_t slot, uint32_t station,
    bool *is_slot_occupied)
{
	if (!*is_slot_occupied) {
		next_slot[station] = 0;
		*is_slot_occupied = true;
	} else {
		next_slot[station] = randint(slot, slot + k) + 1;
	}
}
