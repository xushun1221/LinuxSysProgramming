/*
@Filename : testcancel.c
@Description : test pthread_testcancel
@Datatime : 2022/06/05 11:42:40
@Author : xushun
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

void* tfunc_1(void* arg) {
    printf("thread 1 : returning\n");
    return (void*)1;
}

void* tfunc_2(void* arg) {
    printf("thread 2 : returning\n");
    pthread_exit((void*)2);
}

void* tfunc_3(void* arg) {
    while (1) {
        //printf("thread 3 : going to die in 5 secs ...\n");
        //sleep(1);
        pthread_testcancel();
    }
    return (void*)3;
}

int main(int argc, char** argv) {
    int ret;
    pthread_t tid;
    void* tret = NULL;
    // thread 1
    pthread_create(&tid, NULL, tfunc_1, NULL);
    pthread_join(tid, &tret);
    printf("thread 1 exit code = %d\n", (int)tret);
    // thread 2
    pthread_create(&tid, NULL, tfunc_2, NULL);
    pthread_join(tid, &tret);
    printf("thread 2 exit code = %d\n", (int)tret);
    // thread 3
    pthread_create(&tid, NULL, tfunc_3, NULL);
    sleep(5);
    pthread_cancel(tid);
    pthread_join(tid, &tret);
    printf("thread 3 exit code = %d\n", (int)tret);
    return 0;
}