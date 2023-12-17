#ifndef TABLE_H
#define TABLE_H
#include <stdint.h>
#include <stdbool.h>

#include "pager.h"
#include "common.h"

typedef struct Table {
    uint32_t root_page_num;
    Pager* pager;
} Table;

typedef struct Cursor {
    Table* table;
    uint32_t page_num;
    uint32_t cell_num;
    bool end_of_table; // Indicates a position one past the last element
} Cursor;

Cursor* table_start(Table* table);

Cursor* table_end(Table* table);

void* cursor_value(Cursor* cursor);

void cursor_advance(Cursor* cursor);

void print_row(Row* row);

void serialize_row(Row* source, void* destination);

void deserialize_row(void* source, Row* destination);

#endif /* TABLE_H */