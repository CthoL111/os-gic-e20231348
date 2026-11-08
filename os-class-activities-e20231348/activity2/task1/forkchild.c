/* forkchild.c — Process creation with fork() and exec() */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    printf("Parent process (PID: %d) — creating child...\n", getpid());

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        /* ---- CHILD PROCESS ---- */
        printf("Child process (PID: %d, Parent PID: %d)\n", getpid(), getppid());
        printf("Child: sleeping 30s — observe process tree now...\n");
        sleep(30);

        printf("Child: executing 'ls -la'...\n");
        execlp("ls", "ls", "-la", NULL);

        /* If execlp returns, an error occurred */
        perror("execlp failed");
        exit(EXIT_FAILURE);
    }
    else {
        /* ---- PARENT PROCESS ---- */
        printf("Parent process (PID: %d) waiting for child (PID: %d) to finish...\n", getpid(), pid);
        
        int status;
        wait(&status); /* Wait for the child to terminate */

        if (WIFEXITED(status)) {
            printf("Parent: Child process exited with status %d.\n", WEXITSTATUS(status));
        } else {
            printf("Parent: Child process terminated abnormally.\n");
        }
    }

    return 0;
}
