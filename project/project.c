#include <stdio.h>
#include "MultiSensorSimulator.h"
#include <time.h>
#include <sys/select.h>

#define NUM_OF_DESCRIPTORS 20
#define VALUES_PER_DESCRIPTOR 5

/* calculate delta for two timespecs */
long time_delta(struct timespec start, struct timespec end)
{

    long diff = end.tv_nsec - start.tv_nsec;
    if(diff < 0)
        diff += 1000000000;
    return diff;
}

int main(int argc, char *argv[]) {
    int sensorDescriptors[NUM_OF_DESCRIPTORS];
    Tmeas measurement;
    struct timespec current_time;
    int i, j, descriptors_returned, closed = 0, readings = 0;
    long time_diff = 0, total = 0, minimum = 0, maximum = 0;
    fd_set fdset;

    StartSimulator(sensorDescriptors, VALUES_PER_DESCRIPTOR);

    FD_ZERO(&fdset);

    while(closed <= NUM_OF_DESCRIPTORS) {
        for(i = 0; i < NUM_OF_DESCRIPTORS; i++) {
            FD_SET(sensorDescriptors[i], &fdset);
        }
        descriptors_returned = select(sensorDescriptors[NUM_OF_DESCRIPTORS - 1] + 1, &fdset, NULL, NULL, NULL);

        if(descriptors_returned) {
            for(j = 0; j < NUM_OF_DESCRIPTORS; j++) {
                if(FD_ISSET(sensorDescriptors[j], &fdset)) {
                    if(read(sensorDescriptors[j], &measurement, sizeof(Tmeas)) <= 0) {
                        close(sensorDescriptors[j]);
                        printf("   * descriptor %d closed\n", j);
                        closed++;
                    }
                    else {
                        clock_gettime(CLOCK_REALTIME, &current_time);
                        time_diff = time_delta(measurement.moment, current_time);
                        printf("value: %d ", measurement.value);
                        printf("timediff: %d ns\n", time_diff);
                        readings++;

                        /* increase total diff count for counting average */
                        total += time_diff;

                        /* update maximum and minimum, if necessary */
                        if(minimum == 0 || time_diff < minimum)
                            minimum = time_diff;
                        if(maximum == 0 || time_diff > maximum)
                            maximum = time_diff;
                    }
                }
            }
        }
    }
    printf("all measurements done, number of readings: %d\n  average: %d\n  minimum: %d\n  maximum: %d\n", readings, total / (VALUES_PER_DESCRIPTOR*NUM_OF_DESCRIPTORS), minimum, maximum);
}
