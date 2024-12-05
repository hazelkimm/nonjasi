#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 100

// Pair struct
typedef struct {
    int x, y;
} Pair;

// Priority Queue for Max-Heap
typedef struct {
    Pair elements[HEAP_SIZE];
    int size;
} MaxHeap;

// Function prototypes
MaxHeap createMaxHeap();
void maxHeapInsert(MaxHeap* heap, Pair value);
Pair maxHeapPop(MaxHeap* heap);
void printMaxHeap(MaxHeap* heap);
void bubbleUpMax(MaxHeap* heap, int index);
void bubbleDownMax(MaxHeap* heap, int index);
int comparePairsMax(Pair a, Pair b);

// Create an empty max-heap
MaxHeap createMaxHeap() {
    MaxHeap heap = {.size = 0};
    return heap;
}

// Insert into the max-heap
void maxHeapInsert(MaxHeap* heap, Pair value) {
    if (heap->size >= HEAP_SIZE) {
        printf("Max-Heap is full!\n");
        return;
    }
    heap->elements[heap->size] = value;
    bubbleUpMax(heap, heap->size);
    heap->size++;
}

// Remove and return the maximum pair
Pair maxHeapPop(MaxHeap* heap) {
    if (heap->size == 0) {
        printf("Max-Heap is empty!\n");
        return (Pair){-1, -1};
    }
    Pair maxValue = heap->elements[0];
    heap->elements[0] = heap->elements[--heap->size];
    bubbleDownMax(heap, 0);
    return maxValue;
}

// Print the max-heap
void printMaxHeap(MaxHeap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("(%d, %d) ", heap->elements[i].x, heap->elements[i].y);
    }
    printf("\n");
}

// Compare two pairs for max-heap logic
int comparePairsMax(Pair a, Pair b) {
    if (a.x != b.x) {
        return b.x - a.x; // Prioritize larger x
    }
    return b.y - a.y; // If x is equal, prioritize larger y
}

// Maintain the max-heap property during insertion
void bubbleUpMax(MaxHeap* heap, int index) {
    while (index > 0 && comparePairsMax(heap->elements[index], heap->elements[(index - 1) / 2]) > 0) {
        Pair temp = heap->elements[index];
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
        if (child + 1 < size && comparePairsMax(heap->elements[child + 1], heap->elements[child]) > 0) {
            child++;
        }
        if (comparePairsMax(heap->elements[index], heap->elements[child]) >= 0) {
            break;
        }
        Pair temp = heap->elements[index];
        heap->elements[index] = heap->elements[child];
        heap->elements[child] = temp;
        index = child;
    }
}

// Main function to test the Max-Heap
int main() {
    printf("\nMax-Heap with Pairs Implementation:\n");

    MaxHeap heap = createMaxHeap();

    maxHeapInsert(&heap, (Pair){10, 20});
    maxHeapInsert(&heap, (Pair){15, 25});
    maxHeapInsert(&heap, (Pair){5, 10});
    maxHeapInsert(&heap, (Pair){10, 15});

    printf("Max-Heap after insertions: ");
    printMaxHeap(&heap);

    printf("Popping maximum: ");
    Pair p = maxHeapPop(&heap);
    printf("(%d, %d)\n", p.x, p.y);

    printf("Max-Heap after popping: ");
    printMaxHeap(&heap);

    return 0;
}