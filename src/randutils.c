#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "randutils.h"

/*
 * Initialise la graine avec le temps courant.
 */
void
reset_seed()
{
	srand(time(NULL));
}

/*
 * Renvoie `true` avec une probabilité `p`.
 */
bool
randbool(float p)
{
	assert(p >= 0 && p <= 1);
	return rand() < p * RAND_MAX;
}

/*
 * Renvoie un entier non signé aléatoire avec une probabilité uniforme, compris
 * entre `lo` (inclus) et `hi` (exclu).
 */
uint32_t
randint(uint32_t lo, uint32_t hi)
{
	assert(lo < hi);
	return lo + (rand() % (hi - lo));
}

/*
 * Renvoie un entier non signé aléatoire suivant une loi uniforme discrète de
 * paramètres (`a`, `b`).
 */
uint32_t
uniform(uint32_t a, uint32_t b)
{
	assert(b >= a);
	return randint(a, b + 1);
}

/*
 * Algorithme "binary exponential backoff" : à chaque tentative, la borne
 * supérieure double.
 */
uint32_t
beb_rand(uint32_t try) {
	uint32_t hi = 1;

	hi <<= try + 1;
	if (hi == 0)
		hi = 1;
	return uniform(1, hi);
}
