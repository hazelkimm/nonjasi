#include <stdio.h>
#include <stdlib.h>

/**********************************************
 * CATALOG OF FUNCTIONS
 **********************************************
 * 
 * INNER STACK (Stack)
 * 1. `Stack* create_stack(int capacity)`
 *    - Creates and initializes a new inner stack with a specified capacity.
 *    - Returns a pointer to the newly created stack.
 * 
 * 2. `void push_stack(Stack* stack, int value)`
 *    - Pushes an integer value onto the inner stack.
 *    - Dynamically resizes the stack if it reaches capacity.
 * 
 * 3. `int pop_stack(Stack* stack)`
 *    - Pops the top element from the inner stack.
 *    - Returns the popped value.
 *    - Prints an error message if the stack is empty.
 * 
 * 4. `int is_empty_stack(Stack* stack)`
 *    - Checks if the inner stack is empty.
 *    - Returns `1` if empty, `0` otherwise.
 * 
 * 5. `int peek_stack(Stack* stack)`
 *    - Returns the top element of the inner stack without popping it.
 *    - Prints an error message if the stack is empty.
 * 
 * 6. `void free_stack(Stack* stack)`
 *    - Frees the memory allocated for the inner stack.
 * 
 **********************************************
 * OUTER STACK (Stack of Stacks)
 * 1. `StackOfStacks* create_stack_of_stacks(int capacity)`
 *    - Creates and initializes a new outer stack (stack of stacks) with a specified capacity.
 *    - Returns a pointer to the newly created stack.
 * 
 * 2. `void push_stack_of_stacks(StackOfStacks* stack, Stack* innerStack)`
 *    - Pushes a pointer to an inner stack onto the outer stack.
 *    - Dynamically resizes the outer stack if it reaches capacity.
 * 
 * 3. `Stack* pop_stack_of_stacks(StackOfStacks* stack)`
 *    - Pops the top inner stack from the outer stack.
 *    - Returns a pointer to the popped inner stack.
 *    - Prints an error message if the outer stack is empty.
 * 
 * 4. `int is_empty_stack_of_stacks(StackOfStacks* stack)`
 *    - Checks if the outer stack is empty.
 *    - Returns `1` if empty, `0` otherwise.
 * 
 * 5. `Stack* peek_stack_of_stacks(StackOfStacks* stack)`
 *    - Returns a pointer to the top inner stack of the outer stack without popping it.
 *    - Prints an error message if the outer stack is empty.
 * 
 * 6. `void free_stack_of_stacks(StackOfStacks* stack)`
 *    - Frees the memory allocated for the outer stack and all its inner stacks.
 * 
***********************************************
 * MERGING STACKS
 * 1. `void merge_inner_stacks(StackOfStacks* outerStack, int i, int j, int k)`
 *    - Merges two inner stacks at indices `i` and `j` into a new stack.
 *    - Deletes the original stacks at indices `i` and `j`.
 *    - Inserts the new merged stack into position `k` in the outer stack.
 *    - Adjusts the outer stack to remove the original stacks and accommodate the merged stack.
 *    - Dynamically resizes the outer stack if needed.
 *    - Prints an error message if indices are invalid.
 **********************************************/

// Structure for an individual stack (Inner Stack)
typedef struct Stack {
    int* data;      // Array to store elements
    int top;        // Index of the top element
    int capacity;   // Maximum capacity of the stack
} Stack;

// Structure for the stack of stacks (Outer Stack)
typedef struct StackOfStacks {
    Stack** data;   // Array of pointers to inner stacks
    int top;        // Index of the top stack
    int capacity;   // Maximum number of stacks
} StackOfStacks;

// Function to create a new inner stack
Stack* create_stack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (int*)malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

// Function to push an element onto an inner stack
void push_stack(Stack* stack, int value) {
    if (stack->top == stack->capacity - 1) {
        stack->capacity *= 2;
        stack->data = (int*)realloc(stack->data, stack->capacity * sizeof(int));
    }
    stack->data[++stack->top] = value;
}

// Function to pop an element from an inner stack
int pop_stack(Stack* stack) {
    if (stack->top == -1) {
        printf("Inner stack underflow\n");
        return -1; // Sentinel value
    }
    return stack->data[stack->top--];
}

// Function to check if an inner stack is empty
int is_empty_stack(Stack* stack) {
    return stack->top == -1;
}

// Function to get the top element of an inner stack
int peek_stack(Stack* stack) {
    if (is_empty_stack(stack)) {
        printf("Inner stack is empty\n");
        return -1; // Sentinel value
    }
    return stack->data[stack->top];
}

// Function to free an inner stack
void free_stack(Stack* stack) {
    free(stack->data);
    free(stack);
}

