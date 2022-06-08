#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
int main() {
    char buf[10];
    int fd = open("/dev/tty", O_RDONLY | O_NONBLOCK); // 非阻塞
    if (fd < 0) {
        perror("open /dev/tty");
        exit(1);
    }
    int read_bytes;
tryagain:
    read_bytes = read(fd, buf, 10);
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
    // close(fd);
    return 0;
}