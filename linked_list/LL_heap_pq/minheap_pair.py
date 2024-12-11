class MinHeap:
    def __init__(self):
        """
        MinHeap 초기화.
        내부적으로 요소를 저장할 빈 리스트 생성.
        """
        self.elements = []

    def compare(self, pair1, pair2):
        """
        두 Pair를 비교하여 우선순위를 결정.
        - x 값이 작은 Pair가 우선.
        - x 값이 같으면 y 값이 작은 Pair가 우선.
        """
        if pair1[0] != pair2[0]:
            return pair1[0] < pair2[0]
        return pair1[1] < pair2[1]

    def bubble_up(self, index):
        """
        새로운 요소 삽입 후 상향 이동하며 Min-Heap 속성 유지.
        부모 노드와 비교해 조건에 맞으면 교환.
        """
        while index > 0 and self.compare(self.elements[index], self.elements[(index - 1) // 2]):
            self.elements[index], self.elements[(index - 1) // 2] = self.elements[(index - 1) // 2], self.elements[index]
            index = (index - 1) // 2

    def bubble_down(self, index):
        """
        루트에서 요소를 제거한 후 하향 이동하며 Min-Heap 속성 유지.
        자식 노드와 비교해 조건에 맞으면 교환.
        """
        size = len(self.elements)
        while index * 2 + 1 < size:
            child = index * 2 + 1
            if child + 1 < size and self.compare(self.elements[child + 1], self.elements[child]):
                child += 1
            if self.compare(self.elements[index], self.elements[child]):
                break
            self.elements[index], self.elements[child] = self.elements[child], self.elements[index]
            index = child

    def min_heapify(self, size, index):
        """
        특정 노드에서 시작하여 서브트리를 Min-Heap 구조로 복구.
        - `sort` 메서드에서 사용.
        """
        smallest = index
        left = 2 * index + 1
        right = 2 * index + 2

        if left < size and self.compare(self.elements[left], self.elements[smallest]):
            smallest = left
        if right < size and self.compare(self.elements[right], self.elements[smallest]):
            smallest = right

        if smallest != index:
            self.elements[index], self.elements[smallest] = self.elements[smallest], self.elements[index]
            self.min_heapify(size, smallest)

    def insert(self, pair):
        """
        새로운 Pair 삽입.
        리스트 끝에 추가한 후 `bubble_up` 호출로 Min-Heap 속성 유지.
        """
        self.elements.append(pair)
        self.bubble_up(len(self.elements) - 1)

    def pop(self):
        """
        Min-Heap의 최소값(Pair)을 제거하고 반환.
        루트 요소 제거 후 `bubble_down` 호출로 Min-Heap 속성 유지.
        """
        if not self.elements:
            raise IndexError("Min-Heap is empty!")
        min_pair = self.elements[0]
        self.elements[0] = self.elements.pop()
        self.bubble_down(0)
        return min_pair

    def sort(self):
        """
        Min-Heap의 요소를 내림차순으로 정렬.
        - `min_heapify`를 사용하여 힙 정렬 방식으로 정렬.
        """
        original_size = len(self.elements)
        # Min-Heap 구조로 변환
        for i in range(original_size // 2 - 1, -1, -1):
            self.min_heapify(original_size, i)

        # 힙 정렬 수행
        for i in range(original_size - 1, 0, -1):
            self.elements[0], self.elements[i] = self.elements[i], self.elements[0]
            self.min_heapify(i, 0)

    def print(self):
        """
        현재 Min-Heap의 모든 요소를 출력.
        """
        print(self.elements)


# Min-Heap 테스트
print("Min-Heap with Pairs Implementation:")
min_heap = MinHeap()
min_heap.insert((10, 20))
min_heap.insert((15, 25))
min_heap.insert((5, 10))
min_heap.insert((10, 15))

print("Min-Heap after insertions: ", end="")
min_heap.print()

print("\nSorting the heap:")
min_heap.sort()
min_heap.print()

print(f"\nPopping minimum: {min_heap.pop()}")
print("Min-Heap after popping: ", end="")
min_heap.print()