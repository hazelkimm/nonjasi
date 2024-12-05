class MinHeap:
    def __init__(self):
        self.elements = []

    def compare(self, pair1, pair2):
        # Compare two pairs: prioritize smaller x, then smaller y
        if pair1[0] != pair2[0]:
            return pair1[0] < pair2[0]
        return pair1[1] < pair2[1]

    def bubble_up(self, index):
        while index > 0 and self.compare(self.elements[index], self.elements[(index - 1) // 2]):
            self.elements[index], self.elements[(index - 1) // 2] = self.elements[(index - 1) // 2], self.elements[index]
            index = (index - 1) // 2

    def bubble_down(self, index):
        size = len(self.elements)
        while index * 2 + 1 < size:
            child = index * 2 + 1
            if child + 1 < size and self.compare(self.elements[child + 1], self.elements[child]):
                child += 1
            if self.compare(self.elements[index], self.elements[child]):
                break
            self.elements[index], self.elements[child] = self.elements[child], self.elements[index]
            index = child

    def insert(self, pair):
        self.elements.append(pair)
        self.bubble_up(len(self.elements) - 1)

    def pop(self):
        if not self.elements:
            raise IndexError("Min-Heap is empty!")
        min_pair = self.elements[0]
        self.elements[0] = self.elements.pop()
        self.bubble_down(0)
        return min_pair

    def print(self):
        print(self.elements)


# Test Min-Heap with Pairs
print("Min-Heap with Pairs Implementation:")
min_heap = MinHeap()
min_heap.insert((10, 20))
min_heap.insert((15, 25))
min_heap.insert((5, 10))
min_heap.insert((10, 15))

print("Min-Heap after insertions: ", end="")
min_heap.print()

print(f"Popping minimum: {min_heap.pop()}")
print("Min-Heap after popping: ", end="")
min_heap.print()