#include <errno.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, const char *argv[]) {
	const char *name = NULL;
	int oflag = O_RDWR | O_CREAT | O_EXCL;
	mode_t mode = ACCESSPERMS; // umask will effect this
	struct mq_attr attr;

	if (argc != 4) {
		fprintf(stderr, "usage: %s queue max_messages max_message_size\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	name = argv[1];

	char *endptr = NULL;
	errno = 0;
	attr.mq_maxmsg = strtoul(argv[2], &endptr, 10);
	if (errno == 0 && (endptr == argv[2] || *endptr != '\0')) {
		errno = EINVAL;
	}
	if (errno != 0) {
		perror("invalid max messages");
		exit(EXIT_FAILURE);
	}

	errno = 0;
	attr.mq_msgsize = strtoul(argv[3], &endptr, 10);
	if (errno == 0 && (endptr == argv[3] || *endptr != '\0')) {
		errno = EINVAL;
	}
	if (errno != 0) {
		perror("invalid max message size");
		exit(EXIT_FAILURE);
	}

	if (mq_open(name, oflag, mode, &attr) == -1) {
		perror("failed to open message queue");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
