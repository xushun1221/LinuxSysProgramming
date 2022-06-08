#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void fetchdir(char* dirpath);
void printFile(char* path);

void fetchdir(char* dirpath) {
    DIR* dp = opendir(dirpath);
    if (dp == NULL) {
        fprintf(stderr, "fetchdir: can't open %s\n", dirpath);
        exit(1);
    }
    struct dirent* sdp;
    char subpath[257];
    while ((sdp = readdir(dp)) != NULL) {
        if (strcmp(sdp -> d_name, ".") == 0 || strcmp(sdp -> d_name, "..") == 0)
            continue; // ；处理"."".."目录 防止无限递归
        if (strlen(dirpath) + strlen(sdp -> d_name) + 2 > 256) { // 路径长度太长
            fprintf(stderr, "fetchdir: name %s %s too long\n", dirpath, sdp -> d_name);
        } else {
            sprintf(subpath, "%s/%s", dirpath, sdp -> d_name); // 拼接路径
            printFile(subpath); // 递归
        }
    }
    closedir(dp);
}

void printFile(char* path) {
    struct stat sbuf;
    if (lstat(path, &sbuf) == -1) {
        fprintf(stderr, "isFile: can't access %s\n", path);
        exit(1);
    }
    if ((sbuf.st_mode & S_IFMT) == S_IFDIR) { // 如果是目录 就展开
        fetchdir(path);
    } else { // 普通文件 直接打印 文件大小 和 路径
        printf("%8ld %s\n", sbuf.st_size, path);
    }
}

int main(int argc, char* argv[]) {
    if (argc == 1) { // 没有命令行参数默认当前目录
        printFile(".");
    } else {
        while (-- argc > 0) { // 处理多个命令行参数
            printFile(*++ argv);
        }
    }
    return 0;
}