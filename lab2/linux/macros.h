//
// Created by mxy on 10/1/2022.
//

#ifndef LAB2_LINUX_MACROS_H
#define LAB2_LINUX_MACROS_H

#include <cstdlib>

constexpr int CHILD_PROGRESS_NUM = 5;
constexpr key_t SHM_KEY = 95169641;
constexpr int SIGNAL_NUM = 3;
constexpr int DEFAULT_PRIVILEGE = 0B110110110;
constexpr int BUFFER_NUM = 3;
constexpr int PRODUCING_TIMES = 6;
constexpr int CONSUMING_TIMES = 4;
constexpr int MIN_SECONDS = 0;
constexpr int MAX_SECONDS = 5;
constexpr int MAX_WRITTEN_NUM = 2233;
constexpr int MIN_WRITTEN_NUM = -2233;
constexpr int DECREASE = -1;
constexpr int INCREASE = 1;

enum class Signal{
    FILLED,
    EMPTY,
    RW_MUX
};

#endif //LAB2_LINUX_MACROS_H
