#include <iostream>
#include <vector>
using namespace std;

/*
 * Node 구조체: 연결 리스트의 각 노드를 정의.
 * MaxHeap 클래스: 연결 리스트를 기반으로 한 최대 힙 구현.
 *
 * 주요 기능:
 * - Node: 정수 값을 저장하며, 다음 노드 포인터를 포함.
 * - MaxHeap:
 *   1. insert: 새로운 값을 최대 힙에 삽입.
 *   2. pop: 최대값 제거 및 반환.
 *   3. print: 현재 힙 상태 출력.
 *   4. sort: 힙 요소를 내림차순으로 정렬 (추가 구현).
 */

// Node 구조체 정의
struct Node {
    int val;       // 노드 값
    Node* next;    // 다음 노드 포인터

    // 생성자
    Node(int v) : val(v), next(nullptr) {}
};

// MaxHeap 클래스 정의
class MaxHeap {
private:
    Node* head; // 연결 리스트의 시작 노드

    // 새로운 노드를 생성하는 헬퍼 함수
    Node* createNode(int value) {
        return new Node(value);
    }

    // 연결 리스트를 배열로 변환 (정렬에 필요)
    vector<int> toArray() const {
        vector<int> array;
        Node* current = head;
        while (current) {
            array.push_back(current->val);
            current = current->next;
        }
        return array;
    }

    // 배열을 연결 리스트로 변환 (정렬 후 재구성)
    void fromArray(const vector<int>& array) {
        clear(); // 기존 리스트 제거
        for (int value : array) {
            insert(value);
        }
    }

    // 연결 리스트 초기화 (메모리 해제)
    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

public:
    // 생성자: head 초기화
    MaxHeap() : head(nullptr) {}

    // 최대 힙에 값 삽입
    void insert(int value) {
        Node* newNode = createNode(value);
        if (!head || newNode->val > head->val) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next && current->next->val >= newNode->val) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    // 최대값 제거 및 반환
    int pop() {
        if (!head) {
            throw runtime_error("Max-Heap is empty!");
        }
        int maxValue = head->val;
        Node* temp = head;
        head = head->next;
        delete temp;
        return maxValue;
    }

    // 힙 출력
    void print() const {
        Node* current = head;
        while (current) {
            cout << current->val << " ";
            current = current->next;
        }
        cout << endl;
    }

    // 힙 정렬 (내림차순)
    void sort() {
        vector<int> array = toArray(); // 힙을 배열로 변환
        // 배열을 내림차순 정렬
        std::sort(array.begin(), array.end(), greater<int>());
        // 정렬된 배열을 연결 리스트로 변환
        fromArray(array);
    }

    // 소멸자: 메모리 해제
    ~MaxHeap() {
        clear();
    }
};

// 메인 함수: MaxHeap 테스트
int main() {
    cout << "\nMax-Heap with Linked List Implementation:\n";

    MaxHeap heap;

    // 삽입 테스트
    heap.insert(10);
    heap.insert(20);
    heap.insert(5);
    heap.insert(15);

    // 힙 출력
    cout << "Max-Heap after insertions: ";
    heap.print();

    // 정렬 테스트
    cout << "\nSorting Max-Heap (Descending Order):\n";
    heap.sort();
    heap.print();

    // 최대값 제거 테스트
    cout << "\nPopping maximum: " << heap.pop() << endl;
    cout << "Max-Heap after popping: ";
    heap.print();

    return 0;
}