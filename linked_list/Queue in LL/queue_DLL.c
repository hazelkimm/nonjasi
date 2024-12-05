/*
1. LinkedListQueue create(capacity): 큐를 생성하고 초기화합니다. 첫 번째 노드를 생성하고 최대 용량(capacity)을 설정합니다.
2. void enqueue(value): 큐에 요소를 추가합니다. 현재 노드의 용량을 초과하면 새 노드를 생성하여 연결합니다.
3. int pop(): 큐에서 첫 번째 요소를 제거하고 반환합니다. 현재 노드가 비어 있으면 다음 노드로 이동하여 처리합니다.
4. int pop_and_shift(): 큐에서 첫 번째 요소를 제거한 후, 뒤쪽 노드의 요소를 앞으로 이동하여 
     첫 번째 노드부터 capacity를 유지하도록 재배치합니다. 마지막 노드가 비면 삭제합니다.
5. int peek(): 큐의 첫 번째 요소를 반환합니다. 요소를 제거하지 않습니다.
6. int total_size(): 큐 전체의 요소 개수를 반환합니다. 모든 노드를 순회하며 요소 수를 계산합니다.
7. void print_queue():큐의 모든 요소를 출력합니다. 각 노드의 데이터를 화살표(->)로 연결하여 표시합니다.
8. int get_element_at(index): 큐에서 특정 인덱스의 요소를 반환합니다. 연결된 노드를 순회하며 인덱스를 계산합니다.
9. void merge_queues(queue): 다른 큐와 병합합니다. 병합된 요소는 현재 큐의 끝에 추가됩니다.
10. int sum_queue(): 큐 내 모든 요소의 합계를 반환합니다.
11. int find_max(): 큐 내에서 가장 큰 값을 반환합니다. 비어 있으면 예외를 발생시킵니다.
12. int find_min(): 큐 내에서 가장 작은 값을 반환합니다. 비어 있으면 예외를 발생시킵니다.
13. int find_element(value): 큐에서 특정 값을 가진 요소의 인덱스를 반환합니다. 값이 없으면 -1을 반환합니다.
14. void print_reverse(): 큐의 모든 요소를 역순으로 출력합니다. 각 노드의 데이터를 역순으로 처리하여 표시합니다.
15. int depth(): 연결된 노드의 총 개수를 반환합니다.
16. void delete_element(value): 큐에서 특정 값을 삭제합니다. 연결된 노드들에서 값을 찾고 제거합니다.
17. double calculate_average(): 큐 내 모든 요소의 평균값을 계산하여 반환합니다.
18. void remove_duplicates(): 큐에서 중복된 요소를 제거합니다. 요소 순서를 유지하며 중복을 제거합니다.
19. void delete_in_range(min_value, max_value): 큐에서 특정 값 범위(min_value ~ max_value)에 해당하는 요소를 삭제합니다.
*/



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// Node 구조체 정의
typedef struct Node {
    int* queue;          // 큐 데이터를 저장하는 배열
    int capacity;        // 큐의 최대 용량
    int size;            // 현재 노드의 요소 개수
    struct Node* next;   // 다음 노드 포인터
    struct Node* prev;   // 이전 노드 포인터
} Node;

// LinkedListQueue 구조체 정의
typedef struct LinkedListQueue {
    Node* head;         // 첫 번째 노드
    Node* tail;         // 마지막 노드
    int capacity;       // 각 노드의 최대 용량
} LinkedListQueue;

// 노드 생성 함수
Node* create_node(int capacity) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->queue = (int*)malloc(capacity * sizeof(int));
    node->capacity = capacity;
    node->size = 0;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

// 1. LinkedListQueue create(capacity)
LinkedListQueue* create_queue(int capacity) {
    LinkedListQueue* queue = (LinkedListQueue*)malloc(sizeof(LinkedListQueue));
    queue->head = create_node(capacity);
    queue->tail = queue->head;
    queue->capacity = capacity;
    return queue;
}

// 2. void enqueue(value)
void enqueue(LinkedListQueue* queue, int value) {
    if (queue->tail->size < queue->capacity) {
        queue->tail->queue[queue->tail->size++] = value;
    } else {
        Node* new_node = create_node(queue->capacity);
        queue->tail->next = new_node;
        new_node->prev = queue->tail;
        queue->tail = new_node;
        queue->tail->queue[queue->tail->size++] = value;
    }
}

