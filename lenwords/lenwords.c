#include "helpers.h"
#include <stdio.h>
#include <string.h>


const size_t MAX_BUF = 8192;
const size_t OUT_BUF = 64;
const char DELIM = ' ';

size_t find_delim(char *array, size_t size, char delim)
{
	for (size_t i = 0; i < size; ++i)
		if (array[i] == delim)
			return i;
	return -1;
}

int main()
{
	char buffer[MAX_BUF];
	char out_buffer[OUT_BUF];
	ssize_t count = 0;
	size_t offset = 0;
	while ((count = read_until(STDIN_FILENO, buffer + offset, MAX_BUF - offset, DELIM)) > 0)
	{
		size_t start = 0;
		size_t delim_offset = 0;
		count += offset;
		while ((delim_offset = find_delim(buffer + start, count - start, DELIM)) != -1)
		{
			sprintf(out_buffer, "%zu ", delim_offset);
			if (write_(STDOUT_FILENO, out_buffer, OUT_BUF) < 0)
				perror("Error while writing");
			start += delim_offset + 1;
		}
		memmove(buffer, buffer + start, count - start);
		offset = count - start;
	}
	if (count < 0)
		perror("Error while reading");
	if (offset > 1) {
		sprintf(out_buffer, "%zu", offset - 1);
		if (write_(STDOUT_FILENO, out_buffer, OUT_BUF) < 0)
			perror("Error while writing");
	}

	return 0;
}


