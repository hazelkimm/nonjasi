#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 100

/*
 * PriorityQueue 구조체: 정수를 저장하고 최대 힙 구조를 유지하는 우선순위 큐.
 * Node 구조체: PriorityQueue를 포함하는 단일 연결 리스트의 노드.
 *
 * 주요 기능:
 * - PriorityQueue: 정수를 기반으로 최대 힙을 구현. 삽입, 삭제, 출력 지원.
 * - Linked List: PriorityQueue를 포함하는 노드로 구성된 단일 연결 리스트.
 * - 각 노드의 PriorityQueue에 데이터 삽입, 삭제, 출력 가능.
 */

// Priority Queue 구조체 정의 (정수용 최대 힙)
typedef struct {
    int elements[HEAP_SIZE];
    int size;
} PriorityQueue;

// 단일 연결 리스트 노드 정의
typedef struct Node {
    PriorityQueue heap;
    struct Node* next;
} Node;

// 함수 프로토타입 선언

// 우선순위 큐 초기화: 빈 큐를 생성합니다.
PriorityQueue createPriorityQueue();

// 우선순위 큐에 새로운 값을 삽입합니다.
void priorityQueueInsert(PriorityQueue* pq, int value);

// 우선순위 큐에서 최대 값을 제거하고 반환합니다.
int priorityQueuePop(PriorityQueue* pq);

// 우선순위 큐의 모든 요소를 출력합니다.
void printPriorityQueue(PriorityQueue* pq);

// 힙 삽입 시 최대 힙 속성을 유지하도록 버블 업 연산을 수행합니다.
void bubbleUp(PriorityQueue* pq, int index);

// 힙 삭제 시 최대 힙 속성을 유지하도록 버블 다운 연산을 수행합니다.
void bubbleDown(PriorityQueue* pq, int index);

// 힙 정렬의 max-heapify 동작을 수행합니다.
void maxHeapify(PriorityQueue* pq, int size, int index);

// 우선순위 큐를 힙 정렬합니다.
void priorityQueueSort(PriorityQueue* pq);

// 새로운 연결 리스트 노드를 생성합니다.
Node* createNode();

// 연결 리스트의 맨 앞에 새로운 노드를 추가합니다.
void addNode(Node** head);

// 연결 리스트의 모든 노드의 힙을 출력합니다.
void printHeaps(Node* head);

// 함수 구현

// 빈 우선순위 큐를 생성합니다.
PriorityQueue createPriorityQueue() {
    PriorityQueue pq = {.size = 0};
    return pq;
}

// 우선순위 큐에 값을 삽입합니다.
void priorityQueueInsert(PriorityQueue* pq, int value) {
    if (pq->size >= HEAP_SIZE) {
        printf("우선순위 큐가 가득 찼습니다!\n");
        return;
    }
    pq->elements[pq->size] = value;
    bubbleUp(pq, pq->size);
    pq->size++;
}

// 우선순위 큐에서 최대 값을 제거하고 반환합니다.
int priorityQueuePop(PriorityQueue* pq) {
    if (pq->size == 0) {
        printf("우선순위 큐가 비어 있습니다!\n");
        return -1;
    }
    int maxValue = pq->elements[0];
    pq->elements[0] = pq->elements[--pq->size];
    bubbleDown(pq, 0);
    return maxValue;
}

// 우선순위 큐의 모든 요소를 출력합니다.
void printPriorityQueue(PriorityQueue* pq) {
    for (int i = 0; i < pq->size; i++) {
        printf("%d ", pq->elements[i]);
    }
    printf("\n");
}

// 버블 업 연산: 힙 삽입 시 최대 힙 속성을 유지합니다.
void bubbleUp(PriorityQueue* pq, int index) {
    while (index > 0 && pq->elements[index] > pq->elements[(index - 1) / 2]) {
        int temp = pq->elements[index];
        pq->elements[index] = pq->elements[(index - 1) / 2];
        pq->elements[(index - 1) / 2] = temp;
        index = (index - 1) / 2;
    }
}

// 버블 다운 연산: 힙 삭제 시 최대 힙 속성을 유지합니다.
void bubbleDown(PriorityQueue* pq, int index) {
    int size = pq->size;
    while (index * 2 + 1 < size) {
        int child = index * 2 + 1;
        if (child + 1 < size && pq->elements[child + 1] > pq->elements[child]) {
            child++;
        }
        if (pq->elements[index] >= pq->elements[child]) {
            break;
        }
        int temp = pq->elements[index];
        pq->elements[index] = pq->elements[child];
        pq->elements[child] = temp;
        index = child;
    }
}

// max-heapify 연산: 힙 정렬 과정에서 최대 힙 속성을 유지합니다.
void maxHeapify(PriorityQueue* pq, int size, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && pq->elements[left] > pq->elements[largest]) {
        largest = left;
    }
    if (right < size && pq->elements[right] > pq->elements[largest]) {
        largest = right;
    }
    if (largest != index) {
        int temp = pq->elements[index];
        pq->elements[index] = pq->elements[largest];
        pq->elements[largest] = temp;

        maxHeapify(pq, size, largest);
    }
}

// 힙 정렬을 수행합니다.
void priorityQueueSort(PriorityQueue* pq) {
    int originalSize = pq->size;

    for (int i = pq->size / 2 - 1; i >= 0; i--) {
        maxHeapify(pq, pq->size, i);
    }

    for (int i = pq->size - 1; i > 0; i--) {
        int temp = pq->elements[0];
        pq->elements[0] = pq->elements[i];
        pq->elements[i] = temp;

        maxHeapify(pq, i, 0);
    }

    pq->size = originalSize;
}

// 새로운 연결 리스트 노드를 생성합니다.
Node* createNode() {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->heap = createPriorityQueue();
    newNode->next = NULL;
    return newNode;
}

// 연결 리스트의 맨 앞에 새로운 노드를 추가합니다.
void addNode(Node** head) {
    Node* newNode = createNode();
    newNode->next = *head;
    *head = newNode;
}

// 연결 리스트의 모든 노드의 힙을 출력합니다.
void printHeaps(Node* head) {
    Node* current = head;
    int index = 0;
    while (current != NULL) {
        printf("노드 %d의 힙: ", index++);
        printPriorityQueue(&current->heap);
        current = current->next;
    }
}

// 메인 함수: 구현 테스트
int main() {
    Node* head = NULL;
    addNode(&head);
    addNode(&head);

    priorityQueueInsert(&head->heap, 15);
    priorityQueueInsert(&head->heap, 20);
    priorityQueueInsert(&head->heap, 10);

    priorityQueueInsert(&head->next->heap, 25);
    priorityQueueInsert(&head->next->heap, 5);
    priorityQueueInsert(&head->next->heap, 30);

    printf("삽입 후 연결 리스트의 힙:\n");
    printHeaps(head);

    priorityQueueSort(&head->heap);
    printf("\n정렬 후 첫 번째 힙:\n");
    printPriorityQueue(&head->heap);

    return 0;
}