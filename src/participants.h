#pragma once

#include <atomic> // for std::atomic, atomic_thread_fence
#include <stddef.h>

#include "global_gc.h"
#include "gc_class_base.h"
#include "local_config.h" // for local_config

struct participant {
    participant *next;
    std::atomic<size_t> active;
    local_config conf;

    inline void enter(GCClassBase *p);
    inline void exit();
};

void participant::enter(GCClassBase *p) {
    size_t cur = active.load(std::memory_order_relaxed);
    active.store(cur + 1, std::memory_order_relaxed);
    std::atomic_signal_fence(std::memory_order_seq_cst);
    if (cur == 0 && p->needs_fence()) {
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
