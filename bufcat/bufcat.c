#include "bufio.h"

const size_t MAX_BUF = 512;

int main()
{
	struct buf_t *buffer = buf_new(MAX_BUF);
	size_t current;
	while ((current = buf_fill(STDIN_FILENO, buffer, 1)) > 0)
	{
		if (buf_flush(STDOUT_FILENO, buffer, current) < 0) {
			buf_free(buffer);
			perror("Error while flushing");
			exit(EXIT_FAILURE);
		}
	}
	buf_free(buffer);
	if (current < 0) {
		perror("Error while filling");
		exit(EXIT_FAILURE);
	}
}
