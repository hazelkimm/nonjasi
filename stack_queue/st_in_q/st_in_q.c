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
 * OUTER QUEUE (Queue of Stacks)
 * 1. `QueueOfStacks* create_queue_of_stacks(int capacity)`
 *    - Creates and initializes a new outer queue (queue of stacks) with a specified capacity.
 *    - Returns a pointer to the newly created queue.
 *
 * 2. `void enqueue_stack(QueueOfStacks* queue, Stack* innerStack)`
 *    - Enqueues a pointer to an inner stack into the queue.
 *    - Dynamically resizes the queue if it reaches capacity.
 *
 * 3. `Stack* dequeue_stack(QueueOfStacks* queue)`
 *    - Dequeues the front inner stack from the queue.
 *    - Returns a pointer to the dequeued inner stack.
 *    - Prints an error message if the queue is empty.
 *
 * 4. `int is_empty_queue_of_stacks(QueueOfStacks* queue)`
 *    - Checks if the queue of stacks is empty.
 *    - Returns `1` if empty, `0` otherwise.
 *
 * 5. `Stack* peek_front_queue_of_stacks(QueueOfStacks* queue)`
 *    - Returns a pointer to the front inner stack of the queue without dequeuing it.
 *    - Prints an error message if the queue is empty.
 *
 * 6. `void free_queue_of_stacks(QueueOfStacks* queue)`
 *    - Frees the memory allocated for the queue and all its inner stacks.
 *
 **********************************************
 * MERGING STACKS
 * 1. `void merge_inner_stacks_in_queue(QueueOfStacks* queue, int i, int j, int k)`
 *    - Merges two inner stacks at indices `i` and `j` in the queue into a new stack.
 *    - Deletes the original stacks at indices `i` and `j`.
 *    - Inserts the merged stack into position `k` in the queue.
 *    - Dynamically resizes the queue if needed.
 *    - Maintains the order of the remaining stacks in the queue.
 *    - Prints an error message if indices are invalid or if `i` equals `j`.
 **********************************************/

// Structure for an individual stack (Inner Stack)
typedef struct Stack {
    int* data;      // Array to store elements
    int top;        // Index of the top element
    int capacity;   // Maximum capacity of the stack
} Stack;

// Structure for the queue of stacks (Outer Queue)
typedef struct QueueOfStacks {
    Stack** data;   // Array of pointers to inner stacks
    int front;      // Index of the front of the queue
    int rear;       // Index of the rear of the queue
    int size;       // Current number of stacks in the queue
    int capacity;   // Maximum number of stacks
} QueueOfStacks;

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

