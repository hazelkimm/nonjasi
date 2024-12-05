#include <iostream>
#include <stdexcept>
#define STACK_CAPACITY 3 // 각 스택의 최대 용량

using namespace std;

typedef int element;

class Node {
public:
    element data;   // 데이터 값
    Node* next;     // 다음 노드를 가리키는 포인터

    Node(element data) : data(data), next(nullptr) {}
};

class Stack {
private:
    Node* top;      // 스택의 최상위 요소
    int size;       // 현재 스택의 크기
    Stack* nextStack; // 다음 연결된 스택

public:
    // 생성자: 스택 초기화
    Stack() : top(nullptr), size(0), nextStack(nullptr) {}

    // 소멸자: 메모리 정리
    ~Stack() {
        clear();           // 현재 스택의 모든 요소 삭제
        delete nextStack;  // 연결된 다음 스택 메모리 삭제
    }

    // 스택이 비었는지 확인
    bool isEmpty() const {
        return top == nullptr;
    }

    // 요소 추가
    void push(element value) {
        if (size >= STACK_CAPACITY) {
            // 현재 스택이 가득 찬 경우 새 스택 생성
            Stack* newStack = new Stack();
            newStack->nextStack = this->nextStack;
            this->nextStack = newStack;
            newStack->push(value);
            return;
        }

        // 새 노드를 만들어 스택의 top에 추가
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
        size++;
    }

    // 최상위 요소 제거 및 반환
    element pop() {
        if (isEmpty()) {
            if (nextStack != nullptr) {
                // 현재 스택이 비었으면 다음 스택으로 이동
                Stack* oldStack = nextStack;
                nextStack = nextStack->nextStack;
                delete oldStack;
                return pop();
            } else {
                throw runtime_error("Stack is empty");
            }
        }

        // 최상위 요소 삭제
        Node* oldTop = top;
        element value = oldTop->data;
        top = oldTop->next;
        delete oldTop;
        size--;
        return value;
    }

    // 최상위 요소 반환
    element peek() const {
        if (isEmpty()) {
            throw runtime_error("Stack is empty");
        }
        return top->data;
    }

    // 스택의 총 크기 반환 (모든 연결된 스택의 요소 수 합산)
    int getSize() const {
        int totalSize = size;
        if (nextStack) {
            totalSize += nextStack->getSize();
        }
        return totalSize;
    }

    // 스택의 모든 요소를 출력
    void print() const {
        int stackNum = 1;
        const Stack* current = this;
        while (current) {
            cout << "Stack " << stackNum++ << ": ";
            Node* node = current->top;
            while (node) {
                cout << node->data << " ";
                node = node->next;
            }
            cout << endl;
            current = current->nextStack;
        }
    }

    // 특정 인덱스의 요소 반환
    element getElementAt(int index) const {
        if (index < size) {
            Node* current = top;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
            return current->data;
        } else if (nextStack) {
            return nextStack->getElementAt(index - size);
        } else {
            throw out_of_range("Index out of bounds");
        }
    }

    // 스택 초기화 (모든 요소 삭제)
    void clear() {
        while (top) {
            Node* oldTop = top;
            top = top->next;
            delete oldTop;
        }
        size = 0;
    }

    // 스택의 깊이 반환 (연결된 스택의 총 개수)
    int depth() const {
        if (nextStack) {
            return 1 + nextStack->depth();
        }
        return 1;
    }

    // 특정 값 삭제
    void removeValue(element value) {
        Node* prev = nullptr;
        Node* current = top;

        // 현재 스택에서 값 찾기
        while (current) {
            if (current->data == value) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    top = current->next;
                }
                delete current;
                size--;
                return;
            }
            prev = current;
            current = current->next;
        }

        // 연결된 스택에서 값 삭제
        if (nextStack) {
            nextStack->removeValue(value);
        }
    }

    // 특정 범위의 값 삭제
    void removeInRange(element minValue, element maxValue) {
        Stack tempStack;

        // 범위에 포함되지 않는 요소를 임시 스택으로 옮김
        while (!isEmpty()) {
            element value = pop();
            if (value < minValue || value > maxValue) {
                tempStack.push(value);
            }
        }

        // 임시 스택의 요소를 다시 원래 스택으로 복사
        while (!tempStack.isEmpty()) {
            push(tempStack.pop());
        }

        // 연결된 스택에서도 삭제
        if (nextStack) {
            nextStack->removeInRange(minValue, maxValue);
        }
    }
};

// 테스트용 main 함수
int main() {
    Stack s1;

    // 요소 추가
    cout << "Pushing elements to s1..." << endl;
    s1.push(10);
    s1.push(20);
    s1.push(30); // 첫 번째 스택이 가득 참
    s1.push(40); // 두 번째 스택 생성
    s1.push(50);

    // 스택 출력
    cout << "Initial stack (s1):" << endl;
    s1.print();

    // 총 크기 확인
    cout << "Total size of stack s1: " << s1.getSize() << endl;

    // 스택 깊이 확인
    cout << "Depth of stack s1: " << s1.depth() << endl;

    // 특정 인덱스의 요소 조회
    int searchIndex = 4;
    cout << "Element at index " << searchIndex << ": " << s1.getElementAt(searchIndex) << endl;

    // 최상단 값 확인 및 삭제
    cout << "Peeking top element: " << s1.peek() << endl;
    cout << "Popping top element: " << s1.pop() << endl;

    // 특정 값 삭제
    int deleteValue = 30;
    cout << "Removing value " << deleteValue << " from stack." << endl;
    s1.removeValue(deleteValue);
    s1.print();

    // 특정 범위의 요소 삭제
    cout << "Removing values in range 10 to 30 from stack." << endl;
    s1.removeInRange(10, 30);
    s1.print();

    return 0;
}
