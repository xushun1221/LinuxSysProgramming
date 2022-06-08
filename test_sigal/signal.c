#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void catch(int signo) {
    printf("catch sig : %d\n", signo);
    return;
}

int main(int argc, char** argv) {
    if (signal(SIGTSTP, catch) == SIG_ERR) { // 捕捉20)SIGTSTP Ctrl+z
        perror("signal error");
        exit(1);
    }
    while (1) { }
    return 0;
}