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

// Implement the following function
typedef struct String
{
    unsigned int size;
    char *str;
} String;

void InfixToPostfix(String *infix, String *postfix);

void initializeStack(Stack *s);
int Precedence(char c);
int isOperator(char c);
#include <string.h>

// Stack function Implementation
int main()
{

    Stack *s = malloc(sizeof(Stack));
    s->head = NULL;
    s->size = 0;
    char temp[50];

    // Q3
    scanf("%s", temp);
    String *infix = malloc(sizeof(String));
    infix->size = 0;
    // Read the temp into infix structure
    infix->str = malloc(50);
    for (int i = 0; temp[i] != '\0'; i++)
        infix->str[i] = temp[i];
    infix->size = strlen(temp);
    infix->str[infix->size] = '\0';

    String *postfix = malloc(sizeof(String));
    postfix->size = 0;
    postfix->str = malloc(3 * infix->size);
    InfixToPostfix(infix, postfix);
    printf("%s\n", postfix->str);
}

/*
    String *postfix = malloc(sizeof(String));
    postfix->size = 0;
    postfix->str = NULL;
    //Save the Postfix expression in postfix string
    InfixToPostfix(infix, postfix);

    printf("%s\n",postfix->str);
    return 0;
}
*/
void initializeStack(Stack *s)
{
    s->head = NULL;
    s->size = 0;
}

void push(Stack *s, char val)
{
    node *newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL)
    {
        exit(1);
    }
    newNode->data = val;
    newNode->next = s->head;
    s->head = newNode;
    s->size++;
}

void pop(Stack *s)
{
    if (s->size == 0)
    {
        exit(1);
    }
    node *temp = s->head;
    s->head = s->head->next;
    free(temp);
    s->size--;
}

char top(Stack *s)
{
    if (s->size == 0)
    {
        exit(1);
    }
    return s->head->data;
}

void print_stack(Stack *s)
{
    node *current = s->head;
    while (current != NULL)
    {
        printf("%c ", current->data);
        current = current->next;
    }
    printf("\n");
}

unsigned int count(Stack *s)
{
    return s->size;
}

int isOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

int Precedence(char ch)
{
    switch (ch)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

void InfixToPostfix(String *infix, String *postfix)
{
    Stack s;
    s.head = NULL;
    s.size = 0;

    int i, j = 0;
    for (i = 0; infix->str[i]; i++)
    {
        char ch = infix->str[i];

        if (ch >= '0' && ch <= '9')
        {
            postfix->str[j++] = ch;
        }
        else if (isOperator(ch) || ch == '^')
        {
            while (s.size > 0 && Precedence(top(&s)) >= Precedence(ch))
            {
                postfix->str[j++] = top(&s);
                pop(&s);
            }
            push(&s, ch);
            postfix->str[j++] = ' ';
        }
        else if (ch == '(')
        {
            push(&s, ch);
        }
        else if (ch == ')')
        {
            while (s.size > 0 && top(&s) != '(')
            {
                postfix->str[j++] = top(&s);
                pop(&s);
            }
            if (s.size > 0 && top(&s) == '(')
            {
                pop(&s);
            }
        }
    }

    while (s.size > 0)
    {
        postfix->str[j++] = top(&s);
        pop(&s);
    }

    postfix->str[j] = '\0';
    postfix->size = j;
}
