#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();  // create child process

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }
    else if (pid == 0) {
        // Child process
        printf("Child (PID: %d) running date command...\n", getpid());
        execlp("date", "date", NULL);  // replace process with date command
        perror("execlp failed");  // runs only if exec fails
    }
    else {
        // Parent process
        printf("Parent (PID: %d) waiting for child (PID: %d)...\n", getpid(), pid);
        wait(NULL);  // wait for child to finish
        printf("Child finished.\n");
    }

    return 0;
}
