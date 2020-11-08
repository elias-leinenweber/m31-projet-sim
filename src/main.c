#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "aloha.h"
#include "randutils.h"

#define P	0.01
#define K	4
#define SLOTS	250
#define TESTS	100

static void	usage(void);
static void	sim_loop(double, uint32_t, uint32_t, uint32_t, bool);
static void	sim(double, uint32_t, uint32_t, uint32_t, bool);

static int	sim_id;

int
main(int argc, char *argv[])
{
	uint32_t i, k, kmax, nmax, slots, slotsmax;
	double n, p, pmax;

	if (argc > 5)
		usage();
	pmax = argc > 1 ? atof(argv[1]) : P;
	kmax = argc > 2 ? atoi(argv[2]) : K;
	nmax = argc > 3 ? atoi(argv[3]) : 100;
	slotsmax = argc > 4 ? atoi(argv[4]) : SLOTS;

	reset_seed();
	printf("sim_id;p;k;n;slots;useful_slots;queued_msgs;np\n");

	/* Première partie. */
	sim_id = 1;
	for (k = K; k <= kmax; ++k)
		for (i = 0; i < TESTS; ++i)
			sim_loop(pmax, k, nmax, SLOTS, false);

	/* Deuxième partie. */
	sim_id = 2;
	for (slots = 0; slots <= slotsmax; ++slots) {
		for (n = 10; n <= 50; n += 10)
			for (i = 0; i < TESTS; ++i)
				sim(0.01, K, n, slots, false);
		for (p = 0.001; p <= 0.005; p += 0.0005)
			for (i = 0; i < TESTS; ++i)
				sim(p, K, 100, slots, false);
	}

	/* Troisième partie. */
	sim_id = 3;
	for (slots = 100; slots <= slotsmax; ++slots) {
		for (n = 18; n <= 23; ++n)
			for (p = 0.00875; p <= 0.01; p += 0.00025)
				for (i = 0; i < TESTS; ++i)
					sim(p, K, n, slots, false);
	}

	/* Quatrième partie. */
	sim_id = 4;
	for (slots = 0; slots <= slotsmax; ++slots) {
		for (n = 30; n <= 40; ++n)
			for (p = 0.00875; p <= 0.01; p += 0.00025)
				for (i = 0; i < TESTS; ++i)
					sim(p, K, n, slots, true);
	}

	return EXIT_SUCCESS;
}

static void
usage(void)
{
	extern const char *__progname;

	fprintf(stderr,
	    "usage: %s [p [k [nmax [slots]]]]\n", __progname);
	exit(1);
}

static void
sim_loop(double p, uint32_t k, uint32_t nmax, uint32_t slots, bool beb)
{
	uint32_t n;

	fprintf(stderr,
	    "Pour p = %.2f, k = %u et n variant de 10 à %u :\n", p, k, nmax);
	for (n = 10; n <= nmax; ++n)
		sim(p, k, n, slots, beb);
}

static void
sim(double p, uint32_t k, uint32_t n, uint32_t slots, bool beb)
{
	struct result res;

	res = slotted_aloha(p, k, n, slots, beb);
	printf("%d;%.4f;%u;%u;%u;%u;%u;%.2f\n", sim_id, p, k, n, slots,
	    res.useful_slots, res.queued_msgs, n * p);
}
