#ifndef PAGER_H
#define PAGER_H
#include <stdint.h>

#define TABLE_MAX_PAGES 4096
#define PAGE_SIZE 4096

typedef struct Pager {
    int file_descriptor;
    uint32_t file_length;
    uint32_t num_pages;
    void* pages[TABLE_MAX_PAGES];
} Pager;

Pager* pager_open(const char* filename);

void* get_page(Pager* pager, uint32_t page_num);

void pager_flush(Pager* pager, uint32_t page_num);

#endif /* PAGER_H */