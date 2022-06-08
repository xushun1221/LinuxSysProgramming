/*
@Filename : cancel.c
@Description : test pthread_cancel
@Datatime : 2022/06/05 11:24:48
@Author : xushun
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

void* tfunc(void* arg) {
    while (1) {
        printf("--child thread : pid = %d, tid = %lu\n", getpid(), pthread_self());
        sleep(1);
    }
    pthread_exit(NULL);
}

int main(int argc, char** argv) {
    int ret;
    pthread_t tid;
    ret = pthread_create(&tid, NULL, tfunc, NULL);
    if (ret != 0) {
        fprintf(stderr, "pthread_create error : %s\n", strerror(ret));
        exit(1);
    }
    sleep(3);
    printf("--main thread : pid = %d, tid = %lu, cancel thread tid(%lu)\n", getpid(), pthread_self(), tid);
    ret = pthread_cancel(tid);
    if (ret != 0) {
        fprintf(stderr, "pthread_cancel error : %s\n", strerror(ret));
        exit(1);
    }
    while(1);
    return 0;
}