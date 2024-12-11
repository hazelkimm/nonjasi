#include <iostream>
#include <vector>
#include <utility> // For std::pair
using namespace std;

// Min-Heap 클래스 정의
class MinHeap {
private:
    vector<pair<int, int>> elements; // 내부 벡터로 힙 구현

    // 두 Pair를 비교하여 우선순위를 결정 (x 우선, 같으면 y 비교)
    bool compare(pair<int, int> a, pair<int, int> b) {
        if (a.first != b.first) {
            return a.first < b.first; // x가 작은 Pair 우선
        }
        return a.second < b.second; // x가 같으면 y가 작은 Pair 우선
    }

    // 삽입 후 상향 이동하여 최소 힙 속성을 유지
    void bubbleUp(int index) {
        while (index > 0 && compare(elements[index], elements[(index - 1) / 2])) {
            swap(elements[index], elements[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    // 삭제 후 하향 이동하여 최소 힙 속성을 유지
    void bubbleDown(int index) {
        int size = elements.size();
        while (index * 2 + 1 < size) {
            int child = index * 2 + 1;
            if (child + 1 < size && compare(elements[child + 1], elements[child])) {
                child++;
            }
            if (compare(elements[index], elements[child])) {
                break;
            }
            swap(elements[index], elements[child]);
            index = child;
        }
    }

    // 특정 노드에서 시작하여 최소 힙 속성을 복구 (힙 정렬용)
    void minHeapify(int size, int index) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && compare(elements[left], elements[smallest])) {
            smallest = left;
        }
        if (right < size && compare(elements[right], elements[smallest])) {
            smallest = right;
        }

        if (smallest != index) {
            swap(elements[index], elements[smallest]);
            minHeapify(size, smallest);
        }
    }

public:
    // MinHeap에 새로운 Pair 삽입
    void insert(pair<int, int> value) {
        elements.push_back(value);
        bubbleUp(elements.size() - 1);
    }

    // MinHeap의 최소값(Pair) 제거 및 반환
    pair<int, int> pop() {
        if (elements.empty()) {
            throw runtime_error("Min-Heap is empty!");
        }
        pair<int, int> minValue = elements[0];
        elements[0] = elements.back();
        elements.pop_back();
        bubbleDown(0);
        return minValue;
    }

    // MinHeap의 모든 요소를 오름차순으로 정렬
    void sort() {
        int originalSize = elements.size();

        // 힙 구조 생성
        for (int i = originalSize / 2 - 1; i >= 0; i--) {
            minHeapify(originalSize, i);
        }

        // 힙 정렬 수행 (요소를 하나씩 정렬)
        for (int i = originalSize - 1; i > 0; i--) {
            swap(elements[0], elements[i]); // 최솟값을 끝으로 이동
            minHeapify(i, 0);              // 축소된 힙에 대해 복구
        }

        // 원래 크기로 복원
        elements.resize(originalSize);
    }

    // MinHeap의 모든 요소 출력
    void print() const {
        for (auto value : elements) {
            cout << "(" << value.first << ", " << value.second << ") ";
        }
        cout << endl;
    }
};

// 메인 함수: MinHeap 테스트
int main() {
    cout << "Min-Heap with Pairs Implementation:\n";

    MinHeap heap;

    heap.insert({10, 20});
    heap.insert({15, 25});
    heap.insert({5, 10});
    heap.insert({10, 15});

    cout << "Min-Heap after insertions: ";
    heap.print();

    cout << "\nSorting the heap:\n";
    heap.sort();
    heap.print();

    cout << "\nPopping minimum: ";
    pair<int, int> p = heap.pop();
    cout << "(" << p.first << ", " << p.second << ")\n";

    cout << "Min-Heap after popping: ";
    heap.print();

    return 0;
}