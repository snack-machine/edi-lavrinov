/**
 * @file bst_test.c
 * @brief Testing of BST
 */

#include "bst_test.h"


void print_node_data(data_t objL_data)
{
    printf("[%d, %d, %d]; ", 
           objL_data.s32_x, objL_data.s32_y, objL_data.s32_z);
}

void print_bst_inorder(node_t objP_root)
{
    if (objP_root == NULL)
    {
        return;
    }

    print_bst_inorder(objP_root->objP_left);
    print_node_data(objP_root->objL_data);
    print_bst_inorder(objP_root->objP_right);
}

void test_bst(void)
{
    // Creation of test sample
    #define TEST_SAMPLE_SIZE 15
    data_t objP_test_data[TEST_SAMPLE_SIZE];
    int objP_test_data_x[TEST_SAMPLE_SIZE] = 
    {
        33, 21, 75, 90, -30,
        2, 87, -18, -75, -5,
        100, 1, 55, 43, 62
    };       


    // Creation of BST
    node_t objP_bst_root = NULL;


    // Inserting 15 nodes
    for (int i = 0; i < TEST_SAMPLE_SIZE; ++i)
    {
        objP_test_data[i].s32_x = objP_test_data_x[i];
        objP_test_data[i].s32_y = objP_test_data_x[i] + 10;
        objP_test_data[i].s32_z = objP_test_data_x[i] - 10;

        objP_bst_root = insert_into_binary_tree(objP_bst_root, objP_test_data[i]);
    }

    printf("Created BST: \n");
    print_bst_inorder(objP_bst_root);
    printf("\n");


    // Trying to find nodes
    node_t objP_search_result = find_in_binary_tree(objP_bst_root, objP_test_data[5]);
    printf("Search result: \n");
    print_node_data(objP_search_result->objL_data);
    printf("\n");

    objP_search_result = find_in_binary_tree(objP_bst_root, objP_test_data[12]);
    printf("Search result: \n");
    print_node_data(objP_search_result->objL_data);
    printf("\n");


    // Trying to find no-existen nodes
    data_t objL_non_existen_data;
    objL_non_existen_data.s32_x = 500;
    objL_non_existen_data.s32_y = 0;
    objL_non_existen_data.s32_z = 0;

    objP_search_result = find_in_binary_tree(objP_bst_root, objL_non_existen_data);
    printf("Search result: \n");
    
    if (objP_search_result == NULL)
    {
        printf("BST doesn't contain this node\n");
    }
    else
    {
        print_node_data(objP_search_result->objL_data);
        printf("\n");
    }


    // Trying to delete from BST
    objP_bst_root = remove_from_binary_tree(objP_bst_root, objP_test_data[5]);
    printf("Deletion result: \n");
    print_bst_inorder(objP_bst_root);
    printf("\n");

    objP_bst_root = remove_from_binary_tree(objP_bst_root, objP_test_data[0]);
    objP_bst_root = remove_from_binary_tree(objP_bst_root, objP_test_data[14]);
    printf("Deletion result: \n");
    print_bst_inorder(objP_bst_root);
    printf("\n");


    // Trying to delete no-existen nodes
    objP_bst_root = remove_from_binary_tree(objP_bst_root, objL_non_existen_data);
    printf("Deletion result: \n");
    print_bst_inorder(objP_bst_root);
    printf("\n");
    

    // Deletion of BST
    objP_bst_root = delete_binary_tree(objP_bst_root);
    printf("Empty BST: \n");
    print_bst_inorder(objP_bst_root);
    printf("\n");
}
