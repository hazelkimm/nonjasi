"""
**********************************************
* CATALOG OF FUNCTIONS AND CLASSES
**********************************************

CLASS: Stack
1. __init__(self):
   - Initializes an empty stack.
   - Creates an internal list to hold stack elements.

2. push(self, value):
   - Adds an element `value` to the top of the stack.

3. pop(self):
   - Removes and returns the top element of the stack.
   - Raises `IndexError` if the stack is empty.

4. top(self):
   - Returns the top element of the stack without removing it.
   - Raises `IndexError` if the stack is empty.

5. is_empty(self):
   - Checks if the stack is empty.
   - Returns `True` if the stack is empty, otherwise `False`.

6. size(self):
   - Returns the number of elements in the stack.

7. print_stack(self):
   - Prints the elements of the stack from bottom to top.

8. get_data(self):
   - Returns the underlying data list of the stack.
   - Useful for operations such as merging.

**********************************************

FUNCTION: merge_inner_stacks
1. merge_inner_stacks(stack_of_stacks, i, j, k):
   - Merges two inner stacks at indices `i` and `j` from `stack_of_stacks`.
   - Deletes the original stacks at indices `i` and `j`.
   - Inserts the merged stack into `stack_of_stacks` at position `k`.

   **Parameters**:
      - `stack_of_stacks`: A `Stack` of `Stack` objects.
      - `i`: Index of the first inner stack to merge.
      - `j`: Index of the second inner stack to merge.
      - `k`: Position to insert the merged stack.

   **Error Handling**:
      - Raises `IndexError` if any of the indices are invalid.
**********************************************
"""

class Stack:
    def __init__(self):
        """
        Initializes an empty stack.
        """
        self.data = []

    def push(self, value):
        """
        Push an element onto the stack.

        Parameters:
            value: The value to be added to the stack.
        """
        self.data.append(value)

    def pop(self):
        """
        Pop the top element from the stack.

        Returns:
            The popped element.

        Raises:
            IndexError: If the stack is empty.
        """
        if self.is_empty():
            raise IndexError("Stack underflow")
        return self.data.pop()

    def top(self):
        """
        Get the top element of the stack without removing it.

        Returns:
            The top element of the stack.

        Raises:
            IndexError: If the stack is empty.
        """
        if self.is_empty():
            raise IndexError("Stack is empty")
        return self.data[-1]

    def is_empty(self):
        """
        Check if the stack is empty.

        Returns:
            True if the stack is empty, False otherwise.
        """
        return len(self.data) == 0

    def size(self):
        """
        Get the size of the stack.

        Returns:
            The number of elements in the stack.
        """
        return len(self.data)

    def print_stack(self):
        """
        Print the stack contents from bottom to top.
        """
        print(" ".join(map(str, self.data)))

    def get_data(self):
        """
        Access the underlying data of the stack.

        Returns:
            A list representing the stack's contents.
        """
        return self.data


def merge_inner_stacks(stack_of_stacks, i, j, k):
    """
    Merge two inner stacks and insert the merged stack into the stack of stacks.

    Parameters:
        stack_of_stacks (Stack): The stack of stacks containing the inner stacks.
        i (int): The index of the first inner stack to merge.
        j (int): The index of the second inner stack to merge.
        k (int): The position to insert the merged stack.

    Raises:
        IndexError: If any of the indices are invalid.
    """
    if i >= stack_of_stacks.size() or j >= stack_of_stacks.size() or k > stack_of_stacks.size() or i == j:
        raise IndexError("Invalid indices")

    # Ensure i is smaller than j for proper deletion
    if i > j:
        i, j = j, i

    # Create a new stack to hold the merged data
    merged_stack = Stack()

    # Retrieve stacks i and j
    stack1 = stack_of_stacks.get_data().pop(i)
    stack2 = stack_of_stacks.get_data().pop(j - 1)

    # Push elements from the first stack
    for value in stack1.get_data():
        merged_stack.push(value)

    # Push elements from the second stack
    for value in stack2.get_data():
        merged_stack.push(value)

    # Insert the merged stack at position k
    stack_of_stacks.get_data().insert(k, merged_stack)


if __name__ == "__main__":
    # Create a stack of stacks
    stack_of_stacks = Stack()

    # Create the first inner stack
    stack1 = Stack()
    stack1.push(1)
    stack1.push(2)

    # Create the second inner stack
    stack2 = Stack()
    stack2.push(3)
    stack2.push(4)
    
    # Create the second inner stack
    stack3 = Stack()
    stack3.push(5)
    stack3.push(6)

    # Push the inner stacks onto the stack of stacks
    stack_of_stacks.push(stack1)
    stack_of_stacks.push(stack2)
    stack_of_stacks.push(stack3)

    # Print the stack of stacks before merging
    print("Before merging:")
    for idx, stack in enumerate(stack_of_stacks.get_data()):
        print(f"Stack {idx}: ", end="")
        stack.print_stack()

    # Merge stack1 and stack2 into a new stack at position 1
    merge_inner_stacks(stack_of_stacks, 0, 1, 1)

    # Print the stack of stacks after merging
    print("\nAfter merging:")
    for idx, stack in enumerate(stack_of_stacks.get_data()):
        print(f"Stack {idx}: ", end="")
        stack.print_stack()