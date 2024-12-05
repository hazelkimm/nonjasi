#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 100

// Pair struct
typedef struct {
    int x, y;
} Pair;

// Priority Queue for pairs (max-heap)
typedef struct {
    Pair elements[HEAP_SIZE];
    int size;
} PriorityQueue;

// Node in the linked list
typedef struct Node {
    PriorityQueue heap;
    struct Node* next;
} Node;

// Function prototypes
PriorityQueue createPriorityQueue();
void priorityQueueInsert(PriorityQueue* pq, Pair value);
Pair priorityQueuePop(PriorityQueue* pq);
void printPriorityQueue(PriorityQueue* pq);

Node* createNode();
void addNode(Node** head);
void printHeaps(Node* head);

void bubbleUp(PriorityQueue* pq, int index);
void bubbleDown(PriorityQueue* pq, int index);
int comparePairs(Pair a, Pair b);

// Create an empty priority queue
PriorityQueue createPriorityQueue() {
    PriorityQueue pq = {.size = 0};
    return pq;
}

// Insert into the priority queue (max-heap logic)
void priorityQueueInsert(PriorityQueue* pq, Pair value) {
    if (pq->size >= HEAP_SIZE) {
        printf("Priority queue is full!\n");
        return;
    }
    pq->elements[pq->size] = value;
    bubbleUp(pq, pq->size);
    pq->size++;
}

// Remove and return the maximum pair
Pair priorityQueuePop(PriorityQueue* pq) {
    if (pq->size == 0) {
        printf("Priority queue is empty!\n");
        return (Pair){-1, -1};
    }
    Pair maxValue = pq->elements[0];
    pq->elements[0] = pq->elements[--pq->size];
    bubbleDown(pq, 0);
    return maxValue;
}

// Print the priority queue
void printPriorityQueue(PriorityQueue* pq) {
    for (int i = 0; i < pq->size; i++) {
        printf("(%d, %d) ", pq->elements[i].x, pq->elements[i].y);
    }
    printf("\n");
}

// Compare two pairs
int comparePairs(Pair a, Pair b) {
    if (a.x != b.x) {
        return b.x - a.x;
    }
    return b.y - a.y;
}

// Maintain the max-heap property during insertion
void bubbleUp(PriorityQueue* pq, int index) {
    while (index > 0 && comparePairs(pq->elements[index], pq->elements[(index - 1) / 2]) > 0) {
        Pair temp = pq->elements[index];
        pq->elements[index] = pq->elements[(index - 1) / 2];
        pq->elements[(index - 1) / 2] = temp;
        index = (index - 1) / 2;
    }
}

// Maintain the max-heap property during removal
void bubbleDown(PriorityQueue* pq, int index) {
    int size = pq->size;
    while (index * 2 + 1 < size) {
        int child = index * 2 + 1;
        if (child + 1 < size && comparePairs(pq->elements[child + 1], pq->elements[child]) > 0) {
            child++;
        }
        if (comparePairs(pq->elements[index], pq->elements[child]) >= 0) {
            break;
        }
        Pair temp = pq->elements[index];
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
    printf("\nMax-Heap with Pairs in Linked List:\n");

    Node* head = NULL;
    addNode(&head);
    addNode(&head);

    // Add elements to the first node's heap
    priorityQueueInsert(&head->heap, (Pair){10, 20});
    priorityQueueInsert(&head->heap, (Pair){15, 25});
    priorityQueueInsert(&head->heap, (Pair){5, 10});

    // Add elements to the second node's heap
    priorityQueueInsert(&head->next->heap, (Pair){20, 30});
    priorityQueueInsert(&head->next->heap, (Pair){25, 15});
    priorityQueueInsert(&head->next->heap, (Pair){30, 5});

    printf("Heaps in the linked list after insertion:\n");
    printHeaps(head);

    // Pop elements from the heaps
    printf("\nPopping elements from the first heap:\n");
    Pair p = priorityQueuePop(&head->heap);
    printf("Popped: (%d, %d)\n", p.x, p.y);
    printf("Heap after popping: ");
    printPriorityQueue(&head->heap);

    printf("\nPopping elements from the second heap:\n");
    Pair q = priorityQueuePop(&head->next->heap);
    printf("Popped: (%d, %d)\n", q.x, q.y);
    printf("Heap after popping: ");
    printPriorityQueue(&head->next->heap);

    return 0;
}