class PriorityQueue:
    def __init__(self):
        self.elements = []

    def bubble_up(self, index):
        while index > 0 and self.elements[index] > self.elements[(index - 1) // 2]:
            self.elements[index], self.elements[(index - 1) // 2] = self.elements[(index - 1) // 2], self.elements[index]
            index = (index - 1) // 2

    def bubble_down(self, index):
        size = len(self.elements)
        while index * 2 + 1 < size:
            child = index * 2 + 1
            if child + 1 < size and self.elements[child + 1] > self.elements[child]:
                child += 1
            if self.elements[index] >= self.elements[child]:
                break
            self.elements[index], self.elements[child] = self.elements[child], self.elements[index]
            index = child

    def insert(self, value):
        self.elements.append(value)
        self.bubble_up(len(self.elements) - 1)

    def pop(self):
        if not self.elements:
            raise IndexError("Priority queue is empty!")
        max_value = self.elements[0]
        self.elements[0] = self.elements.pop()
        self.bubble_down(0)
        return max_value

    def print(self):
        print(self.elements)


class Node:
    def __init__(self):
        self.heap = PriorityQueue()
        self.next = None


class LinkedList:
    def __init__(self):
        self.head = None

    def add_node(self):
        new_node = Node()
        new_node.next = self.head
        self.head = new_node

    def print_heaps(self):
        current = self.head
        index = 0
        while current:
            print(f"Heap in Node {index}: ", end="")
            current.heap.print()
            current = current.next
            index += 1


# Test Max-Heap with Integers
print("Max-Heap with Integers in Linked List:")

ll = LinkedList()
ll.add_node()
ll.add_node()

# Add elements to the first node's heap
ll.head.heap.insert(10)
ll.head.heap.insert(20)
ll.head.heap.insert(5)

# Add elements to the second node's heap
ll.head.next.heap.insert(15)
ll.head.next.heap.insert(25)
ll.head.next.heap.insert(30)

print("Heaps in the linked list after insertion:")
ll.print_heaps()

# Pop elements from the heaps
print("\nPopping elements from the first heap:")
print(f"Popped: {ll.head.heap.pop()}")
print("Heap after popping: ", end="")
ll.head.heap.print()