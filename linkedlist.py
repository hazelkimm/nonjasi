class Node:
    def __init__(self, data):
        self.data = data
        self.next = None


class LList:
    def __init__(self):
        self.size = 0
        self.head = None
        self.tail = None

    # Print the size
    def get_size(self):
        return self.size

    def is_empty(self):
        return self.size == 0
    
    def clear(self):
        self.head = self.tail = None
        self.size = 0

    def get_first(self):
        return self.head.data if self.head else None

    def get_last(self):
        return self.tail.data if self.tail else None

    # Print the linked list
    def print_list(self):
        cur = self.head
        while cur:
            print(cur.data, end=" ")
            cur = cur.next
        print()

    # Insert node at the beginning of the list
    def add_first(self, item):
        temp = Node(item)
        temp.next = self.head
        if self.head is None:
            self.tail = temp
        self.head = temp
        self.size += 1
    
    # Insert node before a specific node
    def add_before(self, next_node, item):
        if next_node is None:
            return
        temp = Node(item)
        if self.head == next_node:  # If next_node is head
            temp.next = self.head
            self.head = temp
        else:
            prev = self.head
            while prev and prev.next != next_node:
                prev = prev.next
            if prev:
                temp.next = prev.next
                prev.next = temp
        self.size += 1

    # Insert node after a specific node
    def add_after(self, prev, item):
        if prev is None:
            return
        temp = Node(item)
        temp.next = prev.next
        prev.next = temp
        if temp.next is None:  # If added at the end, update tail
            self.tail = temp
        self.size += 1

    # Get the node at a specific index
    def get_node_by_index(self, index):
        if index < 0:
            return None
        p = self.head
        for i in range(index):
            if p is None:
                return None
            p = p.next
        return p

    # Insert node at a specific index
    def add_by_index(self, index, item):
        if index < 0:
            return self.head

        if index == 0:
            self.add_first(item)
            return self.head

        prev = self.get_node_by_index(index-1)
        if prev:
            self.add_after(prev, item)
        self.size += 1
        return self.head

    # Insert into ordered list
    def add_to_ordered_list(self, item):
        p = self.head
        q = None

        while p and p.data < item:
            q = p
            p = p.next

        if q is None:
            self.add_first(item)
        else:
            self.add_after(q, item)
        

    # Find node of value
    def find_node(self, item):
        cur = self.head
        while cur:
            if cur.data == item:
                return cur
            cur = cur.next
        return None

    # Remove first node
    def remove_first(self):
        if self.head is None:
            return None
        temp = self.head
        self.head = self.head.next
        if self.head is None:
            self.tail = None
        self.size -= 1
        return self.head
    
    # Remove last node
    def remove_last(self):
        if self.tail is None:
            return None
        if self.head == self.tail:  # Only one element
            self.head = self.tail = None
        else:
            prev = self.head
            while prev.next != self.tail:
                prev = prev.next
            prev.next = None
            self.tail = prev
        self.size -= 1
        return self.tail

    # Remove node after a specific node
    def remove_after(self, prv):
        if prv is None or prv.next is None:
            return
        temp = prv.next
        prv.next = temp.next
        if prv.next is None:
            self.tail = prv
        self.size -= 1

    # Remove node by index
    def remove_by_index(self, index):
        if index < 0:
            return self.head

        if index == 0:
            return self.remove_first()

        prev = self.get_node_by_index(index-1)
        if prev and prev.next:
            self.remove_after(prev)
        self.size -= 1
        return self.head

    # Remove node by value
    def remove_by_value(self, item):
        p = self.head
        q = None

        while p and p.data != item:
            q = p
            p = p.next

        if p is None:
            return self.head

        if q is None:
            return self.remove_first()
        else:
            self.remove_after(q)
        return self.head

    # Function to merge two sorted lists
    @staticmethod
    def merge(list1, list2):
        dummy = Node(0)
        tail = dummy

        while list1 and list2:
            if list1.data <= list2.data:
                tail.next = list1
                list1 = list1.next
            else:
                tail.next = list2
                list2 = list2.next
            tail = tail.next

        tail.next = list1 if list1 else list2

        return dummy.next

    # Function to concatenate two lists
    def concat(self, list2):
        if self.head is None:
            self.head = list2.head
            self.tail = list2.tail
            self.size = list2.size
        elif list2.head is None:
            return
        else:
            self.tail.next = list2.head
            self.tail = list2.tail
            self.size += list2.size

    # Function to get the middle node
    def get_mid(self):
        slow = self.head
        fast = self.head.next
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
        return slow

    # Function to sort the list (ascending order)
    def sort(self):
        if self.head is None or self.head.next is None:
            return self.head

        mid = self.get_mid()
        half = mid.next
        mid.next = None

        left_sorted = LList()
        left_sorted.head = self.head
        left_sorted.size = self.size // 2
        right_sorted = LList()
        right_sorted.head = half
        right_sorted.size = self.size - left_sorted.size

        left_sorted.head = left_sorted.sort()
        right_sorted.head = right_sorted.sort()
        self.head = self.merge(left_sorted.head, right_sorted.head)

        cur = self.head
        while cur and cur.next:
            cur = cur.next
        self.tail = cur

        return self.head
    
    def insertion_sort(self):
        if self.head is None or self.head.next is None:
            return
        
        sorted_list = None  # 새로운 정렬된 리스트의 시작 지점
        cur = self.head  # 정렬되지 않은 리스트의 노드를 탐색할 포인터
        
        while cur:
            next_node = cur.next  # 다음 노드를 미리 저장
            if sorted_list is None or sorted_list.data >= cur.data:
                cur.next = sorted_list
                sorted_list = cur
            else:
                temp = sorted_list
                while temp.next and temp.next.data < cur.data:
                    temp = temp.next
                cur.next = temp.next
                temp.next = cur
            
            cur = next_node  # 다음 노드로 이동
        
        self.head = sorted_list

    def selection_sort(self):
        if self.head is None or self.head.next is None:
            return
        
        cur = self.head
        
        while cur:
            min_node = cur
            r = cur.next
            
            while r:
                if r.data < min_node.data:
                    min_node = r
                r = r.next
            
            if min_node != cur:
                cur.data, min_node.data = min_node.data, cur.data
            
            cur = cur.next

    # Function to reverse the list
    def reverse(self):
        prev = None
        cur = self.head
        while cur:
            next_node = cur.next
            cur.next = prev
            prev = cur
            cur = next_node
        self.tail = self.head
        self.head = prev
        return self.head

    def rotate(self, d):
        """
        d%size: 실제로 회전하는 횟수(한바퀴, 즉 d == size인 경우는 제자리임으로)
        d = 0: 아무런 작업도 하지 않음
        d > 0: 오른쪽 회전
        d < 0: 왼쪽 회전
        """
        if self.head == None or d == 0 or self.size == 0:
            return
        d %= self.size #실제 회전수
        if d == 0: #그냥 한바퀴인 경우
            return
        if d < 0:
            d = self.size + d #왼쪽으로 d만큼이라는 것은 오른쪽으로 size-d만큼이라는것

        ##오른쪽 회전
        #1. 새로운 tail 먼저 지정
        new_tail = self.head
        for _ in range(self.size - d - 1):
            new_tail = new_tail.next

        
        #새로운 head: 새로운 tail 바로 옆
        new_head = new_tail.next
        new_tail.next = None #연결 끊기

        #원래 끊어진 부분 잇기
        self.tail.next = self.head

        #head, tail 갱신
        self.head = new_head
        self.tail = new_tail


    def hasCycle(self, head: Node) -> bool:
        slow_ptr = head
        fast_ptr = head
        
        while fast_ptr is not None and fast_ptr.next is not None:
            slow_ptr = slow_ptr.next
            fast_ptr = fast_ptr.next.next
            
            if slow_ptr == fast_ptr:
                return True
        
        return False

    def detectCycle(self, head: Node) -> Node:
        if head is None or head.next is None:
            return None
        
        slow_ptr = head
        fast_ptr = head
        entry_ptr = head
        
        while fast_ptr.next is not None and fast_ptr.next.next is not None:
            slow_ptr = slow_ptr.next
            fast_ptr = fast_ptr.next.next
            
            if slow_ptr == fast_ptr:
                while slow_ptr != entry_ptr:
                    slow_ptr = slow_ptr.next
                    entry_ptr = entry_ptr.next
                return entry_ptr
        
        return None
    
    
        # Convert linked list to array
    def linkedlist_to_array(self):
        arr = []
        current = self.head
        while current:
            arr.append(current.data)
            current = current.next
        return arr

    # Convert array to linked list
    def array_to_linkedlist(self, arr):
        self.clear()  # 기존 리스트를 초기화합니다.
        for item in arr:
            if self.tail is None:  # 리스트가 비어 있으면 첫 번째 요소로 추가
                self.add_first(item)
            else:
                self.add_after(self.tail, item)




