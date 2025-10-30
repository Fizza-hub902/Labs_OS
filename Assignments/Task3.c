#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Function executed by each thread
void* calculate(void* arg){
    int num = *(int*)arg;   //Get the integer passed by main
    printf("Thread: Number = %d\n",num);
    printf("Thread: Square = %d\n",num * num);
    printf("Thread: Cube = %d\n",num * num * num);
    pthread_exit(NULL);
}
int main(){
    pthread_t thread;
    int num;
    printf("--------------------------------------------------\n");
    printf("Roll No: 23-NTU-CS-1157\n");
    printf("Name: Fizza Shameen\n");
    printf("--------------------------------------------------\n\n");

    //Create thread and pass the number
    if(pthread_create(&thread,NULL,calculate,&num)!=0){
        perror("Failed to create thread");
        return 1;
    }
    //Wait for thread to finish
    pthread_join(thread,NULL);
    printf("Main thread: Work completed.\n");
    return 0;
}