#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 100

// MinHeap 구조체 정의
typedef struct {
    int elements[HEAP_SIZE]; // 힙 요소를 저장할 배열
    int size;                // 현재 힙의 크기
} MinHeap;

// 함수 프로토타입 선언
MinHeap createMinHeap();
void minHeapInsert(MinHeap* heap, int value);
int minHeapPop(MinHeap* heap);
void printMinHeap(MinHeap* heap);
void bubbleUpMin(MinHeap* heap, int index);
void bubbleDownMin(MinHeap* heap, int index);
void minHeapify(MinHeap* heap, int size, int index);
void sortMinHeap(MinHeap* heap);

// 빈 MinHeap 생성
MinHeap createMinHeap() {
    MinHeap heap = {.size = 0};
    return heap;
}

// MinHeap에 값을 삽입
void minHeapInsert(MinHeap* heap, int value) {
    if (heap->size >= HEAP_SIZE) {
        printf("Min-Heap is full!\n");
        return;
    }
    heap->elements[heap->size] = value;
    bubbleUpMin(heap, heap->size); // 삽입 후 Min-Heap 속성 복구
    heap->size++;
}

// MinHeap에서 최소값 제거 및 반환
int minHeapPop(MinHeap* heap) {
    if (heap->size == 0) {
        printf("Min-Heap is empty!\n");
        return -1;
    }
    int minValue = heap->elements[0];        // 루트 요소(최소값) 저장
    heap->elements[0] = heap->elements[--heap->size]; // 마지막 요소를 루트로 이동
    bubbleDownMin(heap, 0);                 // Min-Heap 속성 복구
    return minValue;
}

// MinHeap 출력
void printMinHeap(MinHeap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->elements[i]);
    }
    printf("\n");
}

// 삽입 시 Min-Heap 속성 유지 (Bubble Up)
void bubbleUpMin(MinHeap* heap, int index) {
    while (index > 0 && heap->elements[index] < heap->elements[(index - 1) / 2]) {
        int temp = heap->elements[index];
        heap->elements[index] = heap->elements[(index - 1) / 2];
        heap->elements[(index - 1) / 2] = temp;
        index = (index - 1) / 2; // 부모 인덱스로 이동
    }
}

// 제거 시 Min-Heap 속성 유지 (Bubble Down)
void bubbleDownMin(MinHeap* heap, int index) {
    int size = heap->size;
    while (index * 2 + 1 < size) { // 자식 노드가 존재하는 동안
        int child = index * 2 + 1; // 왼쪽 자식
        if (child + 1 < size && heap->elements[child + 1] < heap->elements[child]) {
            child++; // 오른쪽 자식 선택
        }
        if (heap->elements[index] <= heap->elements[child]) {
            break; // 현재 노드가 자식 노드보다 작거나 같으면 종료
        }
        int temp = heap->elements[index];
        heap->elements[index] = heap->elements[child];
        heap->elements[child] = temp;
        index = child; // 자식 인덱스로 이동
    }
}

// 특정 노드에서 시작하여 서브트리를 Min-Heap으로 복구
void minHeapify(MinHeap* heap, int size, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && heap->elements[left] < heap->elements[smallest]) {
        smallest = left;
    }
    if (right < size && heap->elements[right] < heap->elements[smallest]) {
        smallest = right;
    }
    if (smallest != index) {
        int temp = heap->elements[index];
        heap->elements[index] = heap->elements[smallest];
        heap->elements[smallest] = temp;

        minHeapify(heap, size, smallest); // 재귀적으로 하위 트리 복구
    }
}

// Min-Heap을 정렬 (힙 정렬)
void sortMinHeap(MinHeap* heap) {
    int originalSize = heap->size;

    // Min-Heapify: 힙 속성 복구
    for (int i = originalSize / 2 - 1; i >= 0; i--) {
        minHeapify(heap, originalSize, i);
    }

    // 힙 정렬: 루트(최소값)를 끝으로 보내고 크기를 줄이며 정렬
    for (int i = originalSize - 1; i > 0; i--) {
        int temp = heap->elements[0];
        heap->elements[0] = heap->elements[i];
        heap->elements[i] = temp;

        minHeapify(heap, i, 0); // 크기를 줄이며 Min-Heap 속성 유지
    }

    heap->size = originalSize; // 원래 크기로 복원
}

// Min-Heap 테스트
int main() {
    printf("Min-Heap Implementation:\n");

    MinHeap heap = createMinHeap();

    minHeapInsert(&heap, 10);
    minHeapInsert(&heap, 20);
    minHeapInsert(&heap, 5);
    minHeapInsert(&heap, 15);

    printf("Min-Heap after insertions: ");
    printMinHeap(&heap);

    printf("\nSorting the heap:\n");
    sortMinHeap(&heap);
    printMinHeap(&heap);

    printf("\nPopping minimum: %d\n", minHeapPop(&heap));
    printf("Min-Heap after popping: ");
    printMinHeap(&heap);

    return 0;
}