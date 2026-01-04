#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>


typedef struct {
    int number;
    bool isPrime;
} ThreadData;


void* checkPrime(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int n = data->number;

    if (n <= 1) {
        data->isPrime = false;
        return NULL;
    }

    data->isPrime = true;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            data->isPrime = false;
            break;
        }
    }

    return NULL;
}

int main() {
    pthread_t thread;
    ThreadData data;

   
    printf("Enter a number: ");
    scanf("%d", &data.number);

    
    pthread_create(&thread, NULL, checkPrime, &data);

    pthread_join(thread, NULL);

    
    if (data.isPrime)
        printf("%d is a prime number.\n", data.number);
    else
        printf("%d is not a prime number.\n", data.number);

    return 0;
}
