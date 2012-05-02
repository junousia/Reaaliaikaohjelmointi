#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

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

    while(1) {
        write(STDOUT_FILENO, "2", 1);
        kill(getppid(), SIGUSR1);
        sigsuspend(&sigmask);
    }
    return 0;
}

