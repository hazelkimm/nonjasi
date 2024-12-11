#include <stdio.h>
#include <stdlib.h>

/*
 * Node 구조체: 연결 리스트의 노드.
 * 각 노드는 정수 값(val)과 다음 노드를 가리키는 포인터(next)를 포함.
 */
typedef struct Node {
    int val;             // 노드의 값
    struct Node* next;   // 다음 노드를 가리키는 포인터
} Node;

/*
 * MaxHeap 구조체: 연결 리스트를 이용하여 최대 힙을 구현.
 * head는 힙의 첫 번째 노드를 가리킴.
 */
typedef struct {
    Node* head; // 힙의 루트 노드를 가리킴
} MaxHeap;

// 함수 프로토타입
MaxHeap* createMaxHeap();                   // 빈 Max-Heap 생성
Node* createNode(int value);                // 새 노드 생성
void maxHeapInsert(MaxHeap* heap, int value); // Max-Heap에 값 삽입
int maxHeapPop(MaxHeap* heap);              // 최대값 제거 및 반환
void printMaxHeap(MaxHeap* heap);           // Max-Heap 출력
void freeMaxHeap(MaxHeap* heap);            // Max-Heap 메모리 해제
void sortMaxHeap(MaxHeap* heap);            // Max-Heap 정렬

// 빈 Max-Heap 생성
MaxHeap* createMaxHeap() {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    heap->head = NULL; // 초기에는 힙이 비어 있음
    return heap;
}

// 새 노드 생성
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = value;
    newNode->next = NULL;
    return newNode;
}

// Max-Heap에 값 삽입
void maxHeapInsert(MaxHeap* heap, int value) {
    Node* newNode = createNode(value);

    // 힙이 비었거나, 새로운 값이 루트보다 큰 경우
    if (!heap->head || value > heap->head->val) {
        newNode->next = heap->head;
        heap->head = newNode;
    } else {
        Node* current = heap->head;

        // 삽입할 위치를 찾기 위해 리스트 순회
        while (current->next && current->next->val >= value) {
            current = current->next;
        }

        // 새로운 노드를 연결
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Max-Heap에서 최대값 제거 및 반환
int maxHeapPop(MaxHeap* heap) {
    if (!heap->head) {
        printf("Max-Heap is empty!\n");
        return -1;
    }

    // 루트 값을 저장하고, 루트 노드를 제거
    int maxValue = heap->head->val;
    Node* temp = heap->head;
    heap->head = heap->head->next;
    free(temp);
    return maxValue;
}

// Max-Heap 출력
void printMaxHeap(MaxHeap* heap) {
    Node* current = heap->head;
    while (current) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");
}

// Max-Heap 정렬
void sortMaxHeap(MaxHeap* heap) {
    if (!heap->head) {
        printf("Max-Heap is empty, cannot sort!\n");
        return;
    }

    Node* sortedHead = NULL;

    // 최대값을 반복적으로 제거하여 정렬된 리스트 생성
    while (heap->head) {
        int maxValue = maxHeapPop(heap);

        // 새로운 노드를 정렬된 리스트에 추가
        Node* newNode = createNode(maxValue);
        newNode->next = sortedHead;
        sortedHead = newNode;
    }

    // 정렬된 리스트를 힙으로 복사
    heap->head = sortedHead;
}

// Max-Heap 메모리 해제
void freeMaxHeap(MaxHeap* heap) {
    Node* current = heap->head;

    // 모든 노드 순회하며 메모리 해제
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    // 힙 구조체 메모리 해제
    free(heap);
}

// 메인 함수: 구현 테스트
int main() {
    printf("\nMax-Heap with Linked List Implementation:\n");

    // 빈 힙 생성
    MaxHeap* heap = createMaxHeap();

    // 힙에 값 삽입
    maxHeapInsert(heap, 10);
    maxHeapInsert(heap, 20);
    maxHeapInsert(heap, 5);
    maxHeapInsert(heap, 15);

    printf("Max-Heap after insertions: ");
    printMaxHeap(heap);

    // 힙 정렬
    printf("\nSorting the Max-Heap:\n");
    sortMaxHeap(heap);
    printMaxHeap(heap);

    // 최대값 제거
    printf("\nPopping maximum: %d\n", maxHeapPop(heap));
    printf("Max-Heap after popping: ");
    printMaxHeap(heap);

    // 메모리 해제
    freeMaxHeap(heap);

    return 0;
}