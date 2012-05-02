#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

pid_t pid;

void sighandler(int signo) {
    return;
}

int main (void) {
    sigset_t sigmask;
    sigset_t procmask;
    sigaddset(&procmask, SIGUSR1);
    sigprocmask(SIG_BLOCK, &procmask, NULL);
    sigfillset(&sigmask);
    sigdelset(&sigmask, SIGUSR1);
    signal(SIGUSR1, sighandler);

    pid = fork();
    if (pid < 0) {
        perror("Fork:");
        exit(1);
    }
    if (pid == 0) {
        execl("./h8b2", "h8b2", NULL);
        exit(0);
    }
    while(1) {
        sigsuspend(&sigmask);
        write(STDOUT_FILENO, "1", 1);
        kill(pid, SIGUSR1);
    }
    wait(0);
    return 0;
}

