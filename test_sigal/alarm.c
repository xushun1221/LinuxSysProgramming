#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    alarm(5);
    int sec = 0;
    while (1) {
        printf("sec : %d\n", ++ sec);
        sleep(1);
        if (sec == 3) {
            alarm(10);
            sec = 10;
        }
    }
    return 0;
}