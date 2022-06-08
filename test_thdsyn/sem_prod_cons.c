/*
@Filename : sem_prod_cons.c
@Description : test semaphore
@Datatime : 2022/06/07 15:06:24
@Author : xushun
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

// 错误输出就不写了^^

#define NUM 5
// 存放产品的循环队列
int queue[NUM];
// 空格子信号量  产品数信号量
sem_t blank_num, product_num;

void* producer(void* arg) {
    int i = 0;
    while (1) {
        sem_wait(&blank_num); // --空格子数
        queue[i] = rand() % 1000 + 1; // 生产一个产品
        printf("++produce : %d\n", queue[i]);
        sem_post(&product_num); // ++ 产品数
        i = (i + 1) % NUM; // 循环队列
        sleep(rand() % 1); // CPU让给消费者
    }
    pthread_exit(NULL);
}

void* consumer(void* arg) {
    int i = 0;
    while (1) {
        sem_wait(&product_num); // -- 产品数
        printf("--consumer : %d\n", queue[i]); // 消费一个商品
        queue[i] = 0;
        sem_post(&blank_num); // ++ 格子数
        i = (i + 1) % NUM;
        sleep(rand() % 3); // 让出CPU
    }
    pthread_exit(NULL);
}

int main(int argc, char** argv) {
    pthread_t prod_tid, cons_tid;
    sem_init(&blank_num, 0, NUM); // 初始空格子5个
    sem_init(&product_num, 0, 0); // 初始产品0个
    pthread_create(&prod_tid, NULL, producer, NULL);
    pthread_create(&cons_tid, NULL, consumer, NULL);
    pthread_join(prod_tid, NULL);
    pthread_join(cons_tid, NULL);
    sem_destroy(&blank_num);
    sem_destroy(&product_num);
    return 0;
}