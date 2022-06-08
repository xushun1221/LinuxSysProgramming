#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    int fd = open("ps.out", O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (fd == -1) {
        perror("open ps.out error");
        exit(1);
    }
    dup2(fd, STDOUT_FILENO);
    execlp("ps", "ps", "aux", NULL);
    // close(fd); // 这里close没用 因为execlp会从之前的进程切换
    return 0;
}