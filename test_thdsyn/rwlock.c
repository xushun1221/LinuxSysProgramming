/*
@Filename : rwlock.c
@Description : test pthread_rwlock
@Datatime : 2022/06/06 15:19:39
@Author : xushun
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

int global_counter;
pthread_rwlock_t rwlock;

void* th_write(void* arg) {
    int i = (int)arg;
    int t;
    while (1) {
        pthread_rwlock_wrlock(&rwlock);
        t = global_counter;
        usleep(1000); // 抱着睡 浪费时间
        printf("==write(%d - tid %lu) : %d, ++ counter %d\n", i, pthread_self(), t, ++ global_counter);
        pthread_rwlock_unlock(&rwlock);
        usleep(10000);
    }
    return NULL;
}

void* th_read(void* arg) {
    int i = (int)arg;
    while (1) {
        pthread_rwlock_rdlock(&rwlock);
        printf("--read (%d - tid %lu) : %d\n", i, pthread_self(), global_counter);
        pthread_rwlock_unlock(&rwlock);
        usleep(2000);
    }
    return NULL;
}

int main(int argc, char** argv) {
    // 错误码判断就不写了 ^^
    int ret;
    pthread_t tids[8];
    ret = pthread_rwlock_init(&rwlock, NULL);
    for (int i = 0; i < 3; ++ i) { // 3 write thread
        ret = pthread_create(tids + i, NULL, th_write, (void*)i);
    }
    for (int i = 0; i < 5; ++ i) { // 5 read  thread
        ret = pthread_create(tids + i + 3, NULL, th_read, (void*)i);
    }
    for (int i = 0; i < 8; ++ i) {
        ret = pthread_join(tids[i], NULL);
    }
    ret = pthread_rwlock_destroy(&rwlock);
    return 0;
}