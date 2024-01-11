#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "table.h"
#include "btree.h"

Cursor* table_start(Table* table) {
    Cursor* cursor = (Cursor*)malloc(sizeof(Cursor));
    cursor->table = table;
    cursor->cell_num = 0;
    cursor->end_of_table = table->root_page_num;

    void* root_node = get_page(table->pager, table->root_page_num);
    uint32_t num_cells = *leaf_node_num_cells(root_node);
    cursor->end_of_table = (num_cells == 0);

    return cursor;
}

/*
Return the position of the given key.
If the key is not present, return the position
where it should be inserted
*/
Cursor* table_find(Table* table, uint32_t key) {
  uint32_t root_page_num = table->root_page_num;
  void* root_node = get_page(table->pager, root_page_num);

  if (get_node_type(root_node) == NODE_LEAF) {
    return leaf_node_find(table, root_page_num, key);
  } else {
    printf("Need to implement searching an internal node\n");
    exit(EXIT_FAILURE);
  }
}

void* cursor_value(Cursor* cursor) {
  uint32_t page_num = cursor->page_num;

  void* page = get_page(cursor->table->pager, page_num);

  return leaf_node_value(page, cursor->cell_num);
}

void cursor_advance(Cursor* cursor) {
    uint32_t page_num = cursor->page_num;
    void* node = get_page(cursor->table->pager, page_num);

    cursor->cell_num += 1;
    if (cursor->cell_num >= (*leaf_node_num_cells(node))) {
        cursor->end_of_table = true;
    }
}

void print_row(Row* row) {
  printf("(%d, %s, %s)\n", row->id, row->username,
         row->email);
}

void serialize_row(Row* source, void* destination) {
  memcpy(destination + ID_OFFSET, &(source->id), ID_SIZE);
  strncpy(destination + USERNAME_OFFSET, source->username, USERNAME_SIZE);
  strncpy(destination + EMAIL_OFFSET, source->email, EMAIL_SIZE);
}

void deserialize_row(void* source, Row* destination) {
  memcpy(&(destination->id), source + ID_OFFSET, ID_SIZE);
  memcpy(&(destination->username), source + USERNAME_OFFSET, USERNAME_SIZE);
  memcpy(&(destination->email), source + EMAIL_OFFSET, EMAIL_SIZE);
}

// Table* new_table() {
//   Table* table = (Table*)malloc(sizeof(Table));
//   table->num_rows = 0;

//   return table;
// }