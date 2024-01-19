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
// Use the code from Q1 for the below functions
void print_stack(Stack *s);
void print_stack_reverse(Stack *s);
void push(Stack *s, char val);
unsigned int count(Stack *s);
void pop(Stack *s);
char top(Stack *s);

node *create_node(char val);
void createStack(Stack *s);

// Implement the following function
typedef struct String
{
    unsigned int size;
    char *str;
} String;

int ParenMatch(String *par_str);

// Stack function Implementation
int main()
{

    Stack *s = malloc(sizeof(Stack));
    s->head = NULL;
    s->size = 0;
    char temp[50];

    // Q2
    scanf("%s", temp);
    String *par_str = malloc(sizeof(String));
    par_str->size = 0;
    // Store the lenght of temp in par_str->size
    // Assign the characters temp[i] to par_str->str[i]

    par_str->str = malloc(55);
    int i = 0;
    for (i = 0; temp[i] != '\0'; i++)
        par_str->str[i] = temp[i];
    par_str->size = i;
    par_str->str[i] = '\0';
    int match = ParenMatch(par_str);
    printf("%d\n", match);
    return 0;
}

node *create_node(char val) // new node creat
{
    node *temp_code = (node *)malloc(sizeof(node)); // memry allote
    if (temp_code == NULL)
    {
        perror("Memory allocation failed"); // error -> Memory allocation failed
        exit(1);
    }
    temp_code->data = val;
    temp_code->next = NULL;
    return temp_code;
}

void push(Stack *s, char val) // push to stck
{
    node *temp_code = create_node(val);
    temp_code->next = s->head;
    s->head = temp_code;
    s->size++;
}

void pop(Stack *s) // pop frm stck
{
    if (s->size == 0)
    {
        printf("Stack is empty. Cannot pop.\n"); // error -> stack empty
        return;
    }
    node *temp = s->head;
    s->head = s->head->next;
    free(temp);
    s->size--;
}

char top(Stack *s) // top elemnt
{
    if (s->size == 0)
    {
        printf("Stack is empty.\n");
        exit(1);
    }
    return s->head->data;
}

unsigned int count(Stack *s) // count elmnts
{
    return s->size;
}
void createStack(Stack *s)
{
    s->head = NULL;
    s->size = 0;
}
void print_stack(Stack *s) // prnt top to bottom
{
    node *temp = s->head;
    printf("Stack (Top to Bottom): ");
    while (temp != NULL)
    {
        printf("%c ", temp->data);
        temp = temp->next; // move
    }
    printf("\n");
}

void print_stack_reverse(Stack *s) // prnt revers ordr
{
    node *temp = s->head;
    if (temp == NULL)
    {
        printf("Stack is empty.\n");
        return;
    }

    char stack_data[s->size]; // arr to stor stck elemnt
    int i = 0;
    while (temp != NULL)
    {
        stack_data[i] = temp->data;
        temp = temp->next;
        i++;
    }

    printf("Stack (Bottom to Top): ");
    for (int j = i - 1; j >= 0; j--)
    {
        printf("%c ", stack_data[j]); // prnt in reverse ordr
    }
    printf("\n");
}

int ParenMatch(String *par_str) // parentheses cheking
{
    Stack s;
    createStack(&s);

    for (int i = 0; i < par_str->size; i++)
    {
        char temp_char = par_str->str[i];

        if (temp_char == '(' || temp_char == '[' || temp_char == '{')
        {
            push(&s, temp_char);
        }
        else if (temp_char == ')' || temp_char == ']' || temp_char == '}')
        {
            if (count(&s) == 0)
            {
                return false; // not mtching
            }
            char top_char = top(&s);
            if ((temp_char == ')' && top_char == '(') ||
                (temp_char == ']' && top_char == '[') ||
                (temp_char == '}' && top_char == '{'))
            {
                pop(&s);
            }
            else
            {
                return false; // mismatch
            }
        }
    }

    return (count(&s) == 0);
}