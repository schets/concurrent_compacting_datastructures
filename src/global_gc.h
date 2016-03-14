#pragma once

#include <atomic>

#include "gc_class_base.h"
class GlobalGC {
public:

    static void set_read_fence(GCClassBase *p);
};
