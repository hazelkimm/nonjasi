# append: 끝에 노드 추가.
# prepend: 처음에 노드 추가.
# insert_after: 특정 값 뒤에 노드 삽입.
# delete: 특정 값을 가진 노드 삭제.
# search: 특정 값을 가진 노드 검색.
# size: 리스트의 크기 반환.
# reverse: 리스트를 뒤집음.
# print_list: 리스트를 보기 좋게 출력.
# has_cycle: 리스트에 사이클이 있는지 확인.
# remove_duplicates: 중복 노드 제거.
# find_nth_to_last: 끝에서 n번째 노드 찾기.
# Sorting: Bubble Sort, Selection Sort, Insertion Sort, Merge Sort, Quick Sort

class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class SinglyLinkedList:
    def __init__(self):
        self.head = None

    # 1. Append a node at the end
    def append(self, data):
        new_node = Node(data)
        if not self.head:
            self.head = new_node
            return
        current = self.head
        while current.next:
            current = current.next
        current.next = new_node

    # 2. Prepend a node at the beginning
    def prepend(self, data):
        new_node = Node(data)
        new_node.next = self.head
        self.head = new_node

    # 3. Insert a node after a specific node
    def insert_after(self, prev_data, data):
        current = self.head
        while current and current.data != prev_data:
            current = current.next
        if current is None:
            raise ValueError(f"Node with data {prev_data} not found.")
        new_node = Node(data)
        new_node.next = current.next
        current.next = new_node

    # 4. Delete a node by value
    def delete(self, data):
        if not self.head:
            return
        if self.head.data == data:
            self.head = self.head.next
            return
        current = self.head
        while current.next and current.next.data != data:
            current = current.next
        if current.next is None:
            raise ValueError(f"Node with data {data} not found.")
        current.next = current.next.next

    # 5. Search for a node by value
    def search(self, data):
        current = self.head
        while current:
            if current.data == data:
                return True
            current = current.next
        return False

    # 6. Get size of the linked list
    def size(self):
        count = 0
        current = self.head
        while current:
            count += 1
            current = current.next
        return count

    # 7. Reverse the linked list
    def reverse(self):
        prev = None
        current = self.head
        while current:
            next_node = current.next
            current.next = prev
            prev = current
            current = next_node
        self.head = prev

    # 8. Print the linked list
    def print_list(self):
        current = self.head
        result = []
        while current:
            result.append(current.data)
            current = current.next
        print(" -> ".join(map(str, result)))

    # 9. Detect a cycle in the linked list
    def has_cycle(self):
        slow, fast = self.head, self.head
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
            if slow == fast:
                return True
        return False

    # 10. Remove duplicates
    def remove_duplicates(self):
        current = self.head
        seen = set()
        prev = None
        while current:
            if current.data in seen:
                prev.next = current.next
            else:
                seen.add(current.data)
                prev = current
            current = current.next

    # 11. Find the nth-to-last node
    def find_nth_to_last(self, n):
        slow = self.head
        fast = self.head
        for _ in range(n):
            if not fast:
                raise ValueError(f"List has fewer than {n} elements.")
            fast = fast.next
        while fast:
            slow = slow.next
            fast = fast.next
        return slow.data

    # 12. Merge two sorted linked lists (static method)
    @staticmethod
    def merge_sorted(l1, l2):
        dummy = Node(0)
        current = dummy
        while l1 and l2:
            if l1.data < l2.data:
                current.next = l1
                l1 = l1.next
            else:
                current.next = l2
                l2 = l2.next
            current = current.next
        current.next = l1 or l2
        return dummy.next
    
    # Bubble Sort
    def bubble_sort(self):
        if not self.head or not self.head.next:
            return

        end = None
        while end != self.head:
            current = self.head
            while current.next != end:
                next_node = current.next
                if current.data > next_node.data:
                    current.data, next_node.data = next_node.data, current.data
                current = current.next
            end = current

    # Selection Sort
    def selection_sort(self):
        current = self.head

        while current:
            min_node = current
            next_node = current.next

            while next_node:
                if next_node.data < min_node.data:
                    min_node = next_node
                next_node = next_node.next

            # Swap data
            if min_node != current:
                current.data, min_node.data = min_node.data, current.data

            current = current.next

    # Insertion Sort
    def insertion_sort(self):
        if not self.head or not self.head.next:
            return

        sorted_list = None
        current = self.head

        while current:
            next_node = current.next
            if not sorted_list or sorted_list.data >= current.data:
                current.next = sorted_list
                sorted_list = current
            else:
                temp = sorted_list
                while temp.next and temp.next.data < current.data:
                    temp = temp.next
                current.next = temp.next
                temp.next = current
            current = next_node

        self.head = sorted_list

    # Merge Sort
    def merge_sort(self):
        if not self.head or not self.head.next:
            return

        def split(head):
            slow = head
            fast = head.next
            while fast and fast.next:
                slow = slow.next
                fast = fast.next.next
            middle = slow.next
            slow.next = None
            return head, middle

        def merge(left, right):
            dummy = Node(0)
            tail = dummy
            while left and right:
                if left.data <= right.data:
                    tail.next = left
                    left = left.next
                else:
                    tail.next = right
                    right = right.next
                tail = tail.next
            tail.next = left or right
            return dummy.next

        def merge_sort_rec(head):
            if not head or not head.next:
                return head
            left, right = split(head)
            left = merge_sort_rec(left)
            right = merge_sort_rec(right)
            return merge(left, right)

        self.head = merge_sort_rec(self.head)

    # Quick Sort
    def quick_sort(self):
        def partition(start, end):
            pivot = start
            current = start.next
            tail = pivot

            while current != end:
                next_node = current.next
                if current.data < pivot.data:
                    # Move current to the front of the partition
                    tail.next = current.next
                    current.next = start
                    start = current
                else:
                    tail = current
                current = next_node

            return pivot, start

        def quick_sort_rec(start, end):
            if start == end or start.next == end:
                return start

            pivot, new_head = partition(start, end)
            pivot.next = quick_sort_rec(pivot.next, end)
            return quick_sort_rec(new_head, pivot)

        self.head = quick_sort_rec(self.head, None)

