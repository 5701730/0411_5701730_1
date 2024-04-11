#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define INITIAL_STACK_SIZE 5

typedef int element;

typedef struct {
    element* data;
    int top;
    int capacity;
} Stack;

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    stack->data = (element*)malloc(sizeof(element) * INITIAL_STACK_SIZE);
    if (stack->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(stack);
        exit(EXIT_FAILURE);
    }
    stack->top = -1;
    stack->capacity = INITIAL_STACK_SIZE;
    return stack;
}

void freeStack(Stack* stack) {
    free(stack->data);
    free(stack);
}

int isEmpty(Stack* stack) {
    return (stack == NULL || stack->top == -1);
}

void push(Stack* stack, element item) {
    if (stack == NULL) {
        fprintf(stderr, "Stack is not initialized\n");
        exit(EXIT_FAILURE);
    }
    if (stack->top == stack->capacity - 1) {
        // Stack is full, need to resize
        stack->capacity *= 2;
        element* newData = (element*)realloc(stack->data, sizeof(element) * stack->capacity);
        if (newData == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        stack->data = newData;
    }
    stack->top++;
    stack->data[stack->top] = item;
    printf("Push : %d\n", item);
}

int pop(Stack* stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Stack is empty\n");
        return -1;
    }
    element popValue = stack->data[stack->top];
    stack->top--;
    printf("Popped : %d\n", popValue);
    return popValue;
}

int main(int argc, char* argv[]) {
    srand((unsigned int)time(NULL));

    Stack* stack = createStack();

    for (int i = 0; i < 30; ++i) {
        int rand_num = rand() % 100 + 1;
        printf("Current rand_num: %d | %s\n", rand_num, rand_num % 2 == 0 ? "Even" : "Odd");
        if (rand_num % 2 == 0) {
            push(stack, rand_num);
        }
        else {
            pop(stack);
        }
    }

    freeStack(stack);
    return 0;
}
