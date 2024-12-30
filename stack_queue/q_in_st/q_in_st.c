#include <stdio.h>
#include <stdlib.h>

/**********************************************
 * CATALOG OF FUNCTIONS AND DATA STRUCTURES
 **********************************************

 * INNER QUEUE (Queue)
 1. `Queue* create_queue(int capacity)`
    - Creates and initializes a new queue with a specified capacity.
    - Returns a pointer to the newly created queue.

 2. `void enqueue(Queue* queue, int value)`
    - Enqueues an integer value into the queue.
    - Dynamically resizes the queue if it reaches its capacity.

 3. `int dequeue(Queue* queue)`
    - Dequeues the front element from the queue.
    - Returns the dequeued value.
    - Prints an error message if the queue is empty.

 4. `int is_empty_queue(Queue* queue)`
    - Checks if the queue is empty.
    - Returns `1` if the queue is empty, otherwise `0`.

 5. `int peek_front(Queue* queue)`
    - Returns the front element of the queue without dequeuing it.
    - Prints an error message if the queue is empty.

 6. `void free_queue(Queue* queue)`
    - Frees the memory allocated for the queue.

 **********************************************

 * OUTER STACK (Stack of Queues)
 1. `StackOfQueues* create_stack_of_queues(int capacity)`
    - Creates and initializes a new stack of queues with a specified capacity.
    - Returns a pointer to the newly created stack.

 2. `void push_queue(StackOfQueues* stack, Queue* innerQueue)`
    - Pushes a pointer to an inner queue onto the stack.
    - Dynamically resizes the stack if it reaches its capacity.

 3. `Queue* pop_queue(StackOfQueues* stack)`
    - Pops the top inner queue from the stack.
    - Returns a pointer to the popped queue.
    - Prints an error message if the stack is empty.

 4. `int is_empty_stack_of_queues(StackOfQueues* stack)`
    - Checks if the stack of queues is empty.
    - Returns `1` if the stack is empty, otherwise `0`.

 5. `void free_stack_of_queues(StackOfQueues* stack)`
    - Frees the memory allocated for the stack and all its inner queues.

 **********************************************

 * MERGING QUEUES
 1. `void merge_inner_queues_in_stack(StackOfQueues* stack, int i, int j, int k)`
    - Merges two inner queues at indices `i` and `j` in the stack into a new queue.
    - Deletes the original queues at indices `i` and `j`.
    - Inserts the merged queue at position `k` in the stack.
    - Shifts all subsequent queues to maintain the stack's order.
    - Dynamically resizes the stack if needed.
    - Prints an error message if indices are invalid or if any of `i`, `j`, and `k` conflict.
**********************************************/

// Structure for an individual queue (Inner Queue)
typedef struct Queue {
    int* data;      // Array to store elements
    int front;      // Index of the front of the queue
    int rear;       // Index of the rear of the queue
    int size;       // Current number of elements in the queue
    int capacity;   // Maximum capacity of the queue
} Queue;

// Structure for the stack of queues (Outer Stack)
typedef struct StackOfQueues {
    Queue** data;   // Array of pointers to inner queues
    int top;        // Index of the top queue in the stack
    int capacity;   // Maximum number of queues
} StackOfQueues;

// Function to create a new queue
Queue* create_queue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->data = (int*)malloc(capacity * sizeof(int));
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

