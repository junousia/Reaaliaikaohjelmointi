#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>

void usage()
{
    printf("usage: app FILE_DESCRIPTOR STRING_TO_WRITE NUM_OF_REPEATS\n");
}

int main(int argc, char *argv[])
{
    int i;

    if(argc <= 3) {
        usage();
    }

    for(i = 0; i<atoi(argv[3]); i++) {
        write(atoi(argv[1]), argv[2], strlen(argv[2]));
        sleep(1);
    }
    kill(getppid(), SIGUSR1);
    exit(0);
}

