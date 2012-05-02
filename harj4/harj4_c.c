#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFSIZE 5

int main() {
    char buffer[BUFSIZ];
    int i;
    setvbuf(stdout, buffer, _IOFBF, 3);
    for(i = 0; i < 13; i++) {
        fprintf(stdout, "a");
        sleep(1);
    }
    exit(0);
}
