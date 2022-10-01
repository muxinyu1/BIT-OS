//
// Created by mxy on 10/1/2022.
//

#include "buffer.h"

void buffer::reset() noexcept {
    this->from = 0;
    this->to = 0;
    std::fill(std::begin(this->data), std::end(this->data), 0);
}

int buffer::write(int what) {
    P(Signal::EMPTY);
    P(Signal::RW_MUX);
    data[to] = what;
    to = (to + 1) % BUFFER_NUM;
    V(Signal::RW_MUX);
    V(Signal::FILLED);
    return what;
}

int buffer::read() {
    P(Signal::FILLED);
    P(Signal::RW_MUX);
    auto result = data[from];
    from = (from + 1) % BUFFER_NUM;
    V(Signal::RW_MUX);
    V(Signal::EMPTY);
    return result;
}

void buffer::P(Signal sig) {
    auto sembuf_ds = sembuf{.sem_num = static_cast<unsigned short int>(sig), .sem_op = DECREASE, .sem_flg = IPC_NOWAIT};
    semop(sig_id, &sembuf_ds, 1);
}

void buffer::V(Signal sig) {
    auto sembuf_ds = sembuf{.sem_num = static_cast<unsigned short int>(sig), .sem_op = INCREASE, .sem_flg = IPC_NOWAIT};
    semop(sig_id, &sembuf_ds, 1);
}
