/**
 * @file bst_test.h
 * @brief Testing of BST
 */

#ifndef BST_TEST_H
#define BST_TEST_H

#include "binary_tree.h"

/**
 * @brief Prints Point object
 * @param objL_data Object of BST's data
 */
void print_node_data(data_t objL_data);

/**
 * @brief Prints all BST nodes
 * @param objP_root Instance of BST
 */
void print_bst_inorder(node_t objP_root);

/**
 * @brief A general test of BST implementation 
 */
void test_bst(void);

#endif // BST_TEST_H
