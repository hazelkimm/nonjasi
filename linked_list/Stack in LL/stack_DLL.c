/*
1. Stack create() - 스택을 생성하고 초기화.
2. void make_empty(Stack s) - 스택을 비우고 모든 노드를 메모리에서 해제.
3. void destroy(Stack s) - 스택 전체를 삭제하고 모든 메모리를 해제.
4. boolean is_empty(Stack s) - 스택이 비었는지 확인.
5. void push(Stack *s, element i) - 스택에 요소를 추가하며 용량 초과 시 새 스택 생성.
6. element pop(Stack *s) - 스택에서 요소를 제거하고 반환하며, 비었으면 이전 스택으로 이동.
7. element peek(Stack s) - 스택의 최상위 요소를 반환 (제거하지 않음).
8. int total_size(Stack s) - 모든 연결된 스택의 요소 개수를 합산하여 반환.
9. void print_stack(Stack s) - 스택의 모든 요소를 출력.
10. element get_element_at(Stack s, int index) - 특정 인덱스의 요소를 반환.
11. Stack merge_stacks(Stack s1, Stack s2) - 두 스택을 하나로 병합하여 반환.
12. element sum_stack(Stack s) - 스택 내 모든 요소의 합계를 계산하여 반환.
13. element find_max(Stack s) - 스택 내 최댓값을 반환.
14. element find_min(Stack s) - 스택 내 최솟값을 반환.
15. int find_element(Stack s, element value) - 특정 값을 가진 요소의 인덱스를 반환.
16. void print_reverse(Stack s) - 스택의 모든 요소를 역순으로 출력.
17. int stack_depth(Stack s) - 연결된 스택의 총 스택 개수를 반환.
18. void delete_element(Stack *s, element value) - 특정 값을 가진 요소를 삭제.
19. Stack copy_stack(Stack s) - 기존 스택을 복사하여 동일한 구조의 새 스택 생성.
20. double calculate_average(Stack s) - 스택 내 모든 요소의 평균값을 계산하여 반환.
21. void remove_duplicates(Stack *s) - 스택에서 중복된 요소를 제거.
22. void delete_in_range(Stack *s, element min_value, element max_value) - 특정 값 범위의 요소를 삭제.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// Element 타입 정의
typedef int element;

// 노드 구조체 정의
typedef struct Node {
    element* stack;
    int capacity;
    int size;
    struct Node* next;
    struct Node* prev;
} Node;

// 스택 구조체 정의
typedef struct Stack {
    Node* head;
    Node* tail;
    int capacity;
} Stack;

// 노드 생성
Node* create_node(int capacity) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->stack = (element*)malloc(sizeof(element) * capacity);
    node->capacity = capacity;
    node->size = 0;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

// 스택 생성 및 초기화
Stack create_stack(int capacity) {
    Stack s;
    s.head = create_node(capacity);
    s.tail = s.head;
    s.capacity = capacity;
    return s;
}

// 스택 비우기 및 메모리 해제
void make_empty(Stack* s) {
    Node* current = s->head;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp->stack);
        free(temp);
    }
    s->head = s->tail = create_node(s->capacity);
}

// 스택 삭제 및 메모리 해제
void destroy(Stack* s) {
    make_empty(s);
    free(s->head->stack);
    free(s->head);
    s->head = s->tail = NULL;
}

// 스택이 비었는지 확인
bool is_empty(Stack s) {
    return s.head == s.tail && s.tail->size == 0;
}

// 요소 추가
void push(Stack* s, element i) {
    if (s->tail->size < s->tail->capacity) {
        s->tail->stack[s->tail->size++] = i;
    } else {
        Node* new_node = create_node(s->capacity);
        s->tail->next = new_node;
        new_node->prev = s->tail;
        s->tail = new_node;
        s->tail->stack[s->tail->size++] = i;
    }
}

// 요소 제거
element pop(Stack* s) {
    if (s->tail->size == 0) {
        if (s->tail->prev) {
            Node* temp = s->tail;
            s->tail = s->tail->prev;
            s->tail->next = NULL;
            free(temp->stack);
            free(temp);
            return pop(s);
        } else {
            printf("스택이 비어 있습니다.\n");
            exit(EXIT_FAILURE);
        }
    }
    return s->tail->stack[--s->tail->size];
}

// 최상위 요소 반환
element peek(Stack s) {
    if (s.tail->size == 0) {
        if (s.tail->prev) {
            return peek((Stack){s.head, s.tail->prev, s.capacity});
        } else {
            printf("스택이 비어 있습니다.\n");
            exit(EXIT_FAILURE);
        }
    }
    return s.tail->stack[s.tail->size - 1];
}

// 스택 전체 크기 계산
int total_size(Stack s) {
    int size = 0;
    Node* current = s.head;
    while (current) {
        size += current->size;
        current = current->next;
    }
    return size;
}

// 스택 출력
void print_stack(Stack s) {
    Node* current = s.head;
    while (current) {
        for (int i = 0; i < current->size; i++) {
            printf("%d ", current->stack[i]);
        }
        if (current->next) printf("-> ");
        current = current->next;
    }
    printf("None\n");
}

// 특정 인덱스 요소 가져오기
element get_element_at(Stack s, int index) {
    Node* current = s.head;
    while (current) {
        if (index < current->size) {
            return current->stack[index];
        }
        index -= current->size;
        current = current->next;
    }
    printf("인덱스가 범위를 초과했습니다.\n");
    exit(EXIT_FAILURE);
}

// 스택 병합
Stack merge_stacks(Stack s1, Stack s2) {
    Stack result = create_stack(s1.capacity);
    Node* current = s1.head;
    while (current) {
        for (int i = 0; i < current->size; i++) {
            push(&result, current->stack[i]);
        }
        current = current->next;
    }
    current = s2.head;
    while (current) {
        for (int i = 0; i < current->size; i++) {
            push(&result, current->stack[i]);
        }
        current = current->next;
    }
    return result;
}

// 스택 합 계산
element sum_stack(Stack s) {
    element total = 0;
    Node* current = s.head;
    while (current) {
        for (int i = 0; i < current->size; i++) {
            total += current->stack[i];
        }
        current = current->next;
    }
    return total;
}

// 최댓값 찾기
element find_max(Stack s) {
    element max_value = INT_MIN;
    Node* current = s.head;
    while (current) {
        for (int i = 0; i < current->size; i++) {
            if (current->stack[i] > max_value) {
                max_value = current->stack[i];
            }
        }
        current = current->next;
    }
    if (max_value == INT_MIN) {
        printf("스택이 비어 있습니다.\n");
        exit(EXIT_FAILURE);
    }
    return max_value;
}

// 최솟값 찾기
element find_min(Stack s) {
    element min_value = INT_MAX;
    Node* current = s.head;
    while (current) {
        for (int i = 0; i < current->size; i++) {
            if (current->stack[i] < min_value) {
                min_value = current->stack[i];
            }
        }
        current = current->next;
    }
    if (min_value == INT_MAX) {
        printf("스택이 비어 있습니다.\n");
        exit(EXIT_FAILURE);
    }
    return min_value;
}

// 특정 값을 가진 요소의 인덱스 반환
int find_element(Stack s, element value) {
    int index = 0;
    Node* current = s.head;
    while (current) {
        for (int i = 0; i < current->size; i++) {
            if (current->stack[i] == value) {
                return index + i;
            }
        }
        index += current->size;
        current = current->next;
    }
    return -1;
}

// 스택 역순 출력
void print_reverse(Stack s) {
    Node* current = s.tail;
    while (current) {
        for (int i = current->size - 1; i >= 0; i--) {
            printf("%d ", current->stack[i]);
        }
        if (current->prev) printf("<- ");
        current = current->prev;
    }
    printf("None\n");
}

// 연결된 스택 깊이 계산
int stack_depth(Stack s) {
    int depth = 0;
    Node* current = s.head;
    while (current) {
        depth++;
        current = current->next;
    }
    return depth;
}

// 특정 값 삭제
void delete_element(Stack* s, element value) {
    Node* current = s->head;
    while (current) {
        int new_size = 0;
        for (int i = 0; i < current->size; i++) {
            if (current->stack[i] != value) {
                current->stack[new_size++] = current->stack[i];
            }
        }
        current->size = new_size;
        current = current->next;
    }
}

// 스택 복사
Stack copy_stack(Stack s) {
    Stack copy = create_stack(s.capacity);
    Node* current = s.head;
    while (current) {
        for (int i = 0; i < current->size; i++) {
            push(&copy, current->stack[i]);
        }
        current = current->next;
    }
    return copy;
}

// 평균값 계산
double calculate_average(Stack s) {
    int total = sum_stack(s);
    int count = total_size(s);
    if (count == 0) {
        printf("스택이 비어 있습니다.\n");
        exit(EXIT_FAILURE);
    }
    return (double)total / count;
}

// 중복 제거
void remove_duplicates(Stack* s) {
    bool seen[10000] = {0};
    Node* current = s->head;
    while (current) {
        int new_size = 0;
        for (int i = 0; i < current->size; i++) {
            if (!seen[current->stack[i]]) {
                seen[current->stack[i]] = true;
                current->stack[new_size++] = current->stack[i];
            }
        }
        current->size = new_size;
        current = current->next;
    }
}

// 범위 내 요소 삭제
void delete_in_range(Stack* s, element min_value, element max_value) {
    Node* current = s->head;
    while (current) {
        int new_size = 0;
        for (int i = 0; i < current->size; i++) {
            if (current->stack[i] < min_value || current->stack[i] > max_value) {
                current->stack[new_size++] = current->stack[i];
            }
        }
        current->size = new_size;
        current = current->next;
    }
}

// 메인 함수
int main() {
    // 스택 생성
    Stack s1 = create_stack(3);
    Stack s2 = create_stack(3);

    printf("1. Push Test:\n");
    push(&s1, 1);
    push(&s1, 2);
    push(&s1, 3);
    push(&s1, 4);
    push(&s1, 5);
    print_stack(s1);

    printf("\n2. Pop Test:\n");
    printf("Popped value: %d\n", pop(&s1));
    print_stack(s1);

    printf("\n3. Peek Test:\n");
    printf("Top value: %d\n", peek(s1));

    printf("\n4. Total Size Test:\n");
    printf("Total size: %d\n", total_size(s1));

    printf("\n5. Print Stack Test:\n");
    print_stack(s1);

    printf("\n6. Get Element At Test:\n");
    printf("Element at index 2: %d\n", get_element_at(s1, 2));

    printf("\n7. Merge Stacks Test:\n");
    push(&s2, 10);
    push(&s2, 20);
    Stack merged = merge_stacks(s1, s2);
    print_stack(merged);

    printf("\n8. Sum Stack Test:\n");
    printf("Sum of stack: %d\n", sum_stack(merged));

    printf("\n9. Find Max Test:\n");
    printf("Max value: %d\n", find_max(merged));

    printf("\n10. Find Min Test:\n");
    printf("Min value: %d\n", find_min(merged));

    printf("\n11. Find Element Test:\n");
    printf("Index of element 10: %d\n", find_element(merged, 10));

    printf("\n12. Print Reverse Test:\n");
    print_reverse(merged);

    printf("\n13. Stack Depth Test:\n");
    printf("Stack depth: %d\n", stack_depth(merged));

    printf("\n14. Delete Element Test:\n");
    delete_element(&merged, 3);
    print_stack(merged);

    printf("\n15. Copy Stack Test:\n");
    Stack copied = copy_stack(merged);
    printf("Original stack:\n");
    print_stack(merged);
    printf("Copied stack:\n");
    print_stack(copied);

    printf("\n16. Calculate Average Test:\n");
    printf("Average value: %.2f\n", calculate_average(merged));

    printf("\n17. Remove Duplicates Test:\n");
    push(&merged, 10);
    push(&merged, 20);
    push(&merged, 20);
    remove_duplicates(&merged);
    print_stack(merged);

    printf("\n18. Delete In Range Test:\n");
    delete_in_range(&merged, 10, 20);
    print_stack(merged);

    printf("\n19. Is Empty Test:\n");
    printf("Is stack empty? %s\n", is_empty(merged) ? "Yes" : "No");

    printf("\n20. Make Empty Test:\n");
    make_empty(&merged);
    print_stack(merged);

    printf("\n21. Is Empty Test After Emptying:\n");
    printf("Is stack empty? %s\n", is_empty(merged) ? "Yes" : "No");

    printf("\n22. Destroy Stack Test:\n");
    destroy(&s1);
    destroy(&s2);
    destroy(&merged);
    destroy(&copied);
    printf("All stacks destroyed.\n");

    return 0;
}

