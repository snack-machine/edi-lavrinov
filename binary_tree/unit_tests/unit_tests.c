/**
 * @file unit_tests.c
 * @brief Unit Testing for BST
 */

#include "../source_code/binary_tree.h"

#include "CUnit/Basic.h"
#include <limits.h>



// Testing of compare_data_t

int init_compare_data_t_suite(void)
{
    return 0;
}

int clean_compare_data_t_suite(void)
{
    return 0;
}

void test_compare_max_value_of_integer(void)
{
    data_t objL_data1;
    data_t objL_data2;
    objL_data1.s32_x = INT_MAX;
    objL_data2.s32_x = INT_MAX - 1; 

    CU_ASSERT_EQUAL(compare_data_t(objL_data1, objL_data2), eFirstIsGreater);
}

void test_compare_min_value_of_integer(void)
{
    data_t objL_data1;
    data_t objL_data2;
    objL_data1.s32_x = INT_MIN;
    objL_data2.s32_x = INT_MIN + 1; 

    CU_ASSERT_EQUAL(compare_data_t(objL_data1, objL_data2), eSecondIsGreater);
}

void test_compare_integers_with_equal_values(void)
{
    data_t objL_data1;
    data_t objL_data2;
    objL_data1.s32_x = 1000;
    objL_data2.s32_x = 1000;

    CU_ASSERT_EQUAL(compare_data_t(objL_data1, objL_data2), eEqual);
}



// Testing of create_binary_tree_node

int init_create_binary_tree_node_suite(void)
{
    return 0;
}

int clean_create_binary_tree_node_suite(void)
{
    return 0;
}

void test_create_valid_node(void)
{
    data_t objL_data;
    objL_data.s32_x = INT_MAX;
    node_t objL_node = create_binary_tree_node(objL_data);

    CU_ASSERT_PTR_NULL(objL_node);
    CU_ASSERT_PTR_NULL(objL_node->objP_left);
    CU_ASSERT_PTR_NULL(objL_node->objP_right);
    CU_ASSERT_EQUAL(compare_data_t(objL_data, objL_node->objL_data), eEqual);
}



// Testing of insert_into_binary_tree

static node_t bst_set_1[4];

int init_insert_into_binary_tree_suite(void)
{
    bst_set_1[0] = NULL;
    bst_set_1[1] = NULL;
    bst_set_1[2] = NULL;
    bst_set_1[3] = NULL;

    return 0;
}

int clean_insert_into_binary_tree_suite(void)
{
    delete_binary_tree(bst_set_1[0]);
    delete_binary_tree(bst_set_1[1]);
    delete_binary_tree(bst_set_1[2]);
    delete_binary_tree(bst_set_1[3]);

    return 0;
}

void test_insert_first_node(void)
{
    node_t objP_root = bst_set_1[0];
    data_t objL_data;
    objL_data.s32_x = 1000;
    objP_root = insert_into_binary_tree(objP_root, objL_data);
    
    CU_ASSERT_PTR_NOT_NULL(objP_root);
    CU_ASSERT_PTR_NULL(objP_root->objP_left);
    CU_ASSERT_PTR_NULL(objP_root->objP_right);   
}

void test_insert_node_with_repeated_key(void)
{
    node_t objP_root = bst_set_1[1];
    data_t objL_data;
    objL_data.s32_x = 1000;

    objP_root = insert_into_binary_tree(objP_root, objL_data);
    objP_root = insert_into_binary_tree(objP_root, objL_data);
    
    CU_ASSERT_PTR_NULL(objP_root->objP_left);
    CU_ASSERT_PTR_NULL(objP_root->objP_right);  
}

void test_insert_node_to_left_subtree(void)
{
    node_t objP_root = bst_set_1[2];

    data_t objL_data1;
    objL_data1.s32_x = 1000;
    objP_root = insert_into_binary_tree(objP_root, objL_data1);

    data_t objL_data2;
    objL_data2.s32_x = 500;
    objP_root = insert_into_binary_tree(objP_root, objL_data2);

    CU_ASSERT_PTR_NOT_NULL(objP_root->objP_left);
    CU_ASSERT_PTR_NULL(objP_root->objP_right);
}

