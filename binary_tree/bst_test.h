/**
 * @file bst_test.h
 * @brief Testing of BST
 */

#ifndef BST_TEST_H
#define BST_TEST_H

#include "binary_tree.h"

/**
 * @brief Prints Point object
 * @param root Object of BST's data
 */
void print_node_data(data_obj_t data);

/**
 * @brief Prints all BST nodes
 * @param root Instance of BST
 */
void print_bst_inorder(node_obj_t root);

/**
 * @brief A general test of BST implementation 
 */
void test_bst(void);

#endif // BST_TEST_H
