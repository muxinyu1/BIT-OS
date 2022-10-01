//
// Created by mxy on 10/1/2022.
//
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <sys/shm.h>
#include <sys/sem.h>
#include <random>
#include "buffer.h"

void start_producing(pid_t pid);
void start_consuming(pid_t pid);
void del_shm();
void init_sig();
void attach_shm();
void detach_shm();
void init_shm();
int create_random_sleep_time();
int create_random_written_num();

int shm_id;
int sig_id;
buffer* buffer_ptr;
auto engine = std::mt19937(std::random_device()());
auto u_sleep = std::uniform_int_distribution<int>(MIN_SECONDS, MAX_SECONDS);
auto u_written = std::uniform_int_distribution<int>(MIN_WRITTEN_NUM, MAX_WRITTEN_NUM);

void start_producing(pid_t pid) {
    attach_shm();
    for (int i = 0; i < PRODUCING_TIMES; ++i) {
        //随机等待一段时间
        sleep(create_random_sleep_time());
        printf("#%X Writes %d\n", pid, buffer_ptr->write(create_random_written_num()));
    }
    detach_shm();
}

void start_consuming(pid_t pid) {
    attach_shm();
    for (int i = 0; i < CONSUMING_TIMES; ++i) {
        sleep(create_random_sleep_time());
        printf("#%X Reads %d\n", pid, buffer_ptr->read());
    }
    detach_shm();
}

void init_sig() {
    //创建信号量集, 其中信号量个数为3
    if ((sig_id = semget(IPC_PRIVATE, SIGNAL_NUM, DEFAULT_PRIVILEGE|IPC_CREAT)) == -1) {
        fprintf(stderr, "semget failed\n");
        exit(EXIT_FAILURE);
    }
    union sig_union{
        short val;
    };
    semctl(sig_id, static_cast<int>(Signal::EMPTY), SETVAL, sig_union{.val = BUFFER_NUM});
    semctl(sig_id, static_cast<int>(Signal::FILLED), SETVAL, sig_union{.val = 0});
    semctl(sig_id, static_cast<int>(Signal::RW_MUX), SETVAL, sig_union{.val = 1});
}

void attach_shm() {
    //attach共享内存
    if (*(int*)(buffer_ptr = static_cast<buffer*>(shmat(shm_id, nullptr, 0))) == -1) {
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }
}

void del_shm() {
    detach_shm();
    if (shmctl(shm_id, IPC_RMID, nullptr) == -1) {
        fprintf(stderr, "shmctl failed\n");
        exit(EXIT_FAILURE);
    }
}

void init_shm() {
    //申请共享内存
    if ((shm_id = shmget(SHM_KEY, sizeof(buffer), DEFAULT_PRIVILEGE|IPC_CREAT)) == -1) {
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }
    attach_shm();
    buffer_ptr->reset();
}

int create_random_sleep_time() {
    return u_sleep(engine);
}

int create_random_written_num() {
    return u_written(engine);
}

void detach_shm() {
    if (shmdt(buffer_ptr) == -1) {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }
}