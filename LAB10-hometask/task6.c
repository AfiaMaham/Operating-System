#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ON_BRIDGE 3
#define TOTAL_CARS 12

sem_t bridge_sem;       
pthread_mutex_t print_lock;

void* car_thread(void* arg) {
    int id = *(int*)arg;

    pthread_mutex_lock(&print_lock);
    printf("Car %d arrived at the bridge\n", id);
    pthread_mutex_unlock(&print_lock);

    sem_wait(&bridge_sem);

    pthread_mutex_lock(&print_lock);
    printf("Car %d is crossing the bridge\n", id);
    pthread_mutex_unlock(&print_lock);

    int cross_time = (rand() % 4) + 1;
    sleep(cross_time);

    pthread_mutex_lock(&print_lock);
    printf("Car %d finished crossing in %d sec\n", id, cross_time);
    pthread_mutex_unlock(&print_lock);

    sem_post(&bridge_sem);

    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t cars[TOTAL_CARS];
    int ids[TOTAL_CARS];
    sem_init(&bridge_sem, 0, MAX_ON_BRIDGE);
    pthread_mutex_init(&print_lock, NULL);

    for (int i = 0; i < TOTAL_CARS; i++) {
        ids[i] = i + 1;
        pthread_create(&cars[i], NULL, car_thread, &ids[i]);
        usleep(150000);   
    }

    for (int i = 0; i < TOTAL_CARS; i++) {
        pthread_join(cars[i], NULL);
    }

    sem_destroy(&bridge_sem);
    pthread_mutex_destroy(&print_lock);

    return 0;
}
