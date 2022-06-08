#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe error");
        exit(1);
    }
    pid_t pid = fork();
    if (pid > 0) { // 父进程 wc -l
        close(pipefd[1]);
        // wc 默认从STDIN输入 需要重定向
        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            perror("dup2 error");
            exit(1);
        }
        execlp("wc", "wc", "-l", NULL);
        perror("execlp error");
        // close(pipfd[0]);
    } else if (pid == 0) { // 子进程 ls
        close(pipefd[0]);
        // ls 默认写入STDOUT 需要重定向
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            perror("dup2 error");
            exit(1);
        }
        execlp("ls", "ls", NULL);
        perror("execlp error");
        // close(pipfd[1]); 关闭不了 需要依赖隐式回收
    } else {
        perror("fork error");
        exit(1);
    }
    return 0;
}