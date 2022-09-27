/**
 * @file binary_tree.c
 * @brief Simple Binary Search Tree implementation
 */

#include "binary_tree.h"


enum ComparisonResult compare_data_t(data_t objL_first, data_t objL_second)
{
    if (objL_first.s32_x > objL_second.s32_x)
    {
        return eFirstIsGreater;
    }
    else if (objL_first.s32_x < objL_second.s32_x)
    {
        return eSecondIsGreater;
    }
    else
    {
        return eEqual;
    }
}

node_t create_binary_tree_node(data_t objL_data)
{
    node_t objP_node = (node_t)malloc(sizeof(struct Node));
    objP_node->objL_data = objL_data;
    objP_node->objP_left = NULL;
    objP_node->objP_right = NULL;
    return objP_node;
}

node_t insert_into_binary_tree(node_t objP_root, data_t objL_data)
{
    if (objP_root == NULL)
    {
        objP_root = create_binary_tree_node(objL_data);
    }
    else if (compare_data_t(objL_data, objP_root->objL_data) == eSecondIsGreater)
    {
        objP_root->objP_left = insert_into_binary_tree(objP_root->objP_left, objL_data);
    }
    else if (compare_data_t(objL_data, objP_root->objL_data) == eFirstIsGreater)
    {
        objP_root->objP_right = insert_into_binary_tree(objP_root->objP_right, objL_data);
    }
    
    return objP_root;
}

node_t find_in_binary_tree(node_t objP_root, data_t objL_data)
{
    if (objP_root == NULL)
    {
        return objP_root;
    }
    else if (compare_data_t(objL_data, objP_root->objL_data) == eSecondIsGreater)
    {
        return find_in_binary_tree(objP_root->objP_left, objL_data);
    }
    else if (compare_data_t(objL_data, objP_root->objL_data) == eFirstIsGreater)
    {
        return find_in_binary_tree(objP_root->objP_right, objL_data);
    }
    else
    {
        return objP_root;
    }
}

node_t min_in_binary_tree(node_t objP_root)
{
    if (objP_root == NULL)
    {
        return NULL;
    }
    else if (objP_root->objP_left == NULL)
    {
        return objP_root;
    }
    else
    {
        return min_in_binary_tree(objP_root->objP_left);
    }
}

node_t remove_from_binary_tree(node_t objP_root, data_t objL_data)
{
    node_t objP_temp;

    if (objP_root == NULL)
    {
        return NULL;
    }
    else if (compare_data_t(objL_data, objP_root->objL_data) == eSecondIsGreater)
    {
        objP_root->objP_left = remove_from_binary_tree(objP_root->objP_left, objL_data);
    }
    else if (compare_data_t(objL_data, objP_root->objL_data) == eFirstIsGreater)
    {
        objP_root->objP_right = remove_from_binary_tree(objP_root->objP_right, objL_data);
    }
    else if (objP_root->objP_left && objP_root->objP_right)
    {
        objP_temp = min_in_binary_tree(objP_root->objP_right);
        objP_root->objL_data = objP_temp->objL_data;
        objP_root->objP_right = remove_from_binary_tree(objP_root->objP_right, objP_root->objL_data);
    }
    else
    {
        objP_temp = objP_root;

        if (objP_root->objP_left == NULL)
        {
            objP_root = objP_root->objP_right;
        }
        else if (objP_root->objP_right == NULL)
        {
            objP_root = objP_root->objP_left;
        }

        free(objP_temp);
    }

    return objP_root;
}

node_t delete_binary_tree(node_t objP_root)
{
    if (objP_root != NULL)
    {
        delete_binary_tree(objP_root->objP_left);
        delete_binary_tree(objP_root->objP_right);
        free(objP_root);
    }

    return NULL;
}
