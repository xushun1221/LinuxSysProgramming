#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe error");
        exit(1);
    }
    pid_t pid = fork();
    if (pid > 0) {
        close(pipefd[0]); // 父进程 关闭读端
        write(pipefd[1], "hello pipe\n", strlen("hellp pipe\n"));
        close(pipefd[1]);
        sleep(1); // 保证在子进程后结束
    } else if (pid == 0) {
        close(pipefd[1]); // 子进程 关闭写端
        char buf[1024];
        int readbytes = read(pipefd[0], buf, sizeof(buf));
        close(pipefd[0]);
        int writebytes = write(STDOUT_FILENO, buf, readbytes);
        if (writebytes == -1) {
            perror("write error");
            exit(1);
        }
    } else {
        perror("fork error");
        exit(1);
    }
    return 0;
}