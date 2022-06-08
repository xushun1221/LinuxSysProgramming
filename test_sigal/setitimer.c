#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>

void myfunc(int signo) {
    printf("alarm\n");
}

int main(int argc, char** argv) {
    struct itimerval it, oldit;

    signal(SIGALRM, myfunc);

    // 定时时长 2s0us
    it.it_value.tv_sec = 2;
    it.it_value.tv_usec = 0;
    // 定时间隔 5s0us
    it.it_interval.tv_sec = 5;
    it.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &it, &oldit) == -1) {
        perror("setitimer error");
        exit(1);
    }

    int sec = 0;
    while (1) {
        printf("-%3d-\n", ++ sec);
        sleep(1);
    }

    return 0;
}