#pragma once

#include <atomic>
#include <stddef.h>
#include "reference.h"

// Base class for the object
class GCClassBase {
    std::atomic<bool> active_gc;

public:
    inline bool needs_fence() {
        return active_gc.load(std::memory_order_relaxed);
    }

    template
    inline

    virtual RefList get_roots() = 0;
};
