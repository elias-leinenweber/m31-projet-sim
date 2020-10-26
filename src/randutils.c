#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "randutils.h"

void
reset_seed()
{
	srand(time(NULL));
}

bool
randbool(float p)
{
	return rand() < p * RAND_MAX;
}

uint32_t
randint(uint32_t lo, uint32_t hi)
{
	return lo + (rand() % (hi - lo));
}
