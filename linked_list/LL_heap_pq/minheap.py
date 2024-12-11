class MinHeap:
    """
    Min-Heap 클래스: 정수형 값을 저장하며, 최소 힙 구조를 유지합니다.
    """

    def __init__(self):
        """Min-Heap 초기화: 요소를 저장할 리스트 생성."""
        self.elements = []

    def bubble_up(self, index):
        """
        새로운 요소를 삽입한 후 최소 힙 속성을 유지하도록 부모와 비교하며 위로 이동.
        """
        while index > 0 and self.elements[index] < self.elements[(index - 1) // 2]:
            # 부모와 현재 노드를 교환
            self.elements[index], self.elements[(index - 1) // 2] = (
                self.elements[(index - 1) // 2],
                self.elements[index],
            )
            index = (index - 1) // 2  # 부모 인덱스로 이동

    def bubble_down(self, index):
        """
        루트에서 요소를 제거한 후 최소 힙 속성을 유지하도록 자식과 비교하며 아래로 이동.
        """
        size = len(self.elements)
        while index * 2 + 1 < size:  # 왼쪽 자식이 존재하는 동안 반복
            child = index * 2 + 1  # 왼쪽 자식
            if child + 1 < size and self.elements[child + 1] < self.elements[child]:
                child += 1  # 오른쪽 자식이 더 작으면 선택
            if self.elements[index] <= self.elements[child]:
                break  # 현재 노드가 자식 노드보다 작거나 같으면 종료
            # 현재 노드와 자식 노드 교환
            self.elements[index], self.elements[child] = (
                self.elements[child],
                self.elements[index],
            )
            index = child  # 자식 노드로 이동

    def insert(self, value):
        """
        Min-Heap에 새로운 값을 삽입합니다.
        """
        self.elements.append(value)  # 요소를 리스트 끝에 추가
        self.bubble_up(len(self.elements) - 1)  # 삽입 후 정렬

    def pop(self):
        """
        Min-Heap에서 최소값을 제거하고 반환합니다.
        """
        if not self.elements:
            raise IndexError("Min-Heap is empty!")
        min_value = self.elements[0]  # 최소값(루트)을 저장
        self.elements[0] = self.elements.pop()  # 마지막 요소를 루트로 이동
        self.bubble_down(0)  # 루트에서 정렬 복구
        return min_value

    def heapify(self):
        """
        기존 리스트를 Min-Heap으로 변환합니다.
        """
        size = len(self.elements)
        for i in range((size // 2) - 1, -1, -1):  # 마지막 내부 노드부터 처리
            self.bubble_down(i)

    def sort(self):
        """
        Min-Heap의 요소를 오름차순으로 정렬합니다 (힙 정렬).
        """
        original_elements = self.elements[:]
        sorted_list = []
        while self.elements:
            sorted_list.append(self.pop())  # 최소값을 제거하여 정렬 리스트에 추가
        self.elements = original_elements  # 원래 힙을 복구
        print("Sorted list:", sorted_list)

    def print(self):
        """
        현재 Min-Heap의 요소를 출력합니다.
        """
        print(self.elements)


# Min-Heap 테스트
print("Min-Heap Implementation:")
min_heap = MinHeap()

# 삽입 테스트
min_heap.insert(10)
min_heap.insert(20)
min_heap.insert(5)
min_heap.insert(15)

print("Min-Heap after insertions: ", end="")
min_heap.print()

# 최소값 제거 테스트
print(f"Popping minimum: {min_heap.pop()}")
print("Min-Heap after popping: ", end="")
min_heap.print()

# 정렬 테스트
print("Sorting the heap:")
min_heap.sort()