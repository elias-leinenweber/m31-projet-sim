#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "aloha.h"

static void	usage(void);

int
main(int argc, char *argv[])
{
	struct result res;
	uint32_t k, n;
	float p;

	if (argc > 3)
		usage();
	p = argc > 1 ? atoi(argv[1]) : 0.01;
	k = argc > 2 ? atoi(argv[2]) : 4;

	printf("Pour p = %.2f, k = %u et n variant de 10 à 100 :\n", p, k);
	printf("n\tSlots_u\tMsg_q\n");
	for (n = 10; n <= 100; ++n) {
		res = slotted_aloha(p, k, n);
		printf("%d\t%u\t%u\n", n, res.useful_slots, res.queued_msgs);
	}
	return 0;
}

static void
usage(void)
{
	extern const char *__progname;

	fprintf(stderr, "usage: %s [p [k]]\n", __progname);
	exit(1);
}
