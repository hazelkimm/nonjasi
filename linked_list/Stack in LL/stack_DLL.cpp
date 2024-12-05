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



#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <set>

using namespace std;

class Node {
public:
    vector<int> stack; // 스택 데이터를 저장하는 벡터
    int capacity;      // 스택의 최대 용량
    Node* next;        // 다음 노드를 가리키는 포인터
    Node* prev;        // 이전 노드를 가리키는 포인터

    Node(int cap) : capacity(cap), next(nullptr), prev(nullptr) {}
};

class LinkedListStack {
private:
    Node* head; // 첫 노드
    Node* tail; // 마지막 노드
    int capacity; // 각 노드의 최대 용량

public:
    LinkedListStack(int cap) : capacity(cap) {
        head = new Node(cap);
        tail = head;
    }

    bool is_empty(LinkedListStack& stack) {
    // 스택이 비었는지 확인
        return stack.head == stack.tail && stack.tail->stack.empty();
    }

    void make_empty(LinkedListStack& stack) {
        // 스택의 모든 노드를 비웁니다.
        Node* current = stack.head->next;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        stack.head->next = nullptr;
        stack.tail = stack.head;
        stack.head->stack.clear();
    }

    void destroy(LinkedListStack& stack) {
        // 스택의 모든 노드와 데이터를 삭제하고 메모리를 해제합니다.
        make_empty(stack);
        delete stack.head;
        stack.head = stack.tail = nullptr;
    }


    void push(int value) {
        // 스택에 요소를 추가합니다. 용량을 초과하면 새 노드를 생성합니다.
        if (tail->stack.size() < tail->capacity) {
            tail->stack.push_back(value);
        } else {
            Node* newNode = new Node(capacity);
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
            tail->stack.push_back(value);
        }
    }

    int pop() {
        // 스택에서 요소를 제거하고 반환합니다.
        if (tail->stack.empty()) {
            if (tail->prev) {
                tail = tail->prev;
                delete tail->next;
                tail->next = nullptr;
                return pop();
            } else {
                throw out_of_range("스택이 비어 있습니다.");
            }
        }
        int value = tail->stack.back();
        tail->stack.pop_back();
        return value;
    }

    int peek() {
        // 스택의 최상위 요소를 반환합니다. (제거하지 않음)
        if (tail->stack.empty()) {
            if (tail->prev) {
                tail = tail->prev;
                delete tail->next;
                tail->next = nullptr;
                return peek();
            } else {
                throw out_of_range("스택이 비어 있습니다.");
            }
        }
        return tail->stack.back();
    }

    int total_size() {
        // 스택 전체의 요소 개수를 반환합니다.
        int size = 0;
        Node* current = head;
        while (current) {
            size += current->stack.size();
            current = current->next;
        }
        return size;
    }

    void print_stack() {
        // 스택의 모든 요소를 출력합니다.
        Node* current = head;
        while (current) {
            for (int value : current->stack) {
                cout << value << " ";
            }
            current = current->next;
            if (current) cout << " -> ";
        }
        cout << "None" << endl;
    }

    int get_element_at(int index) {
        // 특정 인덱스에 위치한 요소를 반환합니다.
        Node* current = head;
        while (current) {
            if (index < current->stack.size()) {
                return current->stack[index];
            }
            index -= current->stack.size();
            current = current->next;
        }
        throw out_of_range("인덱스가 범위를 초과했습니다.");
    }

    void merge_stacks(LinkedListStack& stack) {
        // 다른 스택과 병합합니다.
        Node* current = stack.head;
        while (current) {
            for (int value : current->stack) {
                push(value);
            }
            current = current->next;
        }
    }

    int sum_stack() {
        // 스택 내 모든 요소의 합을 반환합니다.
        int total = 0;
        Node* current = head;
        while (current) {
            for (int value : current->stack) {
                total += value;
            }
            current = current->next;
        }
        return total;
    }

    int find_max() {
        // 스택 내 최댓값을 반환합니다.
        int max_value = INT_MIN;
        Node* current = head;
        while (current) {
            for (int value : current->stack) {
                max_value = max(max_value, value);
            }
            current = current->next;
        }
        if (max_value == INT_MIN) throw runtime_error("스택이 비어 있습니다.");
        return max_value;
    }

    int find_min() {
        // 스택 내 최솟값을 반환합니다.
        int min_value = INT_MAX;
        Node* current = head;
        while (current) {
            for (int value : current->stack) {
                min_value = min(min_value, value);
            }
            current = current->next;
        }
        if (min_value == INT_MAX) throw runtime_error("스택이 비어 있습니다.");
        return min_value;
    }

    int find_element(int value) {
        // 특정 값을 가진 요소의 인덱스를 반환합니다.
        int index = 0;
        Node* current = head;
        while (current) {
            auto it = find(current->stack.begin(), current->stack.end(), value);
            if (it != current->stack.end()) {
                return index + distance(current->stack.begin(), it);
            }
            index += current->stack.size();
            current = current->next;
        }
        return -1;
    }

