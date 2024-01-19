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
    Binary_search_node *new_node = (Binary_search_node *)malloc(sizeof(Binary_search_node));
    if (new_node == NULL)
    {
        return false;
    }

    new_node->node_value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent_node = NULL;

    if (*root == NULL)
    {
        *root = new_node;
    }
    else
    {
        Binary_search_node *current = *root;
        while (1)
        {
            int comparison = compareChars(value, current->node_value);
            if (comparison == 0)
            {

                free(new_node);
                return false;
            }
            else if (comparison < 0)
            {
                if (current->left == NULL)
                {
                    current->left = new_node;
                    new_node->parent_node = current;
                    break;
                }
                current = current->left;
            }
            else
            {
                if (current->right == NULL)
                {
                    current->right = new_node;
                    new_node->parent_node = current;
                    break;
                }
                current = current->right;
            }
        }
    }
    return true;
}

void print_pre_order(Binary_search_node **root)
{
    if (*root == NULL)
        return;

    printf("%c", (*root)->node_value);
    print_pre_order(&((*root)->left));
    print_pre_order(&((*root)->right));
}

void print_in_order(Binary_search_node **root)
{

    if (*root == NULL)
        return;

    static int f = 0;
    if (f == 0)
        printf("\n");
    f += 1;

    print_in_order(&((*root)->left));
    printf("%c", (*root)->node_value);
    print_in_order(&((*root)->right));
}

void print_post_order(Binary_search_node **root)
{

    if (*root == NULL)
        return;

    static int f = 0;
    if (f == 0)
        printf("\n");
    f += 1;
    print_post_order(&((*root)->left));
    print_post_order(&((*root)->right));
    printf("%c", (*root)->node_value);
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

    // print all orders
    print_pre_order(&root);
    print_in_order(&root);
    print_post_order(&root);
    return 0;
}
