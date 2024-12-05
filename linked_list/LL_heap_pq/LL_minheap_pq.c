#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 100

// Priority Queue for integers
typedef struct {
    int elements[HEAP_SIZE];
    int size;
} PriorityQueue;

// Node in the linked list
typedef struct Node {
    PriorityQueue heap;
    struct Node* next;
} Node;

// Function prototypes
PriorityQueue createPriorityQueue();
void priorityQueueInsert(PriorityQueue* pq, int value);
int priorityQueuePop(PriorityQueue* pq);
void printPriorityQueue(PriorityQueue* pq);

Node* createNode();
void addNode(Node** head);
void printHeaps(Node* head);

// Helper function to maintain the min-heap property
void bubbleUp(PriorityQueue* pq, int index);
void bubbleDown(PriorityQueue* pq, int index);

// Create an empty priority queue
PriorityQueue createPriorityQueue() {
    PriorityQueue pq = {.size = 0};
    return pq;
}

// Insert into the priority queue (min-heap logic)
void priorityQueueInsert(PriorityQueue* pq, int value) {
    if (pq->size >= HEAP_SIZE) {
        printf("Priority queue is full!\n");
        return;
    }
    pq->elements[pq->size] = value;
    bubbleUp(pq, pq->size);
    pq->size++;
}

// Remove and return the minimum element
int priorityQueuePop(PriorityQueue* pq) {
    if (pq->size == 0) {
        printf("Priority queue is empty!\n");
        return -1;
    }
    int minValue = pq->elements[0];
    pq->elements[0] = pq->elements[--pq->size];
    bubbleDown(pq, 0);
    return minValue;
}

// Print the priority queue
void printPriorityQueue(PriorityQueue* pq) {
    for (int i = 0; i < pq->size; i++) {
        printf("%d ", pq->elements[i]);
    }
    printf("\n");
}

// Maintain the min-heap property during insertion
void bubbleUp(PriorityQueue* pq, int index) {
    while (index > 0 && pq->elements[index] < pq->elements[(index - 1) / 2]) {
        int temp = pq->elements[index];
        pq->elements[index] = pq->elements[(index - 1) / 2];
        pq->elements[(index - 1) / 2] = temp;
        index = (index - 1) / 2;
    }
}

// Maintain the min-heap property during removal
void bubbleDown(PriorityQueue* pq, int index) {
    int size = pq->size;
    while (index * 2 + 1 < size) {
        int child = index * 2 + 1;
        if (child + 1 < size && pq->elements[child + 1] < pq->elements[child]) {
            child++;
        }
        if (pq->elements[index] <= pq->elements[child]) {
            break;
        }
        int temp = pq->elements[index];
        pq->elements[index] = pq->elements[child];
        pq->elements[child] = temp;
        index = child;
    }
}

// Create a new linked list node
Node* createNode() {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->heap = createPriorityQueue();
    newNode->next = NULL;
    return newNode;
}

// Add a new node to the linked list
void addNode(Node** head) {
    Node* newNode = createNode();
    newNode->next = *head;
    *head = newNode;
}

// Print all heaps in the linked list
void printHeaps(Node* head) {
    Node* current = head;
    int index = 0;
    while (current != NULL) {
        printf("Heap in Node %d: ", index++);
        printPriorityQueue(&current->heap);
        current = current->next;
    }
}

// Main function to test the implementation
int main() {
    printf("Min-Heap with Integers in Linked List:\n");

    Node* head = NULL;
    addNode(&head);
    addNode(&head);

    // Add elements to the first node's heap
    priorityQueueInsert(&head->heap, 10);
    priorityQueueInsert(&head->heap, 20);
    priorityQueueInsert(&head->heap, 5);

    // Add elements to the second node's heap
    priorityQueueInsert(&head->next->heap, 15);
    priorityQueueInsert(&head->next->heap, 25);
    priorityQueueInsert(&head->next->heap, 30);

    printf("Heaps in the linked list after insertion:\n");
    printHeaps(head);

    // Pop elements from the heaps
    printf("\nPopping elements from the first heap:\n");
    printf("Popped: %d\n", priorityQueuePop(&head->heap));
    printf("Heap after popping: ");
    printPriorityQueue(&head->heap);

    return 0;
}