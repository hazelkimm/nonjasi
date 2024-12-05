class Node:
    """A Node of the linked list."""
    def __init__(self, val):
        self.val = val
        self.next = None


class MinHeap:
    """Min-Heap implemented as a linked list."""
    def __init__(self):
        self.head = None

    def insert(self, val):
        """Insert a value into the Min-Heap."""
        new_node = Node(val)
        if not self.head or val < self.head.val:
            new_node.next = self.head
            self.head = new_node
        else:
            current = self.head
            while current.next and current.next.val <= val:
                current = current.next
            new_node.next = current.next
            current.next = new_node

    def pop(self):
        """Remove and return the smallest value from the Min-Heap."""
        if not self.head:
            raise IndexError("Min-Heap is empty!")
        min_val = self.head.val
        self.head = self.head.next
        return min_val

    def print_heap(self):
        """Print the Min-Heap."""
        current = self.head
        while current:
            print(current.val, end=" ")
            current = current.next
        print()


# Test Min-Heap
print("Min-Heap with Linked List Implementation:")
min_heap = MinHeap()

min_heap.insert(10)
min_heap.insert(20)
min_heap.insert(5)
min_heap.insert(15)

print("Min-Heap after insertions: ", end="")
min_heap.print_heap()

print(f"Popping minimum: {min_heap.pop()}")
print("Min-Heap after popping: ", end="")
min_heap.print_heap()