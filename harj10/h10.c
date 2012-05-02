#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

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
        for(i=0; i<10; i++) {
            sprintf(&chr, "%d", i);
            write(fd_arr[1], &chr, 1);
            sleep(1);
        }
        close(fd_arr[1]);
        exit(0);
    }
    close(fd_arr[1]);
    while(read(fd_arr[0], &chr, 1) != 0)
        write(STDOUT_FILENO, &chr, 1);
    wait(0);
    return 0;
}
