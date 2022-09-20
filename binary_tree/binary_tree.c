/**
 * @file binary_tree.c
 * @brief Simple Binary Search Tree implementation
 */

#include "binary_tree.h"


int compare_data_obj_t(data_obj_t first, data_obj_t second)
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
  node_obj_t node = (node_obj_t)malloc(sizeof(node_obj_t));
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
    return create_binary_tree_node(data);
  }
  else if (compare_data_obj_t(data, root->data) == eFirstIsGreater)
  {
    root->right = insert_into_binary_tree(root->right, data);
  }
  else
  {
    root->left = insert_into_binary_tree(root->left, data);
  }

  return root;
}

node_obj_t find_in_binary_tree(node_obj_t root, data_obj_t data)
{
  if (root == NULL || compare_data_obj_t(root->data, data) == eEqual)
  {
    return root;
  }
  else if (compare_data_obj_t(root->data, data) == eFirstIsGreater)
  {
    return find_in_binary_tree(root->right, data);
  }
  else
  {
    return find_in_binary_tree(root->left, data);
  }
}

node_obj_t remove_from_binary_tree(node_obj_t root, data_obj_t data)
{
  if (root == NULL)
  {
    return NULL;
  }

  if (compare_data_obj_t(data, root->data) == eFirstIsGreater)
  {
    root->right = remove_from_binary_tree(root->right, data);
  }
  else if (compare_data_obj_t(data, root->data) == eSecondIsGreater)
  {
    root->left = remove_from_binary_tree(root->left, data);
  }
  else
  {
    if (root->left == NULL && root->right == NULL)
    {
      free(root);
      return NULL;
    }
    else if(root->left == NULL || root->right == NULL)
    {
      node_obj_t temp;
      
      if(root->left == NULL)
      {
        temp = root->right;
      }
      else
      {
        temp = root->left;
      }
                
      free(root);
      return temp;
    }
    else
    {
      node_obj_t temp = find_minimum(root->right);
      root->data = temp->data;
      root->right = remove_from_binary_tree(root->right, temp->data);
    }
  }
}

void delete_binary_tree(node_obj_t root)
{
  if (root != NULL)
  {
    delete_binary_tree(root->left);
    delete_binary_tree(root->right);
    free(root);
  }
}
