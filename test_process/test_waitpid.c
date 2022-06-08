#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
int main(int argc, char* argv[]) {
    pid_t pid, tpid, wpid;
    int i;
    for (i = 0; i < 5; ++ i) {
        pid = fork();
        if (pid == 0) { // 子
            break;
        } else if (i == 2) { // 父
            tpid = pid;
        }
    }
    if (i == 5) { // 父
        sleep(5);
        wpid = waitpid(tpid, NULL, WNOHANG);
        if (wpid == -1) {
            perror("waitpid error");
            exit(1);
        }
        printf("I'm parent, waitpid %d\n", tpid);
    } else { // 子
        sleep(i);
        printf("I'm %dth child, my pid = %d\n", i + 1, getpid());
    }
    return 0;
}