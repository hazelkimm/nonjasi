#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 100

// Pair 구조체: 두 개의 정수 x, y를 저장
typedef struct {
    int x, y;
} Pair;

// MinHeap 구조체: Pair를 저장하는 최소 힙
typedef struct {
    Pair elements[HEAP_SIZE];
    int size; // 현재 힙의 크기
} MinHeap;

// 함수 프로토타입
MinHeap createMinHeap();
void minHeapInsert(MinHeap* heap, Pair value);
Pair minHeapPop(MinHeap* heap);
void printMinHeap(MinHeap* heap);
void bubbleUpMin(MinHeap* heap, int index);
void bubbleDownMin(MinHeap* heap, int index);
void minHeapify(MinHeap* heap, int size, int index);
void sortMinHeap(MinHeap* heap);
int comparePairsMin(Pair a, Pair b);

// 빈 최소 힙 생성
MinHeap createMinHeap() {
    MinHeap heap = {.size = 0};
    return heap;
}

// 최소 힙에 요소 삽입
void minHeapInsert(MinHeap* heap, Pair value) {
    if (heap->size >= HEAP_SIZE) {
        printf("Min-Heap is full!\n");
        return;
    }
    heap->elements[heap->size] = value; // 배열의 마지막에 삽입
    bubbleUpMin(heap, heap->size);      // 힙 속성 복구
    heap->size++;
}

// 최소값을 제거하고 반환
Pair minHeapPop(MinHeap* heap) {
    if (heap->size == 0) {
        printf("Min-Heap is empty!\n");
        return (Pair){-1, -1};
    }
    Pair minValue = heap->elements[0];   // 루트 요소(최소값)
    heap->elements[0] = heap->elements[--heap->size]; // 마지막 요소를 루트로 이동
    bubbleDownMin(heap, 0);             // 힙 속성 복구
    return minValue;
}

// 힙의 모든 요소를 출력
void printMinHeap(MinHeap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("(%d, %d) ", heap->elements[i].x, heap->elements[i].y);
    }
    printf("\n");
}

// 두 Pair를 비교하여 우선순위를 결정 (x 우선, 같으면 y 비교)
int comparePairsMin(Pair a, Pair b) {
    if (a.x != b.x) {
        return a.x - b.x; // x가 작은 Pair 우선
    }
    return a.y - b.y; // x가 같으면 y가 작은 Pair 우선
}

// 삽입 시 최소 힙 속성을 유지하도록 상향 이동
void bubbleUpMin(MinHeap* heap, int index) {
    while (index > 0 && comparePairsMin(heap->elements[index], heap->elements[(index - 1) / 2]) < 0) {
        Pair temp = heap->elements[index];
        heap->elements[index] = heap->elements[(index - 1) / 2];
        heap->elements[(index - 1) / 2] = temp;
        index = (index - 1) / 2;
    }
}

// 삭제 시 최소 힙 속성을 유지하도록 하향 이동
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

// 주어진 노드에서 시작하여 최소 힙 속성을 복구
void minHeapify(MinHeap* heap, int size, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && comparePairsMin(heap->elements[left], heap->elements[smallest]) < 0) {
        smallest = left;
    }
    if (right < size && comparePairsMin(heap->elements[right], heap->elements[smallest]) < 0) {
        smallest = right;
    }
    if (smallest != index) {
        Pair temp = heap->elements[index];
        heap->elements[index] = heap->elements[smallest];
        heap->elements[smallest] = temp;
        minHeapify(heap, size, smallest);
    }
}

// 힙 요소를 오름차순으로 정렬 (힙 정렬 사용)
void sortMinHeap(MinHeap* heap) {
    int originalSize = heap->size;

    // 최소 힙 구조로 변환
    for (int i = heap->size / 2 - 1; i >= 0; i--) {
        minHeapify(heap, heap->size, i);
    }

    // 힙에서 가장 작은 요소를 배열 뒤로 이동하여 정렬
    for (int i = heap->size - 1; i > 0; i--) {
        Pair temp = heap->elements[0];
        heap->elements[0] = heap->elements[i];
        heap->elements[i] = temp;

        minHeapify(heap, i, 0);
    }

    // 원래 크기 복구
    heap->size = originalSize;
}

// 메인 함수: 구현 테스트
int main() {
    printf("Min-Heap with Pairs Implementation:\n");

    MinHeap heap = createMinHeap();

    minHeapInsert(&heap, (Pair){10, 20});
    minHeapInsert(&heap, (Pair){15, 25});
    minHeapInsert(&heap, (Pair){5, 10});
    minHeapInsert(&heap, (Pair){10, 15});

    printf("Min-Heap after insertions: ");
    printMinHeap(&heap);

    printf("\nSorting the heap:\n");
    sortMinHeap(&heap);
    printMinHeap(&heap);

    return 0;
}