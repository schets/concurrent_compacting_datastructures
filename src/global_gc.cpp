#include "global_gc.h"
#include <thread>
#include <chrono>

/* static */ void GlobalGC::set_read_fence(GCClassBase *p) {
    p->active_gc.store(true, std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_seq_cst);
    // sleep long enough so that currently active threads commit depth store
    std::this_thread::sleep_for(std::chrono::microseconds(50));
}
