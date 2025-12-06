#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define WASH_STATIONS 2
#define CARS 8   

sem_t station_sem;          
pthread_mutex_t lock;      

int queue_length = 0;      

void* car_thread(void* arg) {
    int id = *(int*)arg;

    pthread_mutex_lock(&lock);
    queue_length++;
    printf("Car %d arrived | Queue length: %d\n", id, queue_length);
    pthread_mutex_unlock(&lock);

    sem_wait(&station_sem);

    pthread_mutex_lock(&lock);
    queue_length--;
    printf("Car %d is being washed | Queue length: %d\n", id, queue_length);
    pthread_mutex_unlock(&lock);

    sleep(3);

    pthread_mutex_lock(&lock);
    printf("Car %d finished washing\n", id);
    pthread_mutex_unlock(&lock);

    sem_post(&station_sem);

    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t cars[CARS];
    int ids[CARS];
    sem_init(&station_sem, 0, WASH_STATIONS);
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < CARS; i++) {
        ids[i] = i + 1;
        pthread_create(&cars[i], NULL, car_thread, &ids[i]);
        usleep(200000);  
    }

    for (int i = 0; i < CARS; i++) {
        pthread_join(cars[i], NULL);
    }

    sem_destroy(&station_sem);
    pthread_mutex_destroy(&lock);

    return 0;
}
