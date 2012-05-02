#include "unistd.h"

int main(void) {
    while(1)
        write(STDOUT_FILENO, "2", 1);
    return 0;
}
