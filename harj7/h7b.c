#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>

#define NUM_OF_CHILDREN 2
#define NUM_OF_REPEATS 4 

static void sig_handler(int sig_no) {
    printf("signal from child\n");
    wait(0);
}

int main (void) {
    pid_t pid;
    int fd;
    int i;
    char buf[20];
    char tmp;
    sigset_t mask; int signo;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    if(signal(SIGUSR1, sig_handler) == SIG_ERR) {
        fprintf(stderr, "Cannot set signal handler\n");
        exit(0);
    }

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
            execl("./appb", "appb", &buf, i==0?"aaaaa\n":"bbbbb\n", &buf2, (char*) 0);
            exit(0);
        }
    }
    printf("all forks done\n");

    for(i = 0; i < NUM_OF_CHILDREN; i++) {
        sigwait(&mask, &signo);
        printf("signal %d received\n",signo);
    }

    /* go to the beginning of the file and dump the content to stdout */
    lseek(fd, 0L, SEEK_SET);
    while(read(fd,&tmp,1) == 1) {
        write(STDOUT_FILENO, &tmp, 1);
        i++;
    }

    return 0;
}
