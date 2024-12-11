class PriorityQueue:
    """
    PriorityQueue: 정수를 저장하고 관리하는 최소 힙 구현.
    """

    def __init__(self):
        """
        PriorityQueue 초기화.
        내부적으로 요소를 저장할 빈 리스트를 생성합니다.
        """
        self.elements = []

    def bubble_up(self, index):
        """
        새로운 요소를 삽입한 후 최소 힙 속성을 유지하기 위해 부모 노드와 비교하여 위로 이동.
        """
        while index > 0 and self.elements[index] < self.elements[(index - 1) // 2]:
            self.elements[index], self.elements[(index - 1) // 2] = self.elements[(index - 1) // 2], self.elements[index]
            index = (index - 1) // 2

    def bubble_down(self, index):
        """
        루트에서 요소를 제거한 후 최소 힙 속성을 유지하기 위해 자식 노드와 비교하며 아래로 이동.
        """
        size = len(self.elements)
        while index * 2 + 1 < size:
            child = index * 2 + 1
            if child + 1 < size and self.elements[child + 1] < self.elements[child]:
                child += 1
            if self.elements[index] <= self.elements[child]:
                break
            self.elements[index], self.elements[child] = self.elements[child], self.elements[index]
            index = child

    def min_heapify(self, size, index):
        """
        특정 노드에서 시작하여 서브트리를 최소 힙으로 복구.
        """
        smallest = index
        left = 2 * index + 1
        right = 2 * index + 2

        if left < size and self.elements[left] < self.elements[smallest]:
            smallest = left
        if right < size and self.elements[right] < self.elements[smallest]:
            smallest = right

        if smallest != index:
            self.elements[index], self.elements[smallest] = self.elements[smallest], self.elements[index]
            self.min_heapify(size, smallest)

    def insert(self, value):
        """
        새로운 정수 값을 우선순위 큐에 삽입.
        """
        self.elements.append(value)
        self.bubble_up(len(self.elements) - 1)

    def pop(self):
        """
        우선순위 큐의 최소값(루트)을 제거하고 반환.
        """
        if not self.elements:
            raise IndexError("우선순위 큐가 비어 있습니다!")
        min_value = self.elements[0]
        self.elements[0] = self.elements.pop()
        self.bubble_down(0)
        return min_value

    def sort(self):
        """
        우선순위 큐의 요소를 정렬.
        """
        original_size = len(self.elements)

        # 최소 힙 생성
        for i in range(len(self.elements) // 2 - 1, -1, -1):
            self.min_heapify(len(self.elements), i)

        # 힙 요소를 하나씩 정렬
        for i in range(len(self.elements) - 1, 0, -1):
            self.elements[0], self.elements[i] = self.elements[i], self.elements[0]
            self.min_heapify(i, 0)

        # 정렬 후 원래 크기 복원
        self.elements = self.elements[:original_size]

    def print(self):
        """
        현재 우선순위 큐의 모든 요소를 출력.
        """
        print(self.elements)


class Node:
    """
    연결 리스트의 노드 클래스.
    각 노드는 PriorityQueue(우선순위 큐)를 포함하며, 다음 노드를 가리킵니다.
    """
    def __init__(self):
        """
        Node 초기화: 빈 PriorityQueue와 다음 노드 포인터를 None으로 설정.
        """
        self.heap = PriorityQueue()
        self.next = None


class LinkedList:
    """
    Node로 구성된 단일 연결 리스트.
    """
    def __init__(self):
        """
        LinkedList 초기화: head를 None으로 설정.
        """
        self.head = None

    def add_node(self):
        """
        새 노드를 연결 리스트의 맨 앞에 추가.
        """
        new_node = Node()
        new_node.next = self.head
        self.head = new_node

    def print_heaps(self):
        """
        연결 리스트의 각 노드에 포함된 힙을 출력.
        """
        current = self.head
        index = 0
        while current:
            print(f"노드 {index}의 힙: ", end="")
            current.heap.print()
            current = current.next
            index += 1


# 테스트 코드
print("정수를 사용하는 최소 힙 기반 연결 리스트:")

ll = LinkedList()
ll.add_node()
ll.add_node()

# 첫 번째 노드의 힙에 정수 삽입
ll.head.heap.insert(10)
ll.head.heap.insert(5)
ll.head.heap.insert(20)

# 두 번째 노드의 힙에 정수 삽입
ll.head.next.heap.insert(15)
ll.head.next.heap.insert(30)
ll.head.next.heap.insert(25)

print("삽입 후 연결 리스트의 힙:")
ll.print_heaps()

# 첫 번째 힙 정렬
print("\n첫 번째 힙 정렬 후 (오름차순):")
ll.head.heap.sort()
ll.head.heap.print()

# 첫 번째 힙에서 요소 제거
print("\n첫 번째 힙에서 요소 제거:")
popped = ll.head.heap.pop()
print(f"제거된 요소: {popped}")
print("제거 후 첫 번째 힙: ", end="")
ll.head.heap.print()