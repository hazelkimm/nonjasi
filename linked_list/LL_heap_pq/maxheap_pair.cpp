#include <iostream>
#include <vector>
#include <utility> // std::pair를 사용하기 위한 헤더
using namespace std;

// Max-Heap 클래스 정의
class MaxHeap {
private:
    vector<pair<int, int>> elements; // 내부 데이터를 저장하는 벡터

    // 두 쌍(pair)을 비교하여 max-heap 속성을 유지하는 함수
    // 첫 번째 값을 우선 비교하며, 같을 경우 두 번째 값을 비교
    bool compare(pair<int, int> a, pair<int, int> b) {
        if (a.first != b.first) {
            return a.first > b.first; // 첫 번째 값이 더 크면 우선
        }
        return a.second > b.second; // 첫 번째 값이 같으면 두 번째 값 비교
    }

    // Bubble up: 삽입 시 max-heap 속성을 유지하도록 위로 이동
    void bubbleUp(int index) {
        while (index > 0 && compare(elements[index], elements[(index - 1) / 2])) {
            swap(elements[index], elements[(index - 1) / 2]); // 부모와 교환
            index = (index - 1) / 2; // 부모 인덱스로 이동
        }
    }

    // Bubble down: 제거 시 max-heap 속성을 유지하도록 아래로 이동
    void bubbleDown(int index) {
        int size = elements.size();
        while (index * 2 + 1 < size) { // 왼쪽 자식이 있을 경우 반복
            int child = index * 2 + 1; // 왼쪽 자식
            if (child + 1 < size && compare(elements[child + 1], elements[child])) {
                child++; // 오른쪽 자식이 더 크면 선택
            }
            if (compare(elements[index], elements[child])) {
                break; // 현재 노드가 더 크면 종료
            }
            swap(elements[index], elements[child]); // 자식과 교환
            index = child; // 자식 인덱스로 이동
        }
    }

    // Max-Heapify: 주어진 노드와 자식들 간의 비교를 통해 max-heap 속성 복구
    void maxHeapify(int size, int index) {
        int largest = index; // 현재 노드를 가장 큰 값으로 가정
        int left = 2 * index + 1; // 왼쪽 자식
        int right = 2 * index + 2; // 오른쪽 자식

        if (left < size && compare(elements[left], elements[largest])) {
            largest = left; // 왼쪽 자식이 더 크면 갱신
        }
        if (right < size && compare(elements[right], elements[largest])) {
            largest = right; // 오른쪽 자식이 더 크면 갱신
        }

        if (largest != index) { // 가장 큰 값이 현재 노드가 아니면 교환
            swap(elements[index], elements[largest]);
            maxHeapify(size, largest); // 재귀적으로 max-heapify 호출
        }
    }

public:
    // Max-Heap에 새로운 쌍(pair)을 삽입
    void insert(pair<int, int> value) {
        elements.push_back(value); // 벡터에 값 추가
        bubbleUp(elements.size() - 1); // bubble up 호출
    }

    // Max-Heap에서 최대값(루트)을 제거하고 반환
    pair<int, int> pop() {
        if (elements.empty()) {
            throw runtime_error("Max-Heap is empty!"); // 예외 처리
        }
        pair<int, int> maxValue = elements[0]; // 루트 값 저장
        elements[0] = elements.back(); // 마지막 값을 루트로 이동
        elements.pop_back(); // 마지막 값 제거
        bubbleDown(0); // bubble down 호출
        return maxValue;
    }

    // Max-Heap을 내림차순으로 정렬
    void sort() {
        int originalSize = elements.size(); // 원래 크기 저장

        // Max-Heapify 호출하여 힙 생성
        for (int i = elements.size() / 2 - 1; i >= 0; i--) {
            maxHeapify(elements.size(), i);
        }

        // 힙 정렬: 최대값을 끝으로 이동하며 힙 축소
        for (int i = elements.size() - 1; i > 0; i--) {
            swap(elements[0], elements[i]); // 최대값을 끝으로 이동
            maxHeapify(i, 0); // 힙 속성 복구
        }

        // 원래 크기로 복원
        elements.resize(originalSize);
    }

    // Max-Heap의 모든 요소를 출력
    void print() const {
        for (auto value : elements) {
            cout << "(" << value.first << ", " << value.second << ") ";
        }
        cout << endl;
    }
};

// Main 함수: Max-Heap 테스트
int main() {
    cout << "\nMax-Heap with Pairs Implementation:\n";

    MaxHeap heap;

    // 쌍(pair) 삽입
    heap.insert({10, 20});
    heap.insert({15, 25});
    heap.insert({5, 10});
    heap.insert({10, 15});

    cout << "Max-Heap after insertions: ";
    heap.print();

    cout << "Popping maximum: ";
    pair<int, int> p = heap.pop();
    cout << "(" << p.first << ", " << p.second << ")\n";

    cout << "Max-Heap after popping: ";
    heap.print();

    cout << "Sorting Max-Heap in descending order: ";
    heap.sort();
    heap.print();

    return 0;
}