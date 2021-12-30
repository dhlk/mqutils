#include <errno.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]) {
	const char *name = NULL;

	if (argc != 2) {
		fprintf(stderr, "usage: %s queue\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	name = argv[1];

	if (mq_unlink(name) == -1) {
		perror("failed to open message queue");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
