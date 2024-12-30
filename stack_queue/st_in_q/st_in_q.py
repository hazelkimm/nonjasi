class Stack:
    def __init__(self):
        """Initializes an empty stack."""
        self.data = []

    def push(self, value):
        """Pushes an element onto the stack."""
        self.data.append(value)

    def pop(self):
        """Pops the top element from the stack."""
        if self.is_empty():
            raise IndexError("Stack underflow")
        return self.data.pop()

    def top(self):
        """Returns the top element of the stack without removing it."""
        if self.is_empty():
            raise IndexError("Stack is empty")
        return self.data[-1]

    def is_empty(self):
        """Checks if the stack is empty."""
        return len(self.data) == 0

    def size(self):
        """Returns the size of the stack."""
        return len(self.data)

    def print_stack(self):
        """Prints the contents of the stack."""
        print(" ".join(map(str, self.data)))

    def get_data(self):
        """Returns the underlying data."""
        return self.data


class Queue:
    def __init__(self):
        """Initializes an empty queue."""
        self.data = []

    def enqueue(self, stack):
        """Enqueues a stack into the queue."""
        self.data.append(stack)

    def dequeue(self):
        """Dequeues the front stack from the queue."""
        if self.is_empty():
            raise IndexError("Queue underflow")
        return self.data.pop(0)

    def peek(self):
        """Returns the front stack without dequeuing it."""
        if self.is_empty():
            raise IndexError("Queue is empty")
        return self.data[0]

    def is_empty(self):
        """Checks if the queue is empty."""
        return len(self.data) == 0

    def size(self):
        """Returns the size of the queue."""
        return len(self.data)

    def print_queue(self):
        """Prints the contents of the queue."""
        for idx, stack in enumerate(self.data):
            print(f"Stack {idx}: ", end="")
            stack.print_stack()

    def get_data(self):
        """Returns the underlying data."""
        return self.data


def merge_stacks_in_queue(queue, i, j, k):
    """
    Merges two stacks in a queue and inserts the merged stack at position k.

    Parameters:
        queue (Queue): The queue containing the stacks.
        i (int): The index of the first stack to merge.
        j (int): The index of the second stack to merge.
        k (int): The position to insert the merged stack.

    Raises:
        IndexError: If any indices are invalid or if `i == j`.
    """
    if i >= queue.size() or j >= queue.size() or i == j or k > queue.size():
        raise IndexError("Invalid indices for merging")

    stacks = queue.get_data()
    merged_stack = Stack()

    # Add elements from the i-th stack
    for value in stacks[i].get_data():
        merged_stack.push(value)

    # Add elements from the j-th stack
    for value in stacks[j].get_data():
        merged_stack.push(value)

    # Remove original stacks
    stacks.pop(max(i, j))
    stacks.pop(min(i, j))

    # Insert the merged stack at position k
    stacks.insert(k, merged_stack)


if __name__ == "__main__":
    print("=== Testing Inner Stack Functions ===")

    # Create an inner stack
    inner_stack = Stack()
    print("Inner stack created.")

    # Push elements
    inner_stack.push(10)
    inner_stack.push(20)
    inner_stack.push(30)
    print("Pushed elements onto the inner stack: 10, 20, 30.")

    # Peek top element
    print(f"Top element of inner stack: {inner_stack.top()}")

    # Pop elements
    print(f"Popped element: {inner_stack.pop()}")
    print(f"Popped element: {inner_stack.pop()}")

    # Check if stack is empty
    print(f"Is inner stack empty? {'Yes' if inner_stack.is_empty() else 'No'}")

    print("\n=== Testing Outer Queue (Queue of Stacks) ===")

    # Create an outer queue
    queue = Queue()
    print("Outer queue created.")

    # Create inner stacks
    stack1 = Stack()
    stack1.push(1)
    stack1.push(2)

    stack2 = Stack()
    stack2.push(3)
    stack2.push(4)

    stack3 = Stack()
    stack3.push(5)
    stack3.push(6)

    stack4 = Stack()
    stack4.push(7)
    stack4.push(8)

    # Enqueue inner stacks into the queue
    queue.enqueue(stack1)
    queue.enqueue(stack2)
    queue.enqueue(stack3)
    queue.enqueue(stack4)
    print("Inner stacks enqueued into the outer queue.")

    # Print outer queue before merging
    print("Queue before merging:")
    queue.print_queue()

    # Merge stack1 and stack2 into position 1
    merge_stacks_in_queue(queue, 0, 1, 1)

    # Print outer queue after merging
    print("\nQueue after merging stacks 0 and 1 into position 1:")
    queue.print_queue()