
#include <stdio.h>
#include <stdlib.h>

// An AVL tree node
typedef struct Node
{
    char key;
    struct Node *left;
    struct Node *right;
    struct Node *par;
    int height;
} Node;

// A utility function to get height of the tree
int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b) ? a : b;
}

/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
Node *newNode(char key)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->par = NULL;
    node->height = 1;
    return (node);
}

// A utility function to right rotate subtree rooted with y
Node *LL_Rotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    if (T2)
        T2->par = y;

    x->par = y->par;
    y->par = x;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// A utility function to left rotate subtree rooted with x
Node *RR_Rotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    if (T2)
        T2->par = x;

    y->par = x->par;
    x->par = y;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Get Balance factor of node N
int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Node *insert(Node *node, char key)
{

    if (node == NULL)

        return newNode(key);

    if (key < node->key)
    {
        node->left = insert(node->left, key);
        node->left->par = node;
    }
    else if (key > node->key)
    {
        node->right = insert(node->right, key);
        node->right->par = node;
    }
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return LL_Rotate(node);

    if (balance < -1 && key > node->right->key)
        return RR_Rotate(node);

    if (balance > 1 && key > node->left->key)
    {
        node->left = RR_Rotate(node->left);
        return LL_Rotate(node);
    }

    if (balance < -1 && key < node->right->key)
    {
        node->right = LL_Rotate(node->right);
        return RR_Rotate(node);
    }

    return node;
}

/* Given a non-empty binary search tree, return the
node with minimum key value found in that tree.
Note that the entire tree does not need to be
searched. */
Node *front(Node *node)
{
    if (node->left != NULL)
        return front(node->left);
    return node;
}

// Recursive function to delete a node with given key
// from subtree with given root. It returns root of
// the modified subtree.
Node *deleteNode(Node *root, char key)
{

    if (root == NULL)
        return root;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else
    {
        if ((root->left == NULL) || (root->right == NULL))
        {
            struct Node *temp = root->left ? root->left : root->right;
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else
        {
            struct Node *temp = front(root->right);
            root->key = temp->key;

            root->right = deleteNode(root->right, temp->key);
        }
    }
    if (root == NULL)
        return root;
    root->height = 1 + max(height(root->left),
                           height(root->right));
    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0)
        return LL_Rotate(root);
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = RR_Rotate(root->left);
        return LL_Rotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return RR_Rotate(root);
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = LL_Rotate(root->right);
        return RR_Rotate(root);
    }

    return root;
}

// A utility function to print preorder traversal of
// the tree.
void preOrder(Node *root)
{
    if (root != NULL)
    {
        printf("%c", root->key);
        preOrder(root->left);
        preOrder(root->right);
        if (root->par == NULL)
        {
            printf("\n");
        }
    }
}

void inOrder(Node *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        printf("%c", root->key);
        inOrder(root->right);
        if (root->par == NULL)
        {
            printf("\n");
        }
    }
}
/* Driver program to test above function*/
int main()
{
    Node *root = NULL;
    char temp;
    /* Constructing tree given sequence */

    while (1)
    {
        temp = getchar();
        if (temp == '\n' || temp == '\0')
        {
            break;
        }
        if (temp >= 33 && temp <= 126)
        {

            root = insert(root, temp);
        }
    }

    // printf("Preorder traversal of the constructed AVL tree is \n");
    preOrder(root);
    // printf("Inorder traversal of the constructed AVL tree is \n");
    inOrder(root);

    while (1)
    {
        temp = getchar();
        if (temp == '\n' || temp == '\0')
        {
            break;
        }
        if (temp >= 33 && temp <= 126)
        {
            root = deleteNode(root, temp);
        }
    }

    // printf("\nPreorder traversal after deletion\n");
    preOrder(root);
    inOrder(root);

    return 0;
}
