#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// This is the shared variable
int shared_data = 0;

// This is to protect the shared variable
pthread_mutex_t lock;

void* thread_1(void* arg) {
    // This is to lock mutex before modifying the shared variable
    pthread_mutex_lock(&lock);

    shared_data = 42;  // This is to write the data into shared variable
    printf("Thread 1: Data written to shared data = %d\n", shared_data);

    // This is to unlock mutex after modifying shared variable
    pthread_mutex_unlock(&lock);

    return NULL;
}

void* thread_2(void* arg) {
    // This is to lock mutex before reading the shared variable
    pthread_mutex_lock(&lock);

    printf("Thread 2: Data read from shared data = %d\n", shared_data);

    // This is to unlock mutex after reading the shared variable
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {
    pthread_t t1, t2;

    // This is to initialize mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex initialization failed\n");
        return 1;
    }

    // This is to create threads
    pthread_create(&t1, NULL, thread_1, NULL);
    pthread_create(&t2, NULL, thread_2, NULL);

    // This is to wait for the threads to be done
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // This is to destroy the mutex
    pthread_mutex_destroy(&lock);

    return 0;
}
