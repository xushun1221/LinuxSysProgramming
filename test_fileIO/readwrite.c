#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
int main() {
    int fd_in = open("./bigfile.txt", O_RDONLY);
    int fd_out = open("./bigfile.cp1", O_WRONLY | O_CREAT | O_TRUNC, 0664);
    char buf[1];
    int read_bytes;
    while ((read_bytes = read(fd_in, buf, 1)) != 0) {
        write(fd_out, buf, read_bytes);
    }
    close(fd_in);
    close(fd_out);
    return 0;
}