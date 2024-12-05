#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 100

// Pair struct
typedef struct {
    int x, y;
} Pair;

// Priority Queue for Min-Heap
typedef struct {
    Pair elements[HEAP_SIZE];
    int size;
} MinHeap;

// Function prototypes
MinHeap createMinHeap();
void minHeapInsert(MinHeap* heap, Pair value);
Pair minHeapPop(MinHeap* heap);
void printMinHeap(MinHeap* heap);
void bubbleUpMin(MinHeap* heap, int index);
void bubbleDownMin(MinHeap* heap, int index);
int comparePairsMin(Pair a, Pair b);

// Create an empty min-heap
MinHeap createMinHeap() {
    MinHeap heap = {.size = 0};
    return heap;
}

// Insert into the min-heap
void minHeapInsert(MinHeap* heap, Pair value) {
    if (heap->size >= HEAP_SIZE) {
        printf("Min-Heap is full!\n");
        return;
    }
    heap->elements[heap->size] = value;
    bubbleUpMin(heap, heap->size);
    heap->size++;
}

// Remove and return the minimum pair
Pair minHeapPop(MinHeap* heap) {
    if (heap->size == 0) {
        printf("Min-Heap is empty!\n");
        return (Pair){-1, -1};
    }
    Pair minValue = heap->elements[0];
    heap->elements[0] = heap->elements[--heap->size];
    bubbleDownMin(heap, 0);
    return minValue;
}

// Print the min-heap
void printMinHeap(MinHeap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("(%d, %d) ", heap->elements[i].x, heap->elements[i].y);
    }
    printf("\n");
}

// Compare two pairs for min-heap logic
int comparePairsMin(Pair a, Pair b) {
    if (a.x != b.x) {
        return a.x - b.x; // Prioritize smaller x
    }
    return a.y - b.y; // If x is equal, prioritize smaller y
}

// Maintain the min-heap property during insertion
void bubbleUpMin(MinHeap* heap, int index) {
    while (index > 0 && comparePairsMin(heap->elements[index], heap->elements[(index - 1) / 2]) < 0) {
        Pair temp = heap->elements[index];
        heap->elements[index] = heap->elements[(index - 1) / 2];
        heap->elements[(index - 1) / 2] = temp;
        index = (index - 1) / 2;
    }
}

// Maintain the min-heap property during removal
void bubbleDownMin(MinHeap* heap, int index) {
    int size = heap->size;
    while (index * 2 + 1 < size) {
        int child = index * 2 + 1;
        if (child + 1 < size && comparePairsMin(heap->elements[child + 1], heap->elements[child]) < 0) {
            child++;
        }
        if (comparePairsMin(heap->elements[index], heap->elements[child]) <= 0) {
            break;
        }
        Pair temp = heap->elements[index];
        heap->elements[index] = heap->elements[child];
        heap->elements[child] = temp;
        index = child;
    }
}

// Main function to test the Min-Heap
int main() {
    printf("Min-Heap with Pairs Implementation:\n");

    MinHeap heap = createMinHeap();

    minHeapInsert(&heap, (Pair){10, 20});
    minHeapInsert(&heap, (Pair){15, 25});
    minHeapInsert(&heap, (Pair){5, 10});
    minHeapInsert(&heap, (Pair){10, 15});

    printf("Min-Heap after insertions: ");
    printMinHeap(&heap);

    printf("Popping minimum: ");
    Pair p = minHeapPop(&heap);
    printf("(%d, %d)\n", p.x, p.y);

    printf("Min-Heap after popping: ");
    printMinHeap(&heap);

    return 0;
}