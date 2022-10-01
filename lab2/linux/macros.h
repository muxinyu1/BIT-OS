//
// Created by mxy on 10/1/2022.
//

#ifndef LAB2_LINUX_MACROS_H
#define LAB2_LINUX_MACROS_H

#include <cstdlib>

//子进程的个数, 2个生产者 + 3个消费者
constexpr int CHILD_PROGRESS_NUM = 5;
//共享内存的key_t
constexpr key_t SHM_KEY = 95169641;
//信号量个数: EMPTY + FILLED + RW_MUX
constexpr int SIGNAL_NUM = 3;
//0666
constexpr int DEFAULT_PRIVILEGE = 0B110110110;
//缓冲区数量
constexpr int BUFFER_NUM = 3;
constexpr int PRODUCING_TIMES = 6;
constexpr int CONSUMING_TIMES = 4;
constexpr int MIN_SECONDS = 0;
constexpr int MAX_SECONDS = 5;
constexpr int MAX_WRITTEN_NUM = 2233;
constexpr int MIN_WRITTEN_NUM = -2233;
//P操作
constexpr int DECREASE = -1;
//V操作
constexpr int INCREASE = 1;

enum class Signal{
    FILLED,
    EMPTY,
    RW_MUX
};

#endif //LAB2_LINUX_MACROS_H
