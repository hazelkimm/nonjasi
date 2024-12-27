class Stack:
    """
    CATALOG OF STACK FUNCTIONS:
    1. __init__():
        Initializes an empty stack.
    2. is_empty():
        Checks if the stack is empty. Returns True or False.
    3. size():
        Returns the number of elements in the stack.
    4. push(value):
        Adds an element to the top of the stack.
    5. pop():
        Removes and returns the top element of the stack.
        Raises an error if the stack is empty.
    6. peek():
        Returns the top element without removing it.
        Raises an error if the stack is empty.
    7. merge(other):
        Merges two stacks into a new stack. Retains the order of elements.
    8. reverse():
        Reverses the elements of the stack in place.
    9. copy():
        Creates and returns a new stack that is a copy of the given stack.
    10. sort():
        Sorts the stack in ascending order.
    11. slice(start, end):
        Creates and returns a new stack containing elements
        from index `start` to `end - 1` of the original stack.
        Raises an error if indices are invalid.
    """

    def __init__(self):
        """Initialize an empty stack."""
        self.data = []

    def is_empty(self):
        """Check if the stack is empty."""
        return len(self.data) == 0

    def size(self):
        """Return the number of elements in the stack."""
        return len(self.data)

    def push(self, value):
        """Add an element to the top of the stack."""
        self.data.append(value)

    def pop(self):
        """Remove and return the top element of the stack."""
        if self.is_empty():
            raise RuntimeError("Stack underflow error!")
        return self.data.pop()

    def peek(self):
        """Return the top element without removing it."""
        if self.is_empty():
            raise RuntimeError("Stack is empty!")
        return self.data[-1]

    def merge(self, other):
        """Merge with another stack and return the merged stack."""
        merged_stack = Stack()
        merged_stack.data = self.data + other.data
        return merged_stack

    def reverse(self):
        """Reverse the elements of the stack in place."""
        self.data.reverse()

    def copy(self):
        """Create and return a copy of the stack."""
        copied_stack = Stack()
        copied_stack.data = self.data[:]
        return copied_stack

    def sort(self):
        """Sort the stack in ascending order."""
        self.data.sort()

    def slice(self, start, end):
        """Slice the stack and return the sliced stack."""
        if start < 0 or end > self.size() or start >= end:
            raise RuntimeError("Invalid slice indices!")
        sliced_stack = Stack()
        sliced_stack.data = self.data[start:end]
        return sliced_stack


# Testing the Python Stack Implementation
if __name__ == "__main__":
    stack1 = Stack()
    stack2 = Stack()

    # Push elements into stack1
    stack1.push(10)
    stack1.push(20)
    stack1.push(30)

    # Push elements into stack2
    stack2.push(40)
    stack2.push(50)
    stack2.push(60)

    # Merge stacks
    merged_stack = stack1.merge(stack2)
    print("Merged stack:", end=" ")
    while not merged_stack.is_empty():
        print(merged_stack.pop(), end=" ")
    print()

    # Reverse stack1
    stack1.reverse()
    print("Reversed stack1:", end=" ")
    while not stack1.is_empty():
        print(stack1.pop(), end=" ")
    print()

    # Push elements into stack2 again
    stack2.push(70)
    stack2.push(80)

    # Copy stack2
    copied_stack = stack2.copy()
    print("Copied stack2:", end=" ")
    while not copied_stack.is_empty():
        print(copied_stack.pop(), end=" ")
    print()

    # Sort stack2
    stack2.push(90)
    stack2.push(25)
    stack2.sort()
    print("Sorted stack2:", end=" ")
    while not stack2.is_empty():
        print(stack2.pop(), end=" ")
    print()