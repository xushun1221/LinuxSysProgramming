#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
int main() {
    char buf[10];
    int flags = fcntl(STDIN_FILENO, F_GETFL);
    if (flags == 1) {
        perror("fcntl error");
        exit(1);
    }
    flags |= O_NONBLOCK; // 设置为非阻塞
    int ret = fcntl(STDIN_FILENO, F_SETFL, flags);
    if (ret == -1) {
        perror("fcntl error");
        exit(1);
    }
    int read_bytes;
tryagain:
    read_bytes = read(STDIN_FILENO, buf, 10);
    if (read_bytes < 0) {
        if (errno != EAGAIN) {
            perror("read /dev/tty");
            exit(1);
        } else {
            write(STDOUT_FILENO, "try again\n", strlen("try again\n"));
            sleep(2);
            goto tryagain;
        }
    }
    write(STDOUT_FILENO, buf, read_bytes);
    return 0;
}