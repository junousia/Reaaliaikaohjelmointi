#include "unistd.h"
#include "fcntl.h"
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int OpenChatFellow();

int main(void) {
    int chat;
    char chatmsg;
    pid_t pid;
    int file;
    int i = 0;
    int child_status;

    if(!(file = open("file.txt", O_CREAT|O_RDWR|O_APPEND))) {
        exit(-1);
    }

    pid = fork();
    if(pid == 0) {
        chat = OpenChatFellow();
        while(read(chat,&chatmsg,1) == 1) {
            write(STDOUT_FILENO, &chatmsg, 1);
            write(file, &chatmsg, 1);
            i++;
        }
        close(chat);
        exit(i);
    }
    else {
        while(read(STDIN_FILENO, &chatmsg, 1) == 1) {
            write(STDOUT_FILENO, &chatmsg, 1);
            if(chatmsg == 'q') {
                break;
            }
        }

        /* wait for the child process */
        wait(&child_status);
        printf("number of characters written by child process: %d\n", WEXITSTATUS(child_status));
        printf("dumping file contents...\n");
        /* go to the beginning of the file and dump the content to stdout */
        lseek(file, 0L, SEEK_SET);
        while(read(file,&chatmsg,1) == 1) {
            write(STDOUT_FILENO, &chatmsg, 1);
            if(i%7 == 6) {
                write(STDOUT_FILENO, "\n", 1);
            }
            i++;
        }
        printf("\ndone\n");
    }


    close(file);
    return 0;
}
