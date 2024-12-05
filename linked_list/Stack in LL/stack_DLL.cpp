#include <iostream>
#include <stdexcept>

#define STACK_CAPACITY 3 // 각 스택의 최대 용량

using namespace std;

class Node {
public:
    int data;       // 노드의 데이터
    Node* prev;     // 이전 노드
    Node* next;     // 다음 노드

    Node(int data) : data(data), prev(nullptr), next(nullptr) {}
};

class Stack {
private:
    Node* top;          // 스택의 최상위 노드
    int size;           // 현재 스택의 크기
    Stack* nextStack;   // 다음 연결된 스택
    Stack* prevStack;   // 이전 연결된 스택

public:
    Stack() : top(nullptr), size(0), nextStack(nullptr), prevStack(nullptr) {}

    ~Stack() {
        clear();
        delete nextStack; // 다음 스택의 메모리도 해제
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    void push(int value) {
        if (size >= STACK_CAPACITY) {
            if (!nextStack) {
                // 새 스택 생성
                nextStack = new Stack();
                nextStack->prevStack = this;
                cout << "Creating new stack for value " << value << "." << endl;
            }
            nextStack->push(value);
            return;
        }

        // 새 노드 추가
        Node* newNode = new Node(value);
        newNode->next = top;
        if (top) {
            top->prev = newNode;
        }
        top = newNode;
        size++;
        cout << "Pushed value " << value << " to current stack. Size is now " << size << "." << endl;
    }

    int pop() {
        if (isEmpty()) {
            if (nextStack) {
                // 현재 스택이 비었으면 다음 스택으로 이동
                replaceWithNextStack();
                return pop();
            } else {
                throw runtime_error("Stack is empty");
            }
        }

        // 최상위 값을 제거
        Node* oldTop = top;
        int value = oldTop->data;
        top = oldTop->next;
        if (top) {
            top->prev = nullptr;
        }
        delete oldTop;
        size--;
        return value;
    }

    int peek() const {
        if (isEmpty()) {
            throw runtime_error("Stack is empty");
        }
        return top->data;
    }

    int totalSize() const {
        int total = size;
        if (nextStack) {
            total += nextStack->totalSize();
        }
        return total;
    }

    void printStack() const {
        const Stack* currentStack = this;
        int stackNum = 1;
        while (currentStack) {
            cout << "Stack " << stackNum++ << ": ";
            Node* currentNode = currentStack->top;
            while (currentNode) {
                cout << currentNode->data << " ";
                currentNode = currentNode->next;
            }
            cout << endl;
            currentStack = currentStack->nextStack;
        }
    }

    int getElementAt(int index) const {
        if (index < size) {
            Node* currentNode = top;
            for (int i = 0; i < index; i++) {
                currentNode = currentNode->next;
            }
            return currentNode->data;
        } else if (nextStack) {
            return nextStack->getElementAt(index - size);
        } else {
            throw out_of_range("Index out of bounds");
        }
    }

    int depth() const {
        if (nextStack) {
            return 1 + nextStack->depth();
        }
        return 1;
    }

    void removeValue(int value) {
        Node* current = top;

        while (current) {
            if (current->data == value) {
                if (current->prev) {
                    current->prev->next = current->next;
                }
                if (current->next) {
                    current->next->prev = current->prev;
                }
                if (current == top) {
                    top = current->next;
                }
                delete current;
                size--;
                return;
            }
            current = current->next;
        }

        if (nextStack) {
            nextStack->removeValue(value);
        }
    }

    void removeInRange(int minValue, int maxValue) {
        Stack tempStack;

        while (!isEmpty()) {
            int value = pop();
            if (value < minValue || value > maxValue) {
                tempStack.push(value);
            }
        }

        while (!tempStack.isEmpty()) {
            push(tempStack.pop());
        }

        if (nextStack) {
            nextStack->removeInRange(minValue, maxValue);
        }
    }

private:
    void clear() {
        while (top) {
            Node* oldTop = top;
            top = top->next;
            delete oldTop;
        }
        size = 0;
    }

    void replaceWithNextStack() {
        if (!nextStack) {
            throw runtime_error("No next stack to replace");
        }
        top = nextStack->top;
        size = nextStack->size;
        Stack* oldNext = nextStack;
        nextStack = nextStack->nextStack;
        if (nextStack) {
            nextStack->prevStack = this;
        }
        oldNext->top = nullptr;
        oldNext->nextStack = nullptr;
        delete oldNext;
    }
};

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
    s1.printStack();

    // 총 크기 확인
    cout << "Total size of stack s1: " << s1.totalSize() << endl;

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
    s1.printStack();

    // 특정 범위의 요소 삭제
    cout << "Removing values in range 10 to 30 from stack." << endl;
    s1.removeInRange(10, 30);
    s1.printStack();

    return 0;
}
