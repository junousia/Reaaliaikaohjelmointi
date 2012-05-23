#include <stdio.h>
#include "MultiSensorSimulator.h"
#include <time.h>
#include <sys/select.h>

#define NUM_OF_DESCRIPTORS 20
#define VALUES_PER_DESCRIPTOR 5

int main(int argc, char *argv[]) {
    int sensorDescriptors[NUM_OF_DESCRIPTORS];
    Tmeas measurement;

    int fd_kb, fd_line, fd_display, i, n;
    fd_set fdset;

    StartSimulator(sensorDescriptors, VALUES_PER_DESCRIPTOR);

    while(1) {
        FD_ZERO(&fdset);
        for(i = 0; i < NUM_OF_DESCRIPTORS; i++) {
            FD_SET(sensorDescriptors[i], &fdset);
        }

        n = select(sensorDescriptors[NUM_OF_DESCRIPTORS - 1] + 1, &fdset, NULL, NULL, NULL);

        if(FD_ISSET(sensorDescriptors[0], &fdset)) {
            read(sensorDescriptors[0], &measurement, sizeof(Tmeas));
        }
    }
}