// Function to create a new stack of stacks
StackOfStacks* create_stack_of_stacks(int capacity) {
    StackOfStacks* stack = (StackOfStacks*)malloc(sizeof(StackOfStacks));
    stack->data = (Stack**)malloc(capacity * sizeof(Stack*));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

// Function to push a new inner stack onto the stack of stacks
void push_stack_of_stacks(StackOfStacks* stack, Stack* innerStack) {
    if (stack->top == stack->capacity - 1) {
        stack->capacity *= 2;
        stack->data = (Stack**)realloc(stack->data, stack->capacity * sizeof(Stack*));
    }
    stack->data[++stack->top] = innerStack;
}

// Function to pop an inner stack from the stack of stacks
Stack* pop_stack_of_stacks(StackOfStacks* stack) {
    if (stack->top == -1) {
        printf("Outer stack underflow\n");
        return NULL; // Sentinel value
    }
    return stack->data[stack->top--];
}

// Function to check if the stack of stacks is empty
int is_empty_stack_of_stacks(StackOfStacks* stack) {
    return stack->top == -1;
}

// Function to get the top inner stack from the stack of stacks
Stack* peek_stack_of_stacks(StackOfStacks* stack) {
    if (is_empty_stack_of_stacks(stack)) {
        printf("Outer stack is empty\n");
        return NULL; // Sentinel value
    }
    return stack->data[stack->top];
}

// Function to free the stack of stacks
void free_stack_of_stacks(StackOfStacks* stack) {
    for (int i = 0; i <= stack->top; i++) {
        free_stack(stack->data[i]);
    }
    free(stack->data);
    free(stack);
}

// Function to merge two inner stacks into one and insert it at the k-th position
void merge_inner_stacks(StackOfStacks* outerStack, int i, int j, int k) {
    if (i > outerStack->top || j > outerStack->top || k > outerStack->top + 1 || i == j) {
        printf("Invalid indices\n");
        return;
    }

    // Create a new stack to hold the merged data
    Stack* mergedStack = create_stack(outerStack->data[i]->capacity + outerStack->data[j]->capacity);

    // Push all elements from the first stack
    for (int idx = 0; idx <= outerStack->data[i]->top; idx++) {
        push_stack(mergedStack, outerStack->data[i]->data[idx]);
    }

    // Push all elements from the second stack
    for (int idx = 0; idx <= outerStack->data[j]->top; idx++) {
        push_stack(mergedStack, outerStack->data[j]->data[idx]);
    }

    // Free the original stacks
    free_stack(outerStack->data[i]);
    free_stack(outerStack->data[j]);

    // Shift elements to remove the original stacks
    for (int idx = i; idx < outerStack->top; idx++) {
        outerStack->data[idx] = outerStack->data[idx + 1];
    }
    outerStack->top--;

    for (int idx = j - 1; idx < outerStack->top; idx++) {
        outerStack->data[idx] = outerStack->data[idx + 1];
    }
    outerStack->top--;

    // Shift elements to make room for the merged stack at position k
    for (int idx = outerStack->top + 1; idx > k; idx--) {
        outerStack->data[idx] = outerStack->data[idx - 1];
    }

    // Insert the merged stack at position k
    outerStack->data[k] = mergedStack;
    outerStack->top++;
}

void print_outer_stack(StackOfStacks* outerStack) {
    for (int i = 0; i <= outerStack->top; i++) {
        printf("Stack %d: ", i);
        for (int j = 0; j <= outerStack->data[i]->top; j++) {
            printf("%d ", outerStack->data[i]->data[j]);
        }
        printf("\n");
    }
}

int main() {
    printf("=== Testing Inner Stack Functions ===\n");

    // Create an inner stack
    Stack* innerStack = create_stack(3);
    printf("Inner stack created.\n");

    // Push elements
    push_stack(innerStack, 10);
    push_stack(innerStack, 20);
    push_stack(innerStack, 30);
    printf("Pushed elements onto the inner stack: 10, 20, 30.\n");

    // Peek top element
    printf("Top element of inner stack: %d\n", peek_stack(innerStack));

    // Pop elements
    printf("Popped element: %d\n", pop_stack(innerStack));
    printf("Popped element: %d\n", pop_stack(innerStack));

    // Check if stack is empty
    printf("Is inner stack empty? %s\n", is_empty_stack(innerStack) ? "Yes" : "No");

    // Free the inner stack
    free_stack(innerStack);
    printf("Inner stack freed.\n");

    printf("\n=== Testing Outer Stack (Stack of Stacks) ===\n");

    // Create an outer stack
    StackOfStacks* outerStack = create_stack_of_stacks(2);
    printf("Outer stack created.\n");

    // Create inner stacks
    Stack* innerStack1 = create_stack(3);
    push_stack(innerStack1, 1);
    push_stack(innerStack1, 2);

    Stack* innerStack2 = create_stack(3);
    push_stack(innerStack2, 3);
    push_stack(innerStack2, 4);

    // Push inner stacks onto the outer stack
    push_stack_of_stacks(outerStack, innerStack1);
    push_stack_of_stacks(outerStack, innerStack2);
    printf("Inner stacks pushed onto the outer stack.\n");

    // Print outer stack
    printf("Outer stack contents:\n");
    print_outer_stack(outerStack);

    // Peek the top inner stack
    printf("Top inner stack (peek):\n");
    for (int i = 0; i <= peek_stack_of_stacks(outerStack)->top; i++) {
        printf("%d ", peek_stack_of_stacks(outerStack)->data[i]);
    }
    printf("\n");

    // Pop the top inner stack
    Stack* poppedStack = pop_stack_of_stacks(outerStack);
    printf("Popped top inner stack. Contents of popped stack: ");
    for (int i = 0; i <= poppedStack->top; i++) {
        printf("%d ", poppedStack->data[i]);
    }
    printf("\n");

    // Check if the outer stack is empty
    printf("Is outer stack empty? %s\n", is_empty_stack_of_stacks(outerStack) ? "Yes" : "No");

    printf("\n=== Testing Merge Inner Stacks ===\n");

    push_stack_of_stacks(outerStack, innerStack2);
    
    Stack* innerStack3 = create_stack(3);
    push_stack(innerStack3, 5);
    push_stack(innerStack3, 6);
    push_stack_of_stacks(outerStack, innerStack3);

    // Print before merging
    printf("Outer stack before merging:\n");
    print_outer_stack(outerStack);

    // Merge two inner stacks
    merge_inner_stacks(outerStack, 0, 1, 1);

    // Print after merging
    printf("Outer stack after merging inner stacks 0 and 1 into position 1:\n");
    print_outer_stack(outerStack);

    // Free the outer stack and its contents
    free_stack_of_stacks(outerStack);
    printf("Outer stack and all inner stacks freed.\n");

    return 0;
}