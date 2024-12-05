#include <stdio.h>
#include <stdlib.h>

#define QUEUE_CAPACITY 3  // 각 큐의 최대 용량

typedef int element;  // 큐에 저장되는 데이터 타입

// 큐 노드 구조체 정의
typedef struct QueueNode {
    element data;              // 노드에 저장된 데이터
    struct QueueNode* next;    // 다음 노드를 가리키는 포인터
} QueueNode;

// 큐 구조체 정의
typedef struct Queue {
    QueueNode* front;  // 큐의 앞쪽 (디큐 위치)
    QueueNode* rear;   // 큐의 뒤쪽 (엔큐 위치)
    int size;          // 큐의 현재 크기
} Queue;

// 연결 리스트 노드 구조체 정의 (각 노드가 큐를 포함)
typedef struct LinkedListNode {
    Queue* queue;                   // 이 노드에 포함된 큐
    struct LinkedListNode* next;    // 다음 연결 리스트 노드를 가리키는 포인터
} LinkedListNode;

// 큐 생성 및 초기화 함수
Queue* create_queue() {
    // 큐를 위한 메모리 할당
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    // 큐의 front와 rear 포인터 및 크기 초기화
    q->front = q->rear = NULL;
    q->size = 0;
    return q;
}

// 연결 리스트 노드 생성 및 초기화 함수
LinkedListNode* create_linked_list_node() {
    // 연결 리스트 노드를 위한 메모리 할당
    LinkedListNode* node = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    if (node == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    // 새로운 큐를 생성하여 노드에 할당
    node->queue = create_queue();
    // 다음 노드 포인터를 NULL로 초기화
    node->next = NULL;
    return node;
}

// 큐에 요소 추가 (엔큐)
void enqueue(Queue* q, element value) {
    // 새로운 큐 노드 생성
    QueueNode* new_node = (QueueNode*)malloc(sizeof(QueueNode));
    if (new_node == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    // 새로운 노드에 데이터와 다음 포인터 설정
    new_node->data = value;
    new_node->next = NULL;

    if (q->rear == NULL) {
        // 큐가 비어있는 경우, front와 rear를 새로운 노드로 설정
        q->front = q->rear = new_node;
    } else {
        // 큐에 요소가 있는 경우, rear 뒤에 새로운 노드를 추가하고 rear를 갱신
        q->rear->next = new_node;
        q->rear = new_node;
    }
    // 큐의 크기 증가
    q->size++;
}

// 큐에서 요소 제거 및 반환 (디큐)
element dequeue(Queue* q) {
    if (q->front == NULL) {
        // 큐가 비어있는 경우 에러 출력 후 종료
        printf("Queue is empty\n");
        exit(EXIT_FAILURE);
    }

    // 큐의 front 노드를 임시 저장
    QueueNode* temp = q->front;
    // 반환할 데이터 저장
    element value = temp->data;
    // front를 다음 노드로 이동
    q->front = q->front->next;

    if (q->front == NULL) {
        // 큐가 비어있으면 rear를 NULL로 설정
        q->rear = NULL;
    }

    // 메모리 해제 및 큐 크기 감소
    free(temp);
    q->size--;
    return value;
}

// 큐의 앞쪽 요소를 반환 (제거하지 않음)
element peek(Queue* q) {
    if (q->front == NULL) {
        // 큐가 비어있는 경우 에러 출력 후 종료
        printf("Queue is empty\n");
        exit(EXIT_FAILURE);
    }
    // front 노드의 데이터 반환
    return q->front->data;
}

// 큐가 비어있는지 확인
int is_queue_empty(Queue* q) {
    return q->front == NULL;
}

// 데이터 구조에 요소 추가
// 마지막 큐가 가득 찼으면 새로운 연결 리스트 노드를 생성하여 요소를 추가
void push(LinkedListNode** head_ref, element value) {
    LinkedListNode* current = *head_ref;

    // 마지막 연결 리스트 노드로 이동
    while (current->next != NULL) {
        current = current->next;
    }

    // 현재 큐가 가득 찼으면 새로운 연결 리스트 노드 생성
    if (current->queue->size >= QUEUE_CAPACITY) {
        // 새로운 연결 리스트 노드 생성
        LinkedListNode* new_node = create_linked_list_node();
        // 새로운 노드를 리스트에 연결
        current->next = new_node;
        current = new_node;
        printf("Creating new queue for value %d.\n", value);
    }

    // 현재 큐에 요소 추가
    enqueue(current->queue, value);
    printf("Pushed value %d to queue. Queue size is now %d.\n", value, current->queue->size);
}

// 데이터 구조에서 요소 제거 및 반환
// 첫 번째 큐가 비게 되면 연결 리스트 노드를 제거
element pop(LinkedListNode** head_ref) {
    if (*head_ref == NULL) {
        // 연결 리스트가 비어있는 경우 에러 출력 후 종료
        printf("List is empty\n");
        exit(EXIT_FAILURE);
    }

    LinkedListNode* head = *head_ref;
    // 첫 번째 큐에서 요소 제거
    element value = dequeue(head->queue);

    // 큐가 비어있으면 연결 리스트 노드 제거
    if (is_queue_empty(head->queue)) {
        *head_ref = head->next;  // 연결 리스트의 헤드를 다음 노드로 변경
        // 큐와 연결 리스트 노드 메모리 해제
        free(head->queue);
        free(head);
    }

    return value;
}

//pop하면 다음 링크드리스트에서 원소 하나 가져와서 이전 링크드리스트 채우기.
//링크드리스트 안의 queue는 항상 첫번째 애가 다 채워지도록 하는 함수
element pop_and_redistribute(LinkedListNode** head_ref) {
    if (*head_ref == NULL) {
        printf("List is empty\n");
        exit(EXIT_FAILURE);
    }

    LinkedListNode* head = *head_ref;
    // 첫 번째 큐에서 요소 제거
    element value = dequeue(head->queue);

    // 첫 번째 큐가 크기가 부족하고 다음 노드가 있을 경우
    while (head->queue->size < QUEUE_CAPACITY && head->next != NULL) {
        LinkedListNode* next_node = head->next;
        if (!is_queue_empty(next_node->queue)) {
            // 다음 큐에서 첫 번째 요소를 가져와 현재 큐에 추가
            enqueue(head->queue, dequeue(next_node->queue));
            printf("Redistributed an element from the next queue to maintain size.\n");
        }

        // 다음 큐가 비어있다면 연결 리스트 노드 제거
        if (is_queue_empty(next_node->queue)) {
            head->next = next_node->next;  // 연결 리스트에서 노드 제거
            free(next_node->queue);
            free(next_node);
            printf("Removed an empty linked list node.\n");
        }
    }

    return value;
}




// 데이터 구조의 첫 번째 요소 반환 (제거하지 않음)
element peek_linked_list(LinkedListNode* head) {
    if (head == NULL) {
        // 연결 리스트가 비어있는 경우 에러 출력 후 종료
        printf("List is empty\n");
        exit(EXIT_FAILURE);
    }
    // 첫 번째 큐의 front 요소 반환
    return peek(head->queue);
}

// 데이터 구조의 총 요소 개수 계산
int total_size(LinkedListNode* head) {
    int size = 0;
    // 연결 리스트를 순회하며 모든 큐의 크기를 합산
    while (head != NULL) {
        size += head->queue->size;
        head = head->next;
    }
    return size;
}

// 데이터 구조의 깊이(큐의 개수) 계산
int depth(LinkedListNode* head) {
    int depth = 0;
    // 연결 리스트를 순회하며 노드의 개수를 계산
    while (head != NULL) {
        depth++;
        head = head->next;
    }
    return depth;
}

// 특정 인덱스의 요소 반환
element get_element_at(LinkedListNode* head, int index) {
    while (head != NULL) {
        if (index < head->queue->size) {
            // 인덱스가 현재 큐의 범위 내에 있으면 해당 요소 반환
            QueueNode* current = head->queue->front;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
            return current->data;
        }
        // 다음 큐로 이동하고 인덱스 조정
        index -= head->queue->size;
        head = head->next;
    }
    // 인덱스가 범위를 벗어난 경우 에러 출력 후 종료
    printf("Index out of bounds\n");
    exit(EXIT_FAILURE);
}

// 특정 값 삭제
void remove_value(LinkedListNode* head, element value) {
    while (head != NULL) {
        QueueNode* current = head->queue->front;
        QueueNode* prev = NULL;

        while (current != NULL) {
            if (current->data == value) {
                // 삭제할 값을 찾았을 때
                if (prev == NULL) {
                    // 삭제할 노드가 큐의 front인 경우
                    head->queue->front = current->next;
                    if (current == head->queue->rear) {
                        // 큐에 노드가 하나만 있었을 경우
                        head->queue->rear = NULL;
                    }
                } else {
                    // 삭제할 노드가 중간 또는 끝에 있는 경우
                    prev->next = current->next;
                    if (current == head->queue->rear) {
                        // 삭제할 노드가 rear인 경우
                        head->queue->rear = prev;
                    }
                }
                // 노드 메모리 해제 및 큐 크기 감소
                free(current);
                head->queue->size--;
                return;
            }
            prev = current;
            current = current->next;
        }
        // 다음 연결 리스트 노드로 이동
        head = head->next;
    }
}

// 특정 범위의 값 삭제
void remove_in_range(LinkedListNode* head, element min_value, element max_value) {
    while (head != NULL) {
        QueueNode* current = head->queue->front;
        QueueNode* prev = NULL;

        while (current != NULL) {
            if (current->data >= min_value && current->data <= max_value) {
                // 삭제할 값을 찾았을 때
                QueueNode* temp = current;
                if (prev == NULL) {
                    // 삭제할 노드가 큐의 front인 경우
                    head->queue->front = current->next;
                    if (current == head->queue->rear) {
                        // 큐에 노드가 하나만 있었을 경우
                        head->queue->rear = NULL;
                    }
                    current = current->next;
                    free(temp);
                    head->queue->size--;
                } else {
                    // 삭제할 노드가 중간 또는 끝에 있는 경우
                    prev->next = current->next;
                    if (current == head->queue->rear) {
                        // 삭제할 노드가 rear인 경우
                        head->queue->rear = prev;
                    }
                    current = current->next;
                    free(temp);
                    head->queue->size--;
                }
            } else {
                // 다음 노드로 이동
                prev = current;
                current = current->next;
            }
        }
        head = head->next;
    }
}

// 데이터 구조 출력
void print_linked_list(LinkedListNode* head) {
    int queue_num = 1;
    // 연결 리스트를 순회
    while (head != NULL) {
        printf("Queue %d: ", queue_num++);
        QueueNode* current = head->queue->front;
        // 큐의 요소들을 출력
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
        head = head->next;
    }
}

// 메모리 해제 함수
void destroy_linked_list(LinkedListNode* head) {
    while (head != NULL) {
        LinkedListNode* temp = head;
        // 큐의 모든 노드 메모리 해제
        while (!is_queue_empty(temp->queue)) {
            dequeue(temp->queue);
        }
        // 큐 메모리 해제
        free(temp->queue);
        // 다음 연결 리스트 노드로 이동
        head = head->next;
        // 연결 리스트 노드 메모리 해제
        free(temp);
    }
}

// 테스트 함수
int main() {
    // 초기 연결 리스트 노드 생성
    LinkedListNode* list = create_linked_list_node();

    // 요소 추가
    printf("Pushing elements to the data structure...\n");
    push(&list, 10);
    push(&list, 20);
    push(&list, 30);  // 첫 번째 큐가 가득 참
    push(&list, 40);  // 두 번째 큐 생성
    push(&list, 50);

    // 데이터 구조 출력
    printf("Initial data structure:\n");
    print_linked_list(list);

    // 총 크기 확인
    printf("Total size: %d\n", total_size(list));

    // 깊이 확인
    printf("Depth (number of queues): %d\n", depth(list));

    // 특정 인덱스의 값 확인
    int index = 4;
    printf("Element at index %d: %d\n", index, get_element_at(list, index));

    // 첫 번째 요소 확인
    printf("Peeking at front element: %d\n", peek_linked_list(list));

    // 요소 제거
    printf("Popping value: %d\n", pop(&list));

    // 데이터 구조 출력
    printf("Data structure after popping:\n");
    print_linked_list(list);

    // 특정 값 삭제
    int value_to_remove = 30;
    printf("Removing value %d from the data structure.\n", value_to_remove);
    remove_value(list, value_to_remove);

    printf("Popping value with redistribution: %d\n", pop_and_redistribute(&list));
    print_linked_list(list);

    // 데이터 구조 출력
    printf("Data structure after removing value %d:\n", value_to_remove);
    print_linked_list(list);

    // 특정 범위의 값 삭제
    int min_value = 10, max_value = 30;
    printf("Removing values in range [%d, %d] from the data structure.\n", min_value, max_value);
    remove_in_range(list, min_value, max_value);

    // 데이터 구조 출력
    printf("Data structure after removing values in range:\n");
    print_linked_list(list);

    // 메모리 해제
    destroy_linked_list(list);

    return 0;
}
