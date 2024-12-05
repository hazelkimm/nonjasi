class QueueNode:
    """큐의 각 노드를 나타내는 클래스"""
    def __init__(self, data):
        self.data = data  # 노드에 저장된 데이터
        self.next = None  # 다음 노드를 가리키는 포인터


class Queue:
    """용량 제한이 있는 큐 클래스"""
    QUEUE_CAPACITY = 3  # 각 큐의 최대 용량

    def __init__(self):
        self.front = None  # 큐의 앞쪽 (디큐 위치)
        self.rear = None   # 큐의 뒤쪽 (엔큐 위치)
        self.size = 0      # 현재 큐의 크기

    def is_empty(self):
        """큐가 비었는지 확인"""
        return self.front is None

    def enqueue(self, value):
        """큐에 요소 추가"""
        new_node = QueueNode(value)
        if self.rear is None:
            # 큐가 비어 있는 경우 front와 rear를 새 노드로 설정
            self.front = self.rear = new_node
        else:
            # 큐가 비어 있지 않은 경우 rear 뒤에 노드를 추가하고 rear를 갱신
            self.rear.next = new_node
            self.rear = new_node
        self.size += 1

    def dequeue(self):
        """큐에서 요소 제거 및 반환"""
        if self.is_empty():
            raise IndexError("Queue is empty")
        value = self.front.data
        self.front = self.front.next
        if self.front is None:
            self.rear = None  # 큐가 비어 있으면 rear도 None으로 설정
        self.size -= 1
        return value

    def peek(self):
        """큐의 앞쪽 요소를 반환 (제거하지 않음)"""
        if self.is_empty():
            raise IndexError("Queue is empty")
        return self.front.data


class LinkedListNode:
    """양방향 링크드 리스트 노드 클래스 (각 노드가 큐를 포함)"""
    def __init__(self):
        self.queue = Queue()  # 큐를 포함
        self.next = None      # 다음 노드를 가리키는 포인터
        self.prev = None      # 이전 노드를 가리키는 포인터


class DoubleLinkedList:
    """양방향 링크드 리스트로 연결된 큐의 데이터 구조"""
    def __init__(self):
        self.head = LinkedListNode()  # 초기 링크드 리스트 노드 생성
        self.tail = self.head         # 마지막 노드 (초기에는 head와 같음)

    def push(self, value):
        """데이터 구조에 요소 추가"""
        if self.tail.queue.size >= Queue.QUEUE_CAPACITY:
            # 현재 큐가 가득 찬 경우 새 링크드 리스트 노드를 생성
            new_node = LinkedListNode()
            self.tail.next = new_node
            new_node.prev = self.tail
            self.tail = new_node
            print(f"Creating new queue for value {value}.")
        
        # 현재 큐에 데이터를 추가
        self.tail.queue.enqueue(value)
        print(f"Pushed value {value} to queue. Queue size is now {self.tail.queue.size}.")

    def pop(self):
        """데이터 구조에서 요소 제거 및 반환"""
        if self.head.queue.is_empty():
            raise IndexError("List is empty")

        value = self.head.queue.dequeue()  # 첫 번째 큐에서 요소 제거
        print(f"Popped value: {value}")
        
        # 첫 번째 큐가 비어 있으면 링크드 리스트 노드를 제거
        if self.head.queue.is_empty() and self.head.next is not None:
            next_node = self.head.next
            next_node.prev = None
            self.head = next_node
            print("Removed an empty linked list node.")
        return value

    def pop_and_redistribute(self):
        """데이터 구조에서 요소 제거 및 첫 번째 큐 유지"""
        if self.head.queue.is_empty():
            raise IndexError("List is empty")

        value = self.head.queue.dequeue()  # 첫 번째 큐에서 요소 제거
        print(f"Popped value: {value}")

        # 첫 번째 큐가 크기가 부족한 경우, 다음 큐에서 요소를 가져옴
        current = self.head
        while current.queue.size < Queue.QUEUE_CAPACITY and current.next is not None:
            next_node = current.next
            if not next_node.queue.is_empty():
                redistributed_value = next_node.queue.dequeue()
                current.queue.enqueue(redistributed_value)
                print(f"Redistributed value {redistributed_value} to maintain size.")
            
            # 다음 큐가 비었으면 링크드 리스트 노드를 제거
            if next_node.queue.is_empty():
                current.next = next_node.next
                if next_node.next:
                    next_node.next.prev = current
                if next_node == self.tail:
                    self.tail = current
                print("Removed an empty linked list node.")
        return value

    def print_structure(self):
        """데이터 구조 출력"""
        current = self.head
        queue_num = 1
        while current is not None:
            print(f"Queue {queue_num}: ", end="")
            node = current.queue.front
            while node is not None:
                print(node.data, end=" ")
                node = node.next
            print()
            current = current.next
            queue_num += 1

    def total_size(self):
        """데이터 구조의 총 요소 개수 계산"""
        current = self.head
        total = 0
        while current is not None:
            total += current.queue.size
            current = current.next
        return total

    def depth(self):
        """데이터 구조의 깊이(큐의 개수) 계산"""
        current = self.head
        depth = 0
        while current is not None:
            depth += 1
            current = current.next
        return depth


# 테스트 코드
if __name__ == "__main__":
    ds = DoubleLinkedList()

    # 요소 추가
    print("Pushing elements to the data structure...")
    ds.push(10)
    ds.push(20)
    ds.push(30)  # 첫 번째 큐가 가득 참
    ds.push(40)  # 두 번째 큐 생성
    ds.push(50)

    # 데이터 구조 출력
    print("Initial data structure:")
    ds.print_structure()

    # 총 크기와 깊이 확인
    print(f"Total size: {ds.total_size()}")
    print(f"Depth (number of queues): {ds.depth()}")

    # 데이터 제거 및 출력
    print("Popping value:")
    ds.pop()
    print("Data structure after popping:")
    ds.print_structure()

    # 재분배를 포함한 데이터 제거
    print("Popping value with redistribution:")
    ds.pop_and_redistribute()
    print("Data structure after redistribution:")
    ds.print_structure()
