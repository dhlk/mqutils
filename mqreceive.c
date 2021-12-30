#include <errno.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]) {
	mqd_t mqdes = 0;
	char *msg_ptr = NULL;
	size_t msg_len = 0;

	if (argc != 2) {
		fprintf(stderr, "usage: %s queue\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if ((mqdes = mq_open(argv[1], O_RDONLY)) == -1) {
		perror("unable to open mq");
		exit(EXIT_FAILURE);
	}

	{
		struct mq_attr attr;
		if (mq_getattr(mqdes, &attr) == -1) {
			perror("unable to get mq attributes");
			exit(EXIT_FAILURE);
		}

		msg_len = (size_t)attr.mq_msgsize;
		msg_ptr = calloc((msg_len / sizeof(char))+1, sizeof(char));
	}

	if (mq_receive(mqdes, msg_ptr, msg_len, NULL) == -1) {
		perror("unable to receive");
		exit(EXIT_FAILURE);
	}

	printf("%s", msg_ptr);

	exit(EXIT_SUCCESS);
}
