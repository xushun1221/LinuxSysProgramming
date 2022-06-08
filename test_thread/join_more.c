/*
@Filename : join_more.c
@Description : join more threads
@Datatime : 2022/06/05 10:31:16
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
    printf("--child thread : %dth, pid = %d, tid = %lu\n", i + 1, getpid(), pthread_self());
    pthread_exit(NULL);
}

int main(int argc, char** argv) {
    pthread_t tid[5];
    int ret;
    for (int i = 0; i < 5; ++ i) {
        if ((ret = pthread_create(tid + i, NULL, tfunc, (void*)i)) != 0) {
            printf("pthread_create error : %d\n", ret);
            exit(1);
        }
    }
    printf("--main thread : pid = %d, tid = %lu\n", getpid(), pthread_self());
    for (int i = 0; i < 5; ++ i) {
        if ((ret = pthread_join(tid[i], NULL)) != 0) {
            printf("pthread_join error : %d\n", ret);
            exit(1);
        }
        printf("--main thread : join tid = %lu\n", tid[i]);
    }
    pthread_exit(NULL);
}