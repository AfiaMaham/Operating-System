#include <stdio.h>
#include <pthread.h>
typedef struct {
    float cgpa;
    char* name;
} ThreadData;

void* printData(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    printf("Thread %f says: %s\n", data->cgpa, data->name);
    return NULL;
}
int main() {
    pthread_t t1;
    ThreadData data1 = {3.64, "Afia"};
    pthread_create(&t1, NULL, printData, &data1);
    pthread_join(t1, NULL);
    printf("All threads done.\n");
    return 0;
}
