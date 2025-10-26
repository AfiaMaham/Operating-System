/*
 Name        : Afia Maham
 Registration : 23-NTU-CS-1126
 Task Title  : Task 4 – Thread Return Values

*/

#include <stdio.h>      
#include <pthread.h>    
#include <stdlib.h>     

// Thread function to compute factorial
void* factorial_function(void* arg) {
    int n = *(int*)arg;          // Retrieve the integer passed as argument
    long long* result = malloc(sizeof(long long));  // Allocate memory for result
    *result = 1;                 // Initialize factorial result

    for (int i = 1; i <= n; i++) {
        *result *= i;
    }

    printf("Thread: Factorial of %d calculated successfully.\n", n);
    return (void*)result;        // Return pointer to result
}

int main() {
    pthread_t thread_id;   // Thread identifier
    int number;
    void* factorial_ptr;   // To store pointer returned by thread

    // Take user input
    printf("Enter an integer to calculate its factorial: ");
    scanf("%d", &number);

    // Create the thread and pass the number
    pthread_create(&thread_id, NULL, factorial_function, &number);

    // Main thread message before joining
    printf("Main thread: Waiting for factorial result...\n");

    // Wait for thread completion and get the returned value
    pthread_join(thread_id, &factorial_ptr);

    // Print the factorial result (dereference pointer)
    printf("Main thread: Factorial of %d is %lld\n", number, *(long long*)factorial_ptr);

    // Free dynamically allocated memory
    free(factorial_ptr);

    // Final message
    printf("Main thread: Work completed.\n");

    return 0;
}
