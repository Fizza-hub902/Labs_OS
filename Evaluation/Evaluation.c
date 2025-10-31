#include <stdio.h>
#include <pthread.h>

int counter = 0;           // Shared global variable
pthread_mutex_t lock;      // Mutex for synchronization

// Thread function without mutex (unsafe)
void* increment_no_mutex(void* arg) {
    for (int i = 0; i < 1000; i++) {
        counter++;  // Race condition here
    }
    return NULL;
}

// Thread function with mutex (safe)
void* increment_with_mutex(void* arg) {
    for (int i = 0; i < 1000; i++) {
        pthread_mutex_lock(&lock);   // Lock before increment
        counter++;
        pthread_mutex_unlock(&lock); // Unlock after increment
    }
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;

    // ---------- Without Mutex ----------
    counter = 0;
    pthread_create(&t1, NULL, increment_no_mutex, NULL);
    pthread_create(&t2, NULL, increment_no_mutex, NULL);
    pthread_create(&t3, NULL, increment_no_mutex, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("Without mutex, counter = %d (should be 3000)\n", counter);

    // ---------- With Mutex ----------
    counter = 0;
    pthread_mutex_init(&lock, NULL); // Initialize mutex

    pthread_create(&t1, NULL, increment_with_mutex, NULL);
    pthread_create(&t2, NULL, increment_with_mutex, NULL);
    pthread_create(&t3, NULL, increment_with_mutex, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    pthread_mutex_destroy(&lock); // Destroy mutex

    printf("With mutex, counter = %d (always 3000)\n", counter);

    return 0;
}



// ---------- Without Mutex ----------
counter = 0;
pthread_t threads[3];

// Create 3 threads (without mutex)
for (int i = 0; i < 3; i++) {
    pthread_create(&threads[i], NULL, increment_no_mutex, NULL);
}

// Wait for all threads to finish
for (int i = 0; i < 3; i++) {
    pthread_join(threads[i], NULL);
}

printf("Without mutex, counter = %d (should be 3000)\n", counter);

// ---------- With Mutex ----------
counter = 0;
pthread_mutex_init(&lock, NULL); // Initialize mutex

// Create 3 threads (with mutex)
for (int i = 0; i < 3; i++) {
    pthread_create(&threads[i], NULL, increment_with_mutex, NULL);
}

// Wait for all threads to finish
for (int i = 0; i < 3; i++) {
    pthread_join(threads[i], NULL);
}

pthread_mutex_destroy(&lock); // Destroy mutex

printf("With mutex, counter = %d (always 3000)\n", counter);

