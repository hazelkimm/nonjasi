#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 100

// Priority Queue for Min-Heap
typedef struct {
    int elements[HEAP_SIZE];
    int size;
} MinHeap;

// Function prototypes
MinHeap createMinHeap();
void minHeapInsert(MinHeap* heap, int value);
int minHeapPop(MinHeap* heap);
void printMinHeap(MinHeap* heap);
void bubbleUpMin(MinHeap* heap, int index);
void bubbleDownMin(MinHeap* heap, int index);

// Create an empty min-heap
MinHeap createMinHeap() {
    MinHeap heap = {.size = 0};
    return heap;
}

// Insert into the min-heap
void minHeapInsert(MinHeap* heap, int value) {
    if (heap->size >= HEAP_SIZE) {
        printf("Min-Heap is full!\n");
        return;
    }
    heap->elements[heap->size] = value;
    bubbleUpMin(heap, heap->size);
    heap->size++;
}

// Remove and return the minimum element
int minHeapPop(MinHeap* heap) {
    if (heap->size == 0) {
        printf("Min-Heap is empty!\n");
        return -1;
    }
    int minValue = heap->elements[0];
    heap->elements[0] = heap->elements[--heap->size];
    bubbleDownMin(heap, 0);
    return minValue;
}

// Print the min-heap
void printMinHeap(MinHeap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->elements[i]);
    }
    printf("\n");
}

// Maintain the min-heap property during insertion
void bubbleUpMin(MinHeap* heap, int index) {
    while (index > 0 && heap->elements[index] < heap->elements[(index - 1) / 2]) {
        int temp = heap->elements[index];
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
        if (child + 1 < size && heap->elements[child + 1] < heap->elements[child]) {
            child++;
        }
        if (heap->elements[index] <= heap->elements[child]) {
            break;
        }
        int temp = heap->elements[index];
        heap->elements[index] = heap->elements[child];
        heap->elements[child] = temp;
        index = child;
    }
}

// Test the Min-Heap
int main() {
    printf("Min-Heap Implementation:\n");

    MinHeap heap = createMinHeap();

    minHeapInsert(&heap, 10);
    minHeapInsert(&heap, 20);
    minHeapInsert(&heap, 5);
    minHeapInsert(&heap, 15);

    printf("Min-Heap after insertions: ");
    printMinHeap(&heap);

    printf("Popping minimum: %d\n", minHeapPop(&heap));
    printf("Min-Heap after popping: ");
    printMinHeap(&heap);

    return 0;
}