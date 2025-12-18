#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5
#define ITEMS 3

int buffer[SIZE];
int in = 0, out = 0;

sem_t empty, full;
pthread_mutex_t lock;

/* Producer */
void* producer(void* arg) {
    int id = *(int*)arg;

    for(int i = 0; i < ITEMS; i++) {
        sem_wait(&empty);              // Wait for empty space
        pthread_mutex_lock(&lock);     // Lock buffer

        buffer[in] = id * 10 + i;
        printf("Producer %d produced %d\n", id, buffer[in]);
        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&lock);   // Unlock buffer
        sem_post(&full);               // Item available
        sleep(1);
    }
    return NULL;
}

/* Consumer */
void* consumer(void* arg) {
    int id = *(int*)arg;

    for(int i = 0; i < ITEMS; i++) {
        sem_wait(&full);               // Wait for item
        pthread_mutex_lock(&lock);     // Lock buffer

        printf("Consumer %d consumed %d\n", id, buffer[out]);
        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&lock);   // Unlock buffer
        sem_post(&empty);              // Space available
        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t p[2], c[2];
    int id[2] = {1, 2};

    sem_init(&empty, 0, SIZE);   // Buffer empty
    sem_init(&full, 0, 0);       // No items
    pthread_mutex_init(&lock, NULL);

    for(int i = 0; i < 2; i++) {
        pthread_create(&p[i], NULL, producer, &id[i]);
        pthread_create(&c[i], NULL, consumer, &id[i]);
    }

    for(int i = 0; i < 2; i++) {
        pthread_join(p[i], NULL);
        pthread_join(c[i], NULL);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&lock);

    return 0;
}
