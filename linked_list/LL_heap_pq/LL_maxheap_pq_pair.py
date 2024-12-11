class PriorityQueue:
    """
    PriorityQueue: Pair(튜플)을 저장하고 관리하는 최대 힙 구현.
    첫 번째 값을 우선적으로 비교하여 우선순위를 결정하며, 필요 시 두 번째 값을 비교.
    """
    def __init__(self):
        """
        PriorityQueue 초기화.
        내부적으로 요소를 저장할 빈 리스트를 생성합니다.
        """
        self.elements = []

    def compare(self, pair1, pair2):
        """
        두 Pair를 비교하는 함수.
        - 첫 번째 값이 큰 경우 우선순위가 높습니다.
        - 첫 번째 값이 같으면 두 번째 값으로 우선순위를 결정합니다.
        """
        if pair1[0] != pair2[0]:
            return pair1[0] > pair2[0]
        return pair1[1] > pair2[1]

    def bubble_up(self, index):
        """
        새로운 요소를 삽입한 후 최대 힙 속성을 유지하기 위해 부모 노드와 비교하여 위로 이동.
        - 삽입 시 호출됩니다.
        """
        while index > 0 and self.compare(self.elements[index], self.elements[(index - 1) // 2]):
            self.elements[index], self.elements[(index - 1) // 2] = self.elements[(index - 1) // 2], self.elements[index]
            index = (index - 1) // 2

    def bubble_down(self, index):
        """
        루트에서 요소를 제거한 후 최대 힙 속성을 유지하기 위해 자식 노드와 비교하며 아래로 이동.
        - 제거 시 호출됩니다.
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

    def max_heapify(self, size, index):
        """
        특정 노드에서 시작하여 서브트리를 최대 힙으로 복구.
        - 힙 정렬에서 사용됩니다.
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
        새로운 Pair(튜플)를 우선순위 큐에 삽입.
        - bubble_up을 호출하여 힙 속성을 유지합니다.
        """
        self.elements.append(pair)
        self.bubble_up(len(self.elements) - 1)

    def pop(self):
        """
        우선순위 큐의 최대값(루트)을 제거하고 반환.
        - bubble_down을 호출하여 힙 속성을 유지합니다.
        """
        if not self.elements:
            raise IndexError("Priority queue is empty!")
        max_pair = self.elements[0]
        self.elements[0] = self.elements.pop()
        self.bubble_down(0)
        return max_pair

    def sort(self):
        """
        우선순위 큐의 요소를 정렬.
        - max_heapify를 사용하여 힙 정렬 방식으로 정렬합니다.
        """
        original_size = len(self.elements)

        # 최대 힙 생성
        for i in range(len(self.elements) // 2 - 1, -1, -1):
            self.max_heapify(len(self.elements), i)

        # 힙 요소를 하나씩 정렬
        for i in range(len(self.elements) - 1, 0, -1):
            self.elements[0], self.elements[i] = self.elements[i], self.elements[0]
            self.max_heapify(i, 0)

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
            print(f"Heap in Node {index}: ", end="")
            current.heap.print()
            current = current.next
            index += 1


# 테스트 코드
print("\nMax-Heap with Pairs in Linked List:")

ll = LinkedList()
ll.add_node()
ll.add_node()

# 첫 번째 노드의 힙에 요소 추가
ll.head.heap.insert((10, 20))
ll.head.heap.insert((15, 25))
ll.head.heap.insert((5, 10))

# 두 번째 노드의 힙에 요소 추가
ll.head.next.heap.insert((20, 30))
ll.head.next.heap.insert((25, 15))
ll.head.next.heap.insert((30, 5))

print("Heaps in the linked list after insertion:")
ll.print_heaps()

# 첫 번째 힙에서 요소 제거
print("\nPopping elements from the first heap:")
popped = ll.head.heap.pop()
print(f"Popped: {popped}")
print("Heap after popping: ", end="")
ll.head.heap.print()

# 첫 번째 힙 정렬
print("\nSorting the first heap:")
ll.head.heap.sort()
print("Heap after sorting: ", end="")
ll.head.heap.print()