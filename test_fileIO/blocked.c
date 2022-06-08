#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main() {
    char buf[10];
    int read_bytes = read(STDIN_FILENO, buf, 10);
    if (read_bytes < 0) {
        perror("read STDIO_FILENO");
        exit(1);
    }
    write(STDOUT_FILENO, buf, read_bytes);
    return 0;
}