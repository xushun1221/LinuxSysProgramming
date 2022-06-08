#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

int main(int argc, char** argv) {
    int fd = open("test.txt", O_CREAT | O_TRUNC | O_RDWR, 0664);
    if (fd == -1) {
        perror("open error");
        exit(1);
    }
    lseek(fd, 99, SEEK_END);
    if (write(fd, "\0", 1) == -1) { // 扩展文件
        perror("write error");
        exit(1);
    }
    int len = lseek(fd, 0, SEEK_END); // 文件长度
    void* p = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); // 创建映射区
    if (p == MAP_FAILED) {
        perror("mmap error");
        exit(1);
    }
    // 对内存中的映射区进行读写
    strcpy(p, "hello mmap\n");
    printf("read from mmap : %s", p);

    if (munmap(p, len) == -1) {
        perror("munmap error");
        exit(1);
    }
    close(fd);
    return 0;
}