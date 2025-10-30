#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Function executed by each thread
void *greet(void* arg){
    char* name = (char*) arg; //Get name passed as argument
    printf("Thread says : Hello, %s! Welcome to the world of threads.\n",name);
    pthread_exit(NULL);
}
int main(){
    pthread_t thread;
    char* name = "Fizza Shameen"; //Name passed to thread
    printf("--------------------------------------------------\n");
    printf("Roll No: 23-NTU-CS-1157\n");
    printf("Name: Fizza Shameen\n");
    printf("--------------------------------------------------\n\n");

    // Create thread
    if(pthread_create(&thread,NULL,greet,name)!=0){
        perror("Failed to create thread.");
        return 1;
    }
    printf("Main thread:Waiting for greeting...\n");

    //Wait for the greeting thread to finish
    pthread_join(thread,NULL);
    printf("Main thread: Greeting completed!\n");
    return 0;
}