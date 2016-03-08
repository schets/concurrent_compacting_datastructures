#pragma once
struct page;

page *alloc_pages(size_t n_pages);
void demap_pages(page *pages, size_t n_pages);
void page_set_rw(page *p, bool read, bool write);
