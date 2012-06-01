#include <stdio.h>
#include "MultiSensorSimulator.h"
#include <time.h>
#include <pthread.h>

#define NUM_OF_DESCRIPTORS 20
#define VALUES_PER_DESCRIPTOR 5

typedef struct result {
    int  id;
    int  descriptor;
    long total_diff;
    long readings;
    long maximum;
    long minimum;
} result_t;

result_t thread_results[NUM_OF_DESCRIPTORS] = {0};

/* calculate delta for two timespecs */
long time_delta(struct timespec start, struct timespec end)
{
    long diff = end.tv_nsec - start.tv_nsec;

    if(diff < 0)
        diff += 1000000000;

    diff += (end.tv_sec - start.tv_sec) * 1000000000;

    return diff;
}

void* tf(void* parm) {
    struct timespec current_time;
    long time_diff;
    Tmeas measurement;
    result_t* result = ((result_t *)parm);

    while(read(result->descriptor, &measurement, sizeof(Tmeas)) != 0) {
        clock_gettime(CLOCK_REALTIME, &current_time);
        time_diff = time_delta(measurement.moment, current_time);

        /* print measurement info */
        printf("thread %d, value: %d, latency: %d us\n", result->id, measurement.value, time_diff/1000);

        /* increase the amount of measurements read */
        result->readings++;

        /* increase total diff count for counting average */
        result->total_diff += time_diff;

        /* update maximum and minimum, if necessary */
        if(result->minimum == 0 || time_diff < result->minimum)
            result->minimum = time_diff;
        if(result->maximum == 0 || time_diff > result->maximum)
            result->maximum = time_diff;
    }

    pthread_exit(result);
}

int main(int argc, char *argv[]) {
    pthread_t threads[NUM_OF_DESCRIPTORS];
    int id, i;
    long readings = 0, total = 0, minimum = 0, maximum = 0;
    result_t* result;
    int sensorDescriptors[NUM_OF_DESCRIPTORS];

    StartSimulator(sensorDescriptors, VALUES_PER_DESCRIPTOR);

    /* create one thread for each descriptor */
    for(i = 0; i < NUM_OF_DESCRIPTORS; i++) {
        thread_results[i].descriptor = sensorDescriptors[i];
        thread_results[i].id = i;
        if(pthread_create(&threads[i], NULL, tf, (void *)&thread_results[i])) {
            perror("pthread_create");
            break;
        }
    }

    for(i = 0; i < NUM_OF_DESCRIPTORS; i++) {
        pthread_join(threads[i], (void**)&result);

        /* increment total counts */
        readings += result->readings;
        total += result->total_diff;

        /* update maximum and minimum, if necessary */
        if(minimum == 0 || result->minimum < minimum)
            minimum = result->minimum;
        if(maximum == 0 || result->maximum > maximum)
            maximum = result->maximum;
    }
    printf("\nDone.\n");
    printf("\n******* Statistics *******\n  number of readings %d\n  average latency %d microseconds\n  maximum latency %d microseconds\n  minimum latency %d microseconds\n**************************\n", readings, total/(NUM_OF_DESCRIPTORS*VALUES_PER_DESCRIPTOR)/1000, maximum/1000, minimum/1000);
}
