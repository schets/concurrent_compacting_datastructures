#pragma once

#include "Object.h"
#include <atomic>
#include <utility>

class Reference {
    Object *obj;
    public:
        Object *load(std::memory_order ord = std::memory_order_relaxed);
        Object *store(Object * _obj);
};

extern "C" {
// Calling convention is a bit different though!
Object *ref_load(Object * store_addr, Object *new_val, Object *parent_val);
}

static_assert(sizeof(Reference) == sizeof(Object *),
              "Reference class is bigger than an object pointer");

inline Object *Reference::load(std::memory_order ord) {
    return obj.load(ord)->redirect;
}

inline void store(Object *nobj, Object*& parent) {
    Object* rval;
    // Maybe could be not volatile
    // and enable some more optimizations (i.e. no mov from rax to rax)
    // but GCC will almost certainly elide some writes...
    asm volatile ("")
}
