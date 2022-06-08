#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int fd_out = open("./bigfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (fd_out == -1) {
        perror("bigfile create failed");
        exit(1);
    }
    char buf[4096];
    for (int i = 0; i < 4096; i ++) {
        buf[i] = 'a';
    }
    for (int i = 0; i < 1000; i ++) {
        if (write(fd_out, buf, 4096) == -1) {
            perror("write error");
            break;
        }
    }
    close(fd_out);
    return 0;
}