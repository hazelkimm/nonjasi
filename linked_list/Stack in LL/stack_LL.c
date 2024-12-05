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


#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define ERROR -1
#define STACK_CAPACITY 3 // 각 스택의 최대 용량

typedef int boolean;
typedef int element;

typedef struct __LLStackType {
    element data;
    struct __LLStackType *next;
} Node;

typedef struct stack_type {
    Node *top;
    int size; // 현재 스택의 크기
    struct stack_type *next_stack; // 다음 스택에 대한 포인터
} *Stack;

Stack create() {
    Stack s = malloc(sizeof(struct stack_type));
    if (s == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    s->top = NULL;
    s->size = 0;
    s->next_stack = NULL;
    return s;
}

void make_empty(Stack s) {
    while (s->top != NULL) {
        Node *old_top = s->top;
        s->top = old_top->next;
        free(old_top);
    }
    s->size = 0;
}

void destroy(Stack s) {
    while (s != NULL) {
        Stack old_stack = s;
        s = s->next_stack;
        make_empty(old_stack);
        free(old_stack);
    }
}

boolean is_empty(Stack s) {
    return s->top == NULL;
}

void push(Stack *s, element i) {
    if ((*s)->size >= STACK_CAPACITY) {
        // 현재 스택이 꽉 찼으면 새 스택을 생성하고 연결
        Stack new_stack = create();
        new_stack->next_stack = *s;
        *s = new_stack;
    }
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = i;
    new_node->next = (*s)->top;
    (*s)->top = new_node;
    (*s)->size++;
}

element pop(Stack *s) {
    if (is_empty(*s)) {
        if ((*s)->next_stack != NULL) {
            // 현재 스택이 비었으면 이전 스택으로 이동
            Stack old_stack = *s;
            *s = (*s)->next_stack;
            free(old_stack);
            return pop(s); // 새 스택에서 pop 재시도
        } else {
            printf("Stack is empty\n");
            exit(EXIT_FAILURE);
        }
    }
    Node *old_top = (*s)->top;
    element i = old_top->data;
    (*s)->top = old_top->next;
    free(old_top);
    (*s)->size--;
    return i;
}

element peek(Stack s) {
    if (is_empty(s)) {
        printf("Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return s->top->data;
}

// 스택의 총 크기를 반환
// 모든 연결된 스택의 요소 수를 합산하여 총 크기를 반환하는 함수.
int total_size(Stack s) {
    int size = 0;
    while (s != NULL) {
        size += s->size;
        s = s->next_stack;
    }
    return size;
}

//스택에 있는 모든 요소 출력
//각 연결된 스택의 요소를 차례로 출력.
void print_stack(Stack s) {
    int stack_num = 1;
    while (s != NULL) {
        printf("Stack %d: ", stack_num++);
        Node *current = s->top;
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
        s = s->next_stack;
    }
}


//. 특정 인덱스의 요소 조회
// 연결된 모든 스택을 순회하며 특정 인덱스의 요소를 반환.
// 예를 들어, index = 4일 때, 스택 전체를 탐색하여 5번째 요소를 반환.
element get_element_at(Stack s, int index) {
    while (s != NULL) {
        if (index < s->size) {
            Node *current = s->top;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
            return current->data;
        }
        index -= s->size;
        s = s->next_stack;
    }
    printf("Index out of bounds\n");
    exit(EXIT_FAILURE);
}

// 스택 병합
// 두 개의 스택을 하나로 병합하여 새로운 연결된 스택을 생성.
Stack merge_stacks(Stack s1, Stack s2) {
    if (s1 == NULL) return s2;
    if (s2 == NULL) return s1;

    Stack current = s1;
    while (current->next_stack != NULL) {
        current = current->next_stack;
    }
    current->next_stack = s2;
    return s1;
}


//  스택 내 요소 합산
// 스택 내 모든 요소의 합을 계산하는 함수입니다
element sum_stack(Stack s) {
    element sum = 0;
    while (s != NULL) {
        Node *current = s->top;
        while (current != NULL) {
            sum += current->data;
            current = current->next;
        }
        s = s->next_stack;
    }
    return sum;
}

// 스택 내 최댓값
element find_max(Stack s) {
    if (s == NULL) {
        printf("Stack is empty\n");
        exit(EXIT_FAILURE);
    }

    element max = s->top->data;
    while (s != NULL) {
        Node *current = s->top;
        while (current != NULL) {
            if (current->data > max) {
                max = current->data;
            }
            current = current->next;
        }
        s = s->next_stack;
    }
    return max;
}

// 스택 내 최소값
element find_min(Stack s) {
    if (s == NULL) {
        printf("Stack is empty\n");
        exit(EXIT_FAILURE);
    }

    element min = s->top->data;
    while (s != NULL) {
        Node *current = s->top;
        while (current != NULL) {
            if (current->data < min) {
                min = current->data;
            }
            current = current->next;
        }
        s = s->next_stack;
    }
    return min;
}



// 특정 값 찾기
// 연결된 스택 전체를 탐색하며 특정 값을 가진 요소가 있는지 확인하고, 있다면 해당 위치(인덱스)를 반환.
int find_element(Stack s, element value) {
    int index = 0;
    while (s != NULL) {
        Node *current = s->top;
        while (current != NULL) {
            if (current->data == value) {
                return index;
            }
            current = current->next;
            index++;
        }
        s = s->next_stack;
    }
    return -1; // 찾지 못함
}


// 역순으로 요소 반환
// 스택의 모든 요소를 역순으로 출력하거나 반환하는 함수.
void print_reverse(Stack s) {
    if (s == NULL) return;
    print_reverse(s->next_stack); // 재귀적으로 다음 스택 호출
    Node *current = s->top;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
}

// 스택 깊이(레벨) 반환
// 연결된 스택의 총 스택 개수를 반환.
int stack_depth(Stack s) {
    int depth = 0;
    while (s != NULL) {
        depth++;
        s = s->next_stack;
    }
    return depth;
}


//스택 내 요소 삭제
// 연결된 모든 스택을 탐색하며 특정 값을 삭제.
// 값이 존재하지 않을 경우 아무 작업도 하지 않음.
void delete_element(Stack *s, element value) {
    Stack current_stack = *s;
    while (current_stack != NULL) {
        Node *prev = NULL, *current = current_stack->top;
        while (current != NULL) {
            if (current->data == value) {
                if (prev == NULL) {
                    current_stack->top = current->next;
                } else {
                    prev->next = current->next;
                }
                free(current);
                current_stack->size--;
                return;
            }
            prev = current;
            current = current->next;
        }
        current_stack = current_stack->next_stack;
    }
}


//스택 복사
// 기존 스택을 복사하여 동일한 구조의 새 스택 생성.

Stack copy_stack(Stack s) {
    if (s == NULL) return NULL;

    Stack new_stack = create();
    Stack current_stack = s;
    Stack last_new_stack = NULL;

    while (current_stack != NULL) {
        Node *current = current_stack->top;
        while (current != NULL) {
            push(&new_stack, current->data);
            current = current->next;
        }
        if (last_new_stack != NULL) {
            last_new_stack->next_stack = new_stack;
        }
        last_new_stack = new_stack;
        current_stack = current_stack->next_stack;
        if (current_stack != NULL) {
            new_stack = create();
        }
    }
    return new_stack;
}

// 스택의 평균값 계산
// 스택 내 모든 요소의 평균값을 계산하는 함수입니다
double calculate_average(Stack s) {
    int count = 0;
    element sum = 0;
    while (s != NULL) {
        Node *current = s->top;
        while (current != NULL) {
            sum += current->data;
            count++;
            current = current->next;
        }
        s = s->next_stack;
    }

    if (count == 0) {
        printf("Stack is empty\n");
        exit(EXIT_FAILURE);
    }

    return (double)sum / count;
}



// 스택 내 요소의 중복 제거
// 스택에서 중복된 값을 제거하여 고유한 값만 남기는 함수
void remove_duplicates(Stack *s) {
    Stack temp_stack = create();
    while (!is_empty(*s)) {
        element value = pop(s);
        if (find_element(temp_stack, value) == -1) {
            push(&temp_stack, value);
        }
    }

    // 복사된 스택을 다시 원래 스택으로 역순으로 넣기
    while (!is_empty(temp_stack)) {
        push(s, pop(&temp_stack));
    }

    destroy(temp_stack);
}


// 스택 내 특정 범위의 요소 삭제
// 스택에서 특정 값의 범위에 해당하는 요소를 삭제
void delete_in_range(Stack *s, element min_value, element max_value) {
    Stack temp_stack = create();
    while (!is_empty(*s)) {
        element value = pop(s);
        if (value < min_value || value > max_value) {
            push(&temp_stack, value);
        }
    }

    // 복사된 스택을 다시 원래 스택으로 역순으로 넣기
    while (!is_empty(temp_stack)) {
        push(s, pop(&temp_stack));
    }

    destroy(temp_stack);
}


// 테스트용 main 함수
int main() {
    // 스택 생성
    Stack s1 = create();
    Stack s2 = create();

    // 요소 추가 (push)
    printf("Pushing elements to s1...\n");
    push(&s1, 10);
    push(&s1, 20);
    push(&s1, 30); // 첫 번째 스택이 가득 참
    push(&s1, 40); // 두 번째 스택 생성
    push(&s1, 50);

    // 스택 출력 (print_stack)
    printf("Initial stack (s1):\n");
    print_stack(s1);

    // 총 크기 확인 (total_size)
    printf("Total size of stack s1: %d\n", total_size(s1));

    // 스택 깊이 확인 (stack_depth)
    printf("Depth of stack s1: %d\n", stack_depth(s1));

    // 최댓값 및 최솟값 확인 (find_max, find_min)
    printf("Maximum value in stack s1: %d\n", find_max(s1));
    printf("Minimum value in stack s1: %d\n", find_min(s1));

    // 스택의 평균값 계산 (calculate_average)
    printf("Average value in stack s1: %.2f\n", calculate_average(s1));

    // 특정 값 찾기 (find_element)
    int value = 30;
    int index = find_element(s1, value);
    printf("Value %d found at index: %d\n", value, index);

    // 특정 인덱스의 요소 조회 (get_element_at)
    int search_index = 4;
    printf("Element at index %d: %d\n", search_index, get_element_at(s1, search_index));

    // 역순 출력 (print_reverse)
    printf("Stack in reverse order:\n");
    print_reverse(s1);
    printf("\n");

    // 요소 삭제 (delete_element)
    printf("Deleting value %d from stack s1.\n", value);
    delete_element(&s1, value);
    printf("Stack after deleting value %d:\n", value);
    print_stack(s1);

    // 중복 제거 (remove_duplicates)
    printf("Adding duplicate elements to s1...\n");
    push(&s1, 10);
    push(&s1, 20);
    printf("Stack with duplicates added:\n");
    print_stack(s1);
    printf("Removing duplicates from s1...\n");
    remove_duplicates(&s1);
    print_stack(s1);

    // 특정 범위의 요소 삭제 (delete_in_range)
    printf("Deleting values in range 10 to 30 from s1...\n");
    delete_in_range(&s1, 10, 30);
    print_stack(s1);

    // 스택 복사 (copy_stack)
    printf("Copying stack s1 to s2...\n");
    s2 = copy_stack(s1);
    printf("Copied stack (s2):\n");
    print_stack(s2);

    // 스택 병합 (merge_stacks)
    printf("Merging s1 and s2 into a new stack...\n");
    Stack merged_stack = merge_stacks(s1, s2);
    printf("Merged stack:\n");
    print_stack(merged_stack);

    // 스택 내 요소 합산 (sum_stack)
    printf("Sum of all elements in merged stack: %d\n", sum_stack(merged_stack));

    // pop 연산 및 최상단 값 확인 (pop, peek)
    printf("Peeking top element in merged stack: %d\n", peek(merged_stack));
    printf("Popping elements from merged stack:\n");
    while (!is_empty(merged_stack)) {
        printf("Popped: %d\n", pop(&merged_stack));
    }

    // 스택이 비었는지 확인 (is_empty)
    printf("Is merged stack empty? %s\n", is_empty(merged_stack) ? "Yes" : "No");

    // 스택 삭제 (destroy)
    destroy(merged_stack);

    return 0;
}
