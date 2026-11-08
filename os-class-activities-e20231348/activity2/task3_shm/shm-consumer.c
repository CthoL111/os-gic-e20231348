/* consumer.c — Shared Memory IPC Consumer */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
    const int SIZE = 4096;
    const char *name = "OS_SHM_REGION";

    int shm_fd;
    void *ptr;

    // Open the shared memory segment
    shm_fd = shm_open(name, O_RDONLY, 0666);
    if (shm_fd == -1) {
        perror("shm_open failed. Ensure producer has run first.");
        exit(EXIT_FAILURE);
    }

    // Map the shared memory segment into the address space
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap failed");
        exit(EXIT_FAILURE);
    }

    // Read the data out from shared memory
    printf("Consumer (PID: %d): Read from shared memory: \"%s\"\n", getpid(), (char *)ptr);

    // Unlink the shared memory segment to clean up the OS resource
    if (shm_unlink(name) == -1) {
        perror("shm_unlink failed");
        exit(EXIT_FAILURE);
    }
    printf("Shared memory cleaned up successfully.\n");

    return 0;
}
