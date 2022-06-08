#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void catch(int signo) {
    printf("\ncatch sig : %d\n", signo);
    printf("1\n");sleep(1);
    printf("2\n");sleep(1);
    printf("3\n");sleep(1);
    return;
}

int main(int argc, char** argv) {

    struct sigaction act, oldact;
    act.sa_handler = catch;        // 设置回调函数
    sigemptyset(&act.sa_mask);      // 设置清空屏蔽字
    act.sa_flags = 0;               // 设置参数 0 默认屏蔽该函数捕捉的信号
    if (sigaction(SIGTSTP, &act, &oldact) == -1) { // 注册 20
        perror("sigaction error");
        exit(1);
    }
    if (sigaction(SIGQUIT, &act, &oldact) == -1) { // 注册 3
        perror("sigaction error");
        exit(1);
    }
    while (1) { }
    return 0;
}