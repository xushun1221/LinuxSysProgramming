#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char* argv[]) {
    DIR* dp = opendir(argv[1]);
    if (dp == NULL) {
        perror("opendir error");
        exit(1);
    }

    struct dirent* sdp;
    while ((sdp = readdir(dp)) != NULL) {
        printf("%s\n", sdp-> d_name);
    }

    closedir(dp);
    return 0;
}