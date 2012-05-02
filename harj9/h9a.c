#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>

int OpenChatFellow();

int main(void) {
    int chat = OpenChatFellow();
    char chatmsg;
    int n;

    int fd_kb, fd_line, fd_display;
    fd_set fdset;


    while(1) {
        FD_ZERO(&fdset);
        FD_SET(STDIN_FILENO, &fdset);
        FD_SET(chat, &fdset);

        n = select(chat + 1, &fdset, NULL, NULL, NULL);

        if(FD_ISSET(STDIN_FILENO, &fdset)) {
            read(STDIN_FILENO, &chatmsg, 1);
            write(STDOUT_FILENO, &chatmsg, 1);
            if(chatmsg == 'q') {
                close(chat);
                return 0;
            }
        }
        if(FD_ISSET(chat, &fdset)) {
            if(read(chat,&chatmsg,1) == 0) {
                close(chat);
                return 0;
            }
            write(STDOUT_FILENO, &chatmsg, 1);
        }
    }
    return 0;
}
