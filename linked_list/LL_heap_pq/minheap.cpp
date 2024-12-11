#include <iostream>
#include <vector>
using namespace std;

// Min-Heap 클래스 정의
class MinHeap {
private:
    vector<int> elements; // Min-Heap의 요소를 저장하는 벡터

    // 삽입 후 Min-Heap 속성을 유지하기 위해 부모와 비교하며 교환
    void bubbleUp(int index) {
        while (index > 0 && elements[index] < elements[(index - 1) / 2]) {
            swap(elements[index], elements[(index - 1) / 2]);
            index = (index - 1) / 2; // 부모 노드로 이동
        }
    }

    // 제거 후 Min-Heap 속성을 유지하기 위해 자식과 비교하며 교환
    void bubbleDown(int index) {
        int size = elements.size();
        while (index * 2 + 1 < size) { // 왼쪽 자식이 있는 동안 반복
            int child = index * 2 + 1; // 왼쪽 자식
            if (child + 1 < size && elements[child + 1] < elements[child]) {
                child++; // 오른쪽 자식이 더 작으면 선택
            }
            if (elements[index] <= elements[child]) {
                break; // 현재 노드가 자식 노드보다 작거나 같으면 종료
            }
            swap(elements[index], elements[child]);
            index = child; // 자식 노드로 이동
        }
    }

    // 주어진 인덱스를 루트로 하는 서브트리를 Min-Heap으로 복구
    void minHeapify(int size, int index) {
        int smallest = index;
        int left = 2 * index + 1;  // 왼쪽 자식 인덱스
        int right = 2 * index + 2; // 오른쪽 자식 인덱스

        // 왼쪽 자식과 비교
        if (left < size && elements[left] < elements[smallest]) {
            smallest = left;
        }
        // 오른쪽 자식과 비교
        if (right < size && elements[right] < elements[smallest]) {
            smallest = right;
        }
        // 가장 작은 값을 가진 노드로 교환 후 재귀 호출
        if (smallest != index) {
            swap(elements[index], elements[smallest]);
            minHeapify(size, smallest);
        }
    }

public:
    // Min-Heap에 값을 삽입
    void insert(int value) {
        elements.push_back(value);
        bubbleUp(elements.size() - 1); // 삽입 후 Min-Heap 속성 복구
    }

    // Min-Heap에서 최소값 제거 및 반환
    int pop() {
        if (elements.empty()) {
            throw runtime_error("Min-Heap is empty!");
        }
        int minValue = elements[0];        // 루트 요소(최소값) 저장
        elements[0] = elements.back();     // 마지막 요소를 루트로 이동
        elements.pop_back();               // 마지막 요소 제거
        bubbleDown(0);                     // Min-Heap 속성 복구
        return minValue;
    }

    // Min-Heap 출력
    void print() const {
        for (int value : elements) {
            cout << value << " ";
        }
        cout << endl;
    }

    // Min-Heap을 정렬 (힙 정렬)
    void sort() {
        int originalSize = elements.size();

        // Min-Heapify: 힙 속성 복구
        for (int i = originalSize / 2 - 1; i >= 0; i--) {
            minHeapify(originalSize, i);
        }

        // 힙 정렬: 루트(최소값)를 끝으로 보내고 크기를 줄이며 정렬
        for (int i = originalSize - 1; i > 0; i--) {
            swap(elements[0], elements[i]); // 루트와 마지막 요소 교환
            minHeapify(i, 0);              // 크기를 줄이며 Min-Heap 속성 유지
        }

        // 정렬 결과 출력
        cout << "Sorted Min-Heap: ";
        for (int value : elements) {
            cout << value << " ";
        }
        cout << endl;

        // Min-Heap 복원을 위해 요소를 다시 삽입
        for (int i = originalSize - 1; i >= 0; i--) {
            elements.push_back(elements[i]);
        }
    }
};

// Main 함수: Min-Heap 테스트
int main() {
    cout << "Min-Heap Implementation:\n";

    MinHeap heap;

    heap.insert(10);
    heap.insert(20);
    heap.insert(5);
    heap.insert(15);

    cout << "Min-Heap after insertions: ";
    heap.print();

    cout << "Popping minimum: " << heap.pop() << endl;
    cout << "Min-Heap after popping: ";
    heap.print();

    cout << "\nSorting the heap:\n";
    heap.sort();

    return 0;
}