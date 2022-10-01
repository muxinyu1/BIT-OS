//
// Created by mxy on 9/29/2022.
//
#include <unistd.h>
#include <cstdlib>
#include <sys/wait.h>
#include <array>
#include "macros.h"

/**
 * pid进程作为生产者
 * @param pid 生产者子进程的pid
 */
extern void start_producing(pid_t pid);

/**
 * 初始化信号量: EMPTY, FILLED, RW_MUX
 */
extern void init_sig();

/**
 * 初始化共享内存
 */
extern void init_shm();

/**
 * pid进程作为消费者
 * @param pid 消费者子进程的pid
 */
extern void start_consuming(pid_t pid);

/**
 * 删除共享内存
 */
extern void del_shm();


int main() {
    init_sig();
    init_shm();

    auto ppid = getpid();
    auto child_progresses = std::array<pid_t, CHILD_PROGRESS_NUM>();
    int i;
    //创建子进程
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
    //如果当前进程是父进程
    if (getpid() == ppid) {
        for (auto child_progress : child_progresses) {
            //等待所有子进程结束
            waitpid(child_progress, nullptr, 0);
        }
        //删除共享内存
        del_shm();
    }
    return EXIT_SUCCESS;
}
