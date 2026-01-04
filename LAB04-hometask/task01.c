#include <stdio.h>
#include <pthread.h>


typedef struct {
    int id;
    char *message;
} ThreadData;


void* printData(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    printf("Thread %d says: %s\n", data->id, data->message);
    return NULL;
}

int main() {
    pthread_t threads[3];           
    ThreadData data[3] = {          
        {1, "Hello from thread 1!"},
        {2, "Greetings from thread 2!"},
        {3, "Hi there from thread 3!"}
    };

   
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, printData, &data[i]);
    }

    
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads have finished.\n");
    return 0;
}
