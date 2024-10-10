class Node:
    def __init__(self, data):
        self.data = data
        self.next = None
        self.prev = None


class LList:
    def __init__(self):
        self.size = 0
        self.head = None
        self.tail = None

    #Print the size
    def get_size(self):
        return self.size
    #만약 위에 def __init__(self) 함수 없으면 def get_size(head) 해야함

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
    # def add_first(head, item):
    #     temp = Node(item)
    #     temp.next = head
    #     if head:
    #         head.prev = temp
    #     return temp  # New head node's address
    
    # 혹은, self가 필요하다면
    def add_first(self, item):
        temp = Node(item)
        temp.next = self.head
        if self.head:
            self.head.prev = temp
        else:
            self.tail = temp
        self.head = temp
        self.size += 1
    
    #Insert node before a specific node
    # def add_before(next, item):
    #     if next is None:
    #         return
    #     temp = Node(item)
    #     temp.prev = next.prev
    #     temp.next = next
    #     if next.prev:
    #         next.prev.next = temp
    #     next.prev = temp

    #혹은 self를 쓰고싶다면
    def add_before(self, next_node, item):
        if next_node is None:
            return
        temp = Node(item)
        temp.prev = next_node.prev
        temp.next = next_node
        if next_node.prev:
            next_node.prev.next = temp
        else:  # next_node was the head
            self.head = temp
        next_node.prev = temp
        self.size += 1

    # Insert node after a specific node
    def add_after(self, prev, item):
        if prev is None:
            return
        temp = Node(item)
        temp.next = prev.next
        temp.prev = prev
        if prev.next:
            prev.next.prev = temp
        else:
            self.tail = temp
        prev.next = temp
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
            return self.add_first(item)

        prev = self.get_node_by_index(index-1)
        if prev:
            self.add_after(prev, item)
        self.size += 1
        return self.head

    # Insert into ordered list
    def add_to_ordered_list(self, item):
        p = self.head
        q = None
        self.size += 1

        while p and p.data < item:
            q = p
            p = p.next

        if q is None:
            return self.add_first(item)
        else:
            return self.add_after(q, item)
            # return self.head
        

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
        if self.head:
            self.head.prev = None
        self.size -= 1
        return self.head
    
    #Remove last node
    def remove_last(self):
        if self.tail is None:
            return None
        temp = self.tail
        self.tail = self.tail.prev
        if self.tail:
            self.tail.next = None
        else:
            self.head = None
        self.size -= 1
        return self.tail

    # Remove node after a specific node
    def remove_after(self, prv):
        if prv is None or prv.next is None:
            return
        temp = prv.next
        prv.next = temp.next
        if temp.next:
            temp.next.prev = prv
        else:
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
                list1.prev = tail
                list1 = list1.next
            else:
                tail.next = list2
                list2.prev = tail
                list2 = list2.next
            tail = tail.next

        tail.next = list1 if list1 else list2

        if tail.next:
            tail.next.prev = tail

        return dummy.next

    # Function to concatenate two lists
    # def concat(list1, list2):
    #     if list1 is None:
    #         return list2
    #     if list2 is None:
    #         return list1
    #     p = list1
    #     while p.next:
    #         p = p.next
    #     p.next = list2
    #     list2.prev = p
    #     return list1

    def concat(self, list2):
        if self.head is None:
            self.head = list2.head
            self.tail = list2.tail
            self.size = list2.size
        elif list2.head is None:
            return
        else:
            self.tail.next = list2.head
            list2.head.prev = self.tail
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
    # def sort(self):
    #     if self.head is None or self.head.next is None:
    #         return self.head

    #     mid = self.head.get_mid()
    #     half = mid.next
    #     mid.next = None
    #     if half:
    #         half.prev = None

    #     return self.merge(self.sort(head), self.sort(half))
    

    def sort(self):
        if self.head is None or self.head.next is None:
            return self.head

        mid = self.get_mid()
        half = mid.next
        mid.next = None
        if half:
            half.prev = None

        left_sorted = LList()
        left_sorted.head = self.head
        left_sorted.size = self.size // 2
        right_sorted = LList()
        right_sorted.head = half
        right_sorted.size = self.size - left_sorted.size

        left_sorted = left_sorted.sort()
        right_sorted = right_sorted.sort()
        self.head = self.merge(left_sorted, right_sorted)

        cur = self.head
        while cur and cur.next:
            cur = cur.next
        self.tail = cur

        return self.head
    # Function to sort the list using insertion sort
    def insertion_sort(self):
        if not self.head or not self.head.next:
            return self.head

        sorted_head = self.head
        cur = self.head.next
        sorted_head.next = None

        while cur:
            next_cur = cur.next
            if cur.data < sorted_head.data:
                cur.next = sorted_head
                sorted_head.prev = cur
                sorted_head = cur
            else:
                search = sorted_head
                while search.next and search.next.data < cur.data:
                    search = search.next
                cur.next = search.next
                if search.next:
                    search.next.prev = cur
                search.next = cur
                cur.prev = search
            cur = next_cur

        self.head = sorted_head
        self.tail = sorted_head
        while self.tail and self.tail.next:
            self.tail = self.tail.next

        return self.head

    # Function to sort the list using selection sort
    def selection_sort(self):
        if not self.head:
            return self.head

        cur = self.head
        while cur:
            min_node = cur
            search = cur.next
            while search:
                if search.data < min_node.data:
                    min_node = search
                search = search.next
            if min_node != cur:
                cur.data, min_node.data = min_node.data, cur.data
            cur = cur.next

        return self.head


    # Function to reverse the list
    def reverse(self):
        prev = None
        cur = self.head
        while cur:
            next_node = cur.next
            cur.next = prev
            cur.prev = next_node
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
        new_tail = self.tail
        for _ in range(d):
            new_tail = new_tail.prev
        
        #새로운 head: 새로운 tail 바로 옆
        new_head = new_tail.next
        new_head.prev = None
        new_tail.next = None #연결 끊기

        #원래 끊어진 부분 잇기
        self.head.prev = self.tail
        self.tail.next = self.head

        #head, tail 갱신
        self.head = new_head
        self.tail = new_tail

        # Convert an array to a linked list
    def array_to_linked_list(self, arr):
        self.clear()  # 기존 리스트를 비웁니다.
        for item in arr:
            self.add_last(item)  # 배열의 각 요소를 리스트의 끝에 추가합니다.

    # 추가된 함수: 리스트의 끝에 노드를 추가하는 함수
    def add_last(self, item):
        if not self.head:  # 리스트가 비어 있는 경우
            self.add_first(item)
        else:
            temp = Node(item)
            self.tail.next = temp
            temp.prev = self.tail
            self.tail = temp
            self.size += 1
    
        # Convert the linked list to an array
    def linked_list_to_array(self):
        arr = []
        current = self.head
        while current:
            arr.append(current.data)  # 현재 노드의 데이터를 배열에 추가
            current = current.next
        return arr




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
    llist.insertion_sort()
    print("List after sorting:")
    llist.print_list()

    # Reverse the list
    llist.reverse()
    print("List after reversing:")
    llist.print_list()

    # Rotate the list
    llist.rotate(2)
    print("List after rotating by 2 positions:")
    llist.print_list()

    # Merge with another list
    list2 = LList()
    list2.add_first(40)
    list2.add_first(35)
    list2.add_first(28)
    print("Second list before concate:")
    list2.print_list()


    llist.concat(list2)
    print("List after concatenating second list:")
    llist.print_list()

     # Reset the list
    llist.clear()
    llist.add_first(4)
    llist.add_first(1)
    llist.add_first(3)
    llist.add_first(2)
    llist.add_first(16)
    llist.add_first(9)
    llist.add_first(10)
    llist.add_first(14)
    llist.add_first(8)
    llist.add_first(7)

    # Test selection sort
    llist.selection_sort()
    print("List after selection sort:")
    llist.print_list()

    # Convert linked list to array
    array_from_list = llist.linked_list_to_array()
    print("Array after converting from linked list:", array_from_list)
    # Convert array back to linked list
    new_llist = LList()  # 새로운 연결 리스트 생성
    new_llist.array_to_linked_list(array_from_list)
    print("Linked list after converting back from array:")
    new_llist.print_list()

    # Clear the list
    llist.clear()
    print("List after clearing:")
    print("Size of the list:", llist.get_size())
    llist.print_list()
