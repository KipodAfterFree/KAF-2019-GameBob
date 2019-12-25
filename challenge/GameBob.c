#include <gb/gb.h>
#include <stdlib.h>
#include <stdio.h>

const int FLAG_SIZE = 26;

void *current = (void *) 0xd000;

unsigned int key[26] = {
    5,
    90,
    196,
    90,
    93,
    228,
    96,
    54,
    121,
    13,
    103,
    54,
    40,
    200,
    139,
    162,
    29,
    98,
    157,
    9,
    126,
    9,
    108,
    251,
    195,
    56
};

struct Node;

typedef struct Node {
    struct Node *next;
    int value;
} Node;

typedef struct Stack {
    Node *head;
} Stack;

Stack *flag_stack;

void *malloc(size_t size)
{
    void *memory = current;
    current = (void *) ((int) current + size);

    return memory;
}

Node *create_node(int value)
{
    Node *node = (Node *) malloc(sizeof(Node));

    node->value = value;
    node->next = NULL;

    return node;
}

Stack *create_stack()
{
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->head = NULL;

    return stack;
}

void push(Stack *stack, int value)
{
    Node *node = create_node(value);
    node->next = stack->head;

    stack->head = node;
}

int pop(Stack *stack)
{
    Node *last = stack->head;
    int value = last->value;

    stack->head = last->next;

    return value;
}

int top(Stack *stack)
{
    return stack->head->value;
}

int is_empty(Stack *stack)
{
    return stack->head == NULL;
}

void print_char_delayed(const char c)
{
    printf("%c", c);

    if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
        delay(100);
    }
}

void print_string_delayed(const char *str)
{
    int i;

    for (i = 0; str[i] != '\0'; i++) {
        print_char_delayed(str[i]);
    }
}

void print_stack(Stack *stack)
{
    int i;

    for (i = 0; i < FLAG_SIZE; i++) {
        print_char_delayed(pop(stack));
    }

    printf("\n");
}

void secret()
{
    Stack *new_stack = (Stack *) malloc(sizeof(Stack));

    int i, key_index;
    int flag_value;
    unsigned int key_value;

    for (i = 0; i < FLAG_SIZE; i++) {
        flag_value = pop(flag_stack);
        flag_value = flag_value >> 2;

        if (i <= 13) {
            key_index = 12 - i;
        } else {
            key_index = 38 - i;
        }

        key_value = key[key_index];
        flag_value = ~(flag_value & key_value) & (flag_value | key_value);

        push(new_stack, flag_value);
    }

    flag_stack = new_stack;
}

void main()
{
    ENABLE_RAM_MBC1;

    print_string_delayed("Welcome to GameBob!\n");
    print_string_delayed("It's a really easy  challenge, so here  is your flag:\n\n\n");

    flag_stack = create_stack();

    push(flag_stack, 524);
    push(flag_stack, 808);
    push(flag_stack, 912);
    push(flag_stack, 408);
    push(flag_stack, 20);
    push(flag_stack, 676);
    push(flag_stack, 400);
    push(flag_stack, 308);
    push(flag_stack, 428);
    push(flag_stack, 368);
    push(flag_stack, 520);
    push(flag_stack, 624);
    push(flag_stack, 36);
    push(flag_stack, 192);
    push(flag_stack, 20);
    push(flag_stack, 680);
    push(flag_stack, 424);
    push(flag_stack, 424);
    push(flag_stack, 748);
    push(flag_stack, 340);
    push(flag_stack, 24);
    push(flag_stack, 152);
    push(flag_stack, 244);
    push(flag_stack, 44);
    push(flag_stack, 328);
    push(flag_stack, 340);

    // secret(flag_stack);
    print_stack(flag_stack);

    DISABLE_RAM_MBC1;
}
