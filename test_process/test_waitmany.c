#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
int main(int argc, char* argv[]) {
    int i;
    for (i = 0; i < 5; ++ i) {
        if (fork() == 0) { // 子
            break;
        }
    }
    if (i == 5) { // 父
        pid_t wpid;
        while ((wpid = waitpid(-1, NULL, WNOHANG)) != -1) {
            if (wpid > 0) {
                printf("wait child %d\n", wpid);
            } else if (wpid == 0) { // 没终止
                sleep(1);
            }
        }
    } else { // 子
        sleep(i);
        printf("I'm %dth child, my pid = %d\n", i + 1, getpid());
    }
    return 0;
}