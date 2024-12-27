#include <stdio.h>
#include <stdlib.h>

/**********************************************
 * CATALOG OF QUEUE FUNCTIONS
 **********************************************
 * 
 * 1. `create_queue() -> Queue*`:
 *    Initializes and returns an empty queue.
 * 
 * 2. `is_empty(Queue* queue) -> int`:
 *    Checks if the queue is empty. Returns 1 (true) or 0 (false).
 * 
 * 3. `is_full(Queue* queue) -> int`:
 *    Checks if the queue is full. Returns 1 (true) or 0 (false).
 * 
 * 4. `resize_queue(Queue* queue)`:
 *    Doubles the capacity of the queue when it becomes full.
 * 
 * 5. `enqueue(Queue* queue, int value)`:
 *    Adds an element to the rear of the queue.
 * 
 * 6. `dequeue(Queue* queue) -> int`:
 *    Removes and returns the front element of the queue.
 *    Throws an error if the queue is empty.
 * 
 * 7. `peek(Queue* queue) -> int`:
 *    Returns the front element without removing it.
 *    Throws an error if the queue is empty.
 * 
 * 8. `size_of_queue(Queue* queue) -> int`:
 *    Returns the number of elements in the queue.
 * 
 * 9. `free_queue(Queue* queue)`:
 *    Frees the memory allocated for the queue.
 * 
 * 10. `merge_queues(Queue* q1, Queue* q2) -> Queue*`:
 *     Merges two queues into a new queue.
 * 
 * 11. `reverse_queue(Queue* queue)`:
 *     Reverses the elements of the queue in place.
 * 
 * 12. `copy_queue(Queue* queue) -> Queue*`:
 *     Creates and returns a copy of the queue.
 * 
 * 13. `sort_queue(Queue* queue)`:
 *     Sorts the elements of the queue in ascending order.
 * 
 * 14. `slice_queue(Queue* queue, int start, int end) -> Queue*`:
 *     Creates and returns a new queue containing elements
 *     from index `start` to `end - 1`.
 **********************************************/

#define INITIAL_CAPACITY 10

typedef struct {
    int* data;        // Dynamic array for storing queue elements
    int front;        // Index of the front element
    int rear;         // Index of the rear element
    int size;         // Number of elements in the queue
    int capacity;     // Maximum capacity of the queue
} Queue;

// Function to initialize a queue
Queue* create_queue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->data = (int*)malloc(INITIAL_CAPACITY * sizeof(int));
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = INITIAL_CAPACITY;
    return queue;
}

// Function to check if the queue is empty
int is_empty(Queue* queue) {
    return queue->size == 0;
}

// Function to check if the queue is full
int is_full(Queue* queue) {
    return queue->size == queue->capacity;
}

// Function to resize the queue when it's full
void resize_queue(Queue* queue) {
    int* new_data = (int*)malloc(2 * queue->capacity * sizeof(int));
    for (int i = 0; i < queue->size; i++) {
        new_data[i] = queue->data[(queue->front + i) % queue->capacity];
    }
    free(queue->data);
    queue->data = new_data;
    queue->front = 0;
    queue->rear = queue->size - 1;
    queue->capacity *= 2;
}

// Function to add an element to the rear of the queue
void enqueue(Queue* queue, int value) {
    if (is_full(queue)) {
        resize_queue(queue);
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = value;
    queue->size++;
}

// Function to remove and return the front element of the queue
int dequeue(Queue* queue) {
    if (is_empty(queue)) {
        fprintf(stderr, "Queue underflow error!\n");
        exit(EXIT_FAILURE);
    }
    int value = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return value;
}

// Function to get the front element without removing it
int peek(Queue* queue) {
    if (is_empty(queue)) {
        fprintf(stderr, "Queue is empty!\n");
        exit(EXIT_FAILURE);
    }
    return queue->data[queue->front];
}

// Function to return the size of the queue
int size_of_queue(Queue* queue) {
    return queue->size;
}

// Function to free the queue
void free_queue(Queue* queue) {
    free(queue->data);
    free(queue);
}

// ** Function: Merge Two Queues **
Queue* merge_queues(Queue* q1, Queue* q2) {
    Queue* merged_queue = create_queue();
    for (int i = 0; i < q1->size; i++) {
        enqueue(merged_queue, q1->data[(q1->front + i) % q1->capacity]);
    }
    for (int i = 0; i < q2->size; i++) {
        enqueue(merged_queue, q2->data[(q2->front + i) % q2->capacity]);
    }
    return merged_queue;
}

// ** Function: Reverse a Queue **
void reverse_queue(Queue* queue) {
    int left = queue->front, right = (queue->front + queue->size - 1) % queue->capacity;
    while (left != right && (left + 1) % queue->capacity != right) {
        int temp = queue->data[left];
        queue->data[left] = queue->data[right];
        queue->data[right] = temp;
        left = (left + 1) % queue->capacity;
        right = (right - 1 + queue->capacity) % queue->capacity;
    }
}

// ** Function: Copy a Queue **
Queue* copy_queue(Queue* queue) {
    Queue* copied_queue = create_queue();
    copied_queue->size = queue->size;
    copied_queue->capacity = queue->capacity;
    copied_queue->data = (int*)malloc(queue->capacity * sizeof(int));
    for (int i = 0; i < queue->size; i++) {
        copied_queue->data[i] = queue->data[(queue->front + i) % queue->capacity];
    }
    copied_queue->front = 0;
    copied_queue->rear = queue->size - 1;
    return copied_queue;
}

// ** Function: Sort a Queue **
void sort_queue(Queue* queue) {
    int* temp_array = (int*)malloc(queue->size * sizeof(int));
    for (int i = 0; i < queue->size; i++) {
        temp_array[i] = queue->data[(queue->front + i) % queue->capacity];
    }
    for (int i = 0; i < queue->size - 1; i++) {
        for (int j = i + 1; j < queue->size; j++) {
            if (temp_array[i] > temp_array[j]) {
                int temp = temp_array[i];
                temp_array[i] = temp_array[j];
                temp_array[j] = temp;
            }
        }
    }
    for (int i = 0; i < queue->size; i++) {
        queue->data[(queue->front + i) % queue->capacity] = temp_array[i];
    }
    free(temp_array);
}

// ** Function: Slice a Queue **
Queue* slice_queue(Queue* queue, int start, int end) {
    if (start < 0 || end > queue->size || start >= end) {
        fprintf(stderr, "Invalid slice indices!\n");
        exit(EXIT_FAILURE);
    }
    Queue* sliced_queue = create_queue();
    for (int i = start; i < end; i++) {
        enqueue(sliced_queue, queue->data[(queue->front + i) % queue->capacity]);
    }
    return sliced_queue;
}

// Main function for testing
int main() {
    Queue* q1 = create_queue();
    Queue* q2 = create_queue();

    enqueue(q1, 10);
    enqueue(q1, 20);
    enqueue(q1, 30);

    enqueue(q2, 40);
    enqueue(q2, 50);
    enqueue(q2, 60);

    Queue* merged = merge_queues(q1, q2);
    printf("Merged queue: ");
    while (!is_empty(merged)) {
        printf("%d ", dequeue(merged));
    }
    printf("\n");

    reverse_queue(q1);
    printf("Reversed queue q1: ");
    while (!is_empty(q1)) {
        printf("%d ", dequeue(q1));
    }
    printf("\n");

    free_queue(q1);
    free_queue(q2);
    free_queue(merged);
    return 0;
}