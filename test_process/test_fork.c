#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[]) {
    printf("before fork *\n");
    printf("before fork **\n");
    printf("before fork ***\n");
    printf("before fork ****\n");
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork error");
        exit(1);
    } else if (pid == 0) {
        printf("-- child process : I'm created by %d\n", getppid());
        printf("-- child process : I'm %d\n", getpid());
    } else if (pid > 0) {
        printf("-- parent process : I'm created by %d\n", getppid());
        printf("-- parent process : my child is %d\n", pid);
        printf("-- parent process : I'm %d\n", getpid());
    }
    sleep(1);
    printf("after fork\n");
    return 0;
}