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
    // read a struct student from mmap
    int fd = open("temp", O_RDONLY, 0664);
    if (fd == -1) {
        perror("open error");
        exit(1);
    }
    student* mem = (student*)mmap(NULL, sizeof(student), PROT_READ, MAP_SHARED, fd, 0);
    if (mem == MAP_FAILED) {
        perror("mmap error");
        exit(1);
    }
    close(fd);

    while (1) {
        // read mem every sec
        printf("id = %d, name = %s, age = %d\n", mem -> id, mem -> name, mem -> age);
        sleep(1);
    }
    if (munmap(mem, sizeof(student)) == -1) {
        perror("munmap error");
        exit(1);
    }
    return 0;
}