#pragma once

#include "Object.h"
#include <atomic>
#include <utility>

class Reference {
    Object *obj;
    public:
        Object *load(std::memory_order ord = std::memory_order_relaxed);
        Object *store(Object *_obj,
                   std::memory_order ord = std::memory_order_relaxed);
};

static_assert(sizeof(Reference) == sizeof(Object *),
              "Reference class is bigger than an object pointer");

inline Object *Reference::load(std::memory_order ord) {
    return obj.load(ord)->redirect;
}

inline Object *store(Object *_obj, Object *parent, std::memory_order ord) {
    this->obj.store(_obj, ord);
}
