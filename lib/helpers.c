#include "helpers.h"

ssize_t read_(int fd, void *buf, size_t count)
{
	int result = 0;
	int current = 0;
	while ((current = read(fd, buf, count - result)) > 0)
	{
		result += current;	
		buf += current;
	}	
	if (current < 0) {
		return -1;
	}
	return result;
}

ssize_t write_(int fd, const void *buf, size_t count) 
{
	int result = count;
   	int current = 0;
	while (result > 0)
	{
		current = write(fd, buf, count);
		if (current < 0) {
			return -1;
		} else {
			result -= current;
			buf += current;
		}
	}		
	return count;
}

ssize_t read_until(int fd, void *buf, size_t count, char delimiter) 
{
	int result = 0;
	int current = 0;
	while ((current = read(fd, buf, count - result)) > 0)
	{
		for (int i = 0; i < current; ++i) {
			if (((char*)buf)[i] == delimiter) 
				return result + current;
		}
		result += current;	
		buf += current;
	}	
	if (current < 0) {
		return -1;
	}
	return result;
}
