#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define THREAD_NUM 2

sem_t semEmpty;
sem_t semFull;

pthread_mutex_t mutexBuffer;

int buffer[10]; //creating buffer size
int count = 0; //start count from 0

void* producer(void* args){
    while(1){
    //produce
    int x = rand() % 100; //gen rand num to be put in buffer
    //sleep(1);

    //add to buffer 
    sem_wait(&semEmpty); //see if buffer has room to produce
    pthread_mutex_lock(&mutexBuffer); //lock while modifying
    buffer[count] = x;
    count++; 
    pthread_mutex_unlock(&mutexBuffer); //unlock when done modifying the buffer
    sem_post(&semFull);
    }
}

void* consumer(void* args){
    while(1){
        int y;

        // remove from the buffer
        sem_wait(&semFull); //need to wait until something in buffer
        pthread_mutex_lock(&mutexBuffer);
         y = buffer[count - 1];
        count--;
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semEmpty);

        //consume
        printf("got %d\n", y);
        sleep(1);
    }

}

int main(int argc, char* argv[]){
    srand(time(NULL));
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutexBuffer, NULL);
    sem_init(&semEmpty, 0, 10); //initializing the num of slots available at the beggining
    sem_init(&semFull, 0, 0);
    for (int i = 0; i < THREAD_NUM; i++){
        if(i > 0){
            if(pthread_create(&th[i], NULL, &producer, NULL) != 0) {
                perror("failed to create thread");
            }
        } else{
            if(pthread_create(&th[i], NULL, &consumer, NULL) != 0){
                perror("failed to create thread");
            }
        }
    }
    for (int i = 0; i < THREAD_NUM; i++){
        if (pthread_join(th[i], NULL) != 0){
            perror("failed to create thread");
        }
    }
    sem_destroy(&semEmpty); //destroy the sems once done
    sem_destroy(&semFull);
    pthread_mutex_destroy(&mutexBuffer);
    return 0;

}