void test_insert_node_to_right_subtree(void)
{
    node_t objP_root = bst_set_1[3];

    data_t objL_data1;
    objL_data1.s32_x = 1000;
    objP_root = insert_into_binary_tree(objP_root, objL_data1);

    data_t objL_data2;
    objL_data2.s32_x = 1500;
    objP_root = insert_into_binary_tree(objP_root, objL_data2);

    CU_ASSERT_PTR_NOT_NULL(objP_root->objP_right);
    CU_ASSERT_PTR_NULL(objP_root->objP_left);
}



// Testing of find_in_binary_tree

static node_t bst_set_2[3];

int init_find_in_binary_tree_suite(void)
{
    bst_set_2[0] = NULL;
    bst_set_2[1] = NULL;
    bst_set_2[2] = NULL;

    return 0;
}

int clean_find_in_binary_tree_suite(void)
{
    delete_binary_tree(bst_set_2[0]);
    delete_binary_tree(bst_set_2[1]);
    delete_binary_tree(bst_set_2[2]);

    return 0;
}

void test_search_in_empty_bst(void)
{
    node_t objP_root = bst_set_2[0];    
    data_t objL_data;
    objL_data.s32_x = 1000;

    CU_ASSERT_PTR_NULL(find_in_binary_tree(objP_root, objL_data));
}

void test_search_of_existing_node(void)
{
    node_t objP_root = bst_set_2[1];

    data_t objL_data1;
    objL_data1.s32_x = 1000;
    objP_root = insert_into_binary_tree(objP_root, objL_data1);

    data_t objL_data2;
    objL_data2.s32_x = 1500;
    objP_root = insert_into_binary_tree(objP_root, objL_data2);

    data_t objL_data3;
    objL_data3.s32_x = 500;
    objP_root = insert_into_binary_tree(objP_root, objL_data3);

    CU_ASSERT_PTR_NOT_NULL(find_in_binary_tree(objP_root, objL_data1));
    CU_ASSERT_PTR_NOT_NULL(find_in_binary_tree(objP_root, objL_data2));
    CU_ASSERT_PTR_NOT_NULL(find_in_binary_tree(objP_root, objL_data3));
}

void test_search_of_non_existent_node(void)
{
    node_t objP_root = bst_set_2[2];

    data_t objL_data1;
    objL_data1.s32_x = 1000;
    objP_root = insert_into_binary_tree(objP_root, objL_data1);

    data_t objL_data2;
    objL_data2.s32_x = 1500;
    objP_root = insert_into_binary_tree(objP_root, objL_data2);

    data_t objL_data3;
    objL_data3.s32_x = 500;
    objP_root = insert_into_binary_tree(objP_root, objL_data3);

    data_t objL_data4;
    objL_data4.s32_x = -1000;

    CU_ASSERT_PTR_NULL(find_in_binary_tree(objP_root, objL_data4));
}



// Testing of min_in_binary_tree

static node_t bst_set_3[2];

int init_min_in_binary_tree_suite(void)
{
    bst_set_3[0] = NULL;
    bst_set_3[1] = NULL;

    return 0;
}

int clean_min_in_binary_tree_suite(void)
{
    delete_binary_tree(bst_set_3[0]);
    delete_binary_tree(bst_set_3[1]);

    return 0;
}

void test_find_minimum_in_empty_tree(void)
{
    node_t objP_root = bst_set_3[0];

    CU_ASSERT_PTR_NULL(min_in_binary_tree(objP_root));
}

void test_find_minimum(void)
{
    node_t objP_root = bst_set_3[1];

    data_t objL_data1;
    objL_data1.s32_x = 1000;
    objP_root = insert_into_binary_tree(objP_root, objL_data1);

    data_t objL_data2;
    objL_data2.s32_x = 1500;
    objP_root = insert_into_binary_tree(objP_root, objL_data2);

    data_t objL_data3;
    objL_data3.s32_x = 500;
    objP_root = insert_into_binary_tree(objP_root, objL_data3);

    node_t objP_result = min_in_binary_tree(objP_root);

    CU_ASSERT_EQUAL(compare_data_t(objP_result->objL_data, objL_data3), eEqual);
    // Checking that minimum node is in the left subtree
    CU_ASSERT_EQUAL(compare_data_t(objP_result->objL_data, objP_root->objP_left->objL_data), eEqual);
}



// Testing of remove_from_binary_tree

static node_t bst_set_4[4];

