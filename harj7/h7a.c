#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

#define NUM_OF_CHILDREN 2
#define NUM_OF_REPEATS 5

int main (void) {
    pid_t pid;
    int fd;
    int i;
    char buf[20];
    if((fd = open("file.txt", O_CREAT|O_RDWR|O_APPEND)) == -1) {
        perror("open");
        exit(1);
    }
    for(i = 0; i < NUM_OF_CHILDREN; i++) {
        printf("fork #%d\n",i);
        pid = fork();
        if (pid < 0) {
            perror("Fork:");
            exit(1);
        }
        if (pid == 0) {
            char buf[5];
            sprintf(buf,"%d",fd);
            char buf2[5];
            sprintf(buf2,"%d",NUM_OF_REPEATS);
            printf("exec #%d\n",i);
            execl("./app", "app", &buf, i==0?"aaaaa\n":"bbbbb\n", &buf2, (char*) 0);
            exit(0);
        }
    }
    printf("forked\n");
    for(i=0; i<NUM_OF_CHILDREN; i++) {
        wait(0);
        printf("child exited\n");
    }
    return 0;
}
