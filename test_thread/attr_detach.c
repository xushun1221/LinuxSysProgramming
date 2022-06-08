/*
@Filename : attr_detach.c
@Description : test create a PTHREAD_CREATE_DETACH thread
@Datatime : 2022/06/05 14:27:42
@Author : xushun
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

void* tfunc(void* arg) {
    printf("thread : pid = %d, tid = %lu\n", getpid(), pthread_self());
    return NULL;
}

int main(int argc, char** argv) {
    int ret;
    pthread_t tid;
    pthread_attr_t attr;
    // 初始化一个 线程属性结构体
    ret = pthread_attr_init(&attr); 
    if (ret != 0) {
        fprintf(stderr, "pthread_attr_init error : %s\n", strerror(ret));
        exit(1);
    }
    // 设置为分离属性
    ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (ret != 0) {
        fprintf(stderr, "pthread_attr_setdetachstate error : %s\n", strerror(ret));
        exit(1);
    }
    // 创建分离属性的线程
    ret = pthread_create(&tid, &attr, tfunc, NULL);
    if (ret != 0) {
        fprintf(stderr, "pthread_create error : %s\n", strerror(ret));
        exit(1);
    }
    // 销毁线程属性结构体
    ret = pthread_attr_destroy(&attr); 
    if (ret != 0) {
        fprintf(stderr, "pthread_attr_destroy error : %s\n", strerror(ret));
        exit(1);
    }
    // 如果回收失败 说明确实为分离态
    ret = pthread_join(tid, NULL);
    if (ret != 0) {
        fprintf(stderr, "pthread_join error : %s\n", strerror(ret));
        exit(1);
    } 

    printf("main thread : pid = %d, tid = %lu\n", getpid(), pthread_self());
    return 0;
}