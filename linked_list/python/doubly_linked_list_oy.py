# 1. Node 클래스 및 DoublyLinkedList 클래스 초기화
#    - 노드와 이중 연결 리스트 초기화
# 2. insert_at_index
#    - 특정 인덱스에 노드를 삽입하는 함수
# 3. delete_at_index
#    - 특정 인덱스의 노드를 삭제하는 함수
# 4. find
#    - 리스트에서 특정 값이 처음 나타나는 위치(인덱스)를 반환하는 함수
# 5. delete_value
#    - 특정 값을 가진 노드를 삭제하는 함수 (값을 기준으로 삭제)
# 6. swap_nodes
#    - 두 인덱스의 노드를 스왑하는 함수
# 7. length
#    - 이중 연결 리스트의 길이를 반환하는 함수
# 8. contains
#    - 이중 연결 리스트에서 특정 값이 있는지 확인하는 함수
# 9. nth_from_end
#    - 이중 연결 리스트에서 끝에서 n번째 노드를 반환하는 함수
# 10. get_middle
#     - 이중 연결 리스트의 중간 지점을 찾는 함수
# 11. reverse
#     - 이중 연결 리스트를 역순으로 만드는 함수
# 12. reverse_in_groups
#     - 주어진 크기(k)로 리스트를 그룹화하여 각 그룹을 역순으로 만드는 함수
# 13. remove_duplicates
#     - 이중 연결 리스트에서 중복된 노드를 제거하는 함수
# 14. pop_last
#     - 이중 연결 리스트에서 마지막 노드를 반환하고 삭제하는 함수
# 15. slice_range
#     - 이중 연결 리스트에서 특정 범위를 슬라이싱해서 반환하는 함수
# 16. bubble_sort
#     - 버블 정렬로 이중 연결 리스트를 정렬하는 함수
# 17. insertion_sort
#     - 삽입 정렬로 이중 연결 리스트를 정렬하는 함수
# 18. selection_sort
#     - 선택 정렬로 이중 연결 리스트를 정렬하는 함수
# 19. merge_sort
#     - 병합 정렬로 이중 연결 리스트를 정렬하는 함수
# 20. detect_cycle
#     - 이중 연결 리스트에 사이클이 있는지 확인하는 함수
# 21. remove_cycle
#     - 이중 연결 리스트에서 사이클이 존재할 경우, 이를 제거하는 함수
# 22. append_list
#     - 다른 이중 연결 리스트를 현재 리스트의 끝에 추가하는 함수
# 23. sorted_insert_in_sorted_list
#     - 정렬된 이중 연결 리스트에 새로운 노드를 올바른 위치에 삽입하는 함수

class Node:
    def __init__(self, data):
        self.data = data
        self.next = None
        self.prev = None  # 추가된 prev 포인터


