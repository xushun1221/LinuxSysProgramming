#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>

int global_int = 100;

int main(int argc, char** argv) {
    int fd = open("temp", O_CREAT | O_TRUNC | O_RDWR, 0664);
    if (fd == -1) {
        perror("open error");
        exit(1);
    }
    if (ftruncate(fd, sizeof(int)) == -1) {
        perror("ftruncate error");
        exit(1);
    }
    int* shared_int = (int*)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    // int* shared_int = (int*)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (shared_int == MAP_FAILED) {
        perror("mmap error");
        exit(1);
    }
    close(fd);
    
    pid_t pid = fork();
    if (pid > 0) {
        sleep(2); // 等待子进程修改变量
        // 读共享内存
        printf("parent process : global_int = %d, shared_int = %d\n", global_int, *shared_int);
        wait(NULL);
        if (unlink("temp") == -1) {
            perror("unlink error");
            exit(1);
        }
    } else if (pid == 0) {
        *shared_int = 666; // 写共享内存
        global_int = 777;
        printf(" child process : global_int = %d, shared_int = %d\n", global_int, *shared_int);
    } else {
        perror("fork error");
        exit(1);
    }
    if (munmap(shared_int, sizeof(int)) == -1) {
        perror("munmap error");
        exit(1);
    }
    return 0;
}