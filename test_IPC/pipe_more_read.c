#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    int pipefd[2];
    if(pipe(pipefd) == -1) {
        perror("pipe error");
        exit(1);
    }
    int index = 0, n = 2;
    pid_t pid;
    for (index = 0; index < n; ++ index) {
        pid = fork();
        if (pid == -1) {
            perror("fork error");
            exit(1);
        } else if (pid == 0) {
            break;
        }
    }
    if (index == 2) { // 父
        close(pipefd[0]);
        write(pipefd[1], "pipe : several read one write\n", strlen("pipe : several read one write\n"));
        close(pipefd[1]);
        wait(NULL);
        wait(NULL);
    } else if (index == 1) { // 1 号进程
        close(pipefd[1]);
        char buf[1024];
        int read_bytes = read(pipefd[0], buf, sizeof(buf));
        if (read_bytes > 0)
            printf("I'm %dth child\n", index);
        write(STDOUT_FILENO, buf, read_bytes);
        close(pipefd[0]);
    } else if (index == 0) { // 0 号进程
        close(pipefd[1]);
        char buf[1024];
        int read_bytes = read(pipefd[0], buf, sizeof(buf));
        if (read_bytes > 0)
            printf("I'm %dth child\n", index);
        write(STDOUT_FILENO, buf, read_bytes);
        close(pipefd[0]);
    }
    return 0;
}