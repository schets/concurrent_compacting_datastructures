extern "C" {
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
}


#include "raw_alloc.h"
#include "page.h"

page *alloc_pages(size_t n) {
    //thread safety soon...
    // lol @ security, there has to be a better way
    int fd = shm_open("__MY_GC_DUMMY", O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
    page *main = (page *)mmap(nullptr, n * sizeof(page), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    page *sister = (page *)mmap(nullptr, n * sizeof(page), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    main->metadata.sister = sister;
    shm_unlink("__MY_GC_DUMMY");
    return main;
}

void demap_pages(page *pages, size_t n_pages) {
    page *sister = pages->metadata.sister;
    munmap(pages, n_pages * sizeof(*pages));
    munmap(sister, n_pages * sizeof(*pages));
}

void page_set_rw(page *p, size_t n, bool read, bool write) {
    int r = 0;
    int w = 0;
    if (!write && !write) {
        mprotect(p, n * sizeof(*p), PROT_NONE);
    }
    else {
        r = read & PROT_READ;
        w = read & PROT_WRITE;
        mprotect(p, n * sizeof(*p), r | w);
    }
}
