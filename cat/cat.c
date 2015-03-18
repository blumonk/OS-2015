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
			return 0;
		}
		if (write_(STDOUT_FILENO, buffer, bytes_count) < 0)
		{
			perror("Error while writing");
			return 0;
		}
	}

	return 0;
}
