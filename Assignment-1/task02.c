/*
 Name        : Afia Maham
 Registration : 23-NTU-CS-1126   
 Task Title  : Task 2 – Personalized Greeting Thread
*/

#include <stdio.h>      
#include <pthread.h>    
#include <string.h>    
#include <stdlib.h>    

// Thread function that prints a personalized greeting
void* greeting_function(void* arg) {
    char* name = (char*)arg;  // Retrieve the name passed as argument
    printf("Thread says: Hello, %s! Welcome to the world of threads.\n", name);
    return NULL; 
}

int main() {
    pthread_t thread_id;   // Thread identifier
    char name[50];         // Buffer to store user name

    // Take user input for the name
    printf("Enter your name: ");
    scanf("%s", name);

    // Create a new thread that prints a personalized greeting
    pthread_create(&thread_id, NULL, greeting_function, name);

    // Main thread message before joining
    printf("Main thread: Waiting for greeting...\n");

    // Wait for the greeting thread to complete
    pthread_join(thread_id, NULL);

    // Final message from main thread
    printf("Main thread: Greeting completed.\n");

    return 0;
}
