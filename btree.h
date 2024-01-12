#ifndef BTREE_H
#define BTREE_H
#include <stdint.h>
#include "common.h"
#include "pager.h"
#include "table.h"

uint32_t* leaf_node_num_cells(void* node);

void* leaf_node_cell(void* node, uint32_t cell_num);

uint32_t* leaf_node_key(void* node, uint32_t cell_num);

void* leaf_node_value(void* node, uint32_t cell_num);

void initialize_leaf_node(void* node);

void leaf_node_insert(Cursor* cursor, uint32_t key, Row* value);

typedef enum { NODE_INTERNAL, NODE_LEAF } NodeType;

NodeType get_node_type(void* node);

void set_node_type(void* node, NodeType type);

Cursor* leaf_node_find(Table* table, uint32_t page_num, uint32_t key);

void set_node_root(void* node, bool is_root);

void print_tree(Pager* pager, uint32_t page_num, uint32_t indentation_level);

Cursor* internal_node_find(Table* table, uint32_t page_num, uint32_t key);

/*
 * Leaf Node Header Layout
 */
extern const uint32_t LEAF_NODE_NUM_CELLS_SIZE;
extern const uint32_t LEAF_NODE_NUM_CELLS_OFFSET;
extern const uint32_t LEAF_NODE_HEADER_SIZE;

/*
 * Leaf Node Body Layout
 */
extern const uint32_t LEAF_NODE_KEY_SIZE;
extern const uint32_t LEAF_NODE_KEY_OFFSET;
extern const uint32_t LEAF_NODE_VALUE_SIZE;
extern const uint32_t LEAF_NODE_VALUE_OFFSET;
extern const uint32_t LEAF_NODE_CELL_SIZE;
extern const uint32_t LEAF_NODE_SPACE_FOR_CELLS;
extern const uint32_t LEAF_NODE_MAX_CELLS;

#endif /* BTREE_H */