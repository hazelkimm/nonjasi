#include <stdio.h>
#include <stdlib.h>

/**********************************************
 * CATALOG OF FUNCTIONS
 **********************************************
 *
 * INNER QUEUE (Queue)
 * 1. `Queue* create_queue(int capacity)`
 * 2. `void enqueue(Queue* queue, int value)`
 * 3. `int dequeue(Queue* queue)`
 * 4. `int is_empty_queue(Queue* queue)`
 * 5. `void free_queue(Queue* queue)`
 *
 * OUTER QUEUE (Queue of Queues)
 * 1. `QueueOfQueues* create_queue_of_queues(int capacity)`
 * 2. `void enqueue_queue(QueueOfQueues* outerQueue, Queue* innerQueue)`
 * 3. `Queue* dequeue_queue(QueueOfQueues* outerQueue)`
 * 4. `int is_empty_queue_of_queues(QueueOfQueues* outerQueue)`
 * 5. `void free_queue_of_queues(QueueOfQueues* outerQueue)`
 *
 * MERGING QUEUES
 * 1. `void merge_inner_queues_in_queue(QueueOfQueues* outerQueue, int i, int j, int k)`
 **********************************************/

// Structure for an individual queue (Inner Queue)
typedef struct Queue {
    int* data;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

// Structure for the queue of queues (Outer Queue)
typedef struct QueueOfQueues {
    Queue** data;
    int front;
    int rear;
    int size;
    int capacity;
} QueueOfQueues;

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
        return -1;
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

// Function to free a queue
void free_queue(Queue* queue) {
    free(queue->data);
    free(queue);
}

// Function to create a new queue of queues
QueueOfQueues* create_queue_of_queues(int capacity) {
    QueueOfQueues* outerQueue = (QueueOfQueues*)malloc(sizeof(QueueOfQueues));
    outerQueue->data = (Queue**)malloc(capacity * sizeof(Queue*));
    outerQueue->front = 0;
    outerQueue->rear = -1;
    outerQueue->size = 0;
    outerQueue->capacity = capacity;
    return outerQueue;
}

// Function to enqueue an inner queue into the outer queue
void enqueue_queue(QueueOfQueues* outerQueue, Queue* innerQueue) {
    if (outerQueue->size == outerQueue->capacity) {
        outerQueue->capacity *= 2;
        outerQueue->data = (Queue**)realloc(outerQueue->data, outerQueue->capacity * sizeof(Queue*));
    }
    outerQueue->rear = (outerQueue->rear + 1) % outerQueue->capacity;
    outerQueue->data[outerQueue->rear] = innerQueue;
    outerQueue->size++;
}

// Function to dequeue an inner queue from the outer queue
Queue* dequeue_queue(QueueOfQueues* outerQueue) {
    if (outerQueue->size == 0) {
        printf("Outer queue underflow\n");
        return NULL;
    }
    Queue* frontQueue = outerQueue->data[outerQueue->front];
    outerQueue->front = (outerQueue->front + 1) % outerQueue->capacity;
    outerQueue->size--;
    return frontQueue;
}

// Function to check if the outer queue is empty
int is_empty_queue_of_queues(QueueOfQueues* outerQueue) {
    return outerQueue->size == 0;
}

// Function to free the outer queue and all its inner queues
void free_queue_of_queues(QueueOfQueues* outerQueue) {
    while (!is_empty_queue_of_queues(outerQueue)) {
        free_queue(dequeue_queue(outerQueue));
    }
    free(outerQueue->data);
    free(outerQueue);
}

// Function to merge two inner queues and insert at position `k`
void merge_inner_queues_in_queue(QueueOfQueues* outerQueue, int i, int j, int k) {
    if (i >= outerQueue->size || j >= outerQueue->size || k > outerQueue->size || i == j) {
        printf("Invalid indices\n");
        return;
    }

    // Create a new queue for the merged data
    Queue* mergedQueue = create_queue(outerQueue->data[(outerQueue->front + i) % outerQueue->capacity]->capacity +
                                      outerQueue->data[(outerQueue->front + j) % outerQueue->capacity]->capacity);

    // Add elements from the first queue
    Queue* queue1 = outerQueue->data[(outerQueue->front + i) % outerQueue->capacity];
    for (int idx = 0; idx < queue1->size; idx++) {
        enqueue(mergedQueue, queue1->data[(queue1->front + idx) % queue1->capacity]);
    }

    // Add elements from the second queue
    Queue* queue2 = outerQueue->data[(outerQueue->front + j) % outerQueue->capacity];
    for (int idx = 0; idx < queue2->size; idx++) {
        enqueue(mergedQueue, queue2->data[(queue2->front + idx) % queue2->capacity]);
    }

    // Free the original queues
    free_queue(queue1);
    free_queue(queue2);

    // Shift queues to fill the gap left by `i` and `j`
    for (int idx = i; idx < outerQueue->size - 1; idx++) {
        outerQueue->data[(outerQueue->front + idx) % outerQueue->capacity] =
            outerQueue->data[(outerQueue->front + idx + 1) % outerQueue->capacity];
    }
    for (int idx = j - 1; idx < outerQueue->size - 2; idx++) {
        outerQueue->data[(outerQueue->front + idx) % outerQueue->capacity] =
            outerQueue->data[(outerQueue->front + idx + 1) % outerQueue->capacity];
    }

    // Insert the merged queue at position `k`
    for (int idx = outerQueue->size - 2; idx >= k; idx--) {
        outerQueue->data[(outerQueue->front + idx + 1) % outerQueue->capacity] =
            outerQueue->data[(outerQueue->front + idx) % outerQueue->capacity];
    }
    outerQueue->data[(outerQueue->front + k) % outerQueue->capacity] = mergedQueue;
    outerQueue->rear = (outerQueue->rear + 1) % outerQueue->capacity;
    outerQueue->size--;
}

// Main function for testing
int main() {
    printf("=== Testing Queue in Queue ===\n");

    // Create an outer queue
    QueueOfQueues* outerQueue = create_queue_of_queues(5);

    // Create and enqueue inner queues
    Queue* queue1 = create_queue(3);
    enqueue(queue1, 1);
    enqueue(queue1, 2);

    Queue* queue2 = create_queue(3);
    enqueue(queue2, 3);
    enqueue(queue2, 4);

    Queue* queue3 = create_queue(3);
    enqueue(queue3, 5);
    enqueue(queue3, 6);

    enqueue_queue(outerQueue, queue1);
    enqueue_queue(outerQueue, queue2);
    enqueue_queue(outerQueue, queue3);

    // Print the outer queue before merging
    printf("Outer queue before merging:\n");
    for (int idx = 0; idx < outerQueue->size; idx++) {
        Queue* queue = outerQueue->data[(outerQueue->front + idx) % outerQueue->capacity];
        for (int j = 0; j < queue->size; j++) {
            printf("%d ", queue->data[(queue->front + j) % queue->capacity]);
        }
        printf("\n");
    }

    // Merge queue1 and queue2 and insert at position 1
    merge_inner_queues_in_queue(outerQueue, 0, 1, 1);

    // Print the outer queue after merging
    printf("Outer queue after merging:\n");
    for (int idx = 0; idx < outerQueue->size; idx++) {
        Queue* queue = outerQueue->data[(outerQueue->front + idx) % outerQueue->capacity];
        for (int j = 0; j < queue->size; j++) {
            printf("%d ", queue->data[(queue->front + j) % queue->capacity]);
        }
        printf("\n");
    }

    // Free the outer queue
    free_queue_of_queues(outerQueue);

    return 0;
}