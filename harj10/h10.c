#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>

void sig_handler(int sig_no) {
    return;
}

int main (void) {
    pid_t pid;
    char chr;
    int fd_arr[2], i = 0;

    pipe(fd_arr);

    pid = fork();
    if (pid < 0) {
        perror("Fork:");
        exit(1);
    }
    if (pid == 0) {
        close (fd_arr[0]);
        signal(SIGPIPE, sig_handler);
        while(1) {
            sprintf(&chr, "%d", i++);
            if(write(fd_arr[1], &chr, 1) == -1) {
                perror("Writing to pipe");
                exit(1);
            }
            sleep(1);
        }
        close(fd_arr[1]);
        exit(0);
    }
    close(fd_arr[1]);
    for(i=0; i<10; i++) {
        if(read(fd_arr[0], &chr, 1) != 0)
            write(STDOUT_FILENO, &chr, 1);
        else
            exit(1);
    }
    close(fd_arr[0]);
    wait(0);
    return 0;
}
