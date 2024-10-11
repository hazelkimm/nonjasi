#include <iostream>
#include <vector>

using namespace std;

class Heap {
public:
    int *harr; // 힙의 요소들을 저장하는 배열
    int capacity; // 힙의 최대 크기
    int heap_size; // 현재 힙에 저장된 요소의 개수

    // 생성자: 힙의 용량을 설정하고 초기화
    Heap(int capacity);

    // 새로운 키를 힙에 삽입하는 함수
    void insertKey(int k);

    // 배열을 받아서 힙을 구성하는 함수
    void buildMaxHeapFromArray(vector<int>& arr);

    // 힙을 프린트하는 함수
    void printHeap();

    // 부모 노드의 인덱스를 반환하는 함수
    int parent(int i) {
        return (i - 1) / 2;
    }

    // 왼쪽 자식 노드의 인덱스를 반환하는 함수
    int left(int i) {
        return (2 * i + 1);
    }

    // 오른쪽 자식 노드의 인덱스를 반환하는 함수
    int right(int i) {
        return (2 * i + 2);
    }
};

// 힙의 생성자: 주어진 용량에 따라 힙을 초기화
Heap::Heap(int capacity) {
    this->capacity = capacity;
    this->heap_size = 0;
    this->harr = new int[capacity];
}

// 힙에 새로운 키를 삽입하는 함수
void Heap::insertKey(int k) {
    if (heap_size == capacity) {
        cout << "\nOverflow: Could not insert key\n";
        return;
    }

    // 새로운 키를 힙의 끝에 삽입
    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;
}

// 최대 힙을 유지하는 함수 (Max Heapify)
// 주어진 인덱스에서 힙 속성을 유지하도록 하는 재귀 함수
void MaxHeapify(Heap A, int i, int n) {
    int l = A.left(i);   // 왼쪽 자식 인덱스
    int r = A.right(i);  // 오른쪽 자식 인덱스
    int largest = i;

    // 왼쪽 자식이 현재 노드보다 크면 largest를 왼쪽 자식으로 설정
    if (l < n && A.harr[l] > A.harr[i]) {
        largest = l;
    }

    // 오른쪽 자식이 largest보다 크면 largest를 오른쪽 자식으로 설정
    if (r < n && A.harr[r] > A.harr[largest]) {
        largest = r;
    }

    // largest가 현재 노드와 다르면 두 노드를 교체하고, 교체된 자식 노드에 대해 MaxHeapify 재귀 호출
    if (largest != i) {
        swap(A.harr[largest], A.harr[i]);
        MaxHeapify(A, largest, n);
    }
}

// 최대 힙을 구성하는 함수
// 힙의 중간 노드부터 시작하여 MaxHeapify를 호출
void BuildMaxHeap(Heap A) {
    for (int i = (A.heap_size - 1) / 2; i >= 0; i--) {
        MaxHeapify(A, i, A.heap_size);
    }
}

// 힙 정렬 함수
// 최대 힙을 구성하고, 힙에서 하나씩 요소를 제거하면서 정렬 수행
void HeapSort(Heap A) {
    BuildMaxHeap(A);  // 최대 힙을 구성
    for (int i = A.heap_size - 1; i >= 0; i--) {
        swap(A.harr[i], A.harr[0]);  // 최대 요소를 맨 뒤로 이동
        MaxHeapify(A, 0, i);  // 남은 요소들에 대해 최대 힙 속성을 유지
    }
}

// 배열을 받아서 힙을 구성하는 함수
void Heap::buildMaxHeapFromArray(vector<int>& arr) {
    heap_size = arr.size();
    if (heap_size > capacity) {
        cout << "Array size exceeds heap capacity!" << endl;
        return;
    }
    
    // 배열 요소를 힙에 복사
    for (int i = 0; i < heap_size; i++) {
        harr[i] = arr[i];
    }
    
    // Max-Heap 구조로 변환
    for (int i = (heap_size - 1) / 2; i >= 0; i--) {
        MaxHeapify(*this, i, heap_size);
    }
}

// 힙을 프린트하는 함수 (level-order)
void Heap::printHeap() {
    cout << "Heap elements: ";
    for (int i = 0; i < heap_size; i++) {
        cout << harr[i] << " ";
    }
    cout << endl;
}

// 메인 함수
int main() {
    // 첫 번째 힙 생성 및 MaxHeapify 호출 테스트
    Heap A(20);
    A.insertKey(16);
    A.insertKey(4);
    A.insertKey(10);
    A.insertKey(14);
    A.insertKey(7);
    A.insertKey(9);
    A.insertKey(3);
    A.insertKey(2);
    A.insertKey(8);
    A.insertKey(1);

    // 1번 인덱스에서 시작하여 최대 힙 속성 유지
    MaxHeapify(A, 1, 10);
    
    // 힙 출력
    A.printHeap();

    // 배열을 사용하여 힙 생성 테스트
    vector<int> arr = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    Heap C(20);
    C.buildMaxHeapFromArray(arr);

    // 힙 출력
    C.printHeap();

    return 0;
}
