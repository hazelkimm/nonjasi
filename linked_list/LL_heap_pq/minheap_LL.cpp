#include <iostream>
using namespace std;

// Node 구조체 정의: 연결 리스트의 각 노드를 나타냄
struct Node {
    int val;         // 노드의 값
    Node* next;      // 다음 노드를 가리키는 포인터

    // 생성자: 값을 초기화하고, next 포인터를 nullptr로 설정
    Node(int v) : val(v), next(nullptr) {}
};

// Min-Heap 클래스 정의 (연결 리스트로 구현)
class MinHeap {
private:
    Node* head;  // Min-Heap의 시작 노드

    // 새로운 노드를 생성하는 헬퍼 함수
    Node* createNode(int value) {
        return new Node(value);
    }

public:
    // 생성자: 빈 Min-Heap 생성
    MinHeap() : head(nullptr) {}

    // Min-Heap에 값 삽입
    void insert(int value) {
        Node* newNode = createNode(value);
        // 새 값이 가장 작으면 헤드에 삽입
        if (!head || newNode->val < head->val) {
            newNode->next = head;
            head = newNode;
        } else {
            // 적절한 위치를 찾아 삽입
            Node* current = head;
            while (current->next && current->next->val <= newNode->val) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    // Min-Heap에서 최소값 제거 및 반환
    int pop() {
        if (!head) {
            throw runtime_error("Min-Heap is empty!");
        }
        int minValue = head->val;
        Node* temp = head;
        head = head->next;
        delete temp;  // 메모리 해제
        return minValue;
    }

    // Min-Heap 출력
    void print() const {
        Node* current = head;
        while (current) {
            cout << current->val << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Min-Heap 정렬
    void sort() const {
        // Min-Heap의 요소를 배열에 저장
        int size = 0;
        Node* current = head;
        while (current) {
            size++;
            current = current->next;
        }

        // 동적 배열 생성
        int* arr = new int[size];
        current = head;
        for (int i = 0; i < size; i++) {
            arr[i] = current->val;
            current = current->next;
        }

        // 배열을 오름차순으로 정렬
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }

        // 정렬 결과 출력
        cout << "Sorted Min-Heap: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;

        // 동적 배열 메모리 해제
        delete[] arr;
    }

    // 소멸자: 연결 리스트의 모든 노드 메모리 해제
    ~MinHeap() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Main 함수: Min-Heap 테스트
int main() {
    cout << "Min-Heap with Linked List Implementation:\n";

    MinHeap heap;

    // Min-Heap에 값 삽입
    heap.insert(10);
    heap.insert(20);
    heap.insert(5);
    heap.insert(15);

    // Min-Heap 상태 출력
    cout << "Min-Heap after insertions: ";
    heap.print();

    // Min-Heap에서 최소값 제거
    cout << "Popping minimum: " << heap.pop() << endl;
    cout << "Min-Heap after popping: ";
    heap.print();

    // Min-Heap 정렬
    cout << "Sorting Min-Heap:\n";
    heap.sort();

    return 0;
}