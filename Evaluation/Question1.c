#include <stdio.h>
#include <pthread.h>

int counter = 0;           //Shared global variable
pthread_mutex_t lock;     //Mutex for Synchronization

//Thread function without Mutex
void* increment_without_mutex(void* arg){
    for(int i = 0; i < 1000; i++){
        counter++;                 //Race condition
    }
    return NULL;
}

//Thread function with mutex
void* increment_with_mutex(void* arg){
    for(int i = 0; i < 1000; i++){
        pthread_mutex_lock(&lock);      //Lock before increment
        counter++;
        pthread_mutex_unlock(&lock)     //Unlock after increment
    }
    return NULL;
}

//Main function
int main(){
    
}
