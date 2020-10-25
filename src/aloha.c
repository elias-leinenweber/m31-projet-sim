#include <stdbool.h>
#include <stdint.h>

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
	uint32_t slot, station;

	reset_seed();
	for (slot = 0; slot < SLOTS; ++slot) {
		for (station = 0; station < n; ++station) {
			if (randbool(p)) {
			}
		}
	}

	return res;
}
