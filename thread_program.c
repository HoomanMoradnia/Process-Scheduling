#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Thread function prototypes
void* thread1_function(void* arg);
void* thread2_function(void* arg);

int main() {
    pthread_t thread1, thread2;
    int ret1, ret2;

    // Create first thread
    ret1 = pthread_create(&thread1, NULL, thread1_function, NULL);
    if (ret1 != 0) {
        perror("Thread 1 creation failed");
        exit(EXIT_FAILURE);
    }

    // Create second thread
    ret2 = pthread_create(&thread2, NULL, thread2_function, NULL);
    if (ret2 != 0) {
        perror("Thread 2 creation failed");
        exit(EXIT_FAILURE);
    }

    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Print completion message
    printf("Done Hooman - [1370]\n");

    return 0;
}

// First thread function
void* thread1_function(void* arg) {
    for (int i = 0; i < 5; i++) {
        printf("Thread Hooman %d\n", i);
        sleep(1);
    }
    return NULL;
}

// Second thread function
void* thread2_function(void* arg) {
    for (int i = 0; i < 5; i++) {
        printf("Born in 2004 %d\n", i);
        sleep(1);
    }
    return NULL;
}