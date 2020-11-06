#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "aloha.h"

static void	usage(void);
static void	sim_loop(float, uint32_t, uint32_t);

int
main(int argc, char *argv[])
{
	uint32_t k, kmax, nmax;
	float p;

	if (argc > 4)
		usage();
	p	= argc > 1 ? atof(argv[1]) : 0.01;
	kmax	= argc > 2 ? atoi(argv[2]) : 4;
	nmax	= argc > 3 ? atoi(argv[3]) : 100;

	printf("k;n;useful_slots;queued_msgs\n");
	for (k = 4; k <= kmax; ++k)
		sim_loop(p, k, nmax);

	return EXIT_SUCCESS;
}

static void
usage(void)
{
	extern const char *__progname;

	fprintf(stderr, "usage: %s [p [k [nmax]]]\n", __progname);
	exit(1);
}

static void
sim_loop(float p, uint32_t k, uint32_t nmax)
{
	struct result res;
	uint32_t n;

	fprintf(stderr,
	    "Pour p = %.2f, k = %u et n variant de 10 à %u :\n", p, k, nmax);
	for (n = 10; n <= nmax; ++n) {
		res = slotted_aloha(p, k, n);
		printf("%u;%d;%u;%u\n", k, n, res.useful_slots,
		    res.queued_msgs);
	}
}
