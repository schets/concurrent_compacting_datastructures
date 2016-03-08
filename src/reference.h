#pragma once

#include "Object.h"
#include <atomic>
#include <utility>

class Reference {
    Object * volatile obj;
    public:
        Object *load();
        void store(Object *nobj);
        void store_repair(Object *nobj, Object*& parent);
};

extern "C" {
Object *ref_store(Object *volatile *store_addr,
                  Object *new_val,
                  Object *parent_val);
}

static_assert(sizeof(Reference) == sizeof(Object *),
              "Reference class is bigger than an object pointer");

inline Object *Reference::load() {
    return obj->redirect;
}

inline void Reference::store(Object* nobj) {
    ref_store(&obj, nobj, nullptr);
}

inline void Reference::store_repair(Object *nobj, Object*& holder) {
    holder = ref_store(&obj, nobj, holder);
}
