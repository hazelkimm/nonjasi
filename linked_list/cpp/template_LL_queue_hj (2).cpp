#include <iostream>
#include <vector>
using namespace std;

// Node 템플릿 클래스 정의 (스택을 포함하는 노드)
template <typename T>
class Node {
public:
    vector<T> stack;  // 벡터로 스택을 구현 (최대 3개까지)
    Node* next;       // 다음 노드를 가리키는 포인터
    static const int MAX_CAPACITY = 3;  // 스택의 최대 크기

    // 생성자
    Node() {
        this->next = nullptr;
    }

    // 스택이 꽉 찼는지 확인
    bool isFull() {
        return stack.size() == MAX_CAPACITY;
    }

    // 스택이 비었는지 확인
    bool isEmpty() {
        return stack.empty();
    }

    // 스택에 원소 추가
    void push(T data) {
        if (!isFull()) {
            stack.push_back(data);
        } else {
            cout << "Stack is full!" << endl;
        }
    }

    // 스택에서 원소 제거 및 반환
    T pop() {
        if (!isEmpty()) {
            T topElement = stack.back();
            stack.pop_back();
            return topElement;
        } else {
            cout << "Stack is empty!" << endl;
            return T();
        }
    }

    // 스택의 최상단 원소 반환
    T peek() {
        if (!isEmpty()) {
            return stack.back();
        } else {
            cout << "Stack is empty!" << endl;
            return T();
        }
    }
};

// Linked List of Stacks 템플릿 클래스 정의
template <typename T>
class LinkedListOfStacks {
private:
    Node<T>* head;  // 리스트의 첫 번째 노드를 가리키는 포인터

public:
    // 생성자
    LinkedListOfStacks() {
        head = new Node<T>();  // 빈 노드로 시작
    }

    // 소멸자: 메모리 해제
    ~LinkedListOfStacks() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
    }

    // 리스트의 마지막 노드를 찾음
    Node<T>* getLastNode() {
        Node<T>* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        return current;
    }

    // 스택에 원소 추가 (push)
    void push(T data) {
        Node<T>* lastNode = getLastNode();
        if (lastNode->isFull()) {
            // 스택이 꽉 찬 경우 새 노드를 추가
            Node<T>* newNode = new Node<T>();
            newNode->push(data);
            lastNode->next = newNode;
        } else {
            // 스택이 비어 있는 경우 원소를 추가
            lastNode->push(data);
        }
    }

    // 스택에서 원소 제거 (pop)
    T pop() {
        Node<T>* current = head;
        Node<T>* prev = nullptr;

        // 마지막 노드까지 이동
        while (current->next != nullptr) {
            prev = current;
            current = current->next;
        }

        // 현재 노드에서 pop 실행
        if (!current->isEmpty()) {
            return current->pop();
        } else if (prev != nullptr && current->isEmpty()) {
            // 현재 노드가 비었으면 이전 노드로 이동하여 pop
            prev->next = nullptr;  // 마지막 노드 제거
            delete current;
            return prev->pop();
        } else {
            cout << "All stacks are empty!" << endl;
            return T();
        }
    }

    // 리스트의 모든 스택을 출력
    void printStacks() {
        Node<T>* current = head;
        int nodeIndex = 1;
        while (current != nullptr) {
            cout << "Stack " << nodeIndex << ": ";
            for (auto& item : current->stack) {
                cout << item << " ";
            }
            cout << endl;
            current = current->next;
            nodeIndex++;
        }
    }
};

int main() {
    LinkedListOfStacks<int> stackList;

    // Push 예시
    for (int i = 1; i <= 10; i++) {
        stackList.push(i);
    }
    stackList.printStacks();

    // Pop 예시
    for (int i = 0; i < 5; i++) {
        cout << "Popped: " << stackList.pop() << endl;
    }
    stackList.printStacks();

    return 0;
}