// 3. int pop()
int pop(LinkedListQueue* queue) {
    if (queue->head->size == 0) {
        if (queue->head->next) {
            Node* temp = queue->head;
            queue->head = queue->head->next;
            queue->head->prev = NULL;
            free(temp->queue);
            free(temp);
            return pop(queue);
        } else {
            fprintf(stderr, "큐가 비어 있습니다.\n");
            exit(EXIT_FAILURE);
        }
    }
    int value = queue->head->queue[0];
    for (int i = 1; i < queue->head->size; i++) {
        queue->head->queue[i - 1] = queue->head->queue[i];
    }
    queue->head->size--;
    return value;
}

// 4. int pop_and_shift()
int pop_and_shift(LinkedListQueue* queue) {
    int popped_value = pop(queue);

    // 뒤쪽 노드에서 요소를 가져와 앞쪽 노드를 채우기
    Node* current = queue->head;
    while (current->next) {
        while (current->size < queue->capacity && current->next->size > 0) {
            current->queue[current->size++] = current->next->queue[0];
            for (int i = 1; i < current->next->size; i++) {
                current->next->queue[i - 1] = current->next->queue[i];
            }
            current->next->size--;
        }
        current = current->next;
    }

    // 마지막 노드가 비었으면 제거
    if (queue->tail->size == 0 && queue->tail != queue->head) {
        Node* temp = queue->tail;
        queue->tail = queue->tail->prev;
        queue->tail->next = NULL;
        free(temp->queue);
        free(temp);
    }
    return popped_value;
}

// 5. int peek()
int peek(LinkedListQueue* queue) {
    if (queue->head->size == 0) {
        fprintf(stderr, "큐가 비어 있습니다.\n");
        exit(EXIT_FAILURE);
    }
    return queue->head->queue[0];
}

// 6. int total_size()
int total_size(LinkedListQueue* queue) {
    int size = 0;
    Node* current = queue->head;
    while (current) {
        size += current->size;
        current = current->next;
    }
    return size;
}

// 7. void print_queue()
void print_queue(LinkedListQueue* queue) {
    Node* current = queue->head;
    while (current) {
        printf("[");
        for (int i = 0; i < current->size; i++) {
            printf("%d", current->queue[i]);
            if (i < current->size - 1) printf(", ");
        }
        printf("] -> ");
        current = current->next;
    }
    printf("None\n");
}

// 8. int get_element_at(index)
int get_element_at(LinkedListQueue* queue, int index) {
    Node* current = queue->head;
    while (current) {
        if (index < current->size) {
            return current->queue[index];
        }
        index -= current->size;
        current = current->next;
    }
    fprintf(stderr, "인덱스가 범위를 초과했습니다.\n");
    exit(EXIT_FAILURE);
}

// 9. void merge_queues(queue)
void merge_queues(LinkedListQueue* queue1, LinkedListQueue* queue2) {
    Node* current = queue2->head;
    while (current) {
        for (int i = 0; i < current->size; i++) {
            enqueue(queue1, current->queue[i]);
        }
        current = current->next;
    }
}

// 10. int sum_queue()
int sum_queue(LinkedListQueue* queue) {
    int sum = 0;
    Node* current = queue->head;
    while (current) {
        for (int i = 0; i < current->size; i++) {
            sum += current->queue[i];
        }
        current = current->next;
    }
    return sum;
}

// 11. int find_max()
int find_max(LinkedListQueue* queue) {
    if (queue->head->size == 0) {
        fprintf(stderr, "큐가 비어 있습니다.\n");
        exit(EXIT_FAILURE);
    }
    int max = INT_MIN;
    Node* current = queue->head;
    while (current) {
        for (int i = 0; i < current->size; i++) {
            if (current->queue[i] > max) max = current->queue[i];
        }
        current = current->next;
    }
    return max;
}

// 12. int find_min()
int find_min(LinkedListQueue* queue) {
    if (queue->head->size == 0) {
        fprintf(stderr, "큐가 비어 있습니다.\n");
        exit(EXIT_FAILURE);
    }
    int min = INT_MAX;
    Node* current = queue->head;
    while (current) {
        for (int i = 0; i < current->size; i++) {
            if (current->queue[i] < min) min = current->queue[i];
        }
        current = current->next;
    }
    return min;
}

// 13. int find_element(value)
int find_element(LinkedListQueue* queue, int value) {
    int index = 0;
    Node* current = queue->head;
    while (current) {
        for (int i = 0; i < current->size; i++) {
            if (current->queue[i] == value) return index + i;
        }
        index += current->size;
        current = current->next;
    }
    return -1;
}