// Function to create a new queue of stacks
QueueOfStacks* create_queue_of_stacks(int capacity) {
    QueueOfStacks* queue = (QueueOfStacks*)malloc(sizeof(QueueOfStacks));
    queue->data = (Stack**)malloc(capacity * sizeof(Stack*));
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

// Function to enqueue an inner stack into the queue
void enqueue_stack(QueueOfStacks* queue, Stack* innerStack) {
    if (queue->size == queue->capacity) {
        queue->capacity *= 2;
        queue->data = (Stack**)realloc(queue->data, queue->capacity * sizeof(Stack*));
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = innerStack;
    queue->size++;
}

// Function to dequeue an inner stack from the queue
Stack* dequeue_stack(QueueOfStacks* queue) {
    if (queue->size == 0) {
        printf("Queue underflow\n");
        return NULL; // Sentinel value
    }
    Stack* frontStack = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return frontStack;
}

// Function to check if the queue is empty
int is_empty_queue_of_stacks(QueueOfStacks* queue) {
    return queue->size == 0;
}

// Function to get the front inner stack from the queue without dequeuing it
Stack* peek_front_queue_of_stacks(QueueOfStacks* queue) {
    if (is_empty_queue_of_stacks(queue)) {
        printf("Queue is empty\n");
        return NULL; // Sentinel value
    }
    return queue->data[queue->front];
}

// Function to free the queue of stacks
void free_queue_of_stacks(QueueOfStacks* queue) {
    while (!is_empty_queue_of_stacks(queue)) {
        free_stack(dequeue_stack(queue));
    }
    free(queue->data);
    free(queue);
}

void merge_inner_stacks_in_queue(QueueOfStacks* queue, int i, int j, int k) {
    if (i >= queue->size || j >= queue->size || k > queue->size || i == j) {
        printf("Invalid indices\n");
        return;
    }

    // Ensure `i` is smaller than `j` for proper order
    if (i > j) {
        int temp = i;
        i = j;
        j = temp;
    }

    // Retrieve stacks at indices `i` and `j`
    Stack* stack1 = queue->data[(queue->front + i) % queue->capacity];
    Stack* stack2 = queue->data[(queue->front + j) % queue->capacity];

    // Create a new stack to hold the merged data
    Stack* mergedStack = create_stack(stack1->capacity + stack2->capacity);

    // Add elements from stack1 and stack2 to the merged stack
    for (int idx = 0; idx <= stack1->top; idx++) {
        push_stack(mergedStack, stack1->data[idx]);
    }
    for (int idx = 0; idx <= stack2->top; idx++) {
        push_stack(mergedStack, stack2->data[idx]);
    }

    // Free the original stacks
    free_stack(stack1);
    free_stack(stack2);

    // Create a temporary array to store the reordered stacks
    Stack** temp = (Stack**)malloc(queue->capacity * sizeof(Stack*));
    int tempIndex = 0;

    // Copy all stacks from the queue to the temporary array
    for (int idx = 0; idx < queue->size; idx++) {
        Stack* currentStack = queue->data[(queue->front + idx) % queue->capacity];
        if (idx != i && idx != j) {
            temp[tempIndex++] = currentStack;
        }
    }

    // Insert the merged stack at position `k`
    for (int idx = queue->size - 2; idx >= k; idx--) {
        temp[idx + 1] = temp[idx];
    }
    temp[k] = mergedStack;

    // Update the queue
    queue->size = tempIndex + 1;
    queue->front = 0;
    queue->rear = queue->size - 1;
    for (int idx = 0; idx < queue->size; idx++) {
        queue->data[idx] = temp[idx];
    }

    free(temp);
}

// Main function for testing
int main() {
    // Create a queue of stacks
    QueueOfStacks* queue = create_queue_of_stacks(5);

    // Create and enqueue stacks
    Stack* stack1 = create_stack(3);
    push_stack(stack1, 1);
    push_stack(stack1, 2);

    Stack* stack2 = create_stack(3);
    push_stack(stack2, 3);
    push_stack(stack2, 4);

    Stack* stack3 = create_stack(3);
    push_stack(stack3, 5);
    push_stack(stack3, 6);

    Stack* stack4 = create_stack(3);
    push_stack(stack4, 7);
    push_stack(stack4, 8);

    enqueue_stack(queue, stack1);
    enqueue_stack(queue, stack2);
    enqueue_stack(queue, stack3);
    enqueue_stack(queue, stack4);

    // Print initial queue
    printf("Queue before merging:\n");
    for (int idx = 0; idx < queue->size; idx++) {
        Stack* stack = queue->data[(queue->front + idx) % queue->capacity];
        for (int j = 0; j <= stack->top; j++) {
            printf("%d ", stack->data[j]);
        }
        printf("\n");
    }

    // Merge stacks 0 and 1 into position 1
    merge_inner_stacks_in_queue(queue, 0, 1, 1);

    // Print queue after merging
    printf("Queue after merging stacks 0 and 1 into position 1:\n");
    for (int idx = 0; idx < queue->size; idx++) {
        Stack* stack = queue->data[(queue->front + idx) % queue->capacity];
        for (int j = 0; j <= stack->top; j++) {
            printf("%d ", stack->data[j]);
        }
        printf("\n");
    }

    // Free the queue
    free_queue_of_stacks(queue);
    return 0;
}