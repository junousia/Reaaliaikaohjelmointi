#include "unistd.h"

int main(void) {
    while(1)
        write(STDOUT_FILENO, "1", 1);
    return 0;
}
