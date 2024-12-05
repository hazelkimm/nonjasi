class MaxHeap:
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
            raise IndexError("Max-Heap is empty!")
        max_value = self.elements[0]
        self.elements[0] = self.elements.pop()
        self.bubble_down(0)
        return max_value

    def print(self):
        print(self.elements)


# Test Max-Heap
print("\nMax-Heap Implementation:")
max_heap = MaxHeap()
max_heap.insert(10)
max_heap.insert(20)
max_heap.insert(5)
max_heap.insert(15)

print("Max-Heap after insertions: ", end="")
max_heap.print()

print(f"Popping maximum: {max_heap.pop()}")
print("Max-Heap after popping: ", end="")
max_heap.print()