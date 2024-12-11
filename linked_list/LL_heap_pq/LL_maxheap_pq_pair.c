#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 100

/*
 * Pair 구조체: 두 정수 x와 y를 저장하는 구조체.
 * PriorityQueue 구조체: Pair로 이루어진 최대 힙을 구현하는 구조체.
 * Node 구조체: 우선순위 큐를 포함한 단일 연결 리스트의 노드.
 * 
 * 주요 기능:
 * - PriorityQueue: Pair를 기반으로 최대 힙을 구현. 삽입, 삭제, 출력 지원.
 * - Linked List: PriorityQueue를 포함하는 노드로 구성된 단일 연결 리스트.
 * - 각 노드의 우선순위 큐에 데이터를 삽입, 삭제, 출력하는 기능 제공.
 */

// Pair struct
typedef struct {
    int x, y;
} Pair;

// Priority Queue for pairs (max-heap)
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

// 우선순위 큐 초기화: 빈 큐를 생성합니다.
PriorityQueue createPriorityQueue();

// 우선순위 큐에 새로운 Pair를 삽입합니다.
void priorityQueueInsert(PriorityQueue* pq, Pair value);

// 우선순위 큐에서 가장 큰 Pair를 제거하고 반환합니다.
Pair priorityQueuePop(PriorityQueue* pq);

// 우선순위 큐의 모든 요소를 출력합니다.
void printPriorityQueue(PriorityQueue* pq);

// PriorityQueue 정렬 (힙 정렬 기반)
void priorityQueueSort(PriorityQueue* pq);

// 힙 정렬의 max-heapify 동작
void maxHeapify(PriorityQueue* pq, int size, int index);

// 새로운 연결 리스트 노드를 생성합니다.
Node* createNode();

// 연결 리스트의 맨 앞에 새로운 노드를 추가합니다.
void addNode(Node** head);

// 연결 리스트의 모든 노드의 힙을 출력합니다.
void printHeaps(Node* head);

// 힙 삽입 시 최대 힙 속성을 유지하도록 버블 업 연산을 수행합니다.
void bubbleUp(PriorityQueue* pq, int index);

// 힙 삭제 시 최대 힙 속성을 유지하도록 버블 다운 연산을 수행합니다.
void bubbleDown(PriorityQueue* pq, int index);

// 두 Pair를 비교하여 우선순위를 결정합니다 (x를 우선 비교, 같으면 y 비교).
int comparePairs(Pair a, Pair b);

// Create an empty priority queue
PriorityQueue createPriorityQueue() {
    PriorityQueue pq = {.size = 0};
    return pq;
}

// Insert into the priority queue (max-heap logic)
void priorityQueueInsert(PriorityQueue* pq, Pair value) {
    if (pq->size >= HEAP_SIZE) {
        printf("Priority queue is full!\n");
        return;
    }
    pq->elements[pq->size] = value;
    bubbleUp(pq, pq->size);
    pq->size++;
}

// Remove and return the maximum pair
Pair priorityQueuePop(PriorityQueue* pq) {
    if (pq->size == 0) {
        printf("Priority queue is empty!\n");
        return (Pair){-1, -1};
    }
    Pair maxValue = pq->elements[0];
    pq->elements[0] = pq->elements[--pq->size];
    bubbleDown(pq, 0);
    return maxValue;
}

// Print the priority queue
void printPriorityQueue(PriorityQueue* pq) {
    for (int i = 0; i < pq->size; i++) {
        printf("(%d, %d) ", pq->elements[i].x, pq->elements[i].y);
    }
    printf("\n");
}

// Compare two pairs
int comparePairs(Pair a, Pair b) {
    if (a.x != b.x) {
        return b.x - a.x;
    }
    return b.y - a.y;
}

// Maintain the max-heap property during insertion
void bubbleUp(PriorityQueue* pq, int index) {
    while (index > 0 && comparePairs(pq->elements[index], pq->elements[(index - 1) / 2]) > 0) {
        Pair temp = pq->elements[index];
        pq->elements[index] = pq->elements[(index - 1) / 2];
        pq->elements[(index - 1) / 2] = temp;
        index = (index - 1) / 2;
    }
}

// Maintain the max-heap property during removal
void bubbleDown(PriorityQueue* pq, int index) {
    int size = pq->size;
    while (index * 2 + 1 < size) {
        int child = index * 2 + 1;
        if (child + 1 < size && comparePairs(pq->elements[child + 1], pq->elements[child]) > 0) {
            child++;
        }
        if (comparePairs(pq->elements[index], pq->elements[child]) >= 0) {
            break;
        }
        Pair temp = pq->elements[index];
        pq->elements[index] = pq->elements[child];
        pq->elements[child] = temp;
        index = child;
    }
}

// Max-heapify function for sorting
void maxHeapify(PriorityQueue* pq, int size, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    // Check left child
    if (left < size && comparePairs(pq->elements[left], pq->elements[largest]) > 0) {
        largest = left;
    }

    // Check right child
    if (right < size && comparePairs(pq->elements[right], pq->elements[largest]) > 0) {
        largest = right;
    }

    // If largest is not the current index
    if (largest != index) {
        Pair temp = pq->elements[index];
        pq->elements[index] = pq->elements[largest];
        pq->elements[largest] = temp;

        // Recursively heapify the affected subtree
        maxHeapify(pq, size, largest);
    }
}

// Heap sort for PriorityQueue
void priorityQueueSort(PriorityQueue* pq) {
    int originalSize = pq->size;

    // Build the max heap
    for (int i = pq->size / 2 - 1; i >= 0; i--) {
        maxHeapify(pq, pq->size, i);
    }

    // Extract elements from heap one by one
    for (int i = pq->size - 1; i > 0; i--) {
        // Move current root to the end
        Pair temp = pq->elements[0];
        pq->elements[0] = pq->elements[i];
        pq->elements[i] = temp;

        // Reduce the heap size and call maxHeapify
        maxHeapify(pq, i, 0);
    }

    // Restore original size
    pq->size = originalSize;
}

// Main function to test heap sort
int main() {
    PriorityQueue pq = createPriorityQueue();

    priorityQueueInsert(&pq, (Pair){10, 20});
    priorityQueueInsert(&pq, (Pair){15, 25});
    priorityQueueInsert(&pq, (Pair){5, 10});
    priorityQueueInsert(&pq, (Pair){20, 30});

    printf("Priority Queue before sorting:\n");
    printPriorityQueue(&pq);

    priorityQueueSort(&pq);

    printf("Priority Queue after sorting:\n");
    printPriorityQueue(&pq);

    return 0;
}