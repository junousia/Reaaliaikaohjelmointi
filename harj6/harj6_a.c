#include "unistd.h"
#include "fcntl.h"
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int chat;
    char chatmsg;
    pid_t pid;
    int i = 0, j=0;

    for(i = 0; i < 5; i++) {
        pid = fork();
        if(pid == 0) {
            for(j = 0; j < 5; j++) {
                printf("%c\n", (char)(65 + i));
                sleep(1);
            }
            exit(i);
        }
    }
    /* wait for the child process */
    for(i = 0; i < 5; i++) {
        wait(0);
    }
    printf("all children done, exiting\n");
    return 0;
}

