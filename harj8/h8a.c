#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void alrm_handler(int sig_no) {
    printf("signal %d received\n", sig_no);
    return;
}

int main (void) {
    pid_t pid;
    int fd;

    signal(SIGALRM, alrm_handler);
    alarm(5);
    pid = fork();
    if (pid < 0) {
        perror("Fork:");
        exit(1);
    }
    if (pid == 0) {
        printf("child waiting for alarm\n");
        pause();
        exit(0);
    }
    printf("parent waiting for alarm\n");
    pause();
    printf("waiting for child\n");
    wait(0);
    printf("child exited\n");
    return 0;
}
