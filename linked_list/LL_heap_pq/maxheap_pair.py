class MaxHeap:
    """
    Max-Heap 클래스: (x, y) 쌍으로 구성된 데이터를 저장하며 최대 힙 속성을 유지합니다.
    """
    def __init__(self):
        """Max-Heap 초기화: 빈 리스트를 사용하여 내부 데이터를 저장합니다."""
        self.elements = []

    def compare(self, pair1, pair2):
        """
        두 Pair를 비교하여 우선순위를 결정합니다.
        - x 값을 우선 비교: x가 클수록 우선순위가 높습니다.
        - x가 같을 경우 y 값을 비교: y가 클수록 우선순위가 높습니다.
        """
        if pair1[0] != pair2[0]:
            return pair1[0] > pair2[0]  # x 값을 우선 비교
        return pair1[1] > pair2[1]      # x가 같으면 y 값을 비교

    def bubble_up(self, index):
        """
        Bubble up: 새로운 요소 삽입 후 부모와 비교하며 힙 속성을 유지합니다.
        """
        while index > 0 and self.compare(self.elements[index], self.elements[(index - 1) // 2]):
            self.elements[index], self.elements[(index - 1) // 2] = self.elements[(index - 1) // 2], self.elements[index]
            index = (index - 1) // 2

    def bubble_down(self, index):
        """
        Bubble down: 루트에서 시작하여 자식 노드들과 비교하며 힙 속성을 유지합니다.
        """
        size = len(self.elements)
        while index * 2 + 1 < size:  # 왼쪽 자식이 있을 경우 반복
            child = index * 2 + 1    # 왼쪽 자식 인덱스
            if child + 1 < size and self.compare(self.elements[child + 1], self.elements[child]):
                child += 1  # 오른쪽 자식이 더 크면 선택
            if self.compare(self.elements[index], self.elements[child]):
                break  # 현재 노드가 더 크면 종료
            self.elements[index], self.elements[child] = self.elements[child], self.elements[index]
            index = child

    def max_heapify(self, size, index):
        """
        Max-Heapify: 특정 노드와 자식들 간의 비교를 통해 최대 힙 속성을 복구합니다.
        - 힙 정렬 과정에서 사용됩니다.
        """
        largest = index
        left = 2 * index + 1
        right = 2 * index + 2

        if left < size and self.compare(self.elements[left], self.elements[largest]):
            largest = left
        if right < size and self.compare(self.elements[right], self.elements[largest]):
            largest = right

        if largest != index:
            self.elements[index], self.elements[largest] = self.elements[largest], self.elements[index]
            self.max_heapify(size, largest)

    def insert(self, pair):
        """
        새로운 Pair를 Max-Heap에 삽입합니다.
        - Bubble up을 호출하여 힙 속성을 유지합니다.
        """
        self.elements.append(pair)
        self.bubble_up(len(self.elements) - 1)

    def pop(self):
        """
        Max-Heap의 최대값(루트)을 제거하고 반환합니다.
        - Bubble down을 호출하여 힙 속성을 유지합니다.
        """
        if not self.elements:
            raise IndexError("Max-Heap is empty!")
        max_pair = self.elements[0]
        self.elements[0] = self.elements.pop()
        self.bubble_down(0)
        return max_pair

    def sort(self):
        """
        Max-Heap을 정렬하여 (내림차순) 리스트로 만듭니다.
        - Max-Heapify를 사용하여 힙 정렬 방식으로 정렬합니다.
        """
        original_size = len(self.elements)

        # Max-Heapify 호출하여 힙 속성 복구
        for i in range(len(self.elements) // 2 - 1, -1, -1):
            self.max_heapify(len(self.elements), i)

        # 정렬 과정: 최대값을 끝으로 이동하며 크기 축소
        for i in range(len(self.elements) - 1, 0, -1):
            self.elements[0], self.elements[i] = self.elements[i], self.elements[0]
            self.max_heapify(i, 0)

        # 원래 크기로 복원
        self.elements = self.elements[:original_size]

    def print(self):
        """Max-Heap의 모든 요소를 출력합니다."""
        print(self.elements)


# 테스트 코드
print("\nMax-Heap with Pairs Implementation:")
max_heap = MaxHeap()

# 데이터 삽입
max_heap.insert((10, 20))
max_heap.insert((15, 25))
max_heap.insert((5, 10))
max_heap.insert((10, 15))

# Max-Heap 상태 출력
print("Max-Heap after insertions: ", end="")
max_heap.print()

# 최대값 제거
print(f"Popping maximum: {max_heap.pop()}")
print("Max-Heap after popping: ", end="")
max_heap.print()

# 힙 정렬 실행
print("\nSorting the Max-Heap (descending order):")
max_heap.sort()
max_heap.print()