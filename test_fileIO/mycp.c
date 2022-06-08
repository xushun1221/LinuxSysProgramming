#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int fd_in = open(argv[1], O_RDONLY);
    if (fd_in == -1) {
        perror("argv1 open failed"); // stdio.h
        exit(1); // stdlib.h
    }
    int fd_out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (fd_out == -1) {
        perror("argv2 open failed");
        close(fd_in);
        exit(1);
    }
    char buf[1024];
    int read_bytes;
    while ((read_bytes = read(fd_in, buf, 1024)) != 0) {
        if (read_bytes == -1) {
            perror("read error");
            break;
        }
        if (write(fd_out, buf, read_bytes) == -1) {
            perror("write error");
            break;
        }
    }
    close(fd_in);
    close(fd_out);
    return 0;
}