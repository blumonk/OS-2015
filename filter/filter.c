#include "helpers.h"
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

const size_t MAX_BUF = 8192;
const char DELIM = '\n';

size_t find_delim(char *array, size_t size, char delim) 
{
	for (size_t i = 0; i < size; ++i)
		if (array[i] == delim)
			return i;
	return -1;
}

int main(int argc, char *argv[]) 
{
	if (argc < 2) {
		perror("Incorrect number of arguments");
		exit(EXIT_FAILURE);
	}
	int dev_null = open("/dev/null", O_WRONLY);
	dup2(dev_null, STDERR_FILENO);
	char buffer[MAX_BUF];
	char *args_buf[argc + 1];
	for (int i = 0; i < argc - 1; ++i)
		args_buf[i] = argv[i + 1];
	args_buf[argc - 1] = buffer;
	args_buf[argc] = (char *) NULL;
	
	ssize_t count = 0;
	size_t offset = 0;
	while ((count = read_until(STDIN_FILENO, buffer + offset, MAX_BUF - offset, DELIM)) > 0) 
	{
		size_t start = 0;
		size_t delim_offset = 0;
		count += offset;
		while ((delim_offset = find_delim(buffer + start, count - start, DELIM)) != -1)
		{
			memcpy(args_buf[argc - 1], buffer + start, delim_offset);
			args_buf[argc - 1][delim_offset] = 0;
			if (spawn(args_buf[0], args_buf) == 0) {
				args_buf[argc - 1][delim_offset] = '\n';
				if (write_(STDOUT_FILENO, args_buf[argc - 1], delim_offset + 1) < 0) {
					perror("Error while writing");
					exit(EXIT_FAILURE);
				}
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
	if (!offset)
		return 0;
	memcpy(args_buf[argc - 1], buffer, offset);
	args_buf[argc - 1][offset] = 0;
	if (spawn(args_buf[0], args_buf) == 0) {
		args_buf[argc - 1][offset] = '\n';
		if (write_(STDOUT_FILENO, args_buf[argc - 1], offset + 1) < 0) {
			perror("Error while writing");
			exit(EXIT_FAILURE);
		}
	}

	return 0;
}
