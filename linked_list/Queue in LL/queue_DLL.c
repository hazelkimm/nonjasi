#include <stdio.h>
#include <stdlib.h>

#define QUEUE_CAPACITY 3  // 각 큐의 최대 용량

typedef int Element;  // 큐에 저장되는 데이터 타입

// 큐의 각 노드를 나타내는 구조체
typedef struct QueueNode {
    Element data;             // 노드에 저장된 데이터
    struct QueueNode* next;   // 다음 노드를 가리키는 포인터
} QueueNode;

// 큐 구조체
typedef struct Queue {
    QueueNode* front;  // 큐의 앞쪽 (디큐 위치)
    QueueNode* rear;   // 큐의 뒤쪽 (엔큐 위치)
    int size;          // 현재 큐의 크기
} Queue;

// 링크드 리스트 노드 구조체 (각 노드가 큐를 포함)
typedef struct LinkedListNode {
    Queue* queue;                 // 큐를 포함
    struct LinkedListNode* next;  // 다음 노드를 가리키는 포인터
    struct LinkedListNode* prev;  // 이전 노드를 가리키는 포인터
} LinkedListNode;

// 큐 생성 함수
Queue* create_queue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    q->front = q->rear = NULL;
    q->size = 0;
    return q;
}

// 링크드 리스트 노드 생성 함수
LinkedListNode* create_linked_list_node() {
    LinkedListNode* node = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    if (node == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->queue = create_queue();
    node->next = node->prev = NULL;
    return node;
}

// 큐에 요소 추가 (엔큐)
void enqueue(Queue* q, Element value) {
    QueueNode* new_node = (QueueNode*)malloc(sizeof(QueueNode));
    if (new_node == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = value;
    new_node->next = NULL;

    if (q->rear == NULL) {
        // 큐가 비어 있는 경우
        q->front = q->rear = new_node;
    } else {
        q->rear->next = new_node;
        q->rear = new_node;
    }
    q->size++;
}

// 큐에서 요소 제거 및 반환 (디큐)
Element dequeue(Queue* q) {
    if (q->front == NULL) {
        printf("Queue is empty\n");
        exit(EXIT_FAILURE);
    }

    QueueNode* temp = q->front;
    Element value = temp->data;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    q->size--;
    return value;
}

// 큐의 앞쪽 요소 반환 (제거하지 않음)
Element peek(Queue* q) {
    if (q->front == NULL) {
        printf("Queue is empty\n");
        exit(EXIT_FAILURE);
    }
    return q->front->data;
}

// 큐가 비었는지 확인
int is_queue_empty(Queue* q) {
    return q->front == NULL;
}

// 데이터 구조에 요소 추가
void push(LinkedListNode** tail_ref, Element value) {
    LinkedListNode* tail = *tail_ref;

    // 마지막 큐가 가득 차면 새 링크드 리스트 노드 생성
    if (tail->queue->size >= QUEUE_CAPACITY) {
        LinkedListNode* new_node = create_linked_list_node();
        tail->next = new_node;
        new_node->prev = tail;
        *tail_ref = new_node;  // tail 갱신
        printf("Creating new queue for value %d.\n", value);
        tail = *tail_ref;
    }

    enqueue(tail->queue, value);
    printf("Pushed value %d to queue. Queue size is now %d.\n", value, tail->queue->size);
}

// 데이터 구조에서 요소 제거 및 반환
Element pop(LinkedListNode** head_ref) {
    LinkedListNode* head = *head_ref;
    if (head == NULL || head->queue->size == 0) {
        printf("List is empty\n");
        exit(EXIT_FAILURE);
    }

    Element value = dequeue(head->queue);
    printf("Popped value: %d\n", value);

    // 첫 번째 큐가 비었으면 링크드 리스트 노드를 제거
    if (is_queue_empty(head->queue) && head->next != NULL) {
        LinkedListNode* next_node = head->next;
        next_node->prev = NULL;
        free(head->queue);
        free(head);
        *head_ref = next_node;  // head 갱신
        printf("Removed an empty linked list node.\n");
    }

    return value;
}

// 데이터 구조에서 요소 제거 및 재분배
Element pop_and_redistribute(LinkedListNode** head_ref) {
    LinkedListNode* head = *head_ref;
    if (head == NULL || head->queue->size == 0) {
        printf("List is empty\n");
        exit(EXIT_FAILURE);
    }

    Element value = dequeue(head->queue);
    printf("Popped value: %d\n", value);

    // 첫 번째 큐가 크기가 부족한 경우, 다음 큐에서 재분배
    LinkedListNode* current = head;
    while (current->queue->size < QUEUE_CAPACITY && current->next != NULL) {
        LinkedListNode* next_node = current->next;
        if (!is_queue_empty(next_node->queue)) {
            Element redistributed_value = dequeue(next_node->queue);
            enqueue(current->queue, redistributed_value);
            printf("Redistributed value %d to maintain size.\n", redistributed_value);
        }

        // 다음 큐가 비었으면 노드를 제거
        if (is_queue_empty(next_node->queue)) {
            current->next = next_node->next;
            if (next_node->next != NULL) {
                next_node->next->prev = current;
            }
            free(next_node->queue);
            free(next_node);
            printf("Removed an empty linked list node.\n");
        }
    }

    return value;
}

// 데이터 구조 출력
void print_structure(LinkedListNode* head) {
    int queue_num = 1;
    while (head != NULL) {
        printf("Queue %d: ", queue_num++);
        QueueNode* current = head->queue->front;
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
        head = head->next;
    }
}

// 데이터 구조 메모리 해제
void destroy_structure(LinkedListNode* head) {
    while (head != NULL) {
        LinkedListNode* temp = head;
        while (!is_queue_empty(temp->queue)) {
            dequeue(temp->queue);
        }
        free(temp->queue);
        head = head->next;
        free(temp);
    }
}

// 테스트 코드
int main() {
    LinkedListNode* head = create_linked_list_node();
    LinkedListNode* tail = head;

    // 요소 추가
    printf("Pushing elements to the data structure...\n");
    push(&tail, 10);
    push(&tail, 20);
    push(&tail, 30);  // 첫 번째 큐가 가득 참
    push(&tail, 40);  // 두 번째 큐 생성
    push(&tail, 50);

    // 데이터 구조 출력
    printf("Initial data structure:\n");
    print_structure(head);

    // 데이터 제거
    printf("Popping value:\n");
    pop(&head);
    printf("Data structure after popping:\n");
    print_structure(head);

    // 재분배를 포함한 데이터 제거
    printf("Popping value with redistribution:\n");
    pop_and_redistribute(&head);
    printf("Data structure after redistribution:\n");
    print_structure(head);

    // 메모리 해제
    destroy_structure(head);

    return 0;
}
