#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define MAX_DOWNLOADS 3
#define TOTAL 8

sem_t slots;  
pthread_mutex_t lock;   

void* download_file(void* arg) {
    int id = *(int*)arg;

    sem_wait(&slots);

    pthread_mutex_lock(&lock);
    printf("Download %d started...\n", id);
    pthread_mutex_unlock(&lock);

    int duration = (rand() % 5) + 1;
    sleep(duration);

    pthread_mutex_lock(&lock);
    printf("Download %d finished after %d seconds.\n", id, duration);
    pthread_mutex_unlock(&lock);

    sem_post(&slots);

    return NULL;
}

int main() {
    srand(time(NULL));

    pthread_t downloads[TOTAL];
    int ids[TOTAL];

    sem_init(&slots, 0, MAX_DOWNLOADS);
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < TOTAL; i++) {
        ids[i] = i + 1;
        pthread_create(&downloads[i], NULL, download_file, &ids[i]);
    }

    for (int i = 0; i < TOTAL; i++) {
        pthread_join(downloads[i], NULL);
    }

    sem_destroy(&slots);
    pthread_mutex_destroy(&lock);

    return 0;
}
