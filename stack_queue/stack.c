#include <stdio.h>
#include <stdlib.h>

/**********************************************
 * CATALOG OF STACK FUNCTIONS
 **********************************************
 * 
 * 1. `create_stack() -> Stack*`:
 *    Initializes and returns an empty stack.
 * 
 * 2. `is_empty(Stack* stack) -> int`:
 *    Checks if the stack is empty. Returns 1 (true) or 0 (false).
 * 
 * 3. `is_full(Stack* stack) -> int`:
 *    Checks if the stack is full. Returns 1 (true) or 0 (false).
 * 
 * 4. `resize_stack(Stack* stack)`:
 *    Doubles the capacity of the stack when it becomes full.
 * 
 * 5. `push(Stack* stack, int value)`:
 *    Adds an element to the top of the stack.
 * 
 * 6. `pop(Stack* stack) -> int`:
 *    Removes and returns the top element of the stack.
 *    Throws an error if the stack is empty.
 * 
 * 7. `peek(Stack* stack) -> int`:
 *    Returns the top element without removing it.
 *    Throws an error if the stack is empty.
 * 
 * 8. `free_stack(Stack* stack)`:
 *    Frees the memory allocated for the stack.
 * 
 * 9. `merge_stacks(Stack* stack1, Stack* stack2) -> Stack*`:
 *    Merges two stacks into a new stack. Retains the order of elements.
 * 
 * 10. `reverse_stack(Stack* stack)`:
 *     Reverses the elements of the stack in place.
 * 
 * 11. `copy_stack(Stack* stack) -> Stack*`:
 *     Creates and returns a new stack that is a copy of the given stack.
 * 
 * 12. `sort_stack(Stack* stack)`:
 *     Sorts the stack in ascending order.
 * 
 * 13. `slice_stack(Stack* stack, int start, int end) -> Stack*`:
 *     Creates and returns a new stack containing elements
 *     from index `start` to `end - 1` of the original stack.
 *     Throws an error if indices are invalid.
 * 
 * 14. `size_of_stack(Stack* stack) -> int`:
 *     Returns the number of elements in the stack.
 * 
 **********************************************/

#define INITIAL_CAPACITY 10

typedef struct {
    int* data;       // Dynamic array for storing stack elements
    int top;         // Index of the top element
    int capacity;    // Current capacity of the stack
} Stack;

// Function to initialize a stack
Stack* create_stack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (int*)malloc(INITIAL_CAPACITY * sizeof(int));
    stack->top = -1;
    stack->capacity = INITIAL_CAPACITY;
    return stack;
}

// Function to check if the stack is empty
int is_empty(Stack* stack) {
    return stack->top == -1;
}

// Function to check if the stack is full
int is_full(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// Function to resize the stack when it's full
void resize_stack(Stack* stack) {
    stack->capacity *= 2;  // Double the capacity
    stack->data = (int*)realloc(stack->data, stack->capacity * sizeof(int));
}

// Function to push an element onto the stack
void push(Stack* stack, int value) {
    if (is_full(stack)) {
        resize_stack(stack);  // Resize if full
    }
    stack->data[++stack->top] = value;
}

// Function to pop an element from the stack
int pop(Stack* stack) {
    if (is_empty(stack)) {
        fprintf(stderr, "Stack underflow error!\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top--];
}

// Function to get the top element without popping
int peek(Stack* stack) {
    if (is_empty(stack)) {
        fprintf(stderr, "Stack is empty!\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top];
}

// Function to free the stack
void free_stack(Stack* stack) {
    free(stack->data);
    free(stack);
}

// ** Function 1: Merge Two Stacks **
Stack* merge_stacks(Stack* stack1, Stack* stack2) {
    Stack* merged_stack = create_stack();

    // Add all elements from stack1
    for (int i = 0; i <= stack1->top; i++) {
        push(merged_stack, stack1->data[i]);
    }

    // Add all elements from stack2
    for (int i = 0; i <= stack2->top; i++) {
        push(merged_stack, stack2->data[i]);
    }

    return merged_stack;
}

// ** Function 2: Reverse a Stack **
void reverse_stack(Stack* stack) {
    int left = 0, right = stack->top;
    while (left < right) {
        // Swap elements
        int temp = stack->data[left];
        stack->data[left] = stack->data[right];
        stack->data[right] = temp;
        left++;
        right--;
    }
}

// ** Function 3: Copy a Stack **
Stack* copy_stack(Stack* stack) {
    Stack* copied_stack = create_stack();
    copied_stack->capacity = stack->capacity;
    copied_stack->top = stack->top;
    copied_stack->data = (int*)malloc(stack->capacity * sizeof(int));

    for (int i = 0; i <= stack->top; i++) {
        copied_stack->data[i] = stack->data[i];
    }

    return copied_stack;
}

// ** Function 4: Sort a Stack **
void sort_stack(Stack* stack) {
    for (int i = 0; i <= stack->top; i++) {
        for (int j = i + 1; j <= stack->top; j++) {
            if (stack->data[i] > stack->data[j]) {
                // Swap elements
                int temp = stack->data[i];
                stack->data[i] = stack->data[j];
                stack->data[j] = temp;
            }
        }
    }
}

// ** Function: Slice a Stack **
Stack* slice_stack(Stack* stack, int start, int end) {
    if (start < 0 || end > stack->top + 1 || start >= end) {
        fprintf(stderr, "Invalid slice indices!\n");
        exit(EXIT_FAILURE);
    }

    Stack* sliced_stack = create_stack();
    for (int i = start; i < end; i++) {
        push(sliced_stack, stack->data[i]);
    }
    return sliced_stack;
}

// ** Function: Return Size of the Stack **
int size_of_stack(Stack* stack) {
    return stack->top + 1;
}

// Main function for testing
int main() {
    Stack* stack1 = create_stack();
    Stack* stack2 = create_stack();

    // Push elements into stack1
    push(stack1, 10);
    push(stack1, 20);
    push(stack1, 30);

    // Push elements into stack2
    push(stack2, 40);
    push(stack2, 50);
    push(stack2, 60);

    // Merge stacks
    Stack* merged_stack = merge_stacks(stack1, stack2);
    printf("Merged stack: ");
    while (!is_empty(merged_stack)) {
        printf("%d ", pop(merged_stack));
    }
    printf("\n");

    // Reverse stack1
    reverse_stack(stack1);
    printf("Reversed stack1: ");
    while (!is_empty(stack1)) {
        printf("%d ", pop(stack1));
    }
    printf("\n");

    // Push elements into stack2 again
    push(stack2, 70);
    push(stack2, 80);

    // Copy stack2
    Stack* copied_stack = copy_stack(stack2);
    printf("Copied stack2: ");
    while (!is_empty(copied_stack)) {
        printf("%d ", pop(copied_stack));
    }
    printf("\n");

    // Sort stack2
    push(stack2, 90);
    push(stack2, 25);
    sort_stack(stack2);
    printf("Sorted stack2: ");
    while (!is_empty(stack2)) {
        printf("%d ", pop(stack2));
    }
    printf("\n");

    // Free all stacks
    free_stack(stack1);
    free_stack(stack2);
    free_stack(merged_stack);
    free_stack(copied_stack);

    return 0;
}