#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "aloha.h"

static void	usage(void);

int
main(int argc, char *argv[])
{
	if (argc != 4)
		usage();

	printf("Hello world!\n");
	return 0;
}

static void
usage(void)
{
	extern const char *__progname;

	fprintf(stderr, "usage: %s p k n\n", __progname);
	exit(1);
}
