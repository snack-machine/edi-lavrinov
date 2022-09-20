/**
 * @file binary_tree.h
 * @brief Simple Binary Search Tree implementation
 */

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


/**
 * @brief s
 */
struct Point
{
  int32_t s32_x;
  int32_t s32_y;
  int32_t s32_z;
};

int compare_data_obj_t(data_obj_t first, data_obj_t second);

/**
 * @brief Binary tree node data type 
 */
struct Node
{
  data_obj_t data;

  node_obj_t left;
  node_obj_t right;
};

typedef struct Point data_obj_t;
typedef struct Node* node_obj_t;


node_obj_t create_binary_tree_node(data_obj_t data);

/**
 * @brief Creation of binary tree
 * @return Root node of binary tree
 */
node_obj_t create_binary_tree(void);

/**
 * @brief Insertion of node in binary tree
 * @param root Instance of binary tree
 * @return Root node of binary tree
 */
node_obj_t insert_into_binary_tree(node_obj_t root, data_obj_t data);
node_obj_t find_in_binary_tree(node_obj_t root, data_obj_t data);
node_obj_t remove_from_binary_tree(node_obj_t root, data_obj_t data);
void delete_binary_tree(node_obj_t root);

#endif // BINARY_TREE_H
