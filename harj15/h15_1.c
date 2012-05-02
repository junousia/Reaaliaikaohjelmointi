#include <fcntl.h>
#include <semaphore.h>
#include <stdlib.h>

int main(void) {
    int fd;
    int i;
    sem_t *semp;
    semp = sem_open("semaphore.smp", O_RDWR|O_CREAT, S_IRUSR|S_IWUSR, 1);
    if (semp == SEM_FAILED) {
        perror("sem_open :");
        exit (1);
    }

    fd = open("file.txt", O_CREAT|O_WRONLY,
            S_IRUSR|S_IWUSR);
    for(i = 0; i < 100000; i++) {
        if (sem_wait(semp) < 0) {
            perror("sem_wait");
            exit(0);
        }
        lseek(fd, 0L, SEEK_END);
        write(fd, "AAAA", 4);
        if (sem_post(semp) < 0) {
            perror("sem_wait");
            exit(0);
        }
    }
    return 0;
}
