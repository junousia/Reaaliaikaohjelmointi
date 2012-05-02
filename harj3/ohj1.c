#include <fcntl.h>

int main(void) {
    int fd;
    int i;
    fd = open("file.txt", O_CREAT|O_WRONLY,
            S_IRUSR|S_IWUSR);
    for(i = 0; i < 100000; i++) {
        lseek(fd, 0L, SEEK_END);
        write(fd, "AAAA", 4);
    }
    return 0;
}
