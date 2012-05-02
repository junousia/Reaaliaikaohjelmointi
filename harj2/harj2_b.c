#include "unistd.h"
#include "fcntl.h"

int OpenChatFellow();

int main(void) {
    int chat = OpenChatFellow();
    char chatmsg;
    int file_flags;

    /* stdin to nonblocking */
    file_flags = fcntl(STDIN_FILENO, F_GETFL);
    file_flags = file_flags | O_NONBLOCK;
    fcntl(STDIN_FILENO, F_SETFL, file_flags);
    /* chat to nonblocking */
    file_flags = fcntl(chat, F_GETFL);
    file_flags = file_flags | O_NONBLOCK;
    fcntl(chat, F_SETFL, file_flags);

    while(1) {
       if(read(chat,&chatmsg,1) == 1) {
           write(STDOUT_FILENO, &chatmsg, 1);
       }
       if(read(STDIN_FILENO, &chatmsg, 1) == 1) {
           write(STDOUT_FILENO, &chatmsg, 1);
           if(chatmsg == 'q') {
               close(chat);
               return 0;
           }
       }
    }
    return 0;
}
