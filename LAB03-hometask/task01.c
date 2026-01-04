#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;

    pid = fork();  

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } 
    else if (pid == 0) {
        printf("Child process (PID: %d) running top...\n", getpid());
        execlp("top", "top", NULL); 
        perror("execlp failed");   
    } 
    else {
        printf("Parent process (PID: %d) created child with PID: %d\n", getpid(), pid);
        sleep(60); 
        printf("Parent process finished.\n");
    }

    return 0;
}
