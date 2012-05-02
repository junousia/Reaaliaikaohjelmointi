#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

pid_t pid;

void sigalrm_handler(int signo) {
    write(STDOUT_FILENO, "1", 1);
    kill(pid, SIGALRM);
    return;
}

int main (void) {
    sigset_t sigmask;
    sigfillset(&sigmask);
    sigdelset(&sigmask, SIGALRM);
    signal(SIGALRM, sigalrm_handler);
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
        //pause();
    }
    wait(0);
    return 0;
}

