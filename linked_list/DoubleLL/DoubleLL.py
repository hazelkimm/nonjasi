# append: 끝에 노드 추가.
# prepend: 처음에 노드 추가.
# insert_after: 특정 노드 뒤에 삽입.
# delete: 특정 값을 가진 노드 삭제.
# search: 특정 값을 가진 노드 검색.
# size: 리스트의 노드 수 반환.
# reverse: 리스트 뒤집기.
# print_list: 리스트 출력.
# print_reverse: 역순으로 리스트 출력.
# remove_duplicates: 중복 값 제거.
# find_nth_to_last: 끝에서 n번째 노드 반환.
# clear: 리스트 비우기.
# Sorting: Bubble Sort, Selection Sort, Insertion Sort, Merge Sort, Quick Sort

class Node:
    def __init__(self, data):
        self.data = data
        self.next = None
        self.prev = None

class DoublyLinkedList:
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
        new_node.prev = current

    # 2. Prepend a node at the beginning
    def prepend(self, data):
        new_node = Node(data)
        if not self.head:
            self.head = new_node
            return
        new_node.next = self.head
        self.head.prev = new_node
        self.head = new_node

    # 3. Insert a node after a specific node
    def insert_after(self, target_data, data):
        current = self.head
        while current and current.data != target_data:
            current = current.next
        if not current:
            raise ValueError(f"Node with data {target_data} not found.")
        new_node = Node(data)
        new_node.next = current.next
        new_node.prev = current
        if current.next:
            current.next.prev = new_node
        current.next = new_node

    # 4. Delete a node by value
    def delete(self, data):
        if not self.head:
            raise ValueError("List is empty.")
        if self.head.data == data:
            self.head = self.head.next
            if self.head:
                self.head.prev = None
            return
        current = self.head
        while current and current.data != data:
            current = current.next
        if not current:
            raise ValueError(f"Node with data {data} not found.")
        if current.next:
            current.next.prev = current.prev
        if current.prev:
            current.prev.next = current.next

    # 5. Search for a node by value
    def search(self, data):
        current = self.head
        while current:
            if current.data == data:
                return True
            current = current.next
        return False

    # 6. Get size of the doubly linked list
    def size(self):
        count = 0
        current = self.head
        while current:
            count += 1
            current = current.next
        return count

    # 7. Reverse the doubly linked list
    def reverse(self):
        current = self.head
        prev_node = None
        while current:
            next_node = current.next
            current.next = prev_node
            current.prev = next_node
            prev_node = current
            current = next_node
        self.head = prev_node

    # 8. Print the linked list
    def print_list(self):
        current = self.head
        result = []
        while current:
            result.append(current.data)
            current = current.next
        print(" -> ".join(map(str, result)))

    # 9. Print the linked list in reverse order
    def print_reverse(self):
        current = self.head
        if not current:
            print("List is empty.")
            return
        while current.next:
            current = current.next
        result = []
        while current:
            result.append(current.data)
            current = current.prev
        print(" <- ".join(map(str, result)))

    # 10. Remove duplicates
    def remove_duplicates(self):
        current = self.head
        seen = set()
        while current:
            if current.data in seen:
                next_node = current.next
                self.delete(current.data)
                current = next_node
            else:
                seen.add(current.data)
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

    # 12. Clear the list
    def clear(self):
        self.head = None
    
    # Bubble Sort for the doubly linked list
    def bubble_sort(self):
        if not self.head or not self.head.next:
            return

        swapped = True
        while swapped:
            swapped = False
            current = self.head
            while current.next:
                if current.data > current.next.data:
                    current.data, current.next.data = current.next.data, current.data
                    swapped = True
                current = current.next

    # Selection Sort for the doubly linked list
    def selection_sort(self):
        if not self.head or not self.head.next:
            return

        current = self.head
        while current:
            min_node = current
            next_node = current.next

            while next_node:
                if next_node.data < min_node.data:
                    min_node = next_node
                next_node = next_node.next

            if min_node != current:
                current.data, min_node.data = min_node.data, current.data

            current = current.next

    # Insertion Sort for the doubly linked list
    def insertion_sort(self):
        if not self.head or not self.head.next:
            return

        current = self.head.next
        while current:
            key = current.data
            prev = current.prev
            while prev and prev.data > key:
                prev.next.data = prev.data
                prev = prev.prev
            if prev:
                prev.next.data = key
            else:
                self.head.data = key
            current = current.next

    # Merge Sort for the doubly linked list
    def merge_sort(self):
        if not self.head or not self.head.next:
            return

        def split(head):
            slow = head
            fast = head.next
            while fast and fast.next:
                slow = slow.next
                fast = fast.next.next
            mid = slow.next
            slow.next = None
            if mid:
                mid.prev = None
            return head, mid

        def merge(left, right):
            dummy = Node(0)
            tail = dummy
            while left and right:
                if left.data <= right.data:
                    tail.next = left
                    left.prev = tail
                    left = left.next
                else:
                    tail.next = right
                    right.prev = tail
                    right = right.next
                tail = tail.next
            tail.next = left or right
            if tail.next:
                tail.next.prev = tail
            return dummy.next

        def merge_sort_rec(head):
            if not head or not head.next:
                return head
            left, right = split(head)
            left = merge_sort_rec(left)
            right = merge_sort_rec(right)
            return merge(left, right)

        self.head = merge_sort_rec(self.head)

    # Quick Sort for the doubly linked list
    def quick_sort(self):
        def partition(low, high):
            pivot = high.data
            i = low.prev

            current = low
            while current != high:
                if current.data <= pivot:
                    i = low if i is None else i.next
                    i.data, current.data = current.data, i.data
                current = current.next

            i = low if i is None else i.next
            i.data, high.data = high.data, i.data
            return i

        def quick_sort_rec(low, high):
            if low and high and low != high and low != high.next:
                pivot = partition(low, high)
                quick_sort_rec(low, pivot.prev)
                quick_sort_rec(pivot.next, high)

        if self.head:
            tail = self.head
            while tail.next:
                tail = tail.next
            quick_sort_rec(self.head, tail)