def main():
    # 새로운 SinglyLinkedList 생성
    ll = SinglyLinkedList()

    # 1. Append: 끝에 노드 추가
    ll.append(1)
    ll.append(2)
    ll.append(3)
    print("After append operations (1, 2, 3):")
    ll.print_list()  # Output: 1 -> 2 -> 3

    # 2. Prepend: 처음에 노드 추가
    ll.prepend(0)
    print("\nAfter prepend operation (0):")
    ll.print_list()  # Output: 0 -> 1 -> 2 -> 3

    # 3. Insert After: 특정 값 뒤에 노드 삽입
    ll.insert_after(2, 4)
    print("\nAfter inserting 4 after 2:")
    ll.print_list()  # Output: 0 -> 1 -> 2 -> 4 -> 3

    # 4. Delete: 특정 값을 가진 노드 삭제
    ll.delete(2)
    print("\nAfter deleting 2:")
    ll.print_list()  # Output: 0 -> 1 -> 4 -> 3

    # 5. Search: 특정 값을 가진 노드 검색
    print("\nSearch for 4:", ll.search(4))  # Output: True
    print("Search for 2:", ll.search(2))    # Output: False

    # 6. Size: 리스트의 크기 반환
    print("\nSize of the list:", ll.size())  # Output: 4

    # 7. Reverse: 리스트를 뒤집음
    ll.reverse()
    print("\nAfter reversing the list:")
    ll.print_list()  # Output: 3 -> 4 -> 1 -> 0

    # 8. Remove Duplicates: 중복 노드 제거
    ll.append(4)
    ll.append(3)
    print("\nAfter adding duplicates (4, 3):")
    ll.print_list()  # Output: 3 -> 4 -> 1 -> 0 -> 4 -> 3

    ll.remove_duplicates()
    print("\nAfter removing duplicates:")
    ll.print_list()  # Output: 3 -> 4 -> 1 -> 0

    # 9. Find Nth-to-Last Node: 끝에서 n번째 노드 찾기
    print("\n2nd-to-last node:", ll.find_nth_to_last(2))  # Output: 1

    # 10. Check for Cycle: 사이클 확인
    print("\nCheck if the list has a cycle:", ll.has_cycle())  # Output: False

    # 11. Sorting Examples
    # 재정렬을 위해 리스트 초기화
    ll = SinglyLinkedList()
    ll.append(3)
    ll.append(1)
    ll.append(4)
    ll.append(2)

    print("\nUnsorted list:")
    ll.print_list()  # Output: 3 -> 1 -> 4 -> 2

    # Bubble Sort
    ll.bubble_sort()
    print("\nAfter Bubble Sort:")
    ll.print_list()  # Output: 1 -> 2 -> 3 -> 4

    # 다시 정렬되지 않은 리스트로 초기화
    ll = SinglyLinkedList()
    ll.append(4)
    ll.append(3)
    ll.append(1)
    ll.append(2)

    # Selection Sort
    ll.selection_sort()
    print("\nAfter Selection Sort:")
    ll.print_list()  # Output: 1 -> 2 -> 3 -> 4

    # 다시 정렬되지 않은 리스트로 초기화
    ll = SinglyLinkedList()
    ll.append(3)
    ll.append(4)
    ll.append(1)
    ll.append(2)

    # Insertion Sort
    ll.insertion_sort()
    print("\nAfter Insertion Sort:")
    ll.print_list()  # Output: 1 -> 2 -> 3 -> 4

    # 다시 정렬되지 않은 리스트로 초기화
    ll = SinglyLinkedList()
    ll.append(4)
    ll.append(2)
    ll.append(1)
    ll.append(3)

    # Merge Sort
    ll.merge_sort()
    print("\nAfter Merge Sort:")
    ll.print_list()  # Output: 1 -> 2 -> 3 -> 4

    # 다시 정렬되지 않은 리스트로 초기화
    ll = SinglyLinkedList()
    ll.append(3)
    ll.append(1)
    ll.append(4)
    ll.append(2)

    # Quick Sort
    ll.quick_sort()
    print("\nAfter Quick Sort:")
    ll.print_list()  # Output: 1 -> 2 -> 3 -> 4

    # 12. Merge Two Sorted Lists
    print("\nMerging two sorted lists:")
    list1 = SinglyLinkedList()
    list1.append(1)
    list1.append(3)
    list1.append(5)

    list2 = SinglyLinkedList()
    list2.append(2)
    list2.append(4)
    list2.append(6)

    merged_head = SinglyLinkedList.merge_sorted(list1.head, list2.head)
    merged_list = SinglyLinkedList()
    merged_list.head = merged_head

    merged_list.print_list()  # Output: 1 -> 2 -> 3 -> 4 -> 5 -> 6


if __name__ == "__main__":
    main()