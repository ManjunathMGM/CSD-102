// Please do not print anything else
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Binary_search_node
{
    char node_value;
    struct Binary_search_node *parent_node;
    struct Binary_search_node *left;
    struct Binary_search_node *right;
} Binary_search_node;

// Functions Provided
int compareChars(char a, char b)
{ // if a>b then return 1, if a<b then return -1, else return 0
    if (a > b)
        return 1;
    else if (a < b)
        return -1;
    else
        return 0;
}
unsigned int max(unsigned int num1, unsigned int num2)
{
    return (num1 > num2) ? num1 : num2;
}

// Binary Search Tree ADT to be implemented
bool insert_bsearch_tree(Binary_search_node **root, char value)
{

    if (*root == NULL)
    {
        // Create a new node
        Binary_search_node *newNode = (Binary_search_node *)malloc(sizeof(Binary_search_node));
        newNode->node_value = value;
        newNode->parent_node = NULL;
        newNode->left = NULL;
        newNode->right = NULL;
        *root = newNode;
        return true;
    }
    int comparison = compareChars(value, (*root)->node_value);
    if (comparison == 0)
    {
        // Value is a duplicate, ignore it.
        return false;
    }
    else if (comparison < 0)
    {
        // Value is smaller, insert in the left subtree
        return insert_bsearch_tree(&((*root)->left), value);
    }
    else
    {
        // Value is larger, insert in the right subtree
        return insert_bsearch_tree(&((*root)->right), value);
    }
}
// Helper function to calculate the size of the binary search tree
unsigned int size_helper(Binary_search_node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return 1 + size_helper(root->left) + size_helper(root->right);
}
// Size of binary search tree
unsigned int size(Binary_search_node **root)
{
    return size_helper(*root);
}
// Helper function to calculate the height of the binary search tree
unsigned int height_helper(Binary_search_node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return 1 + max(height_helper(root->left), height_helper(root->right));
}
// Height of binary search tree
unsigned int height(Binary_search_node **root)
{
    if (*root == NULL)
    {
        return 0;
    }
    return max(height_helper((*root)->left), height_helper((*root)->right));
}

int main()
{
    // Please do not edit the main function
    Binary_search_node *root = NULL;
    // Enter valid characters in line to enter into binary search tree
    char temp;
    while (1)
    {
        temp = getchar();
        if (temp == '\n' || temp == '\0')
        {
            break;
        }
        if (temp >= 33 && temp <= 126)
        {
            insert_bsearch_tree(&root, temp);
        }
    }
    printf("Size= %d\n", size(&root));
    printf("Height= %d\n", height(&root));
    return 0;
}
