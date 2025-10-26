/*
 Name        : Afia Maham
 Registration : 23-NTU-CS-1126   
 Task Title  : Task 1 – Thread Information Display
*/

#include <stdio.h>     
#include <pthread.h>    
#include <unistd.h>     
#include <stdlib.h>     
#include <time.h>       

// Thread function that will be executed by each thread
void* thread_function(void* arg) {
    int thread_num = *(int*)arg;        // Retrieve thread number passed as argument
    pthread_t thread_id = pthread_self(); // Get unique thread ID

    // Print thread starting information
    printf("Thread %d started. Thread ID: %lu\n", thread_num, thread_id);

    // Generate random sleep time between 1 and 3 seconds
    int sleep_time = (rand() % 3) + 1;
    sleep(sleep_time);  // Simulate work by sleeping

    // Print thread completion message
    printf("Thread %d (ID: %lu) completed after %d seconds.\n", thread_num, thread_id, sleep_time);

    return NULL; 
}

int main() {
    pthread_t threads[5];    // Array to store 5 thread identifiers
    int thread_nums[5];      // Array to store thread numbers

    srand(time(NULL)); // Initialize random seed using current time

    printf("Main thread starting...\n");
    printf("Main Thread ID: %lu\n\n", pthread_self());

    // Create 5 threads
    for (int i = 0; i < 5; i++) {
        thread_nums[i] = i + 1;  // Assign thread numbers 1–5
        pthread_create(&threads[i], NULL, thread_function, &thread_nums[i]);
    }

    // Wait for all threads to complete
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    // Final message after all threads complete
    printf("\nMain thread: All threads have completed.\n");
    return 0;
}
