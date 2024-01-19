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
	node->height = 1; // new node is initially added at leaf
	return (node);
}

// A utility function to right rotate subtree rooted with y
Node *LL_Rotate(Node *y)
{
	Node *x = y->left;
	Node *T2 = x->right;
	x->right = y;
	y->left = T2;
	y->height = max(height(y->left),
					height(y->right)) +
				1;
	x->height = max(height(x->left),
					height(x->right)) +
				1;
	return x;
}

// A utility function to left rotate subtree rooted with x
Node *RR_Rotate(Node *x)
{
	Node *y = x->right;
	Node *T2 = y->left;
	y->left = x;
	x->right = T2;
	x->height = max(height(x->left),
					height(x->right)) +
				1;
	y->height = max(height(y->left),
					height(y->right)) +
				1;
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
		return (newNode(key));

	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);
	else
		return node;

	node->height = 1 + max(height(node->left),
						   height(node->right));

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
	while (node->left != NULL)
		node = node->left;
	return node;
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
	}
}

void inOrder(Node *root)
{
	static int i = 0;
	while (i == 0)
	{
		printf("\n");
		i -= 1;
	}

	if (root != NULL)
	{
		inOrder(root->left);
		printf("%c", root->key);
		inOrder(root->right);
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

	return 0;
}