def main():
    # 새로운 DoublyLinkedList 생성
    dll = DoublyLinkedList()

    # 1. Append: 끝에 노드 추가
    dll.append(1)
    dll.append(2)
    dll.append(3)
    print("After append operations (1, 2, 3):")
    dll.print_list()  # Output: 1 -> 2 -> 3

    # 2. Prepend: 처음에 노드 추가
    dll.prepend(0)
    print("\nAfter prepend operation (0):")
    dll.print_list()  # Output: 0 -> 1 -> 2 -> 3

    # 3. Insert After: 특정 노드 뒤에 삽입
    dll.insert_after(2, 2.5)
    print("\nAfter inserting 2.5 after 2:")
    dll.print_list()  # Output: 0 -> 1 -> 2 -> 2.5 -> 3

    # 4. Delete: 특정 값을 가진 노드 삭제
    dll.delete(2.5)
    print("\nAfter deleting 2.5:")
    dll.print_list()  # Output: 0 -> 1 -> 2 -> 3

    # 5. Search: 특정 값을 가진 노드 검색
    print("\nSearch for 2:", dll.search(2))    # Output: True
    print("Search for 4:", dll.search(4))      # Output: False

    # 6. Size: 리스트의 노드 수 반환
    print("\nSize of the list:", dll.size())  # Output: 4

    # 7. Reverse: 리스트 뒤집기
    dll.reverse()
    print("\nAfter reversing the list:")
    dll.print_list()  # Output: 3 -> 2 -> 1 -> 0

    # 8. Print the list in reverse order
    print("\nPrint the list in reverse order:")
    dll.print_reverse()  # Output: 0 <- 1 <- 2 <- 3

    # 9. Remove Duplicates
    dll.append(2)
    dll.append(3)
    print("\nAfter adding duplicates (2, 3):")
    dll.print_list()  # Output: 3 -> 2 -> 1 -> 0 -> 2 -> 3

    dll.remove_duplicates()
    print("\nAfter removing duplicates:")
    dll.print_list()  # Output: 3 -> 2 -> 1 -> 0

    # 10. Find Nth-to-Last Node
    print("\n2nd-to-last node:", dll.find_nth_to_last(2))  # Output: 1

    # 11. Clear the list
    dll.clear()
    print("\nAfter clearing the list:")
    dll.print_list()  # Output: List is empty.

    # 12. Sorting Examples
    # 리스트 초기화 및 노드 추가
    dll.append(4)
    dll.append(2)
    dll.append(1)
    dll.append(3)

    print("\nUnsorted list:")
    dll.print_list()  # Output: 4 -> 2 -> 1 -> 3

    # Bubble Sort
    dll.bubble_sort()
    print("\nAfter Bubble Sort:")
    dll.print_list()  # Output: 1 -> 2 -> 3 -> 4

    # 다시 정렬되지 않은 리스트로 초기화
    dll = DoublyLinkedList()
    dll.append(3)
    dll.append(1)
    dll.append(4)
    dll.append(2)

    # Selection Sort
    dll.selection_sort()
    print("\nAfter Selection Sort:")
    dll.print_list()  # Output: 1 -> 2 -> 3 -> 4

    # 다시 정렬되지 않은 리스트로 초기화
    dll = DoublyLinkedList()
    dll.append(4)
    dll.append(3)
    dll.append(2)
    dll.append(1)

    # Insertion Sort
    dll.insertion_sort()
    print("\nAfter Insertion Sort:")
    dll.print_list()  # Output: 1 -> 2 -> 3 -> 4

    # 다시 정렬되지 않은 리스트로 초기화
    dll = DoublyLinkedList()
    dll.append(4)
    dll.append(1)
    dll.append(3)
    dll.append(2)

    # Merge Sort
    dll.merge_sort()
    print("\nAfter Merge Sort:")
    dll.print_list()  # Output: 1 -> 2 -> 3 -> 4

    # 다시 정렬되지 않은 리스트로 초기화
    dll = DoublyLinkedList()
    dll.append(2)
    dll.append(4)
    dll.append(1)
    dll.append(3)

    # Quick Sort
    dll.quick_sort()
    print("\nAfter Quick Sort:")
    dll.print_list()  # Output: 1 -> 2 -> 3 -> 4

if __name__ == "__main__":
    main()
