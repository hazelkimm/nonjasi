#include <stdio.h>
#include <stdlib.h>

#define STACK_CAPACITY 3 // 각 스택의 최대 용량

typedef int element;

typedef struct Node {
    element data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;               // 스택의 최상위 노드
    int size;                // 현재 스택의 크기
    struct Stack* nextStack; // 다음 연결된 스택
    struct Stack* prevStack; // 이전 연결된 스택
} Stack;

// 스택 생성
Stack* create_stack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    stack->top = NULL;
    stack->size = 0;
    stack->nextStack = NULL;
    stack->prevStack = NULL;
    return stack;
}

// 노드 생성
Node* create_node(element value) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->data = value;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

// 스택이 비었는지 확인
int is_empty(Stack* stack) {
    return stack->top == NULL;
}

// 스택에 값 추가
void push(Stack** stack_ref, element value) {
    Stack* stack = *stack_ref;
    if (stack->size >= STACK_CAPACITY) {
        if (stack->nextStack == NULL) {
            printf("Creating new stack for value %d.\n", value);
            stack->nextStack = create_stack();
            stack->nextStack->prevStack = stack;
        }
        push(&stack->nextStack, value);
        return;
    }

    Node* new_node = create_node(value);
    new_node->next = stack->top;
    if (stack->top != NULL) {
        stack->top->prev = new_node;
    }
    stack->top = new_node;
    stack->size++;
    printf("Pushed value %d to current stack. Size is now %d.\n", value, stack->size);
}

// 스택의 최상위 값 제거 및 반환
element pop(Stack** stack_ref) {
    Stack* stack = *stack_ref;
    if (is_empty(stack)) {
        if (stack->nextStack != NULL) {
            *stack_ref = stack->nextStack;
            stack->nextStack->prevStack = NULL;
            free(stack);
            return pop(stack_ref);
        } else {
            printf("Stack is empty\n");
            exit(EXIT_FAILURE);
        }
    }

    Node* old_top = stack->top;
    element value = old_top->data;
    stack->top = old_top->next;
    if (stack->top != NULL) {
        stack->top->prev = NULL;
    }
    free(old_top);
    stack->size--;
    return value;
}

// 스택의 최상위 값 확인
element peek(Stack* stack) {
    if (is_empty(stack)) {
        printf("Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return stack->top->data;
}

// 모든 연결된 스택의 총 크기 반환
int total_size(Stack* stack) {
    if (stack == NULL) {
        return 0;
    }
    return stack->size + total_size(stack->nextStack);
}

// 연결된 스택의 깊이 반환
int stack_depth(Stack* stack) {
    if (stack == NULL) {
        return 0;
    }
    return 1 + stack_depth(stack->nextStack);
}

// 특정 인덱스의 요소 반환
element get_element_at(Stack* stack, int index) {
    if (index < stack->size) {
        Node* current = stack->top;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    } else if (stack->nextStack != NULL) {
        return get_element_at(stack->nextStack, index - stack->size);
    } else {
        printf("Index out of bounds\n");
        exit(EXIT_FAILURE);
    }
}

// 특정 값 삭제
void remove_value(Stack* stack, element value) {
    Node* current = stack->top;

    while (current != NULL) {
        if (current->data == value) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }
            if (current == stack->top) {
                stack->top = current->next;
            }
            free(current);
            stack->size--;
            return;
        }
        current = current->next;
    }

    if (stack->nextStack != NULL) {
        remove_value(stack->nextStack, value);
    }
}

// 특정 범위의 요소 삭제
void remove_in_range(Stack* stack, element min_value, element max_value) {
    if (stack == NULL) return;

    Stack* temp_stack = create_stack();
    while (!is_empty(stack)) {
        element value = pop(&stack);
        if (value < min_value || value > max_value) {
            push(&temp_stack, value);
        }
    }

    while (!is_empty(temp_stack)) {
        push(&stack, pop(&temp_stack));
    }

    free(temp_stack);
    if (stack->nextStack != NULL) {
        remove_in_range(stack->nextStack, min_value, max_value);
    }
}

// 스택 출력
void print_stack(Stack* stack) {
    int stack_num = 1;
    while (stack != NULL) {
        printf("Stack %d: ", stack_num++);
        Node* current = stack->top;
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
        stack = stack->nextStack;
    }
}

// 메모리 해제
void destroy_stack(Stack* stack) {
    while (stack != NULL) {
        Node* current = stack->top;
        while (current != NULL) {
            Node* next = current->next;
            free(current);
            current = next;
        }
        Stack* next_stack = stack->nextStack;
        free(stack);
        stack = next_stack;
    }
}

// 테스트 함수
int main() {
    Stack* s1 = create_stack();

    // 요소 추가
    printf("Pushing elements to s1...\n");
    push(&s1, 10);
    push(&s1, 20);
    push(&s1, 30); // 첫 번째 스택이 가득 참
    push(&s1, 40); // 두 번째 스택 생성
    push(&s1, 50);

    // 스택 출력
    printf("Initial stack (s1):\n");
    print_stack(s1);

    // 총 크기 확인
    printf("Total size of stack s1: %d\n", total_size(s1));

    // 스택 깊이 확인
    printf("Depth of stack s1: %d\n", stack_depth(s1));

    // 특정 인덱스의 요소 조회
    int search_index = 4;
    printf("Element at index %d: %d\n", search_index, get_element_at(s1, search_index));

    // 최상단 값 확인 및 삭제
    printf("Peeking top element: %d\n", peek(s1));
    printf("Popping top element: %d\n", pop(&s1));

    // 특정 값 삭제
    int delete_value = 30;
    printf("Removing value %d from stack.\n", delete_value);
    remove_value(s1, delete_value);
    print_stack(s1);

    // 특정 범위의 요소 삭제
    printf("Removing values in range 10 to 30 from stack.\n");
    remove_in_range(s1, 10, 30);
    print_stack(s1);

    // 스택 메모리 해제
    destroy_stack(s1);

    return 0;
}
