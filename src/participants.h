#pragma once

#include <atomic>

struct participant {
    participant *next;
    std::atomic<size_t> active;

    inline void enter();
    inline void exit();
};

void participant::enter() {
    size_t cur = active.load(std::memory_order_relaxed);
    active.store(cur + 1, std::memory_order_relaxed);
    if (cur == 0) {
        std::atomic_thread_fence(std::memory_order_seq_cst);
    }
}

void participant::exit() {
    size_t cur = active.load(std::memory_order_relaxed);
    active.store(cur - 1, std::memory_order_release);
}

participant *get_active_participants();
void add_active_participant(participant *p);

inline participant *get_current_participant() {
    thread_local participant *p = nullptr;
    if (p == nullptr) {
        p = new participant;
        add_active_participant(p);
    }
    return p;
}
