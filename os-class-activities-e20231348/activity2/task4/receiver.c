/* receiver.c — Message Queue IPC Receiver */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <unistd.h>

int main() {
    const char *queue_name = "/os_msg_queue";
    mqd_t mq;
    char buffer[256];
    unsigned int prio;

    // Open the existing queue
    mq = mq_open(queue_name, O_RDONLY);
    if (mq == (mqd_t)-1) {
        perror("mq_open failed");
        exit(EXIT_FAILURE);
    }

    // Receive message
    ssize_t bytes_read = mq_receive(mq, buffer, 256, &prio);
    if (bytes_read == -1) {
        perror("mq_receive failed");
        exit(EXIT_FAILURE);
    }

    printf("Receiver (PID: %d): Received message: \"%s\"\n", getpid(), buffer);

    // Close and remove the queue from system
    mq_close(mq);
    mq_unlink(queue_name);
    printf("Message queue cleaned up successfully.\n");

    return 0;
}
