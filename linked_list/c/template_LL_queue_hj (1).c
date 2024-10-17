#include <stdio.h>
#include <stdlib.h>

#define MAX_CAPACITY 3

// Node 구조체 정의 (Queue를 포함)
typedef struct Node {
    int queue[MAX_CAPACITY];  // 큐를 배열로 구현 (최대 3개까지)
    int front;                // 큐의 첫 번째 원소 인덱스
    int rear;                 // 큐의 마지막 원소 인덱스
    struct Node* next;        // 다음 노드를 가리키는 포인터
} Node;

// Linked List of Queue 구조체 정의
typedef struct {
    Node* head;  // 리스트의 첫 번째 노드를 가리키는 포인터
    Node* tail;  // 리스트의 마지막 노드를 가리키는 포인터
} LinkedListOfQueues;

// 새로운 노드 생성
Node* createNode() {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->front = 0;
    newNode->rear = 0;
    newNode->next = NULL;
    return newNode;
}

// Linked List of Queue 초기화
LinkedListOfQueues* createLinkedListOfQueues() {
    LinkedListOfQueues* list = (LinkedListOfQueues*)malloc(sizeof(LinkedListOfQueues));
    list->head = createNode();  // 빈 노드로 시작
    list->tail = list->head;    // 처음에는 head와 tail이 동일
    return list;
}

// 큐가 가득 찼는지 확인
int isFull(Node* node) {
    return node->rear == MAX_CAPACITY;
}

// 큐가 비었는지 확인
int isEmpty(Node* node) {
    return node->front == node->rear;
}

// 큐에 원소 추가
void enqueue(LinkedListOfQueues* list, int data) {
    // tail 노드를 이용하여 추가할 위치를 찾음
    Node* lastNode = list->tail;
    
    if (isFull(lastNode)) {
        // 큐가 가득 찬 경우 새 노드를 추가
        Node* newNode = createNode();
        newNode->queue[newNode->rear++] = data;
        lastNode->next = newNode;  // 리스트에 새 노드 연결
        list->tail = newNode;      // tail을 새 노드로 갱신
    } else {
        // 큐에 데이터 추가
        lastNode->queue[lastNode->rear++] = data;
    }
}

// 큐에서 원소 제거 및 반환
int dequeue(LinkedListOfQueues* list) {
    Node* current = list->head;

    if (isEmpty(current)) {
        if (current->next != NULL) {
            // 현재 노드가 비었으면 다음 노드로 이동
            list->head = current->next;
            free(current);  // 메모리 해제
            current = list->head;
        } else {
            printf("All queues are empty!\n");
            return -1;  // 더 이상 데이터가 없음
        }
    }

    // 현재 큐에서 원소 제거 및 반환
    return current->queue[current->front++];
}

// 큐 출력 (디버깅용)
void printQueues(LinkedListOfQueues* list) {
    Node* current = list->head;
    int nodeIndex = 1;
    while (current != NULL) {
        printf("Queue %d: ", nodeIndex++);
        for (int i = current->front; i < current->rear; i++) {
            printf("%d ", current->queue[i]);
        }
        printf("\n");
        current = current->next;
    }
}

int main() {
    LinkedListOfQueues* queueList = createLinkedListOfQueues();

    // Enqueue 예시
    for (int i = 1; i <= 10; i++) {
        enqueue(queueList, i);
    }
    printQueues(queueList);

    // Dequeue 예시
    for (int i = 0; i < 5; i++) {
        printf("Dequeued: %d\n", dequeue(queueList));
    }
    printQueues(queueList);

    return 0;
}
