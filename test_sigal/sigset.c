#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void print_set(sigset_t set) {
    for (int i = 1; i <= 32; ++ i) {
        if (sigismember(&set, i)) {
            putchar('1');
        } else {
            putchar('0');
        }
    }
    printf("\n");
}

int main(int argc, char** argv) {
    sigset_t set, oldset, pedset;
    sigemptyset(&set); // 创建空的信号集
    sigaddset(&set, SIGINT); // 添加SIGINT信号 (Ctrl+c)
    if (sigprocmask(SIG_BLOCK, &set, &oldset) == -1) { // 将SIGINT信号阻塞
        perror("sigprocmask error");
        exit(1);
    }
    while (1) {
        if (sigpending(&pedset) == -1) { // 读取pending未决信号集
            perror("sigpending error");
            exit(1);
        }
        print_set(pedset); // 打印pending
        sleep(1);
    }
    if (sigprocmask(SIG_SETMASK, &oldset, &set)) { // 恢复原来的mask
        perror("sigprocmask error");
        exit(1);
    }
    return 0;
}