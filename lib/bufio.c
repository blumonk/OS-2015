#include "bufio.h"
#include <stdbool.h>

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
	if (buf == NULL || required > buf->size)
		abort();
#endif
	size_t current;
	size_t result = 0;
    size_t old_size = buf->size;
	while (result < required)
	{
		current = write(fd, buf->data + result, old_size - result);
		result += current;
		if (current < 0)
			return -1;
	}
	buf->size -= result;
	memmove(buf->data, buf->data + result, old_size - result);
	return result;
}

ssize_t buf_getline(fd_t fd, struct buf_t *buf, char *dest)
{
    bool got_endl = false;
    size_t endl_pos;
    size_t result = 0;
    while (true) {
        endl_pos = 0;
        while (endl_pos < buf->size)
        {
            char curr = *((char*)buf->data + endl_pos); 
            if (curr == '\n') {
                got_endl = true;
                break;
            }
            endl_pos++;
        }
        if (got_endl) {
            memmove(dest, buf->data, endl_pos);
            *(dest + endl_pos) = 0;
            result += endl_pos;
            endl_pos++;
            memmove(buf->data, buf->data + endl_pos, buf->size - endl_pos);
            buf->size -= endl_pos;
            return result;
        } else {
            memmove(dest, buf->data, buf->size);
            dest += buf->size;
            result += buf->size;
            buf->size = 0;
        }
        if (buf_fill(fd, buf, 1) <= 0)
            return result;
    }
    return result;
}

ssize_t buf_write(fd_t fd, struct buf_t *buf, char *src, size_t len)
{
    size_t result = 0;
    while (len) {
        size_t space = buf->capacity - buf->size;
        if (len < space) {
            memmove(buf->data + buf->size, src, len);
            buf->size += len;
            return result + len;
        } else {
            len -= space;
            memmove(buf->data + buf->size, src, space);
            buf->size += space;
            src += space;
            ssize_t curr;
            if ((curr = buf_flush(fd, buf, 1)) < 0) {
                return result;
            } else {
                result += curr;
            }
        }
    }
    return -1;
}
