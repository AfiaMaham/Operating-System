/*
 Name        : Afia Maham
 Registration : 23-NTU-CS-1126     
 Task Title  : Task 3 – Number Info Thread
*/

#include <stdio.h>    
#include <pthread.h>   
#include <stdlib.h>     

// Thread function to display number info
void* number_info(void* arg) {
    int num = *(int*)arg;  // Retrieve the integer passed from main

    printf("Thread: The number is %d\n", num);
    printf("Thread: Square of %d is %d\n", num, num * num);
    printf("Thread: Cube of %d is %d\n", num, num * num * num);

    return NULL; 
}

int main() {
    pthread_t thread_id;  // Thread identifier
    int number;

    // Take integer input from the user
    printf("Enter an integer: ");
    scanf("%d", &number);

    // Create a thread and pass the address of the number
    pthread_create(&thread_id, NULL, number_info, &number);

    // Main thread message before waiting
    printf("Main thread: Waiting for number info...\n");

    // Wait for the thread to complete its work
    pthread_join(thread_id, NULL);

    // Final message after thread completion
    printf("Main thread: Work completed.\n");

    return 0;
}
