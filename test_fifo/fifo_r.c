#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>

int main (int argc, char** argv) {
    if (argc < 2) {
        printf("enter like : fifo_c fifoname\n");
        return -1;
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open fifo error");
        exit(1);
    }
    char buf[1024];
    while (1) {
        int read_bytes = read(fd, buf, sizeof(buf));
        write(STDOUT_FILENO, buf, read_bytes);
    }
    close(fd);
    return 0;
}