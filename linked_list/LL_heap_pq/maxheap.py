class MaxHeap:
    def __init__(self):
        """Max-Heap 초기화: 내부적으로 요소를 저장할 빈 리스트 생성"""
        self.elements = []

    def bubble_up(self, index):
        """
        삽입된 요소를 부모와 비교하여 위로 이동.
        - Max-Heap 속성을 유지합니다.
        """
        while index > 0 and self.elements[index] > self.elements[(index - 1) // 2]:
            self.elements[index], self.elements[(index - 1) // 2] = self.elements[(index - 1) // 2], self.elements[index]
            index = (index - 1) // 2

    def bubble_down(self, index):
        """
        루트에서 시작하여 자식 노드와 비교하며 아래로 이동.
        - Max-Heap 속성을 유지합니다.
        """
        size = len(self.elements)
        while index * 2 + 1 < size:
            child = index * 2 + 1
            if child + 1 < size and self.elements[child + 1] > self.elements[child]:
                child += 1  # 오른쪽 자식이 더 크면 선택
            if self.elements[index] >= self.elements[child]:
                break  # 부모가 자식보다 크거나 같으면 종료
            self.elements[index], self.elements[child] = self.elements[child], self.elements[index]
            index = child

    def insert(self, value):
        """Max-Heap에 값 추가. bubble_up 호출하여 힙 속성 유지."""
        self.elements.append(value)
        self.bubble_up(len(self.elements) - 1)

    def pop(self):
        """
        Max-Heap의 최대값(루트)을 제거하고 반환.
        - bubble_down 호출하여 힙 속성 유지.
        """
        if not self.elements:
            raise IndexError("Max-Heap is empty!")
        max_value = self.elements[0]
        self.elements[0] = self.elements.pop()
        self.bubble_down(0)
        return max_value

    def max_heapify(self, size, index):
        """
        특정 노드에서 시작하여 서브트리를 Max-Heap으로 복구.
        - 정렬 과정에서 사용됩니다.
        """
        largest = index
        left = 2 * index + 1
        right = 2 * index + 2

        if left < size and self.elements[left] > self.elements[largest]:
            largest = left
        if right < size and self.elements[right] > self.elements[largest]:
            largest = right

        if largest != index:
            self.elements[index], self.elements[largest] = self.elements[largest], self.elements[index]
            self.max_heapify(size, largest)

    def sort(self):
        """
        Max-Heap 정렬 (Heap Sort).
        - 요소를 내림차순으로 정렬한 결과를 만듭니다.
        """
        size = len(self.elements)
        # Max-Heapify로 전체 힙 복구
        for i in range(size // 2 - 1, -1, -1):
            self.max_heapify(size, i)

        # 요소를 하나씩 끝으로 이동하며 정렬
        for i in range(size - 1, 0, -1):
            self.elements[0], self.elements[i] = self.elements[i], self.elements[0]
            self.max_heapify(i, 0)

    def print(self):
        """현재 Max-Heap의 모든 요소 출력."""
        print(self.elements)


# Test Max-Heap
print("\nMax-Heap Implementation:")
max_heap = MaxHeap()
max_heap.insert(10)
max_heap.insert(20)
max_heap.insert(5)
max_heap.insert(15)

print("Max-Heap after insertions: ", end="")
max_heap.print()

print(f"Popping maximum: {max_heap.pop()}")
print("Max-Heap after popping: ", end="")
max_heap.print()

# Sort the Max-Heap
print("Sorting the Max-Heap: ")
max_heap.sort()
max_heap.print()