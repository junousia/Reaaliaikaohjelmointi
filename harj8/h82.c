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

    pid = fork();
    if (pid < 0) {
        perror("Fork:");
        exit(1);
    }
    if (pid == 0) {
        alarm(5);
        execl("./h8bexec", "h8bexec", NULL);
        exit(0);
    }
    wait(0);
    printf("child exited\n");
    return 0;
}
