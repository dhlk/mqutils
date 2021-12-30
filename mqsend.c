#include <errno.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[]) {
	mqd_t mqdes = 0;
	const char *msg_ptr = NULL;
	size_t msg_len = 0;
	unsigned int msg_prio = 0;

	if (argc != 4) {
		fprintf(stderr, "usage: %s queue message priority\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if ((mqdes = mq_open(argv[1], O_WRONLY)) == -1) {
		perror("unable to open mq");
		exit(EXIT_FAILURE);
	}

	msg_ptr = argv[2];
	msg_len = strlen(msg_ptr);

	char *endptr = NULL;
	errno = 0;
	msg_prio = (int)strtoul(argv[3], &endptr, 10);
	if (errno == 0 && (endptr == argv[3] || *endptr != '\0')) {
		errno = EINVAL;
	}
	if (errno != 0) {
		perror("invalid priority");
		exit(EXIT_FAILURE);
	}

	if (mq_send(mqdes, msg_ptr, msg_len, msg_prio) == -1) {
		perror("unable to send message");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
