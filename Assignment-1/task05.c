/*
 Name        : Afia Maham
 Registration : 23-NTU-CS-1126
 Task Title  : Task 5 – Struct-Based Thread Communication

*/

#include <stdio.h>      
#include <pthread.h>    
#include <string.h>     
#include <stdlib.h>     

// Define the Student struct
typedef struct {
    int student_id;
    char name[50];
    float gpa;
} Student;

// Thread function to process student info
void* process_student(void* arg) {
    Student* s = (Student*)arg;  // Typecast argument to Student pointer

    printf("Thread: Processing Student ID: %d\n", s->student_id);
    printf("Name: %s\n", s->name);
    printf("GPA: %.2f\n", s->gpa);

    // Allocate memory for Dean’s List result (1 = eligible, 0 = not eligible)
    int* eligible = malloc(sizeof(int));
    if (s->gpa >= 3.5) {
        printf("Result: %s made the Dean's List!\n\n", s->name);
        *eligible = 1;
    } else {
        printf("Result: %s did NOT make the Dean's List.\n\n", s->name);
        *eligible = 0;
    }

    return (void*)eligible;  // Return pointer to result
}

int main() {
    pthread_t threads[3];   // To hold thread identifiers
    Student students[3];    // Array of 3 Student structs
    void* result;           // To store thread return values
    int deans_list_count = 0;

    // Initialize student data
    students[0].student_id = 101;
    strcpy(students[0].name, "Ali");
    students[0].gpa = 3.8;

    students[1].student_id = 102;
    strcpy(students[1].name, "Sara");
    students[1].gpa = 3.2;

    students[2].student_id = 103;
    strcpy(students[2].name, "Usman");
    students[2].gpa = 3.9;

    printf("Main thread: Starting student evaluation threads...\n\n");

    // Create 3 threads, each receiving a different Student struct
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, process_student, &students[i]);
    }

    // Wait for all threads and count Dean’s List students
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], &result);
        deans_list_count += *(int*)result;  // Add 1 if eligible
        free(result);  // Free memory returned from thread
    }

    printf("Main thread: Total students on the Dean’s List = %d\n", deans_list_count);
    printf("Main thread: Work completed.\n");

    return 0;
}
