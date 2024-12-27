class Queue:
    """
    CATALOG OF QUEUE FUNCTIONS:
    1. __init__():
    Initializes an empty queue.

    2. is_empty() -> bool:
    Checks if the queue is empty. Returns True or False.

    3. size() -> int:
    Returns the number of elements in the queue.

    4. enqueue(value: int):
    Adds an element to the rear of the queue.

    5. dequeue() -> int:
    Removes and returns the front element of the queue.
    Raises an error if the queue is empty.

    6. peek() -> int:
    Returns the front element without removing it.
    Raises an error if the queue is empty.

    7. merge(other: "Queue") -> "Queue":
    Merges two queues into a new queue.

    8. reverse():
    Reverses the elements of the queue in place.

    9. copy() -> "Queue":
    Creates and returns a copy of the queue.

    10. sort():
        Sorts the elements of the queue in ascending order.

    11. slice(start: int, end: int) -> "Queue":
        Creates and returns a new queue containing elements
        from index `start` to `end - 1`.
    """
    
    def __init__(self):
        """Initialize an empty queue."""
        self.data = []
        self.size = 0

    def is_empty(self):
        """Check if the queue is empty."""
        return self.size == 0

    def size(self):
        """Return the number of elements in the queue."""
        return self.size

    def enqueue(self, value):
        """Add an element to the rear of the queue."""
        self.data.append(value)
        self.size += 1

    def dequeue(self):
        """Remove and return the front element of the queue."""
        if self.is_empty():
            raise RuntimeError("Queue underflow error!")
        value = self.data.pop(0)
        self.size -= 1
        return value

    def peek(self):
        """Return the front element without removing it."""
        if self.is_empty():
            raise RuntimeError("Queue is empty!")
        return self.data[0]

    def merge(self, other):
        """Merge with another queue and return a new queue."""
        merged_queue = Queue()
        merged_queue.data = self.data + other.data
        merged_queue.size = self.size + other.size
        return merged_queue

    def reverse(self):
        """Reverse the elements of the queue in place."""
        self.data.reverse()

    def copy(self):
        """Create and return a copy of the queue."""
        copied_queue = Queue()
        copied_queue.data = self.data[:]
        copied_queue.size = self.size
        return copied_queue

    def sort(self):
        """Sort the queue in ascending order."""
        self.data.sort()

    def slice(self, start, end):
        """Slice the queue and return a new queue."""
        if start < 0 or end > self.size or start >= end:
            raise RuntimeError("Invalid slice indices!")
        sliced_queue = Queue()
        sliced_queue.data = self.data[start:end]
        sliced_queue.size = end - start
        return sliced_queue

    def display(self):
        """Display the elements of the queue."""
        print(" ".join(map(str, self.data)))


# Main function for testing
if __name__ == "__main__":
    q1 = Queue()
    q2 = Queue()

    # Enqueue elements into q1
    q1.enqueue(10)
    q1.enqueue(20)
    q1.enqueue(30)

    # Enqueue elements into q2
    q2.enqueue(40)
    q2.enqueue(50)
    q2.enqueue(60)

    # Merge queues
    merged_queue = q1.merge(q2)
    print("Merged queue:", end=" ")
    merged_queue.display()

    # Reverse q1
    q1.reverse()
    print("Reversed q1:", end=" ")
    q1.display()

    # Copy q2
    copied_queue = q2.copy()
    print("Copied q2:", end=" ")
    copied_queue.display()

    # Sort q2
    q2.enqueue(25)
    q2.sort()
    print("Sorted q2:", end=" ")
    q2.display()

    # Slice q2
    sliced_queue = q2.slice(1, 4)
    print("Sliced q2 (1 to 4):", end=" ")
    sliced_queue.display()