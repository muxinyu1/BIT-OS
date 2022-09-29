#include <unistd.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include "macros.h"

int main() {
    int shm_id;
    if ((shm_id = shmget(SHARED_MEM_KEY, sizeof(struct data), IPC_CREAT)) == -1) {
        fprintf(stderr, "shmget failed.\n");
        exit(EXIT_FAILURE);
    }
    void* shm_addr;
    if (*(int*)(shm_addr = shmat(shm_id, 0, 0)) == -1) {
        fprintf(stderr, "shmat failed.\n");
        exit(EXIT_FAILURE);
    }
    struct data* shared_data = (struct shared_data*)shm_addr;
    while (!shared_data->writen)
    {
        /* code */
    }
    
}