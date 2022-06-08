/*
@Filename : thread_create.c
@Description : 
@Datatime : 2022/06/04 14:44:38
@Author : xushun
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

void* tfunc(void* arg) {
    printf("--thread : pid = %d, tid = %lu\n", getpid(), pthread_self());
    return NULL;
}

int main(int argc, char** argv) {
    pthread_t tid;
    // create a new child thread
    int ret;
    if ((ret = pthread_create(&tid, NULL, tfunc, NULL)) != 0) {
        // perror("pthread_create error");
        printf("pthread_create error : %d\n", ret);
        exit(1);
    }
    printf("--main : pid = %d, tid = %lu\n", getpid(), pthread_self());
    // ensure childe thread complete
    sleep(5);
    return 0;
}