#include <stdbool.h>
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
