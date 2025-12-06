#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define K 4             
#define STUDENTS 10     

sem_t computers;         
pthread_mutex_t lock;   

int computer_in_use[K];  

void* student_thread(void* arg) {
    int id = *(int*)arg;
    sem_wait(&computers);
    pthread_mutex_lock(&lock);

    int assigned = -1;
    for (int i = 0; i < K; i++) {
        if (computer_in_use[i] == -1) {
            computer_in_use[i] = id;
            assigned = i;
            printf("Student %d is using computer %d\n", id, i);
            break;
        }
    }

    pthread_mutex_unlock(&lock);
    sleep((rand() % 4) + 1);
    pthread_mutex_lock(&lock);
    computer_in_use[assigned] = -1;
    printf("Student %d finished using computer %d\n", id, assigned);
    pthread_mutex_unlock(&lock);
    sem_post(&computers);
    return NULL;
}

int main() {
    srand(time(NULL));

    pthread_t students[STUDENTS];
    int ids[STUDENTS];

    for (int i = 0; i < K; i++)
        computer_in_use[i] = -1;

    sem_init(&computers, 0, K);
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < STUDENTS; i++) {
        ids[i] = i + 1;
        pthread_create(&students[i], NULL, student_thread, &ids[i]);
    }

    for (int i = 0; i < STUDENTS; i++) {
        pthread_join(students[i], NULL);
    }

    sem_destroy(&computers);
    pthread_mutex_destroy(&lock);
    return 0;
}
