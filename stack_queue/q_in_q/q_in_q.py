class Queue:
    def __init__(self):
        """
        Initialize an empty queue.
        """
        self.data = []  # List to store the queue elements
        self.front_idx = 0  # Index of the front element

    def enqueue(self, value):
        """
        Add an element to the queue.

        Args:
            value: The value to be added to the queue.
        """
        self.data.append(value)

    def dequeue(self):
        """
        Remove and return the front element of the queue.

        Returns:
            The front element of the queue.

        Raises:
            IndexError: If the queue is empty.
        """
        if self.is_empty():
            raise IndexError("Queue underflow")
        value = self.data[self.front_idx]
        self.front_idx += 1
        return value

    def front(self):
        """
        Return the front element without removing it.

        Returns:
            The front element of the queue.

        Raises:
            IndexError: If the queue is empty.
        """
        if self.is_empty():
            raise IndexError("Queue is empty")
        return self.data[self.front_idx]

    def is_empty(self):
        """
        Check if the queue is empty.

        Returns:
            True if the queue is empty, otherwise False.
        """
        return self.front_idx >= len(self.data)

    def size(self):
        """
        Return the size of the queue.

        Returns:
            The number of elements in the queue.
        """
        return len(self.data) - self.front_idx

    def print(self):
        """
        Print the contents of the queue.
        """
        print(" ".join(map(str, self.data[self.front_idx:])))

    def get_data(self):
        """
        Get the underlying data of the queue.

        Returns:
            The list representing the queue's contents.
        """
        return self.data[self.front_idx:]

    def reset(self):
        """
        Reset the queue's data to remove unused space from the front.
        """
        self.data = self.data[self.front_idx:]
        self.front_idx = 0


def merge_inner_queues_in_queue(outer_queue, i, j, k):
    """
    Merge two inner queues in the outer queue and insert at position `k`.

    Args:
        outer_queue (Queue): The outer queue containing inner queues.
        i (int): Index of the first inner queue to merge.
        j (int): Index of the second inner queue to merge.
        k (int): The position to insert the merged queue.

    Raises:
        IndexError: If indices `i`, `j`, or `k` are invalid.
    """
    if i >= outer_queue.size() or j >= outer_queue.size() or k > outer_queue.size() or i == j:
        raise IndexError("Invalid indices for merging")

    # Convert the queue to a list for easier manipulation
    outer_data = outer_queue.get_data()

    # Create a new queue for the merged data
    merged_queue = Queue()

    # Merge the i-th queue
    for val in outer_data[i].get_data():
        merged_queue.enqueue(val)

    # Merge the j-th queue
    for val in outer_data[j].get_data():
        merged_queue.enqueue(val)

    # Remove i-th and j-th queues
    if i < j:
        del outer_data[j]
        del outer_data[i]
    else:
        del outer_data[i]
        del outer_data[j]

    # Insert the merged queue at position `k`
    outer_data.insert(k, merged_queue)

    # Replace the outer queue with the updated list
    new_outer_queue = Queue()
    for q in outer_data:
        new_outer_queue.enqueue(q)

    outer_queue.data = new_outer_queue.data
    outer_queue.front_idx = new_outer_queue.front_idx


# Main function for testing
if __name__ == "__main__":
    print("=== Testing Queue in Queue ===")

    # Create the outer queue
    outer_queue = Queue()

    # Create and enqueue inner queues
    queue1 = Queue()
    queue1.enqueue(1)
    queue1.enqueue(2)

    queue2 = Queue()
    queue2.enqueue(3)
    queue2.enqueue(4)

    queue3 = Queue()
    queue3.enqueue(5)
    queue3.enqueue(6)

    outer_queue.enqueue(queue1)
    outer_queue.enqueue(queue2)
    outer_queue.enqueue(queue3)

    # Print the outer queue before merging
    print("Outer queue before merging:")
    for q in outer_queue.get_data():
        q.print()

    # Merge queue1 and queue2 and insert at position 1
    merge_inner_queues_in_queue(outer_queue, 0, 1, 1)

    # Print the outer queue after merging
    print("\nOuter queue after merging:")
    for q in outer_queue.get_data():
        q.print()