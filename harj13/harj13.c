#include <stdio.h>
#include <pthread.h>

#define NUM_OF_THREADS 20

int global_variable = 0;

void* tf(void* parm) {
    int i;
    for(i = 0; i < 100000; i++) {
        // atomic increment, built in to gcc
        __sync_fetch_and_add(&global_variable, 1);
        *(int *)parm += 1;
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t threads[NUM_OF_THREADS];
    int arr[NUM_OF_THREADS] = {0}, i;
    
    /* create one thread for each descriptor */
    for(i = 0; i < NUM_OF_THREADS; i++) {
        if(pthread_create(&threads[i], NULL, tf, (void *)&arr[i])) {
            perror("pthread_create");
            break;
        }
    }

    for(i = 0; i < NUM_OF_THREADS; i++) {
        pthread_join(threads[i], NULL);
        printf("thread %d counter: %d\n", i, arr[i]);
    }
    printf("global counter: %d\n", global_variable);
}
