#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    char data;
    struct node *next;
} node;

typedef struct Stack
{
    struct node *head;
    unsigned int size;
} Stack;

// Stack ADT
void print_stack(Stack *s);
void print_stack_reverse(Stack *s);
void push(Stack *s, char val);
unsigned int count(Stack *s);
void pop(Stack *s);
char top(Stack *s);

// Stack function Implementation

int main()
{

    Stack *s = malloc(sizeof(Stack));
    s->head = NULL;
    s->size = 0;
    char temp[50];

    // Q1
    scanf("%s", temp);
    for (int i = 0; i < 50; i++)
    {
        if (temp[i] == '\0')
            break;
        push(s, temp[i]);
    }
    print_stack_reverse(s);
    pop(s);
    scanf("%s", temp);
    for (int i = 0; i < 50; i++)
    {
        if (temp[i] == '\0')
            break;
        push(s, temp[i]);
    }
    print_stack_reverse(s);

    return 0;
}

node *create_node(char val) // new node
{
    node *tump_nde = (node *)malloc(sizeof(node));
    tump_nde->data = val;
    tump_nde->next = NULL;
    return tump_nde;
}

void createStack(Stack *s) // empty stck
{
    s->head = NULL;
    s->size = 0;
}

void print_stack(Stack *s) // prnt elements
{
    node *tomp = s->head; // top
    while (tomp != NULL)  // move nxt node in stck
    {
        printf("%c", tomp->data);
        tomp = tomp->next;
    }
    printf("\n");
}

void print_stack_reverse(Stack *s) // prnt elemts revers order
{
    node *tomp = s->head;

    char stack_data[s->size]; // reverse storeing elemts in arr
    int i = 0;
    while (tomp != NULL)
    {
        stack_data[i] = tomp->data; // storing
        tomp = tomp->next;          // move
        i++;
    }

    for (int j = i - 1; j >= 0; j--) // print revers ordr
    {
        printf("%c", stack_data[j]);
    }
    printf("\n");
}

void push(Stack *s, char val) // push new elmt to stck
{
    node *tump_nde = create_node(val);
    tump_nde->next = s->head;
    s->head = tump_nde;
    s->size++;
}

void pop(Stack *s) // pop top elmt
{
    if (s->size == 0)
    {
        printf("Stack Underflow\n"); // empty stack -> cant pop
    }
    else
    {
        node *tomp = s->head;
        s->head = s->head->next;
        free(tomp);
        s->size--;
    }
}