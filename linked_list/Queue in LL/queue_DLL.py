'''
1. LinkedListQueue create(capacity): 큐를 생성하고 초기화합니다. 첫 번째 노드를 생성하고 최대 용량(capacity)을 설정합니다.
2. void enqueue(value): 큐에 요소를 추가합니다. 현재 노드의 용량을 초과하면 새 노드를 생성하여 연결합니다.
3. int pop(): 큐에서 첫 번째 요소를 제거하고 반환합니다. 현재 노드가 비어 있으면 다음 노드로 이동하여 처리합니다.
4. int pop_and_shift(): 큐에서 첫 번째 요소를 제거한 후, 뒤쪽 노드의 요소를 앞으로 이동하여 
     첫 번째 노드부터 capacity를 유지하도록 재배치합니다. 마지막 노드가 비면 삭제합니다.
5. int peek(): 큐의 첫 번째 요소를 반환합니다. 요소를 제거하지 않습니다.
6. int total_size(): 큐 전체의 요소 개수를 반환합니다. 모든 노드를 순회하며 요소 수를 계산합니다.
7. void print_queue():큐의 모든 요소를 출력합니다. 각 노드의 데이터를 화살표(->)로 연결하여 표시합니다.
8. int get_element_at(index): 큐에서 특정 인덱스의 요소를 반환합니다. 연결된 노드를 순회하며 인덱스를 계산합니다.
9. void merge_queues(queue): 다른 큐와 병합합니다. 병합된 요소는 현재 큐의 끝에 추가됩니다.
10. int sum_queue(): 큐 내 모든 요소의 합계를 반환합니다.
11. int find_max(): 큐 내에서 가장 큰 값을 반환합니다. 비어 있으면 예외를 발생시킵니다.
12. int find_min(): 큐 내에서 가장 작은 값을 반환합니다. 비어 있으면 예외를 발생시킵니다.
13. int find_element(value): 큐에서 특정 값을 가진 요소의 인덱스를 반환합니다. 값이 없으면 -1을 반환합니다.
14. void print_reverse(): 큐의 모든 요소를 역순으로 출력합니다. 각 노드의 데이터를 역순으로 처리하여 표시합니다.
15. int depth(): 연결된 노드의 총 개수를 반환합니다.
16. void delete_element(value): 큐에서 특정 값을 삭제합니다. 연결된 노드들에서 값을 찾고 제거합니다.
17. double calculate_average(): 큐 내 모든 요소의 평균값을 계산하여 반환합니다.
18. void remove_duplicates(): 큐에서 중복된 요소를 제거합니다. 요소 순서를 유지하며 중복을 제거합니다.
19. void delete_in_range(min_value, max_value): 큐에서 특정 값 범위(min_value ~ max_value)에 해당하는 요소를 삭제합니다.
'''

class Node:
    """노드 클래스: 큐 데이터를 저장하고 연결을 관리"""
    def __init__(self, capacity):
        self.queue = []  # 큐 데이터를 저장하는 리스트
        self.capacity = capacity  # 큐의 최대 용량
        self.next = None  # 다음 노드 참조
        self.prev = None  # 이전 노드 참조


