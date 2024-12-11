#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 100

/*
 * Pair 구조체: 두 정수 x와 y를 저장하는 구조체.
 * PriorityQueue 구조체: Pair로 이루어진 최소 힙을 구현하는 구조체.
 * Node 구조체: PriorityQueue를 포함한 단일 연결 리스트의 노드.
 * 
 * 주요 기능:
 * - PriorityQueue: Pair를 기반으로 최소 힙을 구현. 삽입, 삭제, 출력 지원.
 * - Linked List: PriorityQueue를 포함하는 노드로 구성된 단일 연결 리스트.
 * - 각 노드의 PriorityQueue에 데이터 삽입, 삭제, 출력 가능.
 */

// Pair struct
typedef struct {
    int x, y;
} Pair;

// Priority Queue for pairs (min-heap)
typedef struct {
    Pair elements[HEAP_SIZE];
    int size;
} PriorityQueue;

// Node in the linked list
typedef struct Node {
    PriorityQueue heap;
    struct Node* next;
} Node;

// Function prototypes
PriorityQueue createPriorityQueue();
void priorityQueueInsert(PriorityQueue* pq, Pair value);
Pair priorityQueuePop(PriorityQueue* pq);
void printPriorityQueue(PriorityQueue* pq);

void minHeapify(PriorityQueue* pq, int size, int index);
void priorityQueueSort(PriorityQueue* pq);

void bubbleUp(PriorityQueue* pq, int index);
void bubbleDown(PriorityQueue* pq, int index);

Node* createNode();
void addNode(Node** head);
void printHeaps(Node* head);
int comparePairs(Pair a, Pair b);

// 우선순위 큐 초기화: 빈 큐를 생성합니다.
PriorityQueue createPriorityQueue() {
    PriorityQueue pq = {.size = 0};
    return pq;
}

// 우선순위 큐에 새로운 Pair를 삽입합니다.
void priorityQueueInsert(PriorityQueue* pq, Pair value) {
    if (pq->size >= HEAP_SIZE) {
        printf("우선순위 큐가 가득 찼습니다!\n");
        return;
    }
    pq->elements[pq->size] = value;
    bubbleUp(pq, pq->size);
    pq->size++;
}

// 우선순위 큐에서 최소값을 제거하고 반환합니다.
Pair priorityQueuePop(PriorityQueue* pq) {
    if (pq->size == 0) {
        printf("우선순위 큐가 비어 있습니다!\n");
        return (Pair){-1, -1};
    }
    Pair minValue = pq->elements[0];
    pq->elements[0] = pq->elements[--pq->size];
    bubbleDown(pq, 0);
    return minValue;
}

// 우선순위 큐의 모든 요소를 출력합니다.
void printPriorityQueue(PriorityQueue* pq) {
    for (int i = 0; i < pq->size; i++) {
        printf("(%d, %d) ", pq->elements[i].x, pq->elements[i].y);
    }
    printf("\n");
}

// 두 Pair를 비교하여 우선순위를 결정합니다 (x를 우선 비교, 같으면 y 비교).
int comparePairs(Pair a, Pair b) {
    if (a.x != b.x) {
        return a.x - b.x;
    }
    return a.y - b.y;
}

// 삽입 시 최소 힙 속성을 유지하도록 버블 업 연산을 수행합니다.
void bubbleUp(PriorityQueue* pq, int index) {
    while (index > 0 && comparePairs(pq->elements[index], pq->elements[(index - 1) / 2]) < 0) {
        Pair temp = pq->elements[index];
        pq->elements[index] = pq->elements[(index - 1) / 2];
        pq->elements[(index - 1) / 2] = temp;
        index = (index - 1) / 2;
    }
}

// 삭제 시 최소 힙 속성을 유지하도록 버블 다운 연산을 수행합니다.
void bubbleDown(PriorityQueue* pq, int index) {
    int size = pq->size;
    while (index * 2 + 1 < size) {
        int child = index * 2 + 1;
        if (child + 1 < size && comparePairs(pq->elements[child + 1], pq->elements[child]) < 0) {
            child++;
        }
        if (comparePairs(pq->elements[index], pq->elements[child]) <= 0) {
            break;
        }
        Pair temp = pq->elements[index];
        pq->elements[index] = pq->elements[child];
        pq->elements[child] = temp;
        index = child;
    }
}

// 힙 정렬의 min-heapify 동작을 수행합니다.
void minHeapify(PriorityQueue* pq, int size, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && comparePairs(pq->elements[left], pq->elements[smallest]) < 0) {
        smallest = left;
    }
    if (right < size && comparePairs(pq->elements[right], pq->elements[smallest]) < 0) {
        smallest = right;
    }

    if (smallest != index) {
        Pair temp = pq->elements[index];
        pq->elements[index] = pq->elements[smallest];
        pq->elements[smallest] = temp;

        minHeapify(pq, size, smallest);
    }
}

// 우선순위 큐를 정렬합니다 (힙 정렬 기반).
void priorityQueueSort(PriorityQueue* pq) {
    int originalSize = pq->size;

    // 최소 힙 생성
    for (int i = pq->size / 2 - 1; i >= 0; i--) {
        minHeapify(pq, pq->size, i);
    }

    // 힙 요소를 하나씩 정렬
    for (int i = pq->size - 1; i > 0; i--) {
        Pair temp = pq->elements[0];
        pq->elements[0] = pq->elements[i];
        pq->elements[i] = temp;

        // 축소된 힙에서 힙 속성 복구
        minHeapify(pq, i, 0);
    }

    // 원래 크기 복원
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
    printf("\n최소 힙을 사용하는 연결 리스트 테스트:\n");

    Node* head = NULL;
    addNode(&head);
    addNode(&head);

    // 첫 번째 노드의 힙에 요소 삽입
    priorityQueueInsert(&head->heap, (Pair){10, 20});
    priorityQueueInsert(&head->heap, (Pair){5, 15});
    priorityQueueInsert(&head->heap, (Pair){20, 10});

    // 두 번째 노드의 힙에 요소 삽입
    priorityQueueInsert(&head->next->heap, (Pair){15, 30});
    priorityQueueInsert(&head->next->heap, (Pair){25, 25});
    priorityQueueInsert(&head->next->heap, (Pair){30, 5});

    printf("삽입 후 연결 리스트의 힙:\n");
    printHeaps(head);

    // 첫 번째 힙 정렬
    printf("\n첫 번째 힙 정렬 후:\n");
    priorityQueueSort(&head->heap);
    printPriorityQueue(&head->heap);

    return 0;
}