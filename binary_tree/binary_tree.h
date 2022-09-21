/**
 * @file binary_tree.h
 * @brief Simple Binary Search Tree implementation
 */

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


struct Point;
struct Node;

typedef struct Point data_obj_t;
typedef struct Node* node_obj_t;

/**
 * @brief Data type to be stored in BST
 */
struct Point
{
    int32_t s32_x;
    int32_t s32_y;
    int32_t s32_z;
};

/**
 * @brief Enumeration to describe result of comparison
 */
enum ComparisonResult
{
    eFirstIsGreater = 1,
    eEqual = 0,
    eSecondIsGreater = -1,
};

/**
 * @brief Compare stored data of two nodes of BST
 * @param first Data of first node
 * @param second Data of second node
 * @return Returns "1" when first > second, "0" when first == second, "-1" when first < second
 */
enum ComparisonResult compare_data_obj_t(data_obj_t first, data_obj_t second);


/**
 * @brief Binary tree Node data type 
 */
struct Node
{
  data_obj_t data;

  node_obj_t left;
  node_obj_t right;
};


/**
 * @brief Creation of Node
 * @param data Data object to be stored in new Node
 * @return New instance of Node
 */
node_obj_t create_binary_tree_node(data_obj_t data);

/**
 * @brief Creation of BST's first node
 * @param data Data object to be stored in first Node
 * @return Root node of binary tree
 */
node_obj_t create_binary_tree(data_obj_t data);

/**
 * @brief Insertion of node in binary tree
 * @param root Instance of BST
 * @param data Data object to be stored in new Node
 * @return Root node of binary tree
 */
node_obj_t insert_into_binary_tree(node_obj_t root, data_obj_t data);

/**
 * @brief Search for a specific node
 * @param root Instance of BST
 * @param data Data object to find in BST
 * @return Node with required data or NULL otherwise
 */
node_obj_t find_in_binary_tree(node_obj_t root, data_obj_t data);

/**
 * @brief Search for a Node's data with minimum value  
 * @param root Instance of BST
 * @return Node with the smallest data value and NULL otherwise
 */
node_obj_t min_in_binary_tree(node_obj_t root);

/**
 * @brief Deletion of Node by data stored in it
 * @param root Instance of BST
 * @param data Data object to remove from BST
 * @return Root of BST without removed Node
 */
node_obj_t remove_from_binary_tree(node_obj_t root, data_obj_t data);

/**
 * @brief Deletion of whole BST 
 * @param root Instance of BST
 * @return Empty tree
 */
node_obj_t delete_binary_tree(node_obj_t root);

#endif // BINARY_TREE_H
