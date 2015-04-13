#include "bufio.h"
#include "helpers.h"
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

const size_t MAX_BUF = 8192;
const size_t MAX_STR = 4096;
const char DELIM = '\n';

int main(int argc, char *argv[]) 
{
    if (argc < 2) {
        perror("Incorrect number of arguments");
        exit(EXIT_FAILURE);
    }
    int dev_null = open("/dev/null", O_WRONLY);
    dup2(dev_null, STDERR_FILENO);
    char last_arg[MAX_STR];
    struct buf_t *buffer = buf_new(MAX_BUF);
    struct buf_t *out_buf = buf_new(MAX_BUF);
    char *args[argc + 1];
    for (int i = 0; i < argc - 1; ++i)
        args[i] = argv[i + 1];
    args[argc] = (char *) NULL;
    ssize_t len;
    while ((len = buf_getline(STDIN_FILENO, buffer, last_arg)) > 0) {
        args[argc - 1] = last_arg;
        int spawn_res = spawn(args[0], args);
        if (spawn_res < 0) {
            perror("Spawn error");
            exit(EXIT_FAILURE);
        } else if (!spawn_res) {
            last_arg[len] = '\n';
            buf_write(STDOUT_FILENO, out_buf, last_arg, len + 1);
        }
    }
    ssize_t res = buf_flush(STDOUT_FILENO, out_buf, 1);
    if (res < 0) {
        perror("Error while flushing buffer");
        exit(EXIT_FAILURE);
    }

    return 0;
}
