#pragma once
#include <atomic>
#include <stdint.h>
#include <stddef.h>

constexpr size_t page_size = 4096;
constexpr size_t bitmap_size_t = page_size / (8 * 32 * sizeof(size_t));
constexpr size_t page_data = page_size - bitmap_size_t;


struct page {
    struct {
        page *sister; // pointer to always-writeable memory space mapped to same spot
        std::atomic<page *> next; // next if this is in a linked list
        std::atomic<size_t> active_map[bitmap_size_t]; //bitmap of which ones are active (only modified by GC)
    } metadata;
    char data[page_size - sizeof(metadata)];
};
