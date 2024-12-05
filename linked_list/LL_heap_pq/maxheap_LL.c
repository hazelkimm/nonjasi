#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int val;
    struct Node* next;
} Node;

// Max-Heap structure implemented as a linked list
typedef struct {
    Node* head;
} MaxHeap;

// Function prototypes
MaxHeap* createMaxHeap();
Node* createNode(int value);
void maxHeapInsert(MaxHeap* heap, int value);
int maxHeapPop(MaxHeap* heap);
void printMaxHeap(MaxHeap* heap);
void freeMaxHeap(MaxHeap* heap);

// Create an empty Max-Heap
MaxHeap* createMaxHeap() {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
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

// Insert into the Max-Heap
void maxHeapInsert(MaxHeap* heap, int value) {
    Node* newNode = createNode(value);
    if (!heap->head || value > heap->head->val) {
        newNode->next = heap->head;
        heap->head = newNode;
    } else {
        Node* current = heap->head;
        while (current->next && current->next->val >= value) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Remove and return the maximum value
int maxHeapPop(MaxHeap* heap) {
    if (!heap->head) {
        printf("Max-Heap is empty!\n");
        return -1;
    }
    int maxValue = heap->head->val;
    Node* temp = heap->head;
    heap->head = heap->head->next;
    free(temp);
    return maxValue;
}

// Print the Max-Heap
void printMaxHeap(MaxHeap* heap) {
    Node* current = heap->head;
    while (current) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");
}

// Free all nodes in the Max-Heap
void freeMaxHeap(MaxHeap* heap) {
    Node* current = heap->head;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(heap);
}

// Main function to test the Max-Heap
int main() {
    printf("\nMax-Heap with Linked List Implementation:\n");

    MaxHeap* heap = createMaxHeap();

    maxHeapInsert(heap, 10);
    maxHeapInsert(heap, 20);
    maxHeapInsert(heap, 5);
    maxHeapInsert(heap, 15);

    printf("Max-Heap after insertions: ");
    printMaxHeap(heap);

    printf("Popping maximum: %d\n", maxHeapPop(heap));
    printf("Max-Heap after popping: ");
    printMaxHeap(heap);

    freeMaxHeap(heap);
    return 0;
}