#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

typedef struct {
    int id;
    char name[256];
    int age;
} student;

int main(int argc, char** argv) {
    // write a struct student to mmap
    int fd = open("temp", O_RDWR | O_CREAT | O_TRUNC, 0664);
    if (fd == -1) {
        perror("open error");
        exit(1);
    }
    if (ftruncate(fd, sizeof(student)) == -1) {
        perror("ftruncate error");
        exit(1);
    }
    student* mem = (student*)mmap(NULL, sizeof(student), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mem == MAP_FAILED) {
        perror("mmap error");
        exit(1);
    }
    close(fd);
    sleep(5);
    student stu = {1, "Alice", 18};
    while (1) {
        // update mem every 2 secs
        memcpy(mem, &stu, sizeof(student)); // string.h
        stu.id ++;
        sleep(2);
    }
    if (munmap(mem, sizeof(student)) == -1) {
        perror("munmap error");
        exit(1);
    }
    return 0;
}