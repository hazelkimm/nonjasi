#include <iostream>
#include <cstdlib>

#define QUEUE_CAPACITY 3  // 각 큐의 최대 용량

using namespace std;

typedef int Element;  // 큐에 저장될 데이터 타입 정의

// 큐의 각 노드를 나타내는 구조체
struct QueueNode {
    Element data;          // 노드에 저장된 데이터
    QueueNode* next;       // 다음 노드를 가리키는 포인터
};

// 큐를 나타내는 구조체
struct Queue {
    QueueNode* front;  // 큐의 앞쪽 (디큐 위치)
    QueueNode* rear;   // 큐의 뒤쪽 (엔큐 위치)
    int size;          // 현재 큐의 크기

    // 큐를 초기화하는 생성자
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    // 큐에 데이터를 추가하는 함수 (엔큐)
    void enqueue(Element value) {
        QueueNode* newNode = new QueueNode{value, nullptr};  // 새 노드 생성
        if (rear == nullptr) {
            // 큐가 비어있는 경우, front와 rear를 새 노드로 설정
            front = rear = newNode;
        } else {
            // 큐에 요소가 있는 경우, rear 뒤에 새 노드를 추가하고 rear 갱신
            rear->next = newNode;
            rear = newNode;
        }
        size++;  // 큐 크기 증가
    }

    // 큐에서 데이터를 제거하고 반환하는 함수 (디큐)
    Element dequeue() {
        if (front == nullptr) {
            // 큐가 비어있는 경우 오류 처리
            cerr << "Queue is empty" << endl;
            exit(EXIT_FAILURE);
        }
        QueueNode* temp = front;   // 제거할 노드를 임시 저장
        Element value = temp->data;  // 데이터를 저장
        front = front->next;  // front를 다음 노드로 이동
        if (front == nullptr) {
            // 큐가 비어있다면 rear도 nullptr로 설정
            rear = nullptr;
        }
        delete temp;  // 제거된 노드의 메모리 해제
        size--;  // 큐 크기 감소
        return value;  // 제거된 데이터를 반환
    }

    // 큐의 앞쪽 데이터를 반환 (제거하지 않음)
    Element peek() {
        if (front == nullptr) {
            // 큐가 비어있는 경우 오류 처리
            cerr << "Queue is empty" << endl;
            exit(EXIT_FAILURE);
        }
        return front->data;  // front에 있는 데이터를 반환
    }

    // 큐가 비어있는지 확인하는 함수
    bool isEmpty() {
        return front == nullptr;
    }
};

// 링크드 리스트 노드를 나타내는 구조체 (각 노드는 큐를 포함)
struct LinkedListNode {
    Queue* queue;          // 큐를 포함
    LinkedListNode* next;  // 다음 링크드 리스트 노드를 가리키는 포인터

    // 생성자를 통해 노드 초기화
    LinkedListNode() : queue(new Queue()), next(nullptr) {}
};

// 데이터를 구조에 추가하는 함수
// 마지막 큐가 가득 차 있으면 새 링크드 리스트 노드를 생성하여 추가
void push(LinkedListNode*& head, Element value) {
    LinkedListNode* current = head;

    // 링크드 리스트의 마지막 노드로 이동
    while (current->next != nullptr) {
        current = current->next;
    }

    // 현재 큐가 가득 찬 경우, 새 링크드 리스트 노드를 생성
    if (current->queue->size >= QUEUE_CAPACITY) {
        LinkedListNode* newNode = new LinkedListNode();
        current->next = newNode;
        current = newNode;
        cout << "Creating new queue for value " << value << "." << endl;
    }

    // 현재 큐에 데이터를 추가
    current->queue->enqueue(value);
    cout << "Pushed value " << value << " to queue. Queue size is now " << current->queue->size << "." << endl;
}

// 데이터를 구조에서 제거하고 반환하는 함수
// 첫 번째 큐가 비게 되면 해당 링크드 리스트 노드를 제거
Element pop(LinkedListNode*& head) {
    if (head == nullptr) {
        // 링크드 리스트가 비어있는 경우 오류 처리
        cerr << "List is empty" << endl;
        exit(EXIT_FAILURE);
    }

    // 첫 번째 큐에서 데이터를 제거
    Element value = head->queue->dequeue();

    // 첫 번째 큐가 비어있다면 링크드 리스트 노드 제거
    if (head->queue->isEmpty()) {
        LinkedListNode* temp = head;
        head = head->next;
        delete temp->queue;
        delete temp;
    }

    return value;  // 제거된 데이터를 반환
}

// 데이터를 제거하면서 첫 번째 큐를 유지하도록 재분배
Element popAndRedistribute(LinkedListNode*& head) {
    if (head == nullptr) {
        cerr << "List is empty" << endl;
        exit(EXIT_FAILURE);
    }

    // 첫 번째 큐에서 데이터를 제거
    Element value = head->queue->dequeue();

    // 첫 번째 큐가 크기가 부족한 경우 다음 큐에서 데이터를 가져옴
    while (head->queue->size < QUEUE_CAPACITY && head->next != nullptr) {
        LinkedListNode* nextNode = head->next;
        if (!nextNode->queue->isEmpty()) {
            // 다음 큐에서 데이터를 가져와 첫 번째 큐에 추가
            head->queue->enqueue(nextNode->queue->dequeue());
            cout << "Redistributed an element from the next queue to maintain size." << endl;
        }

        // 다음 큐가 비어있다면 링크드 리스트 노드를 제거
        if (nextNode->queue->isEmpty()) {
            head->next = nextNode->next;
            delete nextNode->queue;
            delete nextNode;
            cout << "Removed an empty linked list node." << endl;
        }
    }

    return value;  // 제거된 데이터를 반환
}

// 데이터 구조를 출력하는 함수
void printDataStructure(LinkedListNode* head) {
    int queueNumber = 1;
    while (head != nullptr) {
        cout << "Queue " << queueNumber++ << ": ";
        QueueNode* current = head->queue->front;
        // 각 큐의 데이터를 출력
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
        head = head->next;  // 다음 링크드 리스트 노드로 이동
    }
}

// 데이터 구조를 삭제하고 메모리를 해제하는 함수
void destroyDataStructure(LinkedListNode*& head) {
    while (head != nullptr) {
        LinkedListNode* temp = head;
        while (!temp->queue->isEmpty()) {
            temp->queue->dequeue();
        }
        delete temp->queue;
        head = head->next;
        delete temp;
    }
}

// 테스트 함수
int main() {
    LinkedListNode* list = new LinkedListNode();  // 초기 링크드 리스트 노드 생성

    // 데이터 추가
    cout << "Pushing elements to the data structure..." << endl;
    push(list, 10);
    push(list, 20);
    push(list, 30);  // 첫 번째 큐가 가득 참
    push(list, 40);  // 두 번째 큐 생성
    push(list, 50);

    // 데이터 구조 출력
    cout << "Initial data structure:" << endl;
    printDataStructure(list);

    // 데이터 제거 및 출력
    cout << "Popping value: " << pop(list) << endl;
    cout << "Data structure after popping:" << endl;
    printDataStructure(list);

    // 재분배를 포함한 데이터 제거
    cout << "Popping value with redistribution: " << popAndRedistribute(list) << endl;
    cout << "Data structure after redistribution:" << endl;
    printDataStructure(list);

    // 메모리 해제
    destroyDataStructure(list);

    return 0;
}
