/*
@Filename : test.c
@Description : 
@Datatime : 2022/06/04 16:29:49
@Author : xushun
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

int main(int argc, char** argv) {
    if (1 == 1) {
        perror("xx error");
        exit(1);
    }
    
    return 0;
}