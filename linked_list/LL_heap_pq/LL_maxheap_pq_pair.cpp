#include <iostream>
#include <vector>
#include <utility>
using namespace std;

// Pair typedef: 두 정수의 쌍 (x, y)을 저장하는 타입 정의
typedef pair<int, int> Pair;

// Priority Queue class for pairs
// PriorityQueue 클래스는 Pair 타입의 요소를 저장하며 최대 힙(Max-Heap) 구조를 유지
class PriorityQueue {
private:
    vector<Pair> elements;  // Pair 요소를 저장하는 내부 벡터

    // void bubbleUp(int index)
    // 새로운 요소를 삽입한 후 최대 힙 속성을 유지하기 위한 헬퍼 함수
    // index 위치의 요소를 부모 노드와 비교하며 위로 이동
    void bubbleUp(int index) {
        while (index > 0 && elements[index] > elements[(index - 1) / 2]) {
            swap(elements[index], elements[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    // void bubbleDown(int index)
    // 최대 힙에서 루트 요소를 제거한 후 힙 속성을 복구하기 위한 헬퍼 함수
    // index 위치의 요소를 자식 노드와 비교하며 아래로 이동
    void bubbleDown(int index) {
        int size = elements.size();
        while (index * 2 + 1 < size) {
            int child = index * 2 + 1;
            if (child + 1 < size && elements[child + 1] > elements[child]) {
                child++;
            }
            if (elements[index] >= elements[child]) {
                break;
            }
            swap(elements[index], elements[child]);
            index = child;
        }
    }

    // void maxHeapify(int size, int index)
    // 주어진 노드와 자식 노드들 간의 비교를 통해 최대 힙 속성을 복구
    // 정렬 과정에서 사용됨
    void maxHeapify(int size, int index) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && elements[left] > elements[largest]) {
            largest = left;
        }
        if (right < size && elements[right] > elements[largest]) {
            largest = right;
        }

        if (largest != index) {
            swap(elements[index], elements[largest]);
            maxHeapify(size, largest);
        }
    }

public:
    // void insert(Pair value)
    // PriorityQueue에 새로운 Pair 요소를 추가
    // bubbleUp을 사용하여 힙 속성을 유지
    void insert(Pair value) {
        elements.push_back(value);
        bubbleUp(elements.size() - 1);
    }

    // Pair pop()
    // PriorityQueue에서 최대값(루트)을 제거하고 반환
    // bubbleDown을 사용하여 힙 속성을 유지
    Pair pop() {
        if (elements.empty()) {
            throw runtime_error("Priority queue is empty!");
        }
        Pair maxValue = elements[0];
        elements[0] = elements.back();
        elements.pop_back();
        bubbleDown(0);
        return maxValue;
    }

    // void print() const
    // PriorityQueue의 모든 요소를 출력
    void print() const {
        for (Pair value : elements) {
            cout << "(" << value.first << ", " << value.second << ") ";
        }
        cout << endl;
    }

    // void sort()
    // PriorityQueue의 요소를 정렬
    // maxHeapify를 활용하여 힙 정렬을 수행
    void sort() {
        int originalSize = elements.size();

        // Build max heap
        for (int i = elements.size() / 2 - 1; i >= 0; i--) {
            maxHeapify(elements.size(), i);
        }

        // Extract elements from heap
        for (int i = elements.size() - 1; i > 0; i--) {
            swap(elements[0], elements[i]);  // Move max to the end
            maxHeapify(i, 0);  // Restore heap property for the reduced heap
        }

        // Restore the original size
        elements.resize(originalSize);
    }

    // bool isEmpty() const
    // PriorityQueue가 비었는지 확인
    bool isEmpty() const {
        return elements.empty();
    }
};

// Node class for the linked list
// Node는 PriorityQueue를 포함하며, 다음 노드를 가리키는 포인터를 가짐
class Node {
public:
    PriorityQueue heap;  // 이 노드의 PriorityQueue
    Node* next;          // 다음 노드를 가리키는 포인터

    // Node 생성자: 빈 PriorityQueue와 nullptr로 초기화
    Node() : next(nullptr) {}
};

// Linked list class
// Node 객체들로 구성된 단일 연결 리스트를 관리
class LinkedList {
private:
    Node* head;  // 리스트의 첫 번째 노드

public:
    // LinkedList 생성자: head를 nullptr로 초기화
    LinkedList() : head(nullptr) {}

    // void addNode()
    // 새로운 노드를 리스트의 앞부분에 추가
    void addNode() {
        Node* newNode = new Node();
        newNode->next = head;
        head = newNode;
    }

    // Node* getHead() const
    // 리스트의 첫 번째 노드를 반환
    Node* getHead() const {
        return head;
    }

    // void printHeaps() const
    // 리스트의 각 노드에 포함된 PriorityQueue를 출력
    void printHeaps() const {
        Node* current = head;
        int index = 0;
        while (current != nullptr) {
            cout << "Heap in Node " << index++ << ": ";
            current->heap.print();
            current = current->next;
        }
    }

    // LinkedList 소멸자: 모든 노드를 삭제하여 메모리 해제
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

// Main function to test the implementation
int main() {
    cout << "\nPair Linked List with Heaps:\n";

    LinkedList list;
    list.addNode();
    list.addNode();

    Node* head = list.getHead();

    // Add elements to the first node's heap
    head->heap.insert({10, 20});
    head->heap.insert({5, 15});
    head->heap.insert({20, 10});

    // Add elements to the second node's heap
    head->next->heap.insert({15, 30});
    head->next->heap.insert({25, 25});
    head->next->heap.insert({30, 5});

    cout << "Heaps in the linked list after insertion:\n";
    list.printHeaps();

    // Sort the heaps in the first node
    cout << "\nSorting the first heap:\n";
    head->heap.sort();
    head->heap.print();

    return 0;
}