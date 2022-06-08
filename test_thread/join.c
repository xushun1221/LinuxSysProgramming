/*
@Filename : join.c
@Description : test pthread_join
@Datatime : 2022/06/05 09:50:22
@Author : xushun
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

typedef struct {
    char name[256];
    int age;
} people;

void* tfunc(void* arg) {
    people* p = malloc(sizeof(people));
    strcpy(p -> name, "xushun");
    p -> age = 23;
    pthread_exit((void*)p);
}

int main(int argc, char** argv) {
    pthread_t tid;
    int ret;
    if ((ret = pthread_create(&tid, NULL, tfunc, NULL)) != 0) {
        printf("pthread_create error : %d\n", ret);
        exit(1);
    }
    people* retp;
    if ((ret = pthread_join(tid, (void**)&retp)) != 0) {
        printf("pthread_join error : %d\n", ret);
        exit(1);
    }
    printf("people : name = \"%s\", age = %d\n", retp -> name, retp -> age);
    pthread_exit(NULL);
}