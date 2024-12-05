class MaxHeap:
    def __init__(self):
        self.elements = []

    def compare(self, pair1, pair2):
        # Compare two pairs: prioritize larger x, then larger y
        if pair1[0] != pair2[0]:
            return pair1[0] > pair2[0]
        return pair1[1] > pair2[1]

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
            raise IndexError("Max-Heap is empty!")
        max_pair = self.elements[0]
        self.elements[0] = self.elements.pop()
        self.bubble_down(0)
        return max_pair

    def print(self):
        print(self.elements)


# Test Max-Heap with Pairs
print("\nMax-Heap with Pairs Implementation:")
max_heap = MaxHeap()
max_heap.insert((10, 20))
max_heap.insert((15, 25))
max_heap.insert((5, 10))
max_heap.insert((10, 15))

print("Max-Heap after insertions: ", end="")
max_heap.print()

print(f"Popping maximum: {max_heap.pop()}")
print("Max-Heap after popping: ", end="")
max_heap.print()