int init_remove_from_binary_tree_suite(void)
{
    bst_set_4[0] = NULL;
    bst_set_4[1] = NULL;
    bst_set_4[2] = NULL;
    bst_set_4[3] = NULL;

    return 0;
}

int clean_remove_from_binary_tree_suite(void)
{
    delete_binary_tree(bst_set_4[0]);
    delete_binary_tree(bst_set_4[1]);
    delete_binary_tree(bst_set_4[2]);
    delete_binary_tree(bst_set_4[3]);

    return 0;
}

void test_remove_from_empty_tree(void)
{
    node_t objP_root = bst_set_4[0];
    data_t objL_data;
    objL_data.s32_x = 500;
    objP_root = remove_from_binary_tree(objP_root, objL_data);

    CU_ASSERT_PTR_NULL(objP_root);
}

void test_remove_from_left_subtree(void)
{
    node_t objP_root = bst_set_4[1];

    data_t objL_data1;
    objL_data1.s32_x = 1000;
    objP_root = insert_into_binary_tree(objP_root, objL_data1);

    data_t objL_data2;
    objL_data2.s32_x = 1500;
    objP_root = insert_into_binary_tree(objP_root, objL_data2);

    data_t objL_data3;
    objL_data3.s32_x = 500;
    objP_root = insert_into_binary_tree(objP_root, objL_data3);

    objP_root = remove_from_binary_tree(objP_root, objL_data3);

    CU_ASSERT_PTR_NULL(objP_root->objP_left);
}

void test_remove_from_right_subtree(void)
{
    node_t objP_root = bst_set_4[2];

    data_t objL_data1;
    objL_data1.s32_x = 1000;
    objP_root = insert_into_binary_tree(objP_root, objL_data1);

    data_t objL_data2;
    objL_data2.s32_x = 1500;
    objP_root = insert_into_binary_tree(objP_root, objL_data2);

    data_t objL_data3;
    objL_data3.s32_x = 500;
    objP_root = insert_into_binary_tree(objP_root, objL_data3);

    objP_root = remove_from_binary_tree(objP_root, objL_data2);

    CU_ASSERT_PTR_NULL(objP_root->objP_right);
}

void test_remove_last_node(void)
{
    node_t objP_root = bst_set_4[3];

    data_t objL_data;
    objL_data.s32_x = 1000;
    objP_root = insert_into_binary_tree(objP_root, objL_data);
    objP_root = remove_from_binary_tree(objP_root, objL_data);

    CU_ASSERT_PTR_NULL(objP_root);
}



// Testing of delete_binary_tree

static node_t bst_set_5[2];

int init_delete_binary_tree_suite(void)
{
    bst_set_5[0] = NULL;
    bst_set_5[1] = NULL;
    
    return 0;
}

int clean_delete_binary_tree_suite(void)
{
    delete_binary_tree(bst_set_5[0]);
    delete_binary_tree(bst_set_5[1]);

    return 0;
}

void test_delete_empty_binary_tree(void)
{
    node_t objP_root = bst_set_5[0];

    CU_ASSERT_PTR_NULL(delete_binary_tree(objP_root));
}

void test_delete_binary_tree(void)
{
    node_t objP_root = bst_set_5[1];

    data_t objL_data1;
    objL_data1.s32_x = 1000;
    objP_root = insert_into_binary_tree(objP_root, objL_data1);

    data_t objL_data2;
    objL_data2.s32_x = 1500;
    objP_root = insert_into_binary_tree(objP_root, objL_data2);

    data_t objL_data3;
    objL_data3.s32_x = 500;
    objP_root = insert_into_binary_tree(objP_root, objL_data3);

    delete_binary_tree(objP_root);

    CU_ASSERT_PTR_NULL(objP_root);
    CU_ASSERT_PTR_NULL(objP_root->objP_left);
    CU_ASSERT_PTR_NULL(objP_root->objP_right);
}





