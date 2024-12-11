class Node:
    """연결 리스트의 노드 클래스."""
    def __init__(self, val):
        self.val = val  # 노드의 값
        self.next = None  # 다음 노드를 가리키는 포인터


class MinHeap:
    """연결 리스트로 구현된 Min-Heap 클래스."""
    def __init__(self):
        """Min-Heap 초기화."""
        self.head = None  # Min-Heap의 시작 노드

    def insert(self, val):
        """Min-Heap에 값을 삽입."""
        new_node = Node(val)
        # 새 값이 가장 작으면 헤드에 삽입
        if not self.head or val < self.head.val:
            new_node.next = self.head
            self.head = new_node
        else:
            # 적절한 위치를 찾아 삽입
            current = self.head
            while current.next and current.next.val <= val:
                current = current.next
            new_node.next = current.next
            current.next = new_node

    def pop(self):
        """Min-Heap에서 최소값 제거 및 반환."""
        if not self.head:
            raise IndexError("Min-Heap is empty!")
        min_val = self.head.val
        self.head = self.head.next  # 헤드를 다음 노드로 이동
        return min_val

    def print_heap(self):
        """Min-Heap을 출력."""
        current = self.head
        while current:
            print(current.val, end=" ")
            current = current.next
        print()

    def sort(self):
        """Min-Heap의 값을 오름차순으로 정렬."""
        # 모든 값을 배열에 저장
        current = self.head
        values = []
        while current:
            values.append(current.val)
            current = current.next

        # 배열을 정렬 (Python 내장 정렬 사용)
        values.sort()

        # 정렬된 결과 출력
        print("Sorted Min-Heap: ", end="")
        for val in values:
            print(val, end=" ")
        print()


# 테스트 코드
print("Min-Heap with Linked List Implementation:")
min_heap = MinHeap()

# Min-Heap에 값 삽입
min_heap.insert(10)
min_heap.insert(20)
min_heap.insert(5)
min_heap.insert(15)

# Min-Heap 상태 출력
print("Min-Heap after insertions: ", end="")
min_heap.print_heap()

# Min-Heap에서 최소값 제거
print(f"Popping minimum: {min_heap.pop()}")
print("Min-Heap after popping: ", end="")
min_heap.print_heap()

# Min-Heap 정렬
print("Sorting Min-Heap:")
min_heap.sort()