#include <stdio.h>
#include "MultiSensorSimulator.h"
#include <time.h>
#include <pthread.h>

#define NUM_OF_DESCRIPTORS 20
#define VALUES_PER_DESCRIPTOR 50

typedef struct result {
    long total_diff;
    long readings;
    long maximum;
    long minimum;
} result_t;

result_t thread_results[NUM_OF_DESCRIPTORS] = {0};
int sensorDescriptors[NUM_OF_DESCRIPTORS];

/* calculate delta for two timespecs */
long time_delta(struct timespec start, struct timespec end)
{
    long diff = end.tv_nsec - start.tv_nsec;
    if(diff < 0)
        diff += 1000000000;
    return diff;
}

void* tf(void* parm) {
    struct timespec current_time;
    long time_diff;
    Tmeas measurement;
    int index = *((int *)parm);
    while(read(sensorDescriptors[index], &measurement, sizeof(Tmeas)) != 0) {
        clock_gettime(CLOCK_REALTIME, &current_time);
        time_diff = time_delta(measurement.moment, current_time);

        /* print measurement info */
        printf("thread: %d, value: %d, latency: %d us\n", index, measurement.value, time_diff/1000);

        /* increase the amount of measurements read */
        thread_results[index].readings++;

        /* increase total diff count for counting average */
        thread_results[index].total_diff += time_diff;

        /* update maximum and minimum, if necessary */
        if(thread_results[index].minimum == 0 || time_diff < thread_results[index].minimum)
            thread_results[index].minimum = time_diff;
        if(thread_results[index].maximum == 0 || time_diff > thread_results[index].maximum)
            thread_results[index].maximum = time_diff;
    }
    pthread_exit(&thread_results[index]);
}

int main(int argc, char *argv[]) {
    pthread_t threads[NUM_OF_DESCRIPTORS];
    int id, i;
    long readings = 0, total = 0, minimum = 0, maximum = 0;
    result_t* result;

    StartSimulator(sensorDescriptors, VALUES_PER_DESCRIPTOR);

    /* create one thread for each descriptor */
    for(i = 0; i < NUM_OF_DESCRIPTORS; i++) {
        if(pthread_create(&threads[i], NULL, tf, (void *)&i)) {
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
