#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    struct stat buff;

    if(argc <= 1) {
        printf("Not enough arguments\n\nUsage: ./harj4_b <filename>\n");
        return 0;
    }

    stat(argv[1], &buff);
    if (S_ISDIR(buff.st_mode))
        printf("Is directory file\n");
    else if (S_ISREG(buff.st_mode))
        printf("Is regular file\n");
    else if (S_ISCHR(buff.st_mode))
        printf("Is character special file\n");
    else
        printf("Is something completely different\n");

    printf("%d%d%d%d\n",
        (buff.st_mode & S_IRWXU) >> 6,
        (buff.st_mode & S_IRWXG) >> 3,
        buff.st_mode  & S_IRWXO,
        buff.st_mode & S_ISUID ? 1 : 0);

    return 0;
}
