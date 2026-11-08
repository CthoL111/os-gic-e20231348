/* producer.c — Shared Memory IPC Producer */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
    const int SIZE = 4096;
    const char *name = "OS_SHM_REGION";
    const char *message = "Hello Pisey! Greetings from the Producer process.";

    int shm_fd;
    void *ptr;

    // Create the shared memory segment
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open failed");
        exit(EXIT_FAILURE);
    }

    // Configure the size of the shared memory segment
    ftruncate(shm_fd, SIZE);

    // Map the shared memory segment into the address space
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap failed");
        exit(EXIT_FAILURE);
    }

    // Write data to the shared memory region
    sprintf(ptr, "%s", message);
    printf("Producer (PID: %d): Wrote to shared memory: \"%s\"\n", getpid(), message);

    return 0;
}
