#include <stdio.h>
#include <stdlib.h>

// Node 구조체 정의
typedef struct Node {
    int val;               // 노드 값
    struct Node* next;     // 다음 노드를 가리키는 포인터
} Node;

// Min-Heap 구조체 정의 (연결 리스트로 구현)
typedef struct {
    Node* head;            // Min-Heap의 시작 노드
} MinHeap;

// 함수 프로토타입 선언
MinHeap* createMinHeap();                    // Min-Heap 초기화
Node* createNode(int value);                 // 새 노드 생성
void minHeapInsert(MinHeap* heap, int value);// Min-Heap에 값 삽입
int minHeapPop(MinHeap* heap);               // Min-Heap에서 최소값 제거 및 반환
void printMinHeap(MinHeap* heap);            // Min-Heap 출력
void freeMinHeap(MinHeap* heap);             // Min-Heap 메모리 해제
void sortMinHeap(MinHeap* heap);             // Min-Heap 정렬

// Min-Heap 초기화 함수
MinHeap* createMinHeap() {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->head = NULL;
    return heap;
}

// 새 노드 생성 함수
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = value;
    newNode->next = NULL;
    return newNode;
}

// Min-Heap에 값 삽입 함수
void minHeapInsert(MinHeap* heap, int value) {
    Node* newNode = createNode(value);
    // 새로운 값이 현재 헤드보다 작으면 맨 앞에 삽입
    if (!heap->head || value < heap->head->val) {
        newNode->next = heap->head;
        heap->head = newNode;
    } else {
        // 새로운 값을 삽입할 위치를 찾아 삽입
        Node* current = heap->head;
        while (current->next && current->next->val <= value) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Min-Heap에서 최소값 제거 및 반환
int minHeapPop(MinHeap* heap) {
    if (!heap->head) {
        printf("Min-Heap is empty!\n");
        return -1;
    }
    int minValue = heap->head->val;
    Node* temp = heap->head;
    heap->head = heap->head->next;
    free(temp);
    return minValue;
}

// Min-Heap 출력 함수
void printMinHeap(MinHeap* heap) {
    Node* current = heap->head;
    while (current) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");
}

// Min-Heap 정렬 함수
void sortMinHeap(MinHeap* heap) {
    Node* current = heap->head;
    int size = 0;

    // Min-Heap의 크기 계산
    while (current) {
        size++;
        current = current->next;
    }

    // Min-Heap의 요소를 배열에 저장
    int* arr = (int*)malloc(size * sizeof(int));
    current = heap->head;
    for (int i = 0; i < size; i++) {
        arr[i] = current->val;
        current = current->next;
    }

    // 배열을 오름차순으로 정렬
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // 정렬된 배열 출력
    printf("Sorted Min-Heap: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 메모리 해제
    free(arr);
}

// Min-Heap 메모리 해제 함수
void freeMinHeap(MinHeap* heap) {
    Node* current = heap->head;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(heap);
}

// 메인 함수: Min-Heap 테스트
int main() {
    printf("Min-Heap with Linked List Implementation:\n");

    MinHeap* heap = createMinHeap();

    // Min-Heap에 값 삽입
    minHeapInsert(heap, 10);
    minHeapInsert(heap, 20);
    minHeapInsert(heap, 5);
    minHeapInsert(heap, 15);

    // Min-Heap 상태 출력
    printf("Min-Heap after insertions: ");
    printMinHeap(heap);

    // Min-Heap에서 최소값 제거
    printf("Popping minimum: %d\n", minHeapPop(heap));
    printf("Min-Heap after popping: ");
    printMinHeap(heap);

    // Min-Heap 정렬
    printf("Sorting Min-Heap:\n");
    sortMinHeap(heap);

    // Min-Heap 메모리 해제
    freeMinHeap(heap);

    return 0;
}