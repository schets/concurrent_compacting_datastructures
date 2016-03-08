#include "local_page_manager.h"

// This is atomic because the GC can insert pages at will!

/* static */ page *local_page_manager::alloc_page() {
    thread_local static local_page_manager man;
    page *next;
    page *curhead = man.head.load(std::memory_order_consume);
    do {
        if (curhead == nullptr) {
            return nullptr;
        }
        next = curhead->metadata.next.load(std::memory_order_relaxed);
    } while (man.head.compare_exchange_weak(curhead, next,
                                            std::memory_order_release,
                                            std::memory_order_consume));
    return curhead;
}