class DoublyLinkedList:
    def __init__(self):
        self.head = None

    # 2. 특정 인덱스에 값을 가진 노드 삽입하는 함수
    def insert_at_index(self, index, data):
        if index < 0 or index > self.length():
            raise IndexError("Index out of bounds")

        new_node = Node(data)

        if index == 0:
            new_node.next = self.head
            if self.head:
                self.head.prev = new_node
            self.head = new_node
        else:
            current = self.head
            for _ in range(index - 1):
                current = current.next
            new_node.next = current.next
            new_node.prev = current
            if current.next:
                current.next.prev = new_node
            current.next = new_node

    # 3. 특정 인덱스의 노드를 삭제하는 함수
    def delete_at_index(self, index):
        if index < 0 or index >= self.length():
            raise IndexError("Index out of bounds")

        if index == 0:
            if self.head:
                self.head = self.head.next
                if self.head:
                    self.head.prev = None
        else:
            current = self.head
            for _ in range(index - 1):
                current = current.next
            current.next = current.next.next
            if current.next:
                current.next.prev = current

    # 4. 리스트에서 특정 값이 처음 나타나는 위치(인덱스)를 반환하는 함수
    def find(self, data):
        current = self.head
        index = 0
        while current:
            if current.data == data:
                return index
            current = current.next
            index += 1
        return -1  # 값이 리스트에 없을 경우

    # 5. 특정 값을 가진 노드를 삭제하는 함수 (값을 기준으로 삭제)
    def delete_value(self, data):
        current = self.head
        while current:
            if current.data == data:
                if current.prev:
                    current.prev.next = current.next
                if current.next:
                    current.next.prev = current.prev
                if current == self.head:
                    self.head = current.next
                return True  # 삭제 성공
            current = current.next
        return False  # 값이 리스트에 없을 경우

    # 6. 두 인덱스의 노드 스왑하는 함수
    def swap_nodes(self, index1, index2):
        if index1 == index2:
            return

        if index1 > index2:
            index1, index2 = index2, index1

        node1 = self.head
        node2 = self.head

        for _ in range(index1):
            node1 = node1.next
        for _ in range(index2):
            node2 = node2.next

        if node1.prev:
            node1.prev.next = node2
        if node2.next:
            node2.next.prev = node1

        node1.next, node2.next = node2.next, node1.next
        node1.prev, node2.prev = node2.prev, node1.prev

        if node1.next:
            node1.next.prev = node1
        if node2.prev:
            node2.prev.next = node2

        if index1 == 0:
            self.head = node2
        elif index2 == 0:
            self.head = node1

    # 7. 리스트 길이 리턴하는 함수
    def length(self):
        count = 0
        current = self.head
        while current:
            count += 1
            current = current.next
        return count

    # 8. 리스트에서 특정 값의 노드 존재 여부 확인 함수
    def contains(self, data):
        current = self.head
        while current:
            if current.data == data:
                return True
            current = current.next
        return False

    # 9. 리스트에서 n번째 마지막 노드 반환 함수
    def nth_from_end(self, n):
        length = self.length()
        if n > length or n <= 0:
            return None

        current = self.head
        for _ in range(length - n):
            current = current.next
        return current.data

    # 10. 중간 지점 찾기 함수
    def get_middle(self):
        if self.head is None:
            return None

        slow, fast = self.head, self.head
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next

        return slow

    # 11. 리스트를 역순으로 만드는 함수
    def reverse(self):
        current = self.head
        prev = None
        while current:
            next_node = current.next
            current.next = prev
            current.prev = next_node
            prev = current
            current = next_node

        self.head = prev

    # 12. 주어진 크기(k)로 리스트를 그룹화하여 각 그룹을 역순으로 만드는 함수
    def reverse_in_groups(self, k):
        def reverse_k_nodes(start, k):
            prev = None
            current = start
            count = 0
            while current and count < k:
                next_node = current.next
                current.next = prev
                current.prev = next_node
                prev = current
                current = next_node
                count += 1
            return prev, current

        new_head = None
        prev_end = None
        current = self.head

        while current:
            group_start = current
            new_start, next_group_start = reverse_k_nodes(group_start, k)

            if not new_head:
                new_head = new_start

            if prev_end:
                prev_end.next = new_start
                if new_start:
                    new_start.prev = prev_end

            prev_end = group_start
            current = next_group_start

        self.head = new_head

    # 13. 리스트에서 중복 노드 제거 함수
    def remove_duplicates(self):
        current = self.head
        while current and current.next:
            if current.data == current.next.data:
                current.next = current.next.next
                if current.next:
                    current.next.prev = current
            else:
                current = current.next

    # 14. 리스트에서 마지막 노드를 반환하고 삭제하는 함수
    def pop_last(self):
        if not self.head:
            return None

        current = self.head
        while current.next:
            current = current.next

        if current.prev:
            current.prev.next = None
        else:
            self.head = None

        return current.data

    # 15. 범위 슬라이싱 함수
    def slice_range(self, start, end):
        if start < 0 or end > self.length() or start > end:
            raise IndexError("Index out of bounds")

        sliced_list = DoublyLinkedList()
        current = self.head
        for _ in range(start):
            current = current.next

        for _ in range(end - start):
            sliced_list.insert_at_index(_, current.data)
            current = current.next

        return sliced_list

    # 16. 버블 정렬 함수
    def bubble_sort(self):
        end = None
        while end != self.head:
            current = self.head
            while current.next != end:
                next_node = current.next
                if current.data > next_node.data:
                    current.data, next_node.data = next_node.data, current.data
                current = next_node
            end = current

    # 17. 삽입 정렬 함수
    def insertion_sort(self):
        sorted_list = None
        current = self.head

        while current:
            next_node = current.next
            sorted_list = self.sorted_insert(sorted_list, current)
            current = next_node

        self.head = sorted_list

    def sorted_insert(self, sorted_list, new_node):
        if not sorted_list or new_node.data < sorted_list.data:
            new_node.next = sorted_list
            if sorted_list:
                sorted_list.prev = new_node
            return new_node

        current = sorted_list
        while current.next and current.next.data < new_node.data:
            current = current.next

        new_node.next = current.next
        new_node.prev = current
        if current.next:
            current.next.prev = new_node
        current.next = new_node
        return sorted_list

    # 18. 선택 정렬 함수
    def selection_sort(self):
        current = self.head

        while current:
            min_node = current
            next_node = current.next
            while next_node:
                if next_node.data < min_node.data:
                    min_node = next_node
                next_node = next_node.next

            current.data, min_node.data = min_node.data, current.data
            current = current.next

    # 19. 병합 정렬 함수
    def merge_sort(self):
        if not self.head or not self.head.next:
            return self.head

        middle = self.get_middle()
        next_to_middle = middle.next
        middle.next = None
        if next_to_middle:
            next_to_middle.prev = None

        left = self.merge_sort_list(self.head)
        right = self.merge_sort_list(next_to_middle)

        sorted_list = self.sorted_merge(left, right)
        self.head = sorted_list

    def merge_sort_list(self, head):
        if not head or not head.next:
            return head

        middle = self.get_middle()
        next_to_middle = middle.next
        middle.next = None
        if next_to_middle:
            next_to_middle.prev = None

        left = self.merge_sort_list(head)
        right = self.merge_sort_list(next_to_middle)

        return self.sorted_merge(left, right)

    def sorted_merge(self, left, right):
        if not left:
            return right
        if not right:
            return left

        if left.data <= right.data:
            left.next = self.sorted_merge(left.next, right)
            left.next.prev = left
            left.prev = None
            return left
        else:
            right.next = self.sorted_merge(left, right.next)
            right.next.prev = right
            right.prev = None
            return right

    # 20. 링크드 리스트에 사이클이 있는지 확인하는 함수 (Floyd's Cycle-Finding Algorithm)
    def detect_cycle(self):
        slow = self.head
        fast = self.head

        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
            if slow == fast:
                return True  # 사이클 발견
        return False  # 사이클 없음

    # 21. 링크드 리스트에서 사이클이 존재할 경우, 이를 제거하는 함수
    def remove_cycle(self):
        if self.head is None:
            return

        slow = self.head
        fast = self.head

        # 첫 번째 충돌점 찾기
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
            if slow == fast:
                break

        if slow == fast:
            slow = self.head
            while slow.next != fast.next:
                slow = slow.next
                fast = fast.next
            fast.next = None  # 사이클 제거

    # 22. 다른 링크드 리스트를 현재 리스트의 끝에 추가하는 함수
    def append_list(self, other_list):
        if self.head is None:
            self.head = other_list.head
        else:
            current = self.head
            while current.next:
                current = current.next
            current.next = other_list.head
            if other_list.head:
                other_list.head.prev = current

    # 23. 정렬된 링크드 리스트에 새로운 노드를 올바른 위치에 삽입하는 함수
    def sorted_insert_in_sorted_list(self, data):
        new_node = Node(data)

        if self.head is None or self.head.data >= new_node.data:
            new_node.next = self.head
            if self.head:
                self.head.prev = new_node
            self.head = new_node
        else:
            current = self.head
            while current.next and current.next.data < new_node.data:
                current = current.next
            new_node.next = current.next
            new_node.prev = current
            if current.next:
                current.next.prev = new_node
            current.next = new_node


