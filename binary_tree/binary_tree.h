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

typedef struct Point data_t;
typedef struct Node* node_t;

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
 * @param objL_first Data of first node
 * @param objL_second Data of second node
 * @return Returns "1" when first > second, "0" when first == second, "-1" when first < second
 */
enum ComparisonResult compare_data_t(data_t objL_first, data_t objL_second);


/**
 * @brief Binary tree Node data type
 */
struct Node
{
  data_t objL_data;

  node_t objP_left;
  node_t objP_right;
};


/**
 * @brief Creation of Node
 * @param objL_data Data object to be stored in new Node
 * @return New instance of Node
 */
node_t create_binary_tree_node(data_t objL_data);

/**
 * @brief Creation of BST's first node
 * @return Start node of BST 
 */
node_t create_binary_tree(void);

/**
 * @brief Insertion of node in binary tree
 * @param objP_root Instance of BST
 * @param objL_data Data object to be stored in new Node
 * @return Root node of binary tree
 */
node_t insert_into_binary_tree(node_t objP_root, data_t objL_data);

/**
 * @brief Search for a specific node
 * @param objP_root Instance of BST
 * @param objL_data Data object to find in BST
 * @return Node with required data or NULL otherwise
 */
node_t find_in_binary_tree(node_t objP_root, data_t objL_data);

/**
 * @brief Search for a Node's data with minimum value  
 * @param objP_root Instance of BST
 * @return Node with the smallest data value and NULL otherwise
 */
node_t min_in_binary_tree(node_t objP_root);

/**
 * @brief Deletion of a Node with specific data
 * @param objP_root Instance of BST
 * @param objL_data Data object to remove from BST
 * @return Root of BST without removed Node
 */
node_t remove_from_binary_tree(node_t objP_root, data_t objL_data);

/**
 * @brief Deletion of whole BST 
 * @param objP_root Instance of BST
 * @return Empty tree
 */
node_t delete_binary_tree(node_t objP_root);

#endif // BINARY_TREE_H
