#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

int main() {
    int fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0664);
    if (fd == -1) {
        perror("open test.txt error");
        exit(1);
    }
    int ret;
    // // ******1*******
    ret = unlink("test.txt");
    if (ret == -1) {
        perror("unlink error");
        exit(1);
    }
    ret = write(fd, "test of unlink\n", strlen("test of unlink\n"));
    if (ret == -1) {
        perror("write error");
        exit(1);
    }
    printf("write success\n");
    ret = write(fd, "after write something\n", strlen("after write something\n"));
    if (ret == -1) {
        perror("write error");
        exit(1);
    }
    printf("enter anykey continue\n");
    getchar();
    close(fd);
    // // ******2*******
    // ret = unlink("test.txt");
    // if (ret == -1) {
    //     perror("unlink error");
    //     exit(1);
    // }
    return 0;
}