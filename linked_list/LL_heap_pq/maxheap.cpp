#include <iostream>
#include <vector>
using namespace std;

// Max-Heap Class
class MaxHeap {
private:
    vector<int> elements;  // 내부적으로 데이터를 저장하는 벡터

    // Bubble up to maintain max-heap property
    void bubbleUp(int index) {
        // 삽입 후 부모와 비교하여 위로 이동, 힙 속성을 유지
        while (index > 0 && elements[index] > elements[(index - 1) / 2]) {
            swap(elements[index], elements[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    // Bubble down to maintain max-heap property
    void bubbleDown(int index) {
        // 루트에서 시작하여 자식과 비교하며 아래로 이동, 힙 속성을 유지
        int size = elements.size();
        while (index * 2 + 1 < size) {
            int child = index * 2 + 1;
            if (child + 1 < size && elements[child + 1] > elements[child]) {
                child++;  // 오른쪽 자식이 더 크면 선택
            }
            if (elements[index] >= elements[child]) {
                break;  // 현재 값이 자식보다 크거나 같으면 종료
            }
            swap(elements[index], elements[child]);
            index = child;
        }
    }

    // Max-Heapify: 특정 인덱스에서 시작하여 서브트리를 최대 힙으로 복구
    void maxHeapify(int size, int index) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && elements[left] > elements[largest]) {
            largest = left;  // 왼쪽 자식이 더 크면 largest 갱신
        }
        if (right < size && elements[right] > elements[largest]) {
            largest = right;  // 오른쪽 자식이 더 크면 largest 갱신
        }

        if (largest != index) {
            swap(elements[index], elements[largest]);
            maxHeapify(size, largest);  // 서브트리에서 재귀 호출
        }
    }

public:
    // Insert a value into the max-heap
    void insert(int value) {
        // 새 값을 힙에 추가하고 bubble up 호출
        elements.push_back(value);
        bubbleUp(elements.size() - 1);
    }

    // Remove and return the maximum element
    int pop() {
        // 힙의 최대값(루트)을 제거하고 반환
        if (elements.empty()) {
            throw runtime_error("Max-Heap is empty!");
        }
        int maxValue = elements[0];
        elements[0] = elements.back();  // 마지막 값을 루트로 이동
        elements.pop_back();
        bubbleDown(0);  // 루트부터 bubble down 수행
        return maxValue;
    }

    // Sort the max-heap (heap sort)
    void sort() {
        // 힙을 정렬하여 내림차순으로 정렬된 결과 생성
        int originalSize = elements.size();

        // Max-Heapify 호출하여 힙 복구
        for (int i = elements.size() / 2 - 1; i >= 0; i--) {
            maxHeapify(elements.size(), i);
        }

        // 최대값을 끝으로 이동하며 크기 축소
        for (int i = elements.size() - 1; i > 0; i--) {
            swap(elements[0], elements[i]);  // 루트와 끝 요소 교환
            maxHeapify(i, 0);               // 축소된 힙에서 max-heapify 호출
        }

        // 원래 크기로 복원
        elements.resize(originalSize);
    }

    // Print the max-heap
    void print() const {
        // 현재 힙의 모든 요소 출력
        for (int value : elements) {
            cout << value << " ";
        }
        cout << endl;
    }
};

// Main function to test the Max-Heap
int main() {
    cout << "\nMax-Heap Implementation:\n";

    MaxHeap heap;

    // 힙에 값 삽입
    heap.insert(10);
    heap.insert(20);
    heap.insert(5);
    heap.insert(15);

    // 삽입 후 힙 출력
    cout << "Max-Heap after insertions: ";
    heap.print();

    // 최대값 제거 및 출력
    cout << "Popping maximum: " << heap.pop() << endl;
    cout << "Max-Heap after popping: ";
    heap.print();

    // 힙 정렬 수행
    cout << "\nSorting the Max-Heap: ";
    heap.sort();
    heap.print();

    return 0;
}