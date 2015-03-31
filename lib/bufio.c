#include "bufio.h"

struct buf_t *buf_new(size_t capacity)
{
	struct buf_t *buf = malloc(sizeof *buf);
	buf->size = 0;
	buf->capacity = capacity;
	if ((buf->data = malloc(capacity)) == NULL) {
#ifdef DEBUG
		abort();
#endif
		return NULL;	
	}
	return buf;
} 

void buf_free(struct buf_t *buf)
{
#ifdef DEBUG
	if (buf == NULL)
		abort();
#endif
	free(buf->data);
	free(buf);
}

size_t buf_capacity(struct buf_t *buf)
{
#ifdef DEBUG
	if (buf == NULL)
		abort();
#endif
	return buf->capacity;	
}

size_t buf_size(struct buf_t *buf)
{
#ifdef DEBUG
	if (buf == NULL)
		abort();
#endif
	return buf->size;
}

ssize_t buf_fill(fd_t fd, struct buf_t *buf, size_t required)
{
#ifdef DEBUG
	if (buf == NULL)
		abort();
#endif
	size_t current;
	size_t result = 0;
	size_t rest = buf->capacity - buf->size;
#ifdef DEBUG
	if (rest < required)
		abort();
#endif
	void *ptr = buf->data + buf->size;
	while ((current = (read(fd, ptr + result, rest - result))) > 0)
	{
		result += current;
		if (result >= required)
			break;
	}
	buf->size += result;
	if (current < 0) {
		return -1;
	}
	return result;
}

ssize_t buf_flush(fd_t fd, struct buf_t *buf, size_t required)
{
#ifdef DEBUG
	if (buf == NULL)
		abort();
#endif
	size_t current;
	size_t result = 0;
	size_t cap = buf->capacity;
	while (result < required)
	{
		current = write(fd, buf->data + result, cap - result);
		result += current;
		if (current < 0)
			return -1;
	}
	buf->size -= result;
	memmove(buf->data, buf->data + result, cap - result);
	return result;
}
