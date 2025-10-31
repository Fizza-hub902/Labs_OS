#include <stdio.h>
#include <pthread.h>

#define num_threads 3
#define increments 1000

int counter = 0; // Shared global variable
pthread_mutex_t lock; // Mutex lock for synchronization

// Thread function WITHOUT mutex
void* increment_without_mutex(void* arg) {
    for (int i = 0; i < increments; i++) {
        counter++; // Race condition happens here!
    }
    return NULL;
}

// Thread function WITH mutex
void* increment_with_mutex(void* arg) {
    for (int i = 0; i < increments; i++) {
        pthread_mutex_lock(&lock);   // Lock before updating shared data
        counter++;
        pthread_mutex_unlock(&lock); // Unlock after update
    }
    return NULL;
}

int main() {
    pthread_t threads[num_threads];

    printf("===== Part 1: Without Mutex =====\n");
    counter = 0; // Reset counter

    // Create 3 threads (no mutex protection)
    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, increment_without_mutex, NULL);
    }

    // Wait for all threads to finish
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final counter value (without mutex): %d\n\n", counter);

    // ------------------------------------------------------

    printf("===== Part 2: With Mutex =====\n");
    counter = 0; // Reset counter
    pthread_mutex_init(&lock, NULL); // Initialize mutex

    // Create 3 threads (with mutex protection)
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_with_mutex, NULL);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock); // Destroy mutex

    // Always 3000 because of proper synchronization
    printf("Final counter value (with mutex): %d\n", counter);

    return 0;
}
