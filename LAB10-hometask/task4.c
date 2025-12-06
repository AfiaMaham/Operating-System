#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define WORKERS 3
#define TASKS 10

sem_t available_workers;     
pthread_mutex_t lock;         

void* task_function(void* arg) {
    int id = *(int*)arg;
    sem_wait(&available_workers);

    pthread_mutex_lock(&lock);
    printf("Task %d is being processed by a worker\n", id);
    pthread_mutex_unlock(&lock);

    sleep((rand() % 2) + 1);

    pthread_mutex_lock(&lock);
    printf("Task %d finished\n", id);
    pthread_mutex_unlock(&lock);

    sem_post(&available_workers);

    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t tasks[TASKS];
    int ids[TASKS];
    sem_init(&available_workers, 0, WORKERS);
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < TASKS; i++) {
        ids[i] = i + 1;
        pthread_create(&tasks[i], NULL, task_function, &ids[i]);
    }

    for (int i = 0; i < TASKS; i++) {
        pthread_join(tasks[i], NULL);
    }

    sem_destroy(&available_workers);
    pthread_mutex_destroy(&lock);

    return 0;
}
