#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int val;
    struct Node* next;
} Node;

// Min-Heap structure implemented as a linked list
typedef struct {
    Node* head;
} MinHeap;

// Function prototypes
MinHeap* createMinHeap();
Node* createNode(int value);
void minHeapInsert(MinHeap* heap, int value);
int minHeapPop(MinHeap* heap);
void printMinHeap(MinHeap* heap);
void freeMinHeap(MinHeap* heap);

// Create an empty Min-Heap
MinHeap* createMinHeap() {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->head = NULL;
    return heap;
}

// Create a new node
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = value;
    newNode->next = NULL;
    return newNode;
}

// Insert into the Min-Heap
void minHeapInsert(MinHeap* heap, int value) {
    Node* newNode = createNode(value);
    if (!heap->head || value < heap->head->val) {
        newNode->next = heap->head;
        heap->head = newNode;
    } else {
        Node* current = heap->head;
        while (current->next && current->next->val <= value) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Remove and return the minimum value
int minHeapPop(MinHeap* heap) {
    if (!heap->head) {
        printf("Min-Heap is empty!\n");
        return -1;
    }
    int minValue = heap->head->val;
    Node* temp = heap->head;
    heap->head = heap->head->next;
    free(temp);
    return minValue;
}

// Print the Min-Heap
void printMinHeap(MinHeap* heap) {
    Node* current = heap->head;
    while (current) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");
}

// Free all nodes in the Min-Heap
void freeMinHeap(MinHeap* heap) {
    Node* current = heap->head;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(heap);
}

// Main function to test the Min-Heap
int main() {
    printf("Min-Heap with Linked List Implementation:\n");

    MinHeap* heap = createMinHeap();

    minHeapInsert(heap, 10);
    minHeapInsert(heap, 20);
    minHeapInsert(heap, 5);
    minHeapInsert(heap, 15);

    printf("Min-Heap after insertions: ");
    printMinHeap(heap);

    printf("Popping minimum: %d\n", minHeapPop(heap));
    printf("Min-Heap after popping: ");
    printMinHeap(heap);

    freeMinHeap(heap);
    return 0;
}