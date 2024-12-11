#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 100

/*
 * Pair 구조체: 두 정수 (x, y)를 저장하는 구조체.
 * MaxHeap 구조체: Pair로 이루어진 최대 힙을 구현하는 구조체.
 */

// Pair 구조체 정의
typedef struct {
    int x, y; // 두 정수 값
} Pair;

// MaxHeap 구조체 정의
typedef struct {
    Pair elements[HEAP_SIZE]; // Pair 요소를 저장하는 배열
    int size;                 // 현재 힙에 저장된 요소의 개수
} MaxHeap;

// 함수 프로토타입 선언
MaxHeap createMaxHeap();                   // 빈 Max-Heap 생성
void maxHeapInsert(MaxHeap* heap, Pair value); // Max-Heap에 Pair 삽입
Pair maxHeapPop(MaxHeap* heap);            // 최대값 제거 및 반환
void printMaxHeap(MaxHeap* heap);          // Max-Heap 출력
void bubbleUpMax(MaxHeap* heap, int index); // 삽입 시 최대 힙 속성 유지
void bubbleDownMax(MaxHeap* heap, int index); // 제거 시 최대 힙 속성 유지
void maxHeapify(MaxHeap* heap, int size, int index); // 최대 힙 속성 복구
void sortMaxHeap(MaxHeap* heap);           // Max-Heap 정렬
int comparePairsMax(Pair a, Pair b);       // Pair 비교 함수 (Max-Heap 기준)

// 빈 Max-Heap 생성
MaxHeap createMaxHeap() {
    MaxHeap heap = {.size = 0};
    return heap;
}

// Max-Heap에 Pair 삽입
void maxHeapInsert(MaxHeap* heap, Pair value) {
    if (heap->size >= HEAP_SIZE) {
        printf("Max-Heap is full!\n");
        return;
    }
    heap->elements[heap->size] = value;
    bubbleUpMax(heap, heap->size); // 삽입 후 힙 속성 유지
    heap->size++;
}

// Max-Heap에서 최대값 제거 및 반환
Pair maxHeapPop(MaxHeap* heap) {
    if (heap->size == 0) {
        printf("Max-Heap is empty!\n");
        return (Pair){-1, -1};
    }
    Pair maxValue = heap->elements[0];     // 루트 요소 저장
    heap->elements[0] = heap->elements[--heap->size]; // 마지막 요소를 루트로 이동
    bubbleDownMax(heap, 0);                // 힙 속성 복구
    return maxValue;
}

// Max-Heap 출력
void printMaxHeap(MaxHeap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("(%d, %d) ", heap->elements[i].x, heap->elements[i].y);
    }
    printf("\n");
}

// Pair 비교 함수 (x를 우선 비교, 같으면 y 비교)
int comparePairsMax(Pair a, Pair b) {
    if (a.x != b.x) {
        return b.x - a.x; // x값이 큰 Pair가 우선순위 높음
    }
    return b.y - a.y;     // x값이 같으면 y값이 큰 Pair 우선
}

// 삽입 시 최대 힙 속성 유지
void bubbleUpMax(MaxHeap* heap, int index) {
    while (index > 0 && comparePairsMax(heap->elements[index], heap->elements[(index - 1) / 2]) > 0) {
        Pair temp = heap->elements[index];
        heap->elements[index] = heap->elements[(index - 1) / 2];
        heap->elements[(index - 1) / 2] = temp;
        index = (index - 1) / 2;
    }
}

// 제거 시 최대 힙 속성 유지
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

// maxHeapify 함수: 특정 노드에서 시작하여 최대 힙 속성 복구
void maxHeapify(MaxHeap* heap, int size, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && comparePairsMax(heap->elements[left], heap->elements[largest]) > 0) {
        largest = left;
    }
    if (right < size && comparePairsMax(heap->elements[right], heap->elements[largest]) > 0) {
        largest = right;
    }

    if (largest != index) {
        Pair temp = heap->elements[index];
        heap->elements[index] = heap->elements[largest];
        heap->elements[largest] = temp;

        maxHeapify(heap, size, largest);
    }
}

// Max-Heap 정렬
void sortMaxHeap(MaxHeap* heap) {
    int originalSize = heap->size;

    // 최대 힙 생성
    for (int i = heap->size / 2 - 1; i >= 0; i--) {
        maxHeapify(heap, heap->size, i);
    }

    // 요소를 하나씩 정렬
    for (int i = heap->size - 1; i > 0; i--) {
        Pair temp = heap->elements[0];
        heap->elements[0] = heap->elements[i];
        heap->elements[i] = temp;

        maxHeapify(heap, i, 0);
    }

    // 크기 복원
    heap->size = originalSize;
}

// 메인 함수: Max-Heap 테스트
int main() {
    printf("\nMax-Heap with Pairs Implementation:\n");

    MaxHeap heap = createMaxHeap();

    maxHeapInsert(&heap, (Pair){10, 20});
    maxHeapInsert(&heap, (Pair){15, 25});
    maxHeapInsert(&heap, (Pair){5, 10});
    maxHeapInsert(&heap, (Pair){10, 15});

    printf("Max-Heap after insertions: ");
    printMaxHeap(&heap);

    printf("\nSorting the Max-Heap:\n");
    sortMaxHeap(&heap);
    printMaxHeap(&heap);

    printf("\nPopping maximum: ");
    Pair p = maxHeapPop(&heap);
    printf("(%d, %d)\n", p.x, p.y);

    printf("Max-Heap after popping: ");
    printMaxHeap(&heap);

    return 0;
}