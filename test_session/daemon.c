/*
@Filename : daemon.c
@Description : create a daemon process
@Datatime : 2022/06/04 11:35:44
@Author : xushun
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <fcntl.h>

int main(int argc, char** argv) {
    // 1. fork and shutdown parent
    if (fork() > 0) {
        exit(0);
    }
    // child begin
    // 2. new session
    if (setsid() == -1) { 
        perror("setsid error");
        exit(1);
    }
    // 3. change work dir
    if (chdir("/home/xushun/LinuxSysPrograming/test_session") == -1) {
        perror("chdir error");
        exit(1);
    }
    // 4. reset umask : default mode == 755
    umask(0022);
    // 5.close and dup fd
    close(STDIN_FILENO); // close fd-0
    if (open("/dev/null", O_RDWR) == -1) { // fd(/dec/null)-0
        perror("open error");
        exit(1);
    }
    dup2(0, STDOUT_FILENO); // dup STDOUT to 0
    dup2(0, STDERR_FILENO); // dup STDERR to 0
    // 6. service
    while (1) { }
    return 0;
}