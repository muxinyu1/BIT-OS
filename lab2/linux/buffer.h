//
// Created by mxy on 10/1/2022.
//

#ifndef LAB2_LINUX_BUFFER_H
#define LAB2_LINUX_BUFFER_H

#include <algorithm>
#include <sys/sem.h>
#include "macros.h"

extern int sig_id;

struct buffer {
private:
    int data[BUFFER_NUM];
    int from;
    int to;
    static void P(Signal sig);
    static void V(Signal sig);
public:
    /**
     * 分配共享内存后初始化
     */
    void reset() noexcept;
    /**
     * 向缓冲区末尾写入
     * @param what 要写入的数
     * @return 写入的数
     */
    int write(int what);
    /**
     * 从缓冲区的开头读取
     * @return 读取到的数
     */
    int read();
};


#endif //LAB2_LINUX_BUFFER_H
