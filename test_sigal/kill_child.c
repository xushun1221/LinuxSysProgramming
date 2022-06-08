#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char** argv) {
    int child_index = 0;
    pid_t pid, kpid;
    for (child_index = 0; child_index < 5; ++ child_index) {
        pid = fork();
        if (pid == 0) {
            break;
        } else if(pid > 0) {
            if (child_index == 2) { // kill 3th child
                kpid = pid;
            }
        } else {
            perror("fork error");
            exit(1);
        }
    }
    if (child_index == 5) { // parent
        sleep(3);
        if (kill(kpid, SIGKILL) == -1) {
            perror("kill error");
            exit(1);
        }
        for (int i = 0; i < 5; ++ i) {
            printf("-- parent : wait %d child\n", wait(NULL));
        }
    } else {
        int sec = 0;
        while (1) {
            if (sec == 6) {
                break;
            }
            printf("-%d- %dth child : %d\n", ++ sec, child_index + 1, getpid());
            sleep(1);
        }
    }
    return 0;
}