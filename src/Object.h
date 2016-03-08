#pragma once

#include <stddef.h>

class Object;
class Reference;

struct RefList {
    Object *refs;
    size_t s;
};

class Object {
    Object *redirect;

public:

    virtual RefList gc_references() = 0;
    virtual size_t gc_get_size() = 0;

    friend class Reference;
};
