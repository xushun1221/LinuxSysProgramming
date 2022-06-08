#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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
        close(pipefd[1]);
        wait(NULL);
        wait(NULL);
    } else if (index == 1) { // 1 号进程 wc -l
        close(pipefd[1]);
        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            perror("dup2 error");
            exit(1);
        }
        execlp("wc", "wc", "-l", NULL);
        perror("execlp error");
        // close(pipefd[0]);
    } else if (index == 0) { // 0 号进程 ls
        close(pipefd[0]);
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            perror("dup2 error");
            exit(1);
        }
        execlp("ls", "ls", NULL);
        perror("execlp error");
        // close(pipefd[1]);
    }
    return 0;
}