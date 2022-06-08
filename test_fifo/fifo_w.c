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
    int fd = open(argv[1], O_WRONLY);
    if (fd == -1) {
        perror("open fifo error");
        exit(1);
    }
    srand(time(NULL));
    char buf[1024];
    int i = 0;
    while (1) {
        sprintf(buf, "pid %d : write to %s : %d\n", getpid(), argv[1], ++ i);
        write(fd, buf, strlen(buf));
        sleep(rand() % 3 + 1);
    }
    close(fd);
    return 0;
}