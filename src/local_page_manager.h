#pragma once

#include "page.h"
#include <stddef.h>

class local_page_manager {
    std::atomic<bool> gc_add_lock;
    std::atomic<page *> head;
    std::atomic<size_t> npages;
public:
    static page *alloc_page();
};
