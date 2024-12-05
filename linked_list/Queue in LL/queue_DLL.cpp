#include <iostream>
#include <cstdlib>

#define QUEUE_CAPACITY 3  // 각 큐의 최대 용량

using namespace std;

typedef int Element;  // 큐에 저장되는 데이터 타입

// 큐의 각 노드를 나타내는 구조체
struct QueueNode {
    Element data;        // 노드에 저장된 데이터
    QueueNode* next;     // 다음 노드를 가리키는 포인터

    // 생성자
    QueueNode(Element value) : data(value), next(nullptr) {}
};

// 큐 구조체
struct Queue {
    QueueNode* front;  // 큐의 앞쪽 (디큐 위치)
    QueueNode* rear;   // 큐의 뒤쪽 (엔큐 위치)
    int size;          // 현재 큐의 크기

    // 생성자
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    // 큐가 비었는지 확인
    bool isEmpty() const {
        return front == nullptr;
    }

    // 큐에 요소 추가 (엔큐)
    void enqueue(Element value) {
        QueueNode* newNode = new QueueNode(value);
        if (rear == nullptr) {
            // 큐가 비어있는 경우 front와 rear를 새 노드로 설정
            front = rear = newNode;
        } else {
            // rear 뒤에 새 노드를 추가하고 rear 갱신
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    // 큐에서 요소 제거 및 반환 (디큐)
    Element dequeue() {
        if (isEmpty()) {
            cerr << "Queue is empty" << endl;
            exit(EXIT_FAILURE);
        }
        QueueNode* temp = front;
        Element value = temp->data;
        front = front->next;
        if (front == nullptr) {
            // 큐가 비어 있으면 rear도 nullptr로 설정
            rear = nullptr;
        }
        delete temp;  // 메모리 해제
        size--;
        return value;
    }

    // 큐의 앞쪽 요소 반환 (제거하지 않음)
    Element peek() const {
        if (isEmpty()) {
            cerr << "Queue is empty" << endl;
            exit(EXIT_FAILURE);
        }
        return front->data;
    }
};

// 양방향 링크드 리스트 노드 구조체 (각 노드가 큐를 포함)
struct LinkedListNode {
    Queue* queue;              // 큐를 포함
    LinkedListNode* next;      // 다음 노드를 가리키는 포인터
    LinkedListNode* prev;      // 이전 노드를 가리키는 포인터

    // 생성자
    LinkedListNode() : queue(new Queue()), next(nullptr), prev(nullptr) {}
};

// 데이터 구조 클래스
class DoubleLinkedList {
private:
    LinkedListNode* head;  // 첫 번째 노드
    LinkedListNode* tail;  // 마지막 노드

public:
    // 생성자
    DoubleLinkedList() {
        head = new LinkedListNode();  // 초기 노드 생성
        tail = head;  // 초기에는 head와 tail이 동일
    }

    // 데이터 추가
    void push(Element value) {
        if (tail->queue->size >= QUEUE_CAPACITY) {
            // 현재 큐가 가득 찬 경우, 새 노드 생성
            LinkedListNode* newNode = new LinkedListNode();
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
            cout << "Creating new queue for value " << value << "." << endl;
        }
        tail->queue->enqueue(value);
        cout << "Pushed value " << value << " to queue. Queue size is now " << tail->queue->size << "." << endl;
    }

    // 데이터 제거
    Element pop() {
        if (head->queue->isEmpty()) {
            cerr << "List is empty" << endl;
            exit(EXIT_FAILURE);
        }

        Element value = head->queue->dequeue();
        cout << "Popped value: " << value << endl;

        if (head->queue->isEmpty() && head->next != nullptr) {
            // 첫 번째 큐가 비었으면 노드를 제거
            LinkedListNode* temp = head;
            head = head->next;
            head->prev = nullptr;
            delete temp->queue;
            delete temp;
            cout << "Removed an empty linked list node." << endl;
        }
        return value;
    }

    // 데이터 제거 및 재분배
    Element popAndRedistribute() {
        if (head->queue->isEmpty()) {
            cerr << "List is empty" << endl;
            exit(EXIT_FAILURE);
        }

        Element value = head->queue->dequeue();
        cout << "Popped value: " << value << endl;

        LinkedListNode* current = head;
        while (current->queue->size < QUEUE_CAPACITY && current->next != nullptr) {
            LinkedListNode* nextNode = current->next;
            if (!nextNode->queue->isEmpty()) {
                Element redistributedValue = nextNode->queue->dequeue();
                current->queue->enqueue(redistributedValue);
                cout << "Redistributed value " << redistributedValue << " to maintain size." << endl;
            }
            if (nextNode->queue->isEmpty()) {
                // 다음 큐가 비어있으면 노드를 제거
                current->next = nextNode->next;
                if (nextNode->next != nullptr) {
                    nextNode->next->prev = current;
                }
                if (nextNode == tail) {
                    tail = current;
                }
                delete nextNode->queue;
                delete nextNode;
                cout << "Removed an empty linked list node." << endl;
            }
        }
        return value;
    }

    // 데이터 구조 출력
    void printStructure() const {
        const LinkedListNode* current = head;
        int queueNum = 1;
        while (current != nullptr) {
            cout << "Queue " << queueNum++ << ": ";
            QueueNode* node = current->queue->front;
            while (node != nullptr) {
                cout << node->data << " ";
                node = node->next;
            }
            cout << endl;
            current = current->next;
        }
    }

    // 데이터 구조의 총 크기 계산
    int totalSize() const {
        const LinkedListNode* current = head;
        int total = 0;
        while (current != nullptr) {
            total += current->queue->size;
            current = current->next;
        }
        return total;
    }

    // 데이터 구조의 깊이 계산
    int depth() const {
        const LinkedListNode* current = head;
        int depth = 0;
        while (current != nullptr) {
            depth++;
            current = current->next;
        }
        return depth;
    }

    // 메모리 해제
    ~DoubleLinkedList() {
        while (head != nullptr) {
            LinkedListNode* temp = head;
            head = head->next;
            delete temp->queue;
            delete temp;
        }
    }
};

// 테스트 코드
int main() {
    DoubleLinkedList dll;

    // 요소 추가
    cout << "Pushing elements to the data structure..." << endl;
    dll.push(10);
    dll.push(20);
    dll.push(30);  // 첫 번째 큐가 가득 참
    dll.push(40);  // 두 번째 큐 생성
    dll.push(50);

    // 데이터 구조 출력
    cout << "Initial data structure:" << endl;
    dll.printStructure();

    // 총 크기와 깊이 확인
    cout << "Total size: " << dll.totalSize() << endl;
    cout << "Depth (number of queues): " << dll.depth() << endl;

    // 데이터 제거 및 출력
    cout << "Popping value:" << endl;
    dll.pop();
    cout << "Data structure after popping:" << endl;
    dll.printStructure();

    // 재분배를 포함한 데이터 제거
    cout << "Popping value with redistribution:" << endl;
    dll.popAndRedistribute();
    cout << "Data structure after redistribution:" << endl;
    dll.printStructure();

    return 0;
}
