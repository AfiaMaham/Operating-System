// Write a C program that finds the maximum value in an array using threads:
// 1.  Create an array of 20 integers with values: {45, 23, 67, 89,  212, 34, 78, 90, 56,1, 38, 72,
// 44, 91, 15, 83, 29, 66, 54, 88}
// 2.  Create 4 threads, each finding maximum in 5 elements:   Thread 1: elements 0-4
//   Thread 2: elements 5-9
//   Thread 3: elements 10-14
//   Thread 4: elements 15-19
// 3.  Pass the starting index and count to each thread using a structure
// 4.  Each thread:
//   Finds maximum in its portion
//   Prints the maximum value it found   Returns the maximum value
// 5.  Main thread collects all return values and finds overall maximum

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
// golbally defined array of size 20
int arr[20] = {45, 23, 67, 89, 12, 34, 78, 90, 56, 21, 38, 72, 44, 91, 15, 83, 29, 66, 54, 88};

// defined struct having two attributes starting and ending value of array
typedef struct{
    int start_index;
    int count;
} ArrayStruct;


// method called by each thread
void* max_element(void* arg){
    // dereference the argument into ArrayStruct type
    ArrayStruct s1 = *(ArrayStruct*)arg;   
    // allocation of space to store result 
    int* max = malloc(sizeof(int));
    // loop that will calculate the maximum element in specified range
    for (int i = s1.start_index; i <= s1.count; i++){
        if (arr[i] > *max){
            *max = arr[i];
        }
    }
    // print the maximum element found
    printf("max value from index %d to %d = %d\n",s1.start_index, s1.count, *max);
    // return the maximum element as void type
    return (void*)max;
}

int main(){ 
    // create array to store thread id
    pthread_t t[4];
    // array to store result of all threads
    void* max_arr[4]; 
    // variable to store final result
    int result = 0;
    // array to store 4 structs
    ArrayStruct s[4];

    // value passing in array of struct
    s[0].start_index = 0;
    s[0].count = 4;

    s[1].start_index = 5;
    s[1].count = 9;

    s[2].start_index = 10;
    s[2].count = 14;

    s[3].start_index = 15;
    s[3].count = 19;


    // used loop to create 4 threads
    for (int i = 0;i<4;i++){
        pthread_create(&t[i], NULL, max_element, &s[i]);
    }
    // loop to wait for each thread
    for (int i = 0;i<4;i++){
        pthread_join(t[i], &max_arr[i]);
    }
    
    // loop to find maximum value among the result from each thread
    for (int i = 0;i<4;i++){
        if (*(int*)max_arr[i]> result){
            result = *(int*)max_arr[i];
        }
    }
    // print final result
    printf("Maximum element in whole array = %d\n",result);
    return 0;
}