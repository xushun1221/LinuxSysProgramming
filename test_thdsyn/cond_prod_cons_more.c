/*
@Filename : cond_prod_cons_more.c
@Description : test producer-consumer model (more consumers)
@Datatime : 2022/06/07 11:38:22
@Author : xushun
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

// 共享数据 链表形式
struct msg{
    int num;
    struct msg* next;
};
// 初始链表中没有节点
struct msg* head;

// 静态初始化条件变量和互斥锁
pthread_cond_t cond = PTHREAD_COND_INITIALIZER; // 链表中是否新增数据了
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void err_pthread(int ret, char* str) {
    if (ret != 0) {
        fprintf(stderr, "%s : %s\n", str, strerror(ret));
        pthread_exit(NULL);
    }
}

void* procuder_pthread(void* arg) {
    while (1) {
        // 生产一个节点
        struct msg* m = malloc(sizeof(struct msg));
        m -> num = rand() % 1000 + 1;
        printf("++producer : %d\n", m -> num);
        // 将生产的节点放入共享链表
        int ret = pthread_mutex_lock(&mutex); // 尝试加锁
        err_pthread(ret, "pthread_mutex_lock error");
        m -> next = head; // 新节点头插 放入链表
        head = m;
        ret = pthread_mutex_unlock(&mutex); // 解锁
        err_pthread(ret, "pthread_mutex_unlock error");
        // 通知阻塞的消费者 有新的节点
        ret = pthread_cond_signal(&cond);
        err_pthread(ret, "pthread_cond_signal error");
        sleep(rand() % 3); // 放弃CPU
    }
    return NULL;
}

void* consumer_pthread(void* arg) {
    while (1) {
        struct msg* m;
        int ret = pthread_mutex_lock(&mutex); // 尝试加锁
        err_pthread(ret, "pthread_mutex_lock error");
        // *******************************************
        while (head == NULL) { // 拿到锁 但是没有数据 就阻塞等待条件变量通知 解锁 条件变量满足时再次尝试加锁
            ret = pthread_cond_wait(&cond, &mutex);
            err_pthread(ret, "pthread_cond_wait error");
            // 当线程结束等待并获得锁时
            // 有可能共享内容被消费完了
            // 不能退出循环进行消费 需要重新等待生产者的通知
        }
        // ********************************************
        // 跳出循环 1. 链表中有数据 2. 无数据 wait阻塞 条件变量满足通知 重新竞争到锁
        // 进行消费
        m = head; // 把链表的第一个节点取下
        head = m -> next;
        ret = pthread_mutex_unlock(&mutex); // 消费完共享数据 解锁
        err_pthread(ret, "pthread_mutex_unlock error");
        printf("--consumer(%lu) : %d\n", pthread_self(), m -> num); // 打印获得的节点
        free(m); // 释放内存
        sleep(rand() % 3); // 放弃CPU
    }
    return NULL;
}

int main(int argc, char** argv) {
    int ret;
    srand(time(NULL));
    pthread_t prod_tid, cons_tids[5];
    // 创建线程 生产者-消费者
    ret = pthread_create(&prod_tid, NULL, procuder_pthread, NULL);
    err_pthread(ret, "pthread_create error");
    for (int i = 0; i < 5; ++ i) {
        ret = pthread_create(cons_tids + i, NULL, consumer_pthread, NULL);
        err_pthread(ret, "pthread_create error");
    }
    // 回收线程
    ret = pthread_join(prod_tid, NULL);
    err_pthread(ret, "pthread_join error");
    for (int i = 0; i < 5; ++ i) {
        ret = pthread_join(cons_tids[i], NULL);
        err_pthread(ret, "pthread_join error");
    }
    return 0;
}