/**
 * @file bst_test.c
 * @brief Testing of BST
 */

#include "bst_test.h"


void print_node_data(data_obj_t data)
{
    printf("[%d, %d, %d]; ", 
           data.s32_x, data.s32_y, data.s32_z);
}

void print_bst_inorder(node_obj_t root)
{
    if (root == NULL)
    {
        return;
    }

    print_bst_inorder(root->left);
    print_node_data(root->data);
    print_bst_inorder(root->right);
}

void test_bst(void)
{
    // Creation of test sample
    #define TEST_SAMPLE_SIZE 15
    data_obj_t test_data[TEST_SAMPLE_SIZE];
    int test_data_x[TEST_SAMPLE_SIZE] = 
    {
        33, 21, 75, 90, -30,
        2, 87, -18, -75, -5,
        100, 1, 55, 43, 62
    };       


    // Creation of BST
    node_obj_t bst_root = create_binary_tree();
               
    bst_root = NULL;


    // Inserting 15 nodes
    for (int i = 0; i < TEST_SAMPLE_SIZE; ++i)
    {
        test_data[i].s32_x = test_data_x[i];
        test_data[i].s32_y = test_data_x[i] + 10;
        test_data[i].s32_z = test_data_x[i] - 10;

        bst_root = insert_into_binary_tree(bst_root, test_data[i]);
    }

    printf("Created BST: \n");
    print_bst_inorder(bst_root);
    printf("\n");


    // Trying to find nodes
    node_obj_t search_result = find_in_binary_tree(bst_root, test_data[5]);
    printf("Search result: \n");
    print_node_data(search_result->data);
    printf("\n");

    search_result = find_in_binary_tree(bst_root, test_data[12]);
    printf("Search result: \n");
    print_node_data(search_result->data);
    printf("\n");


    // Trying to find no-existen nodes
    data_obj_t non_existen_data;
    non_existen_data.s32_x = 500;
    non_existen_data.s32_y = 0;
    non_existen_data.s32_z = 0;

    search_result = find_in_binary_tree(bst_root, non_existen_data);
    printf("Search result: \n");
    
    if (search_result == NULL)
    {
        printf("BST doesn't contain this node\n");
    }
    else
    {
        print_node_data(search_result->data);
        printf("\n");
    }


    // Trying to delete from BST
    bst_root = remove_from_binary_tree(bst_root, test_data[5]);
    printf("Deletion result: \n");
    print_bst_inorder(bst_root);
    printf("\n");

    bst_root = remove_from_binary_tree(bst_root, test_data[0]);
    bst_root = remove_from_binary_tree(bst_root, test_data[14]);
    printf("Deletion result: \n");
    print_bst_inorder(bst_root);
    printf("\n");


    // Trying to delete no-existen nodes
    bst_root = remove_from_binary_tree(bst_root, non_existen_data);
    printf("Deletion result: \n");
    print_bst_inorder(bst_root);
    printf("\n");
    

    // Deletion of BST
    bst_root = delete_binary_tree(bst_root);
    printf("Empty BST: \n");
    print_bst_inorder(bst_root);
    printf("\n");
}