    void print_reverse() {
        // 스택의 모든 요소를 역순으로 출력합니다.
        Node* current = tail;
        while (current) {
            for (auto it = current->stack.rbegin(); it != current->stack.rend(); ++it) {
                cout << *it << " ";
            }
            current = current->prev;
            if (current) cout << " <- ";
        }
        cout << "None" << endl;
    }

    int depth() {
        // 연결된 스택의 총 개수를 반환합니다.
        int depth = 0;
        Node* current = head;
        while (current) {
            depth++;
            current = current->next;
        }
        return depth;
    }

    void delete_element(int value) {
        // 스택에서 특정 값을 삭제합니다.
        Node* current = head;
        while (current) {
            auto it = remove(current->stack.begin(), current->stack.end(), value);
            current->stack.erase(it, current->stack.end());
            current = current->next;
        }
    }

    double calculate_average() {
        // 스택 내 모든 요소의 평균값을 반환합니다.
        int total_sum = sum_stack();
        int total_elements = total_size();
        if (total_elements == 0) throw runtime_error("스택이 비어 있습니다.");
        return static_cast<double>(total_sum) / total_elements;
    }

    void remove_duplicates() {
        // 스택에서 중복된 요소를 제거합니다.
        set<int> seen;
        Node* current = head;
        while (current) {
            vector<int> new_stack;
            for (int value : current->stack) {
                if (seen.find(value) == seen.end()) {
                    new_stack.push_back(value);
                    seen.insert(value);
                }
            }
            current->stack = new_stack;
            current = current->next;
        }
    }

    void delete_in_range(int min_value, int max_value) {
        // 특정 값 범위의 요소를 삭제합니다.
        Node* current = head;
        while (current) {
            vector<int> new_stack;
            for (int value : current->stack) {
                if (value < min_value || value > max_value) {
                    new_stack.push_back(value);
                }
            }
            current->stack = new_stack;
            current = current->next;
        }
    }
};

// 메인 함수
int main() {
    LinkedListStack stack(3);

    // 1. Push 테스트
    cout << "1. Push Test:\n";
    for (int i = 1; i <= 10; ++i) stack.push(i);
    stack.print_stack();

    // 2. Pop 테스트
    cout << "\n2. Pop Test:\n";
    cout << "Popped value: " << stack.pop() << endl;
    stack.print_stack();

    // 3. Peek 테스트
    cout << "\n3. Peek Test:\n";
    cout << "Top value: " << stack.peek() << endl;

    // 4. Total Size 테스트
    cout << "\n4. Total Size Test:\n";
    cout << "Total size: " << stack.total_size() << endl;

    // 5. Get Element At 테스트
    cout << "\n5. Get Element At Test:\n";
    cout << "Element at index 4: " << stack.get_element_at(4) << endl;

    // 6. Sum Stack 테스트
    cout << "\n6. Sum Stack Test:\n";
    cout << "Sum of stack: " << stack.sum_stack() << endl;

    // 7. Find Max 테스트
    cout << "\n7. Find Max Test:\n";
    cout << "Max value: " << stack.find_max() << endl;

    // 8. Find Min 테스트
    cout << "\n8. Find Min Test:\n";
    cout << "Min value: " << stack.find_min() << endl;

    // 9. Find Element 테스트
    cout << "\n9. Find Element Test:\n";
    cout << "Index of element 5: " << stack.find_element(5) << endl;

    // 10. Print Reverse 테스트
    cout << "\n10. Print Reverse Test:\n";
    stack.print_reverse();

    // 11. Depth 테스트
    cout << "\n11. Depth Test:\n";
    cout << "Depth: " << stack.depth() << endl;

    // 12. Delete Element 테스트
    cout << "\n12. Delete Element Test:\n";
    stack.delete_element(4);
    stack.print_stack();

    // 13. Calculate Average 테스트
    cout << "\n13. Calculate Average Test:\n";
    cout << "Average: " << stack.calculate_average() << endl;

    // 14. Remove Duplicates 테스트
    cout << "\n14. Remove Duplicates Test:\n";
    stack.push(5);
    stack.push(6);
    stack.push(6);
    stack.remove_duplicates();
    stack.print_stack();

    // 15. Delete in Range 테스트
    cout << "\n15. Delete in Range Test:\n";
    stack.delete_in_range(2, 6);
    stack.print_stack();

    // 16. Merge Stacks 테스트
    cout << "\n16. Merge Stacks Test:\n";
    LinkedListStack stack2(3);
    for (int i = 20; i <= 23; ++i) stack2.push(i);
    stack.merge_stacks(stack2);
    stack.print_stack();

    return 0;
}
