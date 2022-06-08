#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

void catch_child(int signo) {
    int wpid, wstatus;
    while ((wpid = waitpid(-1, &wstatus, WNOHANG)) > 0) {
        printf("--catch child : %d : ", wpid);
        if (WIFEXITED(wstatus)) { // 正常退出 退出代码
            printf("exit %d\n", WEXITSTATUS(wstatus));
        } else if (WIFSIGNALED(wstatus)) { // 异常终止 终止信号
            printf("cancel signal %d\n", WTERMSIG(wstatus));
        }
    }
    return;
}

int main(int argc, char** argv) {
    // 屏蔽SIGCHLD 防止未注册捕捉函数时 子进程结束
    sigset_t set, oldset, pedset;
    sigemptyset(&set);
    sigaddset(&set, SIGCHLD);
    if (sigprocmask(SIG_BLOCK, &set, &oldset) == -1) {
        perror("sigprocmask error");
        exit(1);
    }
    //
    const int n = 20;
    int i;
    pid_t pid;
    for (i = 0; i < n; ++ i) { // fork 20 child
        if ((pid = fork()) == 0) { // parent
            break;
        } else if (pid < 0) {
            perror("fork error");
            exit(1);
        }
    }
    if (i == n) { // parent
        printf("--parent process : %d\n", getpid());
        struct sigaction act, oldact;
        act.sa_handler = catch_child;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;
        if (sigaction(SIGCHLD, &act, &oldact) == -1) {
            perror("sigaction error");
            exit(1);
        }
        // 捕捉函数注册完成 解除对SIGCHLD的阻塞
        if (sigprocmask(SIG_SETMASK, &oldset, &set)) { // 恢复原来的mask
            perror("sigprocmask error");
            exit(1);
        }
        //
        while (1) { }
    } else { // child
        printf("--child process : %d\n", getpid());
        return i + 1;
    }
    return 0;
}