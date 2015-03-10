#include <stdio.h>
#include <unistd.h> 
#include "helpers.h"

int main()
{
	char buffer[512];
	int bytes_count = 0;
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