// Function to enqueue an element into a queue
void enqueue(Queue* queue, int value) {
    if (queue->size == queue->capacity) {
        queue->capacity *= 2;
        queue->data = (int*)realloc(queue->data, queue->capacity * sizeof(int));
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = value;
    queue->size++;
}

// Function to dequeue an element from a queue
int dequeue(Queue* queue) {
    if (queue->size == 0) {
        printf("Queue underflow\n");
        return -1; // Sentinel value
    }
    int value = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return value;
}

// Function to check if a queue is empty
int is_empty_queue(Queue* queue) {
    return queue->size == 0;
}

// Function to peek the front element of a queue
int peek_front(Queue* queue) {
    if (is_empty_queue(queue)) {
        printf("Queue is empty\n");
        return -1; // Sentinel value
    }
    return queue->data[queue->front];
}

// Function to free a queue
void free_queue(Queue* queue) {
    free(queue->data);
    free(queue);
}

// Function to create a new stack of queues
StackOfQueues* create_stack_of_queues(int capacity) {
    StackOfQueues* stack = (StackOfQueues*)malloc(sizeof(StackOfQueues));
    stack->data = (Queue**)malloc(capacity * sizeof(Queue*));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

// Function to push a queue onto the stack
void push_queue(StackOfQueues* stack, Queue* queue) {
    if (stack->top == stack->capacity - 1) {
        stack->capacity *= 2;
        stack->data = (Queue**)realloc(stack->data, stack->capacity * sizeof(Queue*));
    }
    stack->data[++stack->top] = queue;
}

// Function to pop a queue from the stack
Queue* pop_queue(StackOfQueues* stack) {
    if (stack->top == -1) {
        printf("Stack underflow\n");
        return NULL; // Sentinel value
    }
    return stack->data[stack->top--];
}

// Function to check if the stack is empty
int is_empty_stack_of_queues(StackOfQueues* stack) {
    return stack->top == -1;
}

// Function to free the stack of queues
void free_stack_of_queues(StackOfQueues* stack) {
    while (!is_empty_stack_of_queues(stack)) {
        free_queue(pop_queue(stack));
    }
    free(stack->data);
    free(stack);
}

void merge_inner_queues_in_stack(StackOfQueues* stack, int i, int j, int k) {
    if (i > stack->top || j > stack->top || k > stack->top + 1 || i == j) {
        printf("Invalid indices\n");
        return;
    }

    // Ensure indices are ordered to avoid shifting issues
    int first = (i < j) ? i : j;
    int second = (i < j) ? j : i;

    // Create a new queue for the merged result
    Queue* mergedQueue = create_queue(
        stack->data[first]->capacity + stack->data[second]->capacity
    );

    // Add elements from the first queue
    Queue* queue1 = stack->data[first];
    for (int idx = 0; idx < queue1->size; idx++) {
        int value = queue1->data[(queue1->front + idx) % queue1->capacity];
        enqueue(mergedQueue, value);
    }

    // Add elements from the second queue
    Queue* queue2 = stack->data[second];
    for (int idx = 0; idx < queue2->size; idx++) {
        int value = queue2->data[(queue2->front + idx) % queue2->capacity];
        enqueue(mergedQueue, value);
    }

    // Free the original queues
    free_queue(queue1);
    free_queue(queue2);

    // Remove the second queue
    for (int idx = second; idx < stack->top; idx++) {
        stack->data[idx] = stack->data[idx + 1];
    }
    stack->top--;

    // Remove the first queue
    for (int idx = first; idx < stack->top; idx++) {
        stack->data[idx] = stack->data[idx + 1];
    }
    stack->top--;

    // Shift queues to make space for the merged queue at position `k`
    for (int idx = stack->top; idx >= k; idx--) {
        stack->data[idx + 1] = stack->data[idx];
    }

    // Insert the merged queue at position `k`
    stack->data[k] = mergedQueue;
    stack->top++;
}

// Main function to test the implementation
int main() {
    printf("=== Testing Merge Inner Queues in Stack ===\n");

    // Create a stack of queues
    StackOfQueues* stack = create_stack_of_queues(5);

    // Create and push queues onto the stack
    Queue* queue1 = create_queue(3);
    enqueue(queue1, 1);
    enqueue(queue1, 2);

    Queue* queue2 = create_queue(3);
    enqueue(queue2, 3);
    enqueue(queue2, 4);

    Queue* queue3 = create_queue(3);
    enqueue(queue3, 5);
    enqueue(queue3, 6);

    Queue* queue4 = create_queue(3);
    enqueue(queue4, 7);
    enqueue(queue4, 8);

    push_queue(stack, queue1);
    push_queue(stack, queue2);
    push_queue(stack, queue3);
    push_queue(stack, queue4);

    // Print the stack before merging
    printf("Stack before merging:\n");
    for (int idx = 0; idx <= stack->top; idx++) {
        Queue* queue = stack->data[idx];
        for (int j = 0; j < queue->size; j++) {
            printf("%d ", queue->data[(queue->front + j) % queue->capacity]);
        }
        printf("\n");
    }

    // Merge queue1 and queue2, place in position 1, and remove the original queues
    merge_inner_queues_in_stack(stack, 0, 1, 1);

    // Print the stack after merging
    printf("Stack after merging queues 0 and 1 into position 1:\n");
    for (int idx = 0; idx <= stack->top; idx++) {
        Queue* queue = stack->data[idx];
        for (int j = 0; j < queue->size; j++) {
            printf("%d ", queue->data[(queue->front + j) % queue->capacity]);
        }
        printf("\n");
    }

    // Free the stack
    free_stack_of_queues(stack);

    return 0;
}