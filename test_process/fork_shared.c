#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int global_var = 100;

int main(int argc, char* argv[]) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork error\n");
        exit(1);
    } else if (pid == 0) {
        global_var = 200;
        printf("-- child process : pid = %d, ppid = %d\n", getpid(), getppid());
        printf("-- child process : global_var = %d\n", global_var);
    } else {
        //sleep(1);
        global_var = 300;
        printf("-- parent process : pid = %d, ppid = %d\n", getpid(), getppid());
        printf("-- parent process : global_var = %d\n", global_var);
    }
    printf("--finish--\n");
    return 0;
}