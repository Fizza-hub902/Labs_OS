#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int counter = 0;           //Shared global variable
pthread_mutex_t lock;      //Mutex for synchronization

//Increment function without mutex
void* increment_without_mutex(void* arg){
    for(int i = 0; i < 1000;i++){
        counter++;
        usleep(1000);               //Race condition
    }
    return NULL;
}

//Increment function with mutex
void* increment_with_mutex(void* arg){
    for(int i = 0; i < 1000; i++){
        pthread_mutex_lock(&lock);       //Lock before increment
        counter++;
        pthread_mutex_unlock(&lock);     //Unlock after increment
        usleep(1000);
    }
    return NULL;
}

int main(){
    pthread_t threads[3];
    counter = 0;

    printf("23-NTU-CS-1157\n");
    printf("\nFizza Shameen\n");

    //Create threads without mutex
    for(int i = 0; i < 3; i++){
        pthread_create(&threads[i],NULL,increment_without_mutex,NULL);
    }

    //Wait for all the threads to finish
    for(int i = 0; i < 3;i++){
        pthread_join(threads[i],NULL);
    }
    printf("\nWithout mutex, counter = %d (should always be 3000)\n",counter);

    //--------With mutex-------//
    counter = 0;
    pthread_mutex_init(&lock,NULL);

    //Create threads with mutex
    for(int i = 0; i < 3; i++){
        pthread_create(&threads[i],NULL,increment_with_mutex,NULL);
    }
    //Wait for threads to finish
    for(int i = 0; i < 3; i++){
        pthread_join(threads[i],NULL);
    }
    pthread_mutex_destroy(&lock);             //Destroy mutex
    printf("With mutex, counter = %d (should always be 3000)\n",counter);
}