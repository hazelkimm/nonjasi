class Node:
    """A Node of the linked list."""
    def __init__(self, val):
        self.val = val
        self.next = None


class MaxHeap:
    """Max-Heap implemented as a linked list."""
    def __init__(self):
        self.head = None

    def insert(self, val):
        """Insert a value into the Max-Heap."""
        new_node = Node(val)
        if not self.head or val > self.head.val:
            new_node.next = self.head
            self.head = new_node
        else:
            current = self.head
            while current.next and current.next.val >= val:
                current = current.next
            new_node.next = current.next
            current.next = new_node

    def pop(self):
        """Remove and return the largest value from the Max-Heap."""
        if not self.head:
            raise IndexError("Max-Heap is empty!")
        max_val = self.head.val
        self.head = self.head.next
        return max_val

    def print_heap(self):
        """Print the Max-Heap."""
        current = self.head
        while current:
            print(current.val, end=" ")
            current = current.next
        print()


# Test Max-Heap
print("\nMax-Heap with Linked List Implementation:")
max_heap = MaxHeap()

max_heap.insert(10)
max_heap.insert(20)
max_heap.insert(5)
max_heap.insert(15)

print("Max-Heap after insertions: ", end="")
max_heap.print_heap()

print(f"Popping maximum: {max_heap.pop()}")
print("Max-Heap after popping: ", end="")
max_heap.print_heap()