class LinkedListQueue:
    """이중 연결 리스트 기반 큐 클래스"""
    def __init__(self, capacity):
        """큐 초기화"""
        self.head = Node(capacity)  # 첫 번째 노드
        self.tail = self.head  # 마지막 노드
        self.capacity = capacity  # 각 노드의 최대 용량

    def enqueue(self, value):
        """요소를 큐에 추가. 용량 초과 시 새 노드 생성"""
        if len(self.tail.queue) < self.tail.capacity:
            self.tail.queue.append(value)
        else:
            new_node = Node(self.capacity)
            self.tail.next = new_node
            new_node.prev = self.tail
            self.tail = new_node
            self.tail.queue.append(value)

    def pop(self):
        """첫 번째 요소 제거 및 반환"""
        if not self.head.queue:
            if self.head.next:
                self.head = self.head.next
                self.head.prev = None
                return self.pop()
            else:
                raise IndexError("큐가 비어 있습니다.")
        return self.head.queue.pop(0)

    def pop_and_shift(self):
        """첫 번째 요소 제거 후 뒤쪽 요소를 앞으로 이동하여 재배치"""
        if not self.head.queue:
            if self.head.next:
                self.head = self.head.next
                self.head.prev = None
                return self.pop_and_shift()
            else:
                raise IndexError("큐가 비어 있습니다.")

        # 첫 번째 요소 제거
        popped_value = self.head.queue.pop(0)

        # 뒤쪽 큐에서 요소를 가져와 앞쪽 큐를 채우기
        current = self.head
        while current.next:
            while len(current.queue) < self.capacity and current.next.queue:
                current.queue.append(current.next.queue.pop(0))
            current = current.next

        # 마지막 노드가 비었으면 제거
        if not current.queue and current != self.head:
            if current.prev:
                current.prev.next = None
            self.tail = current.prev

        return popped_value

    def peek(self):
        """첫 번째 요소 반환 (제거하지 않음)"""
        if not self.head.queue:
            raise IndexError("큐가 비어 있습니다.")
        return self.head.queue[0]

    def total_size(self):
        """큐 전체 요소 개수 반환"""
        size = 0
        current = self.head
        while current:
            size += len(current.queue)
            current = current.next
        return size

    def print_queue(self):
        """큐의 모든 요소 출력"""
        current = self.head
        while current:
            print(current.queue, end=" -> ")
            current = current.next
        print("None")

    def get_element_at(self, index):
        """특정 인덱스의 요소 반환"""
        current = self.head
        while current:
            if index < len(current.queue):
                return current.queue[index]
            index -= len(current.queue)
            current = current.next
        raise IndexError("인덱스가 범위를 초과했습니다.")

    def merge_queues(self, other):
        """다른 큐와 병합"""
        current = other.head
        while current:
            for value in current.queue:
                self.enqueue(value)
            current = current.next

    def sum_queue(self):
        """큐 내 모든 요소 합 반환"""
        total = 0
        current = self.head
        while current:
            total += sum(current.queue)
            current = current.next
        return total

    def find_max(self):
        """큐 내 최댓값 반환"""
        if not self.head.queue:
            raise ValueError("큐가 비어 있습니다.")
        max_value = float('-inf')
        current = self.head
        while current:
            max_value = max(max_value, max(current.queue))
            current = current.next
        return max_value

    def find_min(self):
        """큐 내 최솟값 반환"""
        if not self.head.queue:
            raise ValueError("큐가 비어 있습니다.")
        min_value = float('inf')
        current = self.head
        while current:
            min_value = min(min_value, min(current.queue))
            current = current.next
        return min_value

    def find_element(self, value):
        """특정 값을 가진 요소의 인덱스 반환"""
        index = 0
        current = self.head
        while current:
            if value in current.queue:
                return index + current.queue.index(value)
            index += len(current.queue)
            current = current.next
        return -1

    def print_reverse(self):
        """큐의 모든 요소 역순 출력"""
        current = self.tail
        while current:
            print(current.queue[::-1], end=" <- ")
            current = current.prev
        print("None")

    def depth(self):
        """연결된 노드의 총 개수 반환"""
        depth = 0
        current = self.head
        while current:
            depth += 1
            current = current.next
        return depth

    def delete_element(self, value):
        """큐에서 특정 값을 삭제"""
        current = self.head
        while current:
            current.queue = [v for v in current.queue if v != value]
            current = current.next

    def calculate_average(self):
        """큐 내 모든 요소의 평균값 반환"""
        total_sum = self.sum_queue()
        total_elements = self.total_size()
        if total_elements == 0:
            raise ValueError("큐가 비어 있습니다.")
        return total_sum / total_elements

    def remove_duplicates(self):
        """큐에서 중복된 요소 제거"""
        seen = set()
        current = self.head
        while current:
            new_queue = []
            for value in current.queue:
                if value not in seen:
                    seen.add(value)
                    new_queue.append(value)
            current.queue = new_queue
            current = current.next

    def delete_in_range(self, min_value, max_value):
        """큐에서 특정 값 범위 삭제"""
        current = self.head
        while current:
            current.queue = [v for v in current.queue if v < min_value or v > max_value]
            current = current.next


# 메인 함수
def main():
    queue = LinkedListQueue(3)

    # 1. Enqueue 테스트
    print("1. Enqueue Test:")
    for i in range(1, 11):
        queue.enqueue(i)
    queue.print_queue()

    # 2. Pop 테스트
    print("\n2. Pop Test:")
    print("Popped:", queue.pop())
    queue.print_queue()

    # 3. Pop and Shift 테스트
    print("\n3. Pop and Shift Test:")
    print("Popped and Shifted:", queue.pop_and_shift())
    queue.print_queue()

    # 4. Peek 테스트
    print("\n4. Peek Test:")
    print("Peeked Value:", queue.peek())

    # 5. Total Size 테스트
    print("\n5. Total Size Test:")
    print("Total Size:", queue.total_size())

    # 6. Get Element At 테스트
    print("\n6. Get Element At Test:")
    print("Element at index 3:", queue.get_element_at(3))

    # 7. Merge Queues 테스트
    print("\n7. Merge Queues Test:")
    other_queue = LinkedListQueue(3)
    for i in range(20, 23):
        other_queue.enqueue(i)
    queue.merge_queues(other_queue)
    queue.print_queue()

    # 8. Sum Queue 테스트
    print("\n8. Sum Queue Test:")
    print("Sum of Queue:", queue.sum_queue())

    # 9. Find Max 테스트
    print("\n9. Find Max Test:")
    print("Max Value:", queue.find_max())

    # 10. Find Min 테스트
    print("\n10. Find Min Test:")
    print("Min Value:", queue.find_min())

    # 11. Find Element 테스트
    print("\n11. Find Element Test:")
    print("Index of Element 7:", queue.find_element(7))

    # 12. Print Reverse 테스트
    print("\n12. Print Reverse Test:")
    queue.print_reverse()

    # 13. Depth 테스트
    print("\n13. Depth Test:")
    print("Depth of Queue:", queue.depth())

    # 14. Delete Element 테스트
    print("\n14. Delete Element Test:")
    queue.delete_element(4)
    queue.print_queue()

    # 15. Calculate Average 테스트
    print("\n15. Calculate Average Test:")
    print("Average of Queue:", queue.calculate_average())

    # 16. Remove Duplicates 테스트
    print("\n16. Remove Duplicates Test:")
    queue.enqueue(5)
    queue.enqueue(7)
    queue.enqueue(7)
    queue.remove_duplicates()
    queue.print_queue()

    # 17. Delete in Range 테스트
    print("\n17. Delete in Range Test:")
    queue.delete_in_range(2, 6)
    queue.print_queue()


# 실행
if __name__ == "__main__":
    main()

