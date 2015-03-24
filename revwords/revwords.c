#include "helpers.h"
#include <stdio.h>
#include <string.h>

const size_t MAX_BUF = 8192;
const char DELIM = ' ';

size_t find_delim(char *array, size_t size, char delim) 
{
	for (size_t i = 0; i < size; ++i)
		if (array[i] == delim)
			return i;
	return -1;
}

void reverse(char *array, size_t size) 
{
	for (size_t i = 0; i < (size + 1) / 2; ++i) 
	{
		char c = array[i];
		array[i] = array[size - 1 - i];
		array[size - 1 - i] = c;
	}
}

int main() 
{
	char buffer[MAX_BUF];
	ssize_t count = 0;
	size_t offset = 0;
	while ((count = read_until(STDIN_FILENO, buffer + offset, MAX_BUF - offset, DELIM)) > 0) 
	{
		size_t start = 0;
		size_t delim_offset = 0;
		count += offset;
		while ((delim_offset = find_delim(buffer + start, count - start, DELIM)) != -1)
		{
			reverse(buffer + start, delim_offset);
			if (write_(STDOUT_FILENO, buffer + start, delim_offset + 1) < 0) {
				perror("Error while writing");
				exit(EXIT_FAILURE);
			}
			start += delim_offset + 1;
		}
		memmove(buffer, buffer + start, count - start);
		offset = count - start;
	}
	if (count < 0) {
		perror("Error while reading");
		exit(EXIT_FAILURE);
	}
	reverse(buffer, offset);
	if (write_(STDOUT_FILENO, buffer, offset) < 0) {
		perror("Error while writing");
		exit(EXIT_FAILURE);
	}

	return 0;
}