int main()
{
    // Initialization of test suites

    if (CUE_SUCCESS != CU_initialize_registry())
    {
        return CU_get_error();
    }

    CU_pSuite objP_TS_compare_data_t = CU_add_suite("comparing data_t", 
                                                    init_compare_data_t_suite, 
                                                    clean_compare_data_t_suite);

    CU_pSuite objP_TS_create_binary_tree_node = CU_add_suite("creation of bst node", 
                                                             init_create_binary_tree_node_suite, 
                                                             clean_create_binary_tree_node_suite);

    CU_pSuite objP_TS_insert_into_binary_tree = CU_add_suite("insertion into bst", 
                                                             init_insert_into_binary_tree_suite, 
                                                             clean_insert_into_binary_tree_suite);

    CU_pSuite objP_TS_find_in_binary_tree = CU_add_suite("search in bst", 
                                                         init_find_in_binary_tree_suite, 
                                                         clean_find_in_binary_tree_suite);

    CU_pSuite objP_TS_min_in_binary_tree = CU_add_suite("get min value in bst", 
                                                        init_min_in_binary_tree_suite, 
                                                        clean_min_in_binary_tree_suite);

    CU_pSuite objP_TS_remove_from_binary_tree = CU_add_suite("remove from bst", 
                                                             init_remove_from_binary_tree_suite, 
                                                             clean_remove_from_binary_tree_suite);

    CU_pSuite objP_TS_delete_binary_tree = CU_add_suite("delete bst", 
                                                        init_delete_binary_tree_suite, 
                                                        clean_delete_binary_tree_suite);

    if (NULL == objP_TS_compare_data_t          ||
        NULL == objP_TS_create_binary_tree_node ||
        NULL == objP_TS_insert_into_binary_tree ||
        NULL == objP_TS_find_in_binary_tree     ||
        NULL == objP_TS_min_in_binary_tree      ||
        NULL == objP_TS_remove_from_binary_tree ||
        NULL == objP_TS_delete_binary_tree)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }



    // Adding tests to test suites

    if (NULL == CU_add_test(objP_TS_compare_data_t, "compare with max", test_compare_max_value_of_integer) ||
        NULL == CU_add_test(objP_TS_compare_data_t, "compare with min", test_compare_min_value_of_integer) ||
        NULL == CU_add_test(objP_TS_compare_data_t, "compare equal", test_compare_integers_with_equal_values))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(objP_TS_create_binary_tree_node, "create node", test_create_valid_node))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == CU_add_test(objP_TS_insert_into_binary_tree, "insert first node", test_insert_first_node)                   ||
        NULL == CU_add_test(objP_TS_insert_into_binary_tree, "insert repeated node", test_insert_node_with_repeated_key)    ||
        NULL == CU_add_test(objP_TS_insert_into_binary_tree, "insert node to the left", test_insert_node_to_left_subtree)   ||
        NULL == CU_add_test(objP_TS_insert_into_binary_tree, "insert node to the right", test_insert_node_to_right_subtree))
    {
        CU_cleanup_registry();
        return CU_get_error();       
    }

    if (NULL == CU_add_test(objP_TS_find_in_binary_tree, "search in empty", test_search_in_empty_bst) ||
        NULL == CU_add_test(objP_TS_find_in_binary_tree, "search", test_search_of_existing_node)      ||
        NULL == CU_add_test(objP_TS_find_in_binary_tree, "search of non-existent", test_search_of_non_existent_node))
    {
        CU_cleanup_registry();
        return CU_get_error();   
    }

    if (NULL == CU_add_test(objP_TS_min_in_binary_tree, "find min in empty bst", test_find_minimum_in_empty_tree) ||
        NULL == CU_add_test(objP_TS_min_in_binary_tree, "find min", test_find_minimum))
    {
        CU_cleanup_registry();
        return CU_get_error(); 
    }

    if (NULL == CU_add_test(objP_TS_remove_from_binary_tree, "remove from empty", test_remove_from_empty_tree)    || 
        NULL == CU_add_test(objP_TS_remove_from_binary_tree, "remove from left", test_remove_from_left_subtree)   ||
        NULL == CU_add_test(objP_TS_remove_from_binary_tree, "remove from right", test_remove_from_right_subtree) ||
        NULL == CU_add_test(objP_TS_remove_from_binary_tree, "remove last node", test_remove_last_node))
    {
        CU_cleanup_registry();
        return CU_get_error();        
    }

    if (NULL == CU_add_test(objP_TS_delete_binary_tree, "delete empty", test_delete_empty_binary_tree) ||
        NULL == CU_add_test(objP_TS_delete_binary_tree, "delete bst", test_delete_binary_tree))
    {
        CU_cleanup_registry();
        return CU_get_error();    
    }
        


    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}
