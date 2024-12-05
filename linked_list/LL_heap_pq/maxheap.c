#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 100

// Priority Queue for Max-Heap
typedef struct {
    int elements[HEAP_SIZE];
    int size;
} MaxHeap;

// Function prototypes
MaxHeap createMaxHeap();
void maxHeapInsert(MaxHeap* heap, int value);
int maxHeapPop(MaxHeap* heap);
void printMaxHeap(MaxHeap* heap);
void bubbleUpMax(MaxHeap* heap, int index);
void bubbleDownMax(MaxHeap* heap, int index);

// Create an empty max-heap
MaxHeap createMaxHeap() {
    MaxHeap heap = {.size = 0};
    return heap;
}

// Insert into the max-heap
void maxHeapInsert(MaxHeap* heap, int value) {
    if (heap->size >= HEAP_SIZE) {
        printf("Max-Heap is full!\n");
        return;
    }
    heap->elements[heap->size] = value;
    bubbleUpMax(heap, heap->size);
    heap->size++;
}

// Remove and return the maximum element
int maxHeapPop(MaxHeap* heap) {
    if (heap->size == 0) {
        printf("Max-Heap is empty!\n");
        return -1;
    }
    int maxValue = heap->elements[0];
    heap->elements[0] = heap->elements[--heap->size];
    bubbleDownMax(heap, 0);
    return maxValue;
}

// Print the max-heap
void printMaxHeap(MaxHeap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->elements[i]);
    }
    printf("\n");
}

// Maintain the max-heap property during insertion
void bubbleUpMax(MaxHeap* heap, int index) {
    while (index > 0 && heap->elements[index] > heap->elements[(index - 1) / 2]) {
        int temp = heap->elements[index];
        heap->elements[index] = heap->elements[(index - 1) / 2];
        heap->elements[(index - 1) / 2] = temp;
        index = (index - 1) / 2;
    }
}

// Maintain the max-heap property during removal
void bubbleDownMax(MaxHeap* heap, int index) {
    int size = heap->size;
    while (index * 2 + 1 < size) {
        int child = index * 2 + 1;
        if (child + 1 < size && heap->elements[child + 1] > heap->elements[child]) {
            child++;
        }
        if (heap->elements[index] >= heap->elements[child]) {
            break;
        }
        int temp = heap->elements[index];
        heap->elements[index] = heap->elements[child];
        heap->elements[child] = temp;
        index = child;
    }
}

// Test the Max-Heap
int main() {
    printf("\nMax-Heap Implementation:\n");

    MaxHeap heap = createMaxHeap();

    maxHeapInsert(&heap, 10);
    maxHeapInsert(&heap, 20);
    maxHeapInsert(&heap, 5);
    maxHeapInsert(&heap, 15);

    printf("Max-Heap after insertions: ");
    printMaxHeap(&heap);

    printf("Popping maximum: %d\n", maxHeapPop(&heap));
    printf("Max-Heap after popping: ");
    printMaxHeap(&heap);

    return 0;
}