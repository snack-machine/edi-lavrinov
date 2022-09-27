/**
 * @file unit_tests.c
 * @brief Unit Testing for BST
 */

#include "../source_code/binary_tree.h"

#include "CUnit/Basic.h"
#include <limits.h>


static node_t bst_root;


int init_suite1(void)
{
    bst_root = NULL;
    return 0;
}

int clean_suite1(void)
{
    bst_root = NULL;
    return 0;
}

void test_compare_data_t(void)
{
    data_t objL_data1;
    data_t objL_data2;

    // Testing overflow of integers
    objL_data1.s32_x = INT_MAX;
    objL_data2.s32_x = INT_MAX + 1; 
    CU_ASSERT(eFirstIsGreater == compare_data_t(objL_data1, objL_data2));

    // Testing underflow of integers
    objL_data1.s32_x = INT_MIN;
    objL_data2.s32_x = INT_MIN - 1; 
    CU_ASSERT(eSecondIsGreater == compare_data_t(objL_data1, objL_data2));
    
    // Testing general usage

    // First is greater
    objL_data1.s32_x = 100;
    objL_data2.s32_x = -100;
    CU_ASSERT(eFirstIsGreater == compare_data_t(objL_data1, objL_data2));

    // Second is greater
    objL_data1.s32_x = -200;
    objL_data2.s32_x = 200;
    CU_ASSERT(eSecondIsGreater == compare_data_t(objL_data1, objL_data2));

    // First equals the second
    objL_data1.s32_x = 300;
    objL_data2.s32_x = 300;
    CU_ASSERT(eEqual == compare_data_t(objL_data1, objL_data2));
}

void test_create_binary_tree_node(void)
{
    // Checking if memory was allocated
    data_t objL_data;
    objL_data.s32_x = 100;
    CU_ASSERT(NULL != create_binary_tree_node(objL_data));
}

void test_insert_into_binary_tree(void)
{
    // Inserting of the first Node 
    data_t objL_data1;
    objL_data1.s32_x = 50;
    bst_root = insert_into_binary_tree(bst_root, objL_data1);
    CU_ASSERT(NULL != bst_root);
    
    // Inserting Node with a repeated key (should be ignored)
    bst_root = insert_into_binary_tree(bst_root, objL_data1);
    CU_ASSERT(NULL == bst_root->objP_left);
    CU_ASSERT(NULL == bst_root->objP_right);

    // Inserting Node to left subtree
    data_t objL_data2;
    objL_data2.s32_x = -10;
    bst_root = insert_into_binary_tree(bst_root, objL_data2);
    CU_ASSERT(NULL != bst_root->objP_left);

    // Inserting Node to right subtree
    data_t objL_data3;
    objL_data3.s32_x = 80;
    bst_root = insert_into_binary_tree(bst_root, objL_data3);
    CU_ASSERT(NULL != bst_root->objP_right);
}

void test_find_in_binary_tree(void)
{
    // Search for an existing element
    data_t objL_data1;
    objL_data1.s32_x = 50;
    CU_ASSERT(NULL != find_in_binary_tree(bst_root, objL_data1));
    
    // Search for a non-existent element
    data_t objL_data2;
    objL_data2.s32_x = 222;
    CU_ASSERT(NULL == find_in_binary_tree(bst_root, objL_data2));

    // Search in an empty BST
    node_t objP_bst = NULL;
    CU_ASSERT(NULL == find_in_binary_tree(objP_bst, objL_data2));
}

void test_min_in_binary_tree(void)
{
    // Searching the minimum element in an empty BST
    node_t objP_bst = NULL;
    CU_ASSERT(NULL == min_in_binary_tree(objP_bst));

    // Searching the minimum element
    node_t objP_result = min_in_binary_tree(bst_root);
    CU_ASSERT(-10 == objP_result->objL_data.s32_x);

    // Checking that minimum node is in the left subtree
    CU_ASSERT(-10 == bst_root->objP_left->objL_data.s32_x);
}

void test_remove_from_binary_tree(void)
{
    // Remove from an empty BST
    node_t objP_bst = NULL;
    data_t objL_data;
    objL_data.s32_x = 50;
    CU_ASSERT(NULL == remove_from_binary_tree(objP_bst, objL_data));

    // Remove from the left subtree
    objL_data.s32_x = -10;
    bst_root = remove_from_binary_tree(bst_root, objL_data);
    CU_ASSERT(NULL == bst_root->objP_left);

    // Remove from the right subtree
    objL_data.s32_x = 80;
    bst_root = remove_from_binary_tree(bst_root, objL_data);
    CU_ASSERT(NULL == bst_root->objP_right);

    // Remove last Node in BST
    objL_data.s32_x = 50;
    bst_root = remove_from_binary_tree(bst_root, objL_data);
    CU_ASSERT(NULL == bst_root);
}

void test_delete_binary_tree(void)
{
    // Deletion of an empty BST
    node_t objP_bst = NULL;
    CU_ASSERT(NULL == delete_binary_tree(objP_bst));

    // Deletion of a BST
    CU_ASSERT(NULL == delete_binary_tree(bst_root));
}


int main()
{
    CU_pSuite objP_suite = NULL;
    if (CUE_SUCCESS != CU_initialize_registry())
    {
        return CU_get_error();
    }

    objP_suite = CU_add_suite("suite_1", init_suite1, clean_suite1);
    if (NULL == objP_suite) 
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Adding tests to a suite 
    if ((NULL == CU_add_test(objP_suite, "Data comparison function", test_compare_data_t))         ||
        (NULL == CU_add_test(objP_suite, "Node creation function", test_create_binary_tree_node))  ||
        (NULL == CU_add_test(objP_suite, "Node insertion function", test_insert_into_binary_tree)) ||
        (NULL == CU_add_test(objP_suite, "Node search function", test_find_in_binary_tree))        ||
        (NULL == CU_add_test(objP_suite, "Min Node search function", test_min_in_binary_tree))     ||
        (NULL == CU_add_test(objP_suite, "Removing Nodes function", test_remove_from_binary_tree)) ||
        (NULL == CU_add_test(objP_suite, "BST deletion function", test_delete_binary_tree)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
