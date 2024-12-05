/*
1. Stack create() - 스택을 생성하고 초기화.
2. void make_empty(Stack s) - 스택을 비우고 모든 노드를 메모리에서 해제.
3. void destroy(Stack s) - 스택 전체를 삭제하고 모든 메모리를 해제.
4. boolean isEmpty(Stack s) - 스택이 비었는지 확인.
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



#include <iostream>
#include <stdexcept>
using namespace std;

// 스택의 최대 용량
#define STACK_CAPACITY 3

// 노드 구조체 정의
struct Node {
    int data;       // 노드 데이터
    Node* next;     // 다음 노드를 가리키는 포인터

    Node(int value) : data(value), next(nullptr) {} // 생성자
};

// 스택 구조체 정의
struct Stack {
    Node* top;              // 스택의 최상위 노드
    int size;               // 현재 스택의 크기
    Stack* next_stack;      // 다음 연결된 스택

    Stack() : top(nullptr), size(0), next_stack(nullptr) {} // 생성자
};

// 스택 생성 함수
Stack* create() {
    return new Stack();
}

// 스택 비우기
void make_empty(Stack* s) {
    while (s->top != nullptr) {
        Node* old_top = s->top;
        s->top = old_top->next;
        delete old_top;
    }
    s->size = 0;
}

// 스택 전체 삭제
void destroy(Stack* s) {
    while (s != nullptr) {
        Stack* old_stack = s;
        s = s->next_stack;
        make_empty(old_stack);
        delete old_stack;
    }
}

// 스택이 비어 있는지 확인
bool isEmpty(Stack* s) {
    return s->top == nullptr;
}

// 스택에 요소 추가
void push(Stack*& s, int value) {
    if (s->size >= STACK_CAPACITY) {
        Stack* new_stack = create();
        new_stack->next_stack = s;
        s = new_stack;
    }
    Node* new_node = new Node(value);
    new_node->next = s->top;
    s->top = new_node;
    s->size++;
}

// 스택에서 요소 제거 및 반환
int pop(Stack*& s) {
    if (isEmpty(s)) {
        if (s->next_stack != nullptr) {
            Stack* old_stack = s;
            s = s->next_stack;
            delete old_stack;
            return pop(s);
        } else {
            throw runtime_error("Stack is empty");
        }
    }
    Node* old_top = s->top;
    int value = old_top->data;
    s->top = old_top->next;
    delete old_top;
    s->size--;
    return value;
}

// 스택의 최상위 요소를 반환 (제거하지 않음)
int peek(Stack* s) {
    if (isEmpty(s)) {
        throw runtime_error("Stack is empty");
    }
    return s->top->data;
}

// 스택의 총 크기를 반환
int total_size(Stack* s) {
    int total = 0;
    while (s != nullptr) {
        total += s->size;
        s = s->next_stack;
    }
    return total;
}

// 스택 출력
void print_stack(Stack* s) {
    int stack_num = 1;
    while (s != nullptr) {
        cout << "Stack " << stack_num++ << ": ";
        Node* current = s->top;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
        s = s->next_stack;
    }
}

// 특정 인덱스의 요소 반환
int get_element_at(Stack* s, int index) {
    while (s != nullptr) {
        if (index < s->size) {
            Node* current = s->top;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
            return current->data;
        }
        index -= s->size;
        s = s->next_stack;
    }
    throw runtime_error("Index out of bounds");
}

// 두 스택 병합
Stack* merge_stacks(Stack* s1, Stack* s2) {
    if (s1 == nullptr) return s2;
    if (s2 == nullptr) return s1;

    Stack* current = s1;
    while (current->next_stack != nullptr) {
        current = current->next_stack;
    }
    current->next_stack = s2;
    return s1;
}

// 스택 내 모든 요소의 합계 계산
int sum_stack(Stack* s) {
    int sum = 0;
    while (s != nullptr) {
        Node* current = s->top;
        while (current != nullptr) {
            sum += current->data;
            current = current->next;
        }
        s = s->next_stack;
    }
    return sum;
}

// 스택 내 최댓값 반환
int find_max(Stack* s) {
    if (s == nullptr) throw runtime_error("Stack is empty");

    int max_value = s->top->data;
    while (s != nullptr) {
        Node* current = s->top;
        while (current != nullptr) {
            max_value = max(max_value, current->data);
            current = current->next;
        }
        s = s->next_stack;
    }
    return max_value;
}

// 스택 내 최솟값 반환
int find_min(Stack* s) {
    if (s == nullptr) throw runtime_error("Stack is empty");

    int min_value = s->top->data;
    while (s != nullptr) {
        Node* current = s->top;
        while (current != nullptr) {
            min_value = min(min_value, current->data);
            current = current->next;
        }
        s = s->next_stack;
    }
    return min_value;
}

// 특정 값을 가진 요소의 인덱스 반환
int find_element(Stack* s, int value) {
    int index = 0;
    while (s != nullptr) {
        Node* current = s->top;
        while (current != nullptr) {
            if (current->data == value) return index;
            current = current->next;
            index++;
        }
        s = s->next_stack;
    }
    return -1; // 찾지 못한 경우
}

// 스택의 모든 요소를 역순으로 출력
void print_reverse(Stack* s) {
    if (s == nullptr) return;
    print_reverse(s->next_stack);
    Node* current = s->top;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
}

// 스택 깊이 반환
int stack_depth(Stack* s) {
    int depth = 0;
    while (s != nullptr) {
        depth++;
        s = s->next_stack;
    }
    return depth;
}

// 특정 값을 가진 요소 삭제
void delete_element(Stack*& s, int value) {
    Stack* current_stack = s;
    while (current_stack != nullptr) {
        Node* prev = nullptr;
        Node* current = current_stack->top;
        while (current != nullptr) {
            if (current->data == value) {
                if (prev == nullptr) {
                    current_stack->top = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                current_stack->size--;
                return;
            }
            prev = current;
            current = current->next;
        }
        current_stack = current_stack->next_stack;
    }
}

// 스택 복사
Stack* copy_stack(Stack* s) {
    if (s == nullptr) return nullptr;

    Stack* new_stack = create();
    Stack* current_stack = s;
    while (current_stack != nullptr) {
        Node* current = current_stack->top;
        while (current != nullptr) {
            push(new_stack, current->data);
            current = current->next;
        }
        current_stack = current_stack->next_stack;
    }
    return new_stack;
}

// 스택 내 모든 요소의 평균값 반환
double calculate_average(Stack* s) {
    int sum = 0, count = 0;
    while (s != nullptr) {
        Node* current = s->top;
        while (current != nullptr) {
            sum += current->data;
            count++;
            current = current->next;
        }
        s = s->next_stack;
    }
    if (count == 0) throw runtime_error("Stack is empty");
    return static_cast<double>(sum) / count;
}

// 스택에서 중복된 요소 제거
void remove_duplicates(Stack*& s) {
    Stack* temp_stack = create();
    while (!isEmpty(s)) {
        int value = pop(s);
        if (find_element(temp_stack, value) == -1) {
            push(temp_stack, value);
        }
    }
    while (!isEmpty(temp_stack)) {
        push(s, pop(temp_stack));
    }
    destroy(temp_stack);
}

// 특정 값 범위의 요소 삭제
void delete_in_range(Stack*& s, int min_value, int max_value) {
    Stack* temp_stack = create();
    while (!isEmpty(s)) {
        int value = pop(s);
        if (value < min_value || value > max_value) {
            push(temp_stack, value);
        }
    }
    while (!isEmpty(temp_stack)) {
        push(s, pop(temp_stack));
    }
    destroy(temp_stack);
}

// 메인 함수
int main() {
    Stack* s1 = create();
    push(s1, 10);
    push(s1, 20);
    push(s1, 30);
    push(s1, 40);
    cout << "Initial stack:" << endl;
    print_stack(s1);

    cout << "Total size: " << total_size(s1) << endl;
    cout << "Stack depth: " << stack_depth(s1) << endl;

    cout << "Finding element 20: Index " << find_element(s1, 20) << endl;

    cout << "Stack in reverse order: ";
    print_reverse(s1);
    cout << endl;

    cout << "Calculating average: " << calculate_average(s1) << endl;

    delete_element(s1, 30);
    cout << "After deleting element 30:" << endl;
    print_stack(s1);

    remove_duplicates(s1);
    cout << "After removing duplicates:" << endl;
    print_stack(s1);

    delete_in_range(s1, 10, 20);
    cout << "After deleting elements in range [10, 20]:" << endl;
    print_stack(s1);

    destroy(s1);
    return 0;
}
