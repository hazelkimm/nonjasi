#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 100

/*
 * MaxHeap 구조체: 정수를 저장하며 최대 힙(Max-Heap) 속성을 유지.
 * 주요 기능:
 * - MaxHeap 생성
 * - 값 삽입 (Insert)
 * - 최대값 제거 (Pop)
 * - 현재 힙 출력
 * - 정렬 (Sort)
 */

// MaxHeap 구조체 정의
typedef struct {
    int elements[HEAP_SIZE]; // 힙 요소를 저장하는 배열
    int size;                // 힙에 저장된 요소의 개수
} MaxHeap;

// 함수 프로토타입 선언
MaxHeap createMaxHeap();                   // 빈 힙 생성
void maxHeapInsert(MaxHeap* heap, int value); // 힙에 값 삽입
int maxHeapPop(MaxHeap* heap);             // 최대값 제거 및 반환
void printMaxHeap(MaxHeap* heap);          // 힙 출력
void bubbleUpMax(MaxHeap* heap, int index);   // 버블 업 (삽입 후 힙 속성 복구)
void bubbleDownMax(MaxHeap* heap, int index); // 버블 다운 (제거 후 힙 속성 복구)
void maxHeapify(MaxHeap* heap, int size, int index); // max-heapify 연산
void sortMaxHeap(MaxHeap* heap);           // 힙 정렬

// 빈 힙 생성
MaxHeap createMaxHeap() {
    MaxHeap heap = {.size = 0};
    return heap;
}

// 힙에 값 삽입
void maxHeapInsert(MaxHeap* heap, int value) {
    if (heap->size >= HEAP_SIZE) {
        printf("Max-Heap is full!\n");
        return;
    }
    heap->elements[heap->size] = value;
    bubbleUpMax(heap, heap->size);
    heap->size++;
}

// 최대값 제거 및 반환
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

// 힙 출력
void printMaxHeap(MaxHeap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->elements[i]);
    }
    printf("\n");
}

// 버블 업 연산
void bubbleUpMax(MaxHeap* heap, int index) {
    while (index > 0 && heap->elements[index] > heap->elements[(index - 1) / 2]) {
        int temp = heap->elements[index];
        heap->elements[index] = heap->elements[(index - 1) / 2];
        heap->elements[(index - 1) / 2] = temp;
        index = (index - 1) / 2;
    }
}

// 버블 다운 연산
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

// max-heapify 연산
void maxHeapify(MaxHeap* heap, int size, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && heap->elements[left] > heap->elements[largest]) {
        largest = left;
    }
    if (right < size && heap->elements[right] > heap->elements[largest]) {
        largest = right;
    }
    if (largest != index) {
        int temp = heap->elements[index];
        heap->elements[index] = heap->elements[largest];
        heap->elements[largest] = temp;

        maxHeapify(heap, size, largest);
    }
}

// 힙 정렬
void sortMaxHeap(MaxHeap* heap) {
    int originalSize = heap->size;

    // 최대 힙 생성
    for (int i = heap->size / 2 - 1; i >= 0; i--) {
        maxHeapify(heap, heap->size, i);
    }

    // 힙 요소를 하나씩 정렬
    for (int i = heap->size - 1; i > 0; i--) {
        int temp = heap->elements[0];
        heap->elements[0] = heap->elements[i];
        heap->elements[i] = temp;

        maxHeapify(heap, i, 0);
    }

    // 원래 크기 복원
    heap->size = originalSize;
}

// 메인 함수: 구현 테스트
int main() {
    printf("\nMax-Heap Implementation:\n");

    MaxHeap heap = createMaxHeap();

    maxHeapInsert(&heap, 10);
    maxHeapInsert(&heap, 20);
    maxHeapInsert(&heap, 5);
    maxHeapInsert(&heap, 15);

    printf("Max-Heap after insertions: ");
    printMaxHeap(&heap);

    printf("\nSorting the Max-Heap: ");
    sortMaxHeap(&heap);
    printMaxHeap(&heap);

    printf("\nPopping maximum: %d\n", maxHeapPop(&heap));
    printf("Max-Heap after popping: ");
    printMaxHeap(&heap);

    return 0;
}