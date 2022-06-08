/*
@Filename : more_thread.c
@Description : 
@Datatime : 2022/06/04 15:26:16
@Author : xushun
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

void* tfunc(void* arg) {
    int i = (int)arg;
    sleep(i);
    if (i == 2) { // 第三个子线程
        exit(0); // 尝试退出线程？
    }
    printf("--child thread : %dth, pid = %d, tid = %lu\n", i + 1, getpid(), pthread_self());
    return NULL;
}

int main(int argc, char** argv) {
    pthread_t tid;
    int ret;
    for (int i = 0; i < 5; ++ i) {
        if ((ret = pthread_create(&tid, NULL, tfunc, (void*)i)) != 0) {
            printf("pthread_create error : %d\n", ret);
            exit(1);
        }
    }
    sleep(5);
    printf("--main thread : pid = %d, tid = %lu\n", getpid(), pthread_self());
    return 0;
}