#include "helpers.h"
#include <stdio.h>

int main()
{
	char buffer[512];
	ssize_t bytes_count = 0;
	while ((bytes_count = read_(STDIN_FILENO, buffer, 512)) > 0)
	{
		if (bytes_count < 0)
		{
			perror("Error while reading");
			exit(EXIT_FAILURE);
		}
		if (write_(STDOUT_FILENO, buffer, bytes_count) < 0)
		{
			perror("Error while writing");
			exit(EXIT_FAILURE);
		}
	}

	return 0;
}
