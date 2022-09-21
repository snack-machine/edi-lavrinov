/**
 * @file binary_tree.c
 * @brief Simple Binary Search Tree implementation
 */

#include "binary_tree.h"


enum ComparisonResult compare_data_obj_t(data_obj_t first, data_obj_t second)
{
    if (first.s32_x > second.s32_x)
    {
        return eFirstIsGreater;
    }
    else if (first.s32_x < second.s32_x)
    {
        return eSecondIsGreater;
    }
    else
    {
        return eEqual;
    }
}

node_obj_t create_binary_tree_node(data_obj_t data)
{
    node_obj_t node = (node_obj_t)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

node_obj_t create_binary_tree(data_obj_t data)
{
    return create_binary_tree_node(data);
}

node_obj_t insert_into_binary_tree(node_obj_t root, data_obj_t data)
{
    if (root == NULL)
    {
        root = create_binary_tree_node(data);
    }
    else if (compare_data_obj_t(data, root->data) == eSecondIsGreater)
    {
        root->left = insert_into_binary_tree(root->left, data);
    }
    else if (compare_data_obj_t(data, root->data) == eFirstIsGreater)
    {
        root->right = insert_into_binary_tree(root->right, data);
    }

    return root;
}

node_obj_t find_in_binary_tree(node_obj_t root, data_obj_t data)
{
    if (root == NULL)
    {
        return root;
    }
    else if (compare_data_obj_t(data, root->data) == eSecondIsGreater)
    {
        return find_in_binary_tree(root->left, data);
    }
    else if (compare_data_obj_t(data, root->data) == eFirstIsGreater)
    {
        return find_in_binary_tree(root->right, data);
    }
    else
    {
        return root;
    }
}

node_obj_t min_in_binary_tree(node_obj_t root)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (root->left == NULL)
    {
        return root;
    }
    else
    {
        return min_in_binary_tree(root->left);
    }
}

node_obj_t remove_from_binary_tree(node_obj_t root, data_obj_t data)
{
    node_obj_t temp;

    if (root == NULL)
    {
        return NULL;
    }
    else if (compare_data_obj_t(data, root->data) == eSecondIsGreater)
    {
        root->left = remove_from_binary_tree(root->left, data);
    }
    else if (compare_data_obj_t(data, root->data) == eFirstIsGreater)
    {
        root->right = remove_from_binary_tree(root->right, data);
    }
    else if (root->left && root->right)
    {
        temp = min_in_binary_tree(root->right);
        root->data = temp->data;
        root->right = remove_from_binary_tree(root->right, root->data);
    }
    else
    {
        temp = root;

        if (root->left == NULL)
        {
            root = root->right;
        }
        else if (root->right == NULL)
        {
            root = root->left;
        }

        free(temp);
    }
}

node_obj_t delete_binary_tree(node_obj_t root)
{
    if (root != NULL)
    {
        delete_binary_tree(root->left);
        delete_binary_tree(root->right);
        free(root);
    }

    return NULL;
}
