#pragma once

#include <atomic>
#include <stdint.h>
#include "reference.h"

class GlobalGC;

// Base class for the object
class GCClassBase {
    std::atomic<uint32_t> depth;
    std::atomic<bool> active_gc;

public:
    inline bool needs_fence() {
        return active_gc.load(std::memory_order_relaxed);
    }

    virtual RefList get_roots() = 0;

    friend class GlobalGC;
};