# 테스트 코드
if __name__ == "__main__":
    dll = DoublyLinkedList()
    dll.insert_at_index(0, 3)
    dll.insert_at_index(1, 1)
    dll.insert_at_index(2, 2)
    dll.insert_at_index(3, 5)
    dll.insert_at_index(4, 4)

    print("Original List:")
    dll.print_list()

    print("Reversed List:")
    dll.reverse()
    dll.print_list()

    print("Bubble Sort:")
    dll.bubble_sort()
    dll.print_list()

    print("Insertion Sort:")
    dll.insertion_sort()
    dll.print_list()

    print("Selection Sort:")
    dll.selection_sort()
    dll.print_list()

    print("Swapping index 1 and 3:")
    dll.swap_nodes(1, 3)
    dll.print_list()

    print("Length of the list:", dll.length())

    print("Middle of the list:", dll.get_middle().data)

    print("Merge Sort:")
    dll.merge_sort()
    dll.print_list()

    print("Slice from index 1 to 4:")
    sliced_dll = dll.slice_range(1, 4)
    sliced_dll.print_list()

    print("Deleting node at index 2:")
    dll.delete_at_index(2)
    dll.print_list()

    print("Checking if list contains value 5:", dll.contains(5))

    print("Removing duplicates:")
    dll.remove_duplicates()
    dll.print_list()

    print("Popping last node:", dll.pop_last())
    dll.print_list()

    print("2nd node from the end:", dll.nth_from_end(2))
