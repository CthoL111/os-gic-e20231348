/* sender.c — Message Queue IPC Sender */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <unistd.h>

int main() {
    const char *queue_name = "/os_msg_queue";
    mqd_t mq;
    char buffer[] = "Structured Message from Sender via POSIX Queue!";
    
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 256;
    attr.mq_curmsgs = 0;

    // Open or create message queue
    mq = mq_open(queue_name, O_CREAT | O_WRONLY, 0666, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open failed");
        exit(EXIT_FAILURE);
    }

    // Send the message block
    if (mq_send(mq, buffer, strlen(buffer) + 1, 0) == -1) {
        perror("mq_send failed");
        exit(EXIT_FAILURE);
    }

    printf("Sender (PID: %d): Sent message to queue.\n", getpid());
    mq_close(mq);

    return 0;
}
