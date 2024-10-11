class MaxHeap:
    def __init__(self):
        self.heap = []  # 힙을 저장하는 리스트

    def parent(self, i):
        return (i - 1) // 2  # 부모 노드의 인덱스 계산

    def left_child(self, i):
        return 2 * i + 1  # 왼쪽 자식 노드의 인덱스 계산

    def right_child(self, i):
        return 2 * i + 2  # 오른쪽 자식 노드의 인덱스 계산

    def insert(self, key):
        # 요소를 힙에 추가
        self.heap.append(key)
        # 새로 삽입된 요소를 올바른 위치로 이동
        self.heapify_up(len(self.heap) - 1)

    def heapify_up(self, i):
        # 부모 노드가 존재하고, 부모보다 현재 노드가 크면 교환
        while i != 0 and self.heap[self.parent(i)] < self.heap[i]:
            # 부모 노드와 교환
            self.heap[self.parent(i)], self.heap[i] = self.heap[i], self.heap[self.parent(i)]
            # 인덱스를 부모로 이동
            i = self.parent(i)

    def extract_max(self):
        if len(self.heap) == 0:
            return None
        # 루트(최대값) 추출
        root = self.heap[0]
        # 마지막 요소를 루트로 이동
        self.heap[0] = self.heap.pop()
        # Max-Heap 속성을 유지하기 위해 재정렬
        self.heapify_down(0)
        return root

    def heapify_down(self, i):
        largest = i
        left = self.left_child(i)
        right = self.right_child(i)

        # 왼쪽 자식이 더 크면 largest 업데이트
        if left < len(self.heap) and self.heap[left] > self.heap[largest]:
            largest = left

        # 오른쪽 자식이 더 크면 largest 업데이트
        if right < len(self.heap) and self.heap[right] > self.heap[largest]:
            largest = right

        # largest가 i와 다르면 교환하고 재귀 호출
        if largest != i:
            self.heap[i], self.heap[largest] = self.heap[largest], self.heap[i]
            self.heapify_down(largest)

    def get_max(self):
        if len(self.heap) == 0:
            return None
        return self.heap[0]

    def size(self):
        return len(self.heap)  # 힙의 크기 반환

    def build_heap_from_list(self, lst):
        # 주어진 리스트로부터 힙을 구성하는 함수
        self.heap = lst[:]  # 리스트의 복사본을 힙으로 설정
        n = len(self.heap)

        # 리스트의 중간부터 시작하여 힙 구조로 변환
        for i in range(n // 2 - 1, -1, -1):
            self.heapify_down(i)

    def print_heap(self):
        # 힙을 출력하는 함수(level-order)
        print("Heap elements:", self.heap)

# 사용 예시
heap = MaxHeap()

# 리스트로부터 힙 생성
lst = [3, 9, 2, 1, 4, 5]
heap.build_heap_from_list(lst)

# 힙 출력
heap.print_heap()  # 힙 구조로 출력

# 요소 추가
heap.insert(10)
heap.print_heap()  # 요소 추가 후 힙 출력

# 최대값 추출
print("Max:", heap.extract_max())  # 최대값 추출 후 출력
heap.print_heap()  # 최대값 추출 후 힙 출력
