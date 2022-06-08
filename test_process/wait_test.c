#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    pid_t pid = fork();
    if (pid == 0) { // 子进程
        printf("-- child process : my pid = %d, sleep 10s\n", getpid());
        sleep(10);
        printf("-- child process : die\n");
    } else if (pid > 0) { // 父进程
        int wstatus;
        pid_t wpid = wait(&wstatus);
        if (wpid == -1) {
            perror("-- parent process : wait error");
            exit(1);
        }
        if (WIFEXITED(wstatus)) {
            printf("-- parent process : child exit with %d\n", WEXITSTATUS(wstatus));
        } else if (WIFSIGNALED(wstatus)) {
            printf("-- parent process : child killed by signal %d\n", WTERMSIG(wstatus));
        }
    }
    return 0;
}