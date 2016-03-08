#pragma once

#include <atomic>

#include "gc_base_class.h"
class GlobalGC {
public:

    void set_read_fence(GCClassBase *p);
};
