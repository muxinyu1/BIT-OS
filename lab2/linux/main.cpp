//
// Created by mxy on 9/29/2022.
//
#include <unistd.h>
#include <cstdlib>
#include <sys/wait.h>
#include <cstdio>

void start_producing(pid_t pid) {

}

void start_consuming(pid_t pid) {

}

int delete_shared_memory() {

}

constexpr int CHILD_PROGRESS_NUM = 5;

int main() {
    //TODO: 创建共享内存并attach, 初始化共享内存初始化信号量
    auto ppid = getpid();
    pid_t child_progresses[CHILD_PROGRESS_NUM];
    int i;
    for (i = 0; i < CHILD_PROGRESS_NUM; ++i) {
        child_progresses[i] = fork();
        if (child_progresses[i] == 0) break;
    }
    if (i < 2) {
        start_producing(child_progresses[i]);
    }
    if (i < CHILD_PROGRESS_NUM) {
        start_consuming(child_progresses[i]);
    }
    if (getpid() == ppid) {
        for (int child_progress : child_progresses) {
            waitpid(child_progress, nullptr, 0);
        }
        if (delete_shared_memory() == -1) {
            fprintf(stderr, "delete_shared_memory failed.\n");
            exit(EXIT_FAILURE);
        }
    }
    return EXIT_SUCCESS;
}
