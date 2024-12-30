# **********************************************
# CATALOG OF CLASSES AND FUNCTIONS
# **********************************************

# CLASS: Queue
# 1. `__init__(self)`
#    - Initializes an empty queue.
#    - Creates an internal list to store elements and a `front_index` to track the front.

# 2. `enqueue(self, value)`
#    - Adds an element `value` to the back of the queue.

# 3. `dequeue(self)`
#    - Removes and returns the front element of the queue.
#    - Raises `IndexError` if the queue is empty.

# 4. `front(self)`
#    - Returns the front element of the queue without removing it.
#    - Raises `IndexError` if the queue is empty.

# 5. `is_empty(self)`
#    - Checks if the queue is empty.
#    - Returns `True` if empty, otherwise `False`.

# 6. `size(self)`
#    - Returns the number of elements currently in the queue.

# 7. `print_queue(self)`
#    - Prints the contents of the queue from front to back.

# 8. `reset(self)`
#    - Resets the queue’s data to optimize storage.
#    - Removes processed elements and realigns the queue.

# **********************************************

# CLASS: StackOfQueues
# 1. `__init__(self)`
#    - Initializes an empty stack of queues.
#    - Creates an internal list to store queues.

# 2. `push(self, queue)`
#    - Pushes a queue onto the stack.

# 3. `pop(self)`
#    - Removes and returns the top queue from the stack.
#    - Raises `IndexError` if the stack is empty.

# 4. `top(self)`
#    - Returns the top queue without removing it.
#    - Raises `IndexError` if the stack is empty.

# 5. `is_empty(self)`
#    - Checks if the stack is empty.
#    - Returns `True` if empty, otherwise `False`.

# 6. `size(self)`
#    - Returns the number of queues currently in the stack.

# 7. `print_stack(self)`
#    - Prints the contents of all queues in the stack.

# 8. `get_stack_data(self)`
#    - Returns the internal list of queues.
#    - Useful for operations like merging.

# **********************************************
# FUNCTION: merge_inner_queues_in_stack
# **********************************************
# 1. `merge_inner_queues_in_stack(stack, i, j, k)`
#    - Merges two inner queues at indices `i` and `j` in the stack of queues.
#    - Deletes the original queues at indices `i` and `j`.
#    - Inserts the merged queue at index `k` in the stack.
#
#    **Parameters**:
#       - `stack`: A `StackOfQueues` object containing queues.
#       - `i`: Index of the first queue to merge.
#       - `j`: Index of the second queue to merge.
#       - `k`: Index where the merged queue will be inserted.
#
#    **Raises**:
#       - `IndexError` if:
#         - Any of the indices `i`, `j`, or `k` are invalid.
#         - `i` equals `j`.
#
#    **Behavior**:
#       - Combines elements from the `i-th` and `j-th` queues into a new merged queue.
#       - Inserts the merged queue at index `k`.
#       - Deletes the original queues at indices `i` and `j`.
# **********************************************

class Queue:
    """
    Represents an individual queue.
    """
    def __init__(self):
        """Initializes an empty queue."""
        self.data = []
        self.front_index = 0

    def enqueue(self, value):
        """Adds an element to the back of the queue."""
        self.data.append(value)

    def dequeue(self):
        """Removes and returns the front element of the queue."""
        if self.is_empty():
            raise IndexError("Queue underflow")
        value = self.data[self.front_index]
        self.front_index += 1
        return value

    def front(self):
        """Returns the front element without removing it."""
        if self.is_empty():
            raise IndexError("Queue is empty")
        return self.data[self.front_index]

    def is_empty(self):
        """Checks if the queue is empty."""
        return self.front_index >= len(self.data)

    def size(self):
        """Returns the number of elements in the queue."""
        return len(self.data) - self.front_index

    def print_queue(self):
        """Prints the queue contents."""
        print(" ".join(map(str, self.data[self.front_index:])))

    def reset(self):
        """Resets the queue to optimize storage."""
        self.data = self.data[self.front_index:]
        self.front_index = 0


class StackOfQueues:
    """
    Represents a stack of queues.
    """
    def __init__(self):
        """Initializes an empty stack of queues."""
        self.stack = []

    def push(self, queue):
        """Pushes a queue onto the stack."""
        self.stack.append(queue)

    def pop(self):
        """Removes and returns the top queue from the stack."""
        if self.is_empty():
            raise IndexError("Stack underflow")
        return self.stack.pop()

    def top(self):
        """Returns the top queue without removing it."""
        if self.is_empty():
            raise IndexError("Stack is empty")
        return self.stack[-1]

    def is_empty(self):
        """Checks if the stack is empty."""
        return len(self.stack) == 0

    def size(self):
        """Returns the number of queues in the stack."""
        return len(self.stack)

    def print_stack(self):
        """Prints the contents of all queues in the stack."""
        for queue in self.stack:
            queue.print_queue()

    def get_stack_data(self):
        """Accesses the stack data for merging."""
        return self.stack

def merge_inner_queues_in_stack(stack, i, j, k):
    """
    Merges two inner queues at indices `i` and `j` in the stack.

    Args:
        stack (StackOfQueues): The stack of queues.
        i (int): Index of the first queue to merge.
        j (int): Index of the second queue to merge.
        k (int): Index where the merged queue will be inserted.

    Raises:
        IndexError: If indices are invalid or if `i` equals `j`.
    """
    if i >= stack.size() or j >= stack.size() or k > stack.size() or i == j:
        raise IndexError("Invalid indices for merging")

    stack_data = stack.get_stack_data()

    # Create a new queue for the merged result
    merged_queue = Queue()

    # Add all elements from the i-th queue
    stack_data[i].reset()
    for value in stack_data[i].data:
        merged_queue.enqueue(value)

    # Add all elements from the j-th queue
    stack_data[j].reset()
    for value in stack_data[j].data:
        merged_queue.enqueue(value)

    # Ensure indices are processed in correct order to avoid shifting issues
    first = min(i, j)
    second = max(i, j)

    # Remove the original queues
    del stack_data[second]
    del stack_data[first]

    # Insert the merged queue at position `k`
    stack_data.insert(k, merged_queue)


if __name__ == "__main__":
    print("=== Testing Merge Inner Queues in Stack ===")

    # Create a stack of queues
    stack = StackOfQueues()

    # Create and push queues onto the stack
    queue1 = Queue()
    queue1.enqueue(1)
    queue1.enqueue(2)

    queue2 = Queue()
    queue2.enqueue(3)
    queue2.enqueue(4)

    queue3 = Queue()
    queue3.enqueue(5)
    queue3.enqueue(6)

    queue4 = Queue()
    queue4.enqueue(7)
    queue4.enqueue(8)

    stack.push(queue1)
    stack.push(queue2)
    stack.push(queue3)
    stack.push(queue4)

    # Print the stack before merging
    print("Stack before merging:")
    stack.print_stack()

    # Merge queue1 and queue2, insert at position 2, and remove original queues at positions 0 and 1
    merge_inner_queues_in_stack(stack, 0, 1, 2)

    # Print the stack after merging
    print("Stack after merging queues 0 and 1 into position 2:")
    stack.print_stack()