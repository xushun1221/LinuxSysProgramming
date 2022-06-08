/*
@Filename : hello.c
@Description : 
@Datatime : 2022/06/06 12:48:00
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
        printf("hello ");
        sleep(rand() % 3);
        printf("world\n");
        sleep(rand() % 3);
    }
    pthread_exit(NULL);
}

int main(int argc, char** argv) {
    int ret;
    pthread_t tid;
    srand(time(NULL));
    ret = pthread_create(&tid, NULL, tfunc, NULL);
    if (ret != 0) {
        fprintf(stderr, "pthread_create error : %s\n", strerror(ret));
        exit(1);
    }
    while (1) {
        printf("HELLO ");
        sleep(rand() % 3);
        printf("WORLD\n");
        sleep(rand() % 3);
    }
    ret = pthread_join(tid, NULL);
    if (ret != 0) {
        fprintf(stderr, "pthread_join error : %s\n", strerror(ret));
        exit(1);
    }
    return 0;
}