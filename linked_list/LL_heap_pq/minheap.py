class MinHeap:
    def __init__(self):
        self.elements = []

    def bubble_up(self, index):
        while index > 0 and self.elements[index] < self.elements[(index - 1) // 2]:
            self.elements[index], self.elements[(index - 1) // 2] = self.elements[(index - 1) // 2], self.elements[index]
            index = (index - 1) // 2

    def bubble_down(self, index):
        size = len(self.elements)
        while index * 2 + 1 < size:
            child = index * 2 + 1
            if child + 1 < size and self.elements[child + 1] < self.elements[child]:
                child += 1
            if self.elements[index] <= self.elements[child]:
                break
            self.elements[index], self.elements[child] = self.elements[child], self.elements[index]
            index = child

    def insert(self, value):
        self.elements.append(value)
        self.bubble_up(len(self.elements) - 1)

    def pop(self):
        if not self.elements:
            raise IndexError("Min-Heap is empty!")
        min_value = self.elements[0]
        self.elements[0] = self.elements.pop()
        self.bubble_down(0)
        return min_value

    def print(self):
        print(self.elements)


# Test Min-Heap
print("Min-Heap Implementation:")
min_heap = MinHeap()
min_heap.insert(10)
min_heap.insert(20)
min_heap.insert(5)
min_heap.insert(15)

print("Min-Heap after insertions: ", end="")
min_heap.print()

print(f"Popping minimum: {min_heap.pop()}")
print("Min-Heap after popping: ", end="")
min_heap.print()