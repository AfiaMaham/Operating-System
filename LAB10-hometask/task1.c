#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define N 3     
#define PEOPLE 10

sem_t rooms;             
pthread_mutex_t lock;  
int occupied = 0;

void* person(void* arg) {
    int id = *(int*)arg;

    sem_wait(&rooms);

    pthread_mutex_lock(&lock);
    occupied++;
    printf("Person %d entered | Occupied rooms: %d\n", id, occupied);
    pthread_mutex_unlock(&lock);

    sleep((rand() % 3) + 1);

    pthread_mutex_lock(&lock);
    occupied--;
    printf("Person %d left   | Occupied rooms: %d\n", id, occupied);
    pthread_mutex_unlock(&lock);

    sem_post(&rooms);

    return NULL;
}

int main() {
    pthread_t t[PEOPLE];
    int ids[PEOPLE];

    sem_init(&rooms, 0, N);           
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < PEOPLE; i++) {
        ids[i] = i + 1;
        pthread_create(&t[i], NULL, person, &ids[i]);
    }

    for (int i = 0; i < PEOPLE; i++) {
        pthread_join(t[i], NULL);
    }

    sem_destroy(&rooms);
    pthread_mutex_destroy(&lock);

    return 0;
}
