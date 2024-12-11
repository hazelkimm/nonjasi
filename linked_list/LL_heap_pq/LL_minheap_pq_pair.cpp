#include <iostream>
#include <vector>
#include <utility>
using namespace std;

/*
 * PriorityQueue 클래스: Pair 타입의 요소를 저장하며 최소 힙(Min-Heap) 구조를 유지.
 * Node 클래스: PriorityQueue를 포함하며, 다음 노드를 가리키는 포인터를 포함.
 * LinkedList 클래스: Node로 구성된 단일 연결 리스트.
 *
 * 주요 기능:
 * - PriorityQueue: Pair 삽입, 삭제, 출력, 힙 속성 유지.
 * - Node: PriorityQueue와 다음 노드 포인터 포함.
 * - LinkedList: Node를 관리하며 힙 데이터 출력 및 조작 지원.
 */

// Pair typedef
typedef pair<int, int> Pair;

// PriorityQueue 클래스 정의 (Pair를 위한 Min-Heap)
class PriorityQueue {
private:
    vector<Pair> elements; // 내부 벡터: Pair 요소를 저장

    // 삽입 시 최소 힙 속성을 유지하도록 버블 업 연산 수행
    void bubbleUp(int index) {
        while (index > 0 && elements[index] < elements[(index - 1) / 2]) {
            swap(elements[index], elements[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    // 삭제 시 최소 힙 속성을 유지하도록 버블 다운 연산 수행
    void bubbleDown(int index) {
        int size = elements.size();
        while (index * 2 + 1 < size) {
            int child = index * 2 + 1;
            if (child + 1 < size && elements[child + 1] < elements[child]) {
                child++;
            }
            if (elements[index] <= elements[child]) {
                break;
            }
            swap(elements[index], elements[child]);
            index = child;
        }
    }

    // 힙 정렬 과정에서 사용되는 min-heapify 연산
    void minHeapify(int size, int index) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && elements[left] < elements[smallest]) {
            smallest = left;
        }
        if (right < size && elements[right] < elements[smallest]) {
            smallest = right;
        }

        if (smallest != index) {
            swap(elements[index], elements[smallest]);
            minHeapify(size, smallest);
        }
    }

public:
    // PriorityQueue에 Pair 삽입
    void insert(Pair value) {
        elements.push_back(value);
        bubbleUp(elements.size() - 1);
    }

    // PriorityQueue에서 최소값(Pair)을 제거하고 반환
    Pair pop() {
        if (elements.empty()) {
            throw runtime_error("우선순위 큐가 비어 있습니다!");
        }
        Pair minValue = elements[0];
        elements[0] = elements.back();
        elements.pop_back();
        bubbleDown(0);
        return minValue;
    }

    // PriorityQueue를 내림차순으로 정렬
    void sort() {
        int originalSize = elements.size();

        // 최소 힙 생성
        for (int i = elements.size() / 2 - 1; i >= 0; i--) {
            minHeapify(elements.size(), i);
        }

        // 힙 요소를 하나씩 정렬
        for (int i = elements.size() - 1; i > 0; i--) {
            swap(elements[0], elements[i]);  // 최소값을 끝으로 이동
            minHeapify(i, 0);               // 힙 속성 복구
        }

        // 원래 크기로 복원
        elements.resize(originalSize);
    }

    // PriorityQueue의 모든 요소를 출력
    void print() const {
        for (Pair value : elements) {
            cout << "(" << value.first << ", " << value.second << ") ";
        }
        cout << endl;
    }

    // PriorityQueue가 비었는지 확인
    bool isEmpty() const {
        return elements.empty();
    }
};

// Node 클래스 정의
class Node {
public:
    PriorityQueue heap; // 이 노드의 PriorityQueue
    Node* next;         // 다음 노드를 가리키는 포인터

    // Node 생성자: 빈 PriorityQueue와 다음 노드 포인터를 초기화
    Node() : next(nullptr) {}
};

// LinkedList 클래스 정의
class LinkedList {
private:
    Node* head; // 리스트의 첫 번째 노드

public:
    // LinkedList 생성자: head를 nullptr로 초기화
    LinkedList() : head(nullptr) {}

    // 새로운 노드를 리스트의 맨 앞에 추가
    void addNode() {
        Node* newNode = new Node();
        newNode->next = head;
        head = newNode;
    }

    // 리스트의 첫 번째 노드 반환
    Node* getHead() const {
        return head;
    }

    // 리스트의 각 노드에 포함된 PriorityQueue를 출력
    void printHeaps() const {
        Node* current = head;
        int index = 0;
        while (current != nullptr) {
            cout << "노드 " << index++ << "의 힙: ";
            current->heap.print();
            current = current->next;
        }
    }

    // LinkedList 소멸자: 모든 노드 삭제
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

// 메인 함수: 구현 테스트
int main() {
    cout << "Pair를 사용하는 최소 힙 기반 연결 리스트:\n";

    LinkedList list;
    list.addNode();
    list.addNode();

    Node* head = list.getHead();

    // 첫 번째 노드의 힙에 Pair 삽입
    head->heap.insert({10, 20});
    head->heap.insert({5, 15});
    head->heap.insert({20, 10});

    // 두 번째 노드의 힙에 Pair 삽입
    head->next->heap.insert({15, 30});
    head->next->heap.insert({25, 25});
    head->next->heap.insert({30, 5});

    cout << "삽입 후 연결 리스트의 힙:\n";
    list.printHeaps();

    // 첫 번째 힙 정렬
    cout << "\n첫 번째 힙 정렬 후 (오름차순):\n";
    head->heap.sort();
    head->heap.print();

    return 0;
}