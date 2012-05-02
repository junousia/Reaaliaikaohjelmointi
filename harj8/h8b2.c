#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void sigalrm_handler(int signo) {
    write(STDOUT_FILENO, "2", 1);
    kill(getppid(), SIGALRM);
    return;
}

int main (void) {
    sigset_t sigmask;
    sigfillset(&sigmask);
    sigdelset(&sigmask, SIGALRM);
    signal(SIGALRM, sigalrm_handler);

    sleep(2);
    kill(getppid(), SIGALRM);

    while(1) {
        sigsuspend(&sigmask);
        //pause();
    }
    return 0;
}

