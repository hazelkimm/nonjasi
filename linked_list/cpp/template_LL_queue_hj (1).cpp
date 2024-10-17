#include <iostream>
#include <queue>
using namespace std;

// Node 템플릿 클래스 정의 (큐를 포함하는 노드)
template <typename T>
class Node {
public:
    queue<T> q;  // 큐를 이용하여 원소를 관리
    Node* next;  // 다음 노드를 가리키는 포인터
    static const int MAX_CAPACITY = 3;  // 큐의 최대 크기

    // 생성자
    Node() {
        this->next = nullptr;
    }

    // 큐가 꽉 찼는지 확인
    bool isFull() {
        return q.size() == MAX_CAPACITY;
    }

    // 큐가 비었는지 확인
    bool isEmpty() {
        return q.empty();
    }

    // 큐에 원소 추가
    void enqueue(T data) {
        if (!isFull()) {
            q.push(data);
        } else {
            cout << "Queue is full!" << endl;
        }
    }

    // 큐에서 원소 제거 및 반환
    T dequeue() {
        if (!isEmpty()) {
            T frontElement = q.front();
            q.pop();
            return frontElement;
        } else {
            cout << "Queue is empty!" << endl;
            return T();  // 기본값 반환
        }
    }

    // 큐의 앞쪽 원소 반환 (삭제하지 않고)
    T peek() {
        if (!isEmpty()) {
            return q.front();
        } else {
            cout << "Queue is empty!" << endl;
            return T();
        }
    }
};

// Linked List of Queues 템플릿 클래스 정의
template <typename T>
class LinkedListOfQueues {
private:
    Node<T>* head;  // 리스트의 첫 번째 노드를 가리키는 포인터

public:
    // 생성자
    LinkedListOfQueues() {
        head = new Node<T>();  // 빈 노드로 시작
    }

    // 소멸자: 메모리 해제
    ~LinkedListOfQueues() {
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

    // 큐에 원소 추가 (enqueue)
    void enqueue(T data) {
        Node<T>* lastNode = getLastNode();
        if (lastNode->isFull()) {
            // 큐가 꽉 찬 경우 새 노드를 추가
            Node<T>* newNode = new Node<T>();
            newNode->enqueue(data);
            lastNode->next = newNode;
        } else {
            // 큐에 원소를 추가
            lastNode->enqueue(data);
        }
    }

    // 큐에서 원소 제거 (dequeue)
    T dequeue() {
        if (head->isEmpty() && head->next != nullptr) {
            // 첫 번째 큐가 비어 있으면 다음 큐로 이동
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }

        if (!head->isEmpty()) {
            return head->dequeue();
        } else {
            cout << "All queues are empty!" << endl;
            return T();
        }
    }

    // 리스트의 모든 큐를 출력
    void printQueues() {
        Node<T>* current = head;
        int nodeIndex = 1;
        while (current != nullptr) {
            cout << "Queue " << nodeIndex << ": ";
            queue<T> tempQueue = current->q;
            while (!tempQueue.empty()) {
                cout << tempQueue.front() << " ";
                tempQueue.pop();
            }
            cout << endl;
            current = current->next;
            nodeIndex++;
        }
    }
};

int main() {
    LinkedListOfQueues<int> queueList;

    // Enqueue 예시
    for (int i = 1; i <= 10; i++) {
        queueList.enqueue(i);
    }
    queueList.printQueues();

    // Dequeue 예시
    for (int i = 0; i < 5; i++) {
        cout << "Dequeued: " << queueList.dequeue() << endl;
    }
    queueList.printQueues();

    return 0;
}