// 14. void print_reverse()
void print_reverse(LinkedListQueue* queue) {
    Node* current = queue->tail;
    while (current) {
        for (int i = current->size - 1; i >= 0; i--) {
            printf("%d ", current->queue[i]);
        }
        printf("<- ");
        current = current->prev;
    }
    printf("None\n");
}

// 15. int depth()
int depth(LinkedListQueue* queue) {
    int depth = 0;
    Node* current = queue->head;
    while (current) {
        depth++;
        current = current->next;
    }
    return depth;
}

// 16. void delete_element(value)
void delete_element(LinkedListQueue* queue, int value) {
    Node* current = queue->head;
    while (current) {
        int* new_queue = (int*)malloc(current->capacity * sizeof(int));
        int new_size = 0;
        for (int i = 0; i < current->size; i++) {
            if (current->queue[i] != value) {
                new_queue[new_size++] = current->queue[i];
            }
        }
        free(current->queue);
        current->queue = new_queue;
        current->size = new_size;
        current = current->next;
    }
}

// 17. double calculate_average()
double calculate_average(LinkedListQueue* queue) {
    int total = sum_queue(queue);
    int count = total_size(queue);
    if (count == 0) {
        fprintf(stderr, "큐가 비어 있습니다.\n");
        exit(EXIT_FAILURE);
    }
    return (double)total / count;
}

// 18. void remove_duplicates()
void remove_duplicates(LinkedListQueue* queue) {
    Node* current = queue->head;
    bool seen[1000] = {false}; // 간단한 중복 체크를 위한 배열
    while (current) {
        int* new_queue = (int*)malloc(current->capacity * sizeof(int));
        int new_size = 0;
        for (int i = 0; i < current->size; i++) {
            if (!seen[current->queue[i]]) {
                seen[current->queue[i]] = true;
                new_queue[new_size++] = current->queue[i];
            }
        }
        free(current->queue);
        current->queue = new_queue;
        current->size = new_size;
        current = current->next;
    }
}

// 19. void delete_in_range(min_value, max_value)
void delete_in_range(LinkedListQueue* queue, int min_value, int max_value) {
    Node* current = queue->head;
    while (current) {
        int* new_queue = (int*)malloc(current->capacity * sizeof(int));
        int new_size = 0;
        for (int i = 0; i < current->size; i++) {
            if (current->queue[i] < min_value || current->queue[i] > max_value) {
                new_queue[new_size++] = current->queue[i];
            }
        }
        free(current->queue);
        current->queue = new_queue;
        current->size = new_size;
        current = current->next;
    }
}

// 메모리 해제
void free_queue(LinkedListQueue* queue) {
    while (queue->head) {
        Node* temp = queue->head;
        queue->head = queue->head->next;
        free(temp->queue);
        free(temp);
    }
    free(queue);
}

// 메인 함수
int main() {
    LinkedListQueue* queue = create_queue(3);

    // 1. Enqueue 테스트
    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);
    enqueue(queue, 4);
    enqueue(queue, 5);
    enqueue(queue, 6);
    enqueue(queue, 7);
    print_queue(queue);

    // 2. Pop 테스트
    printf("Popped: %d\n", pop(queue));
    print_queue(queue);

    // 3. Pop and Shift 테스트
    printf("Popped and Shifted: %d\n", pop_and_shift(queue));
    print_queue(queue);

    // 4. Total Size 테스트
    printf("Total size: %d\n", total_size(queue));

    // 5. Depth 테스트
    printf("Depth: %d\n", depth(queue));

    // 6. Get Element At 테스트
    printf("Element at index 1: %d\n", get_element_at(queue, 1));

    // 7. Sum Queue 테스트
    printf("Sum of queue: %d\n", sum_queue(queue));

    // 8. Find Max 테스트
    printf("Max value: %d\n", find_max(queue));

    // 9. Find Min 테스트
    printf("Min value: %d\n", find_min(queue));

    // 10. Find Element 테스트
    printf("Index of value 4: %d\n", find_element(queue, 4));

    // 11. Print Reverse 테스트
    printf("Reverse: ");
    print_reverse(queue);

    // 12. Delete Element 테스트
    delete_element(queue, 4);
    print_queue(queue);

    // 13. Calculate Average 테스트
    printf("Average: %.2f\n", calculate_average(queue));

    // 14. Remove Duplicates 테스트
    enqueue(queue, 2);
    enqueue(queue, 3);
    remove_duplicates(queue);
    print_queue(queue);

    // 15. Delete in Range 테스트
    delete_in_range(queue, 2, 3);
    print_queue(queue);

    // 메모리 해제
    free_queue(queue);
    return 0;
}
