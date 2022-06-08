#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[]) {
    int i;
    for (i = 0; i < 5; ++ i) {
        if (fork() == 0) {// 子进程
            break;
        }
    }
    if (i == 5) {
        sleep(1); // 保证父进程最后结束
        printf("I'm parent\n");
    } else {
        printf("I'm %dth child\n", i + 1);
    }
    return 0;
}