if __name__ == "__main__":
    # Create an empty list and check if it's empty
    llist = LList()
    print("List initially empty:", llist.is_empty())

    # Add elements to the list
    llist.add_first(10)
    llist.add_first(20)
    llist.add_first(30)
    print("List after adding elements at the beginning:")
    llist.print_list()

    # Add elements by index
    llist.add_by_index(1, 15)
    llist.add_by_index(0, 25)
    print("List after adding elements by index:")
    llist.print_list()

    # Add to ordered list
    llist.add_to_ordered_list(18)
    llist.add_to_ordered_list(5)
    print("List after adding to ordered list:")
    llist.print_list()

    # Get first and last elements
    print("First element:", llist.get_first())
    print("Last element:", llist.get_last())

    # Find a node
    node = llist.find_node(15)
    print("Finding node with value 15:", "Found" if node else "Not found")

    # Add before a specific node
    node = llist.find_node(18)
    if node:
        llist.add_before(node, 17)
        print("List after adding 17 before 18:")
        llist.print_list()

    # Add after a specific node
    node = llist.find_node(10)
    if node:
        llist.add_after(node, 12)
        print("List after adding 12 after 10:")
        llist.print_list()

    # Remove elements
    llist.remove_by_value(25)
    print("List after removing element with value 25:")
    llist.print_list()

    llist.remove_by_index(2)
    print("List after removing element at index 2:")
    llist.print_list()

    llist.remove_first()
    print("List after removing the first element:")
    llist.print_list()

    llist.remove_last()
    print("List after removing the last element:")
    llist.print_list()

    # Remove after a specific node
    node = llist.find_node(15)
    if node:
        llist.remove_after(node)
        print("List after removing the node after 15:")
        llist.print_list()

    # Sort the list
    llist.selection_sort()
    print("List after selection sorting:")
    llist.print_list()

    # Reverse the list
    llist.reverse()
    print("List after reversing:")
    llist.print_list()

    # Rotate the list
    llist.rotate(2)
    print("List after rotating by 2 positions:")
    llist.print_list()

    # Sort the list
    llist.insertion_sort()
    print("List after insertion sorting:")
    llist.print_list()

    # Merge with another list
    list2 = LList()
    list2.add_first(40)
    list2.add_first(35)
    list2.add_first(28)
    print("Second list before merging:")
    list2.print_list()

    merged_head = LList.merge(llist.head, list2.head)
    merged_list = LList()
    merged_list.head = merged_head
    cur = merged_head
    size = 0
    while cur:
        size += 1
        cur = cur.next
    merged_list.size = size
    merged_list.tail = cur if cur else merged_list.get_node_by_index(size - 1)
    print("Merged list:")
    merged_list.print_list()

    # Concatenate another list
    list3 = LList()
    list3.add_first(55)
    list3.add_first(60)
    list3.add_first(65)
    print("Third list before concatenation:")
    list3.print_list()

    merged_list.concat(list3)
    print("List after concatenating third list:")
    merged_list.print_list()

    # Convert merged_list to array and back to linked list
    array_from_list = merged_list.linkedlist_to_array()
    print("Array after converting from linked list:", array_from_list)

    merged_list.array_to_linkedlist(array_from_list)
    print("Linked list after converting back from array:")
    merged_list.print_list()


    # Clear the list
    merged_list.clear()
    print("List after clearing:")
    print("Size of the list:", merged_list.get_size())
    merged_list.print_list()
