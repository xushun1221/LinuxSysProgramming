#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[]) {
    int fd = open("test.txt", O_RDWR);
    if (fd == -1) {
        perror("open error");
        exit(1);
    }
    // 把标准输出重定向到test.txt
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2 error");
        exit(1);
    }
    printf("dup2 test write to STDOUT\n");
    close(fd);
    return 0;
}