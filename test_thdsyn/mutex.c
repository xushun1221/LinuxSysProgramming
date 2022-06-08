/*
@Filename : mutex.c
@Description : test pthread_mutex
@Datatime : 2022/06/06 10:50:10
@Author : xushun
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

pthread_mutex_t mutex; // 互斥锁

void* tfunc(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex); // 加锁
        printf("hello ");
        sleep(rand() % 3);
        printf("world\n");
        pthread_mutex_unlock(&mutex); // 解锁
        sleep(rand() % 3);
    }
    pthread_exit(NULL);
}

int main(int argc, char** argv) {
    int ret;
    pthread_t tid;
    srand(time(NULL));
    ret = pthread_mutex_init(&mutex, NULL); // 创建互斥锁
    if (ret != 0) {
        fprintf(stderr, "pthread_mutex_init error : %s\n", strerror(ret));
        exit(1);
    }
    ret = pthread_create(&tid, NULL, tfunc, NULL);
    if (ret != 0) {
        fprintf(stderr, "pthread_create error : %s\n", strerror(ret));
        exit(1);
    }
    while (1) {
        pthread_mutex_lock(&mutex); // 加锁
        printf("HELLO ");
        sleep(rand() % 3);
        printf("WORLD\n");
        pthread_mutex_unlock(&mutex); // 解锁
        sleep(rand() % 3);
    }
    ret = pthread_join(tid, NULL);
    if (ret != 0) {
        fprintf(stderr, "pthread_join error : %s\n", strerror(ret));
        exit(1);
    }
    ret = pthread_mutex_destroy(&mutex); // 销毁互斥锁
    if (ret != 0) {
        fprintf(stderr, "pthread_destroy error : %s\n", strerror(ret));
        exit(1);
    }
    return 0;
}