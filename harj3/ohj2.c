#include <fcntl.h>

int main(void) {
    int fd;
    int i;
    if((fd = open("file.txt", O_WRONLY)) == -1) {
        perror("open");
        exit(1);
    }
    for(i = 0; i < 100000; i++) {
        lseek(fd, 0L, SEEK_END);
        write(fd, "BBBB", 4);
    }
    return 0;
}
