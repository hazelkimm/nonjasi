#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept> // For exceptions

/**********************************************
 * CATALOG OF STACK FUNCTIONS
 **********************************************
 * 
 * 1. `Stack()`:
 *    Initializes an empty stack.
 * 
 * 2. `bool isEmpty() const`:
 *    Checks if the stack is empty. Returns true or false.
 * 
 * 3. `int size() const`:
 *    Returns the number of elements in the stack.
 * 
 * 4. `void push(int value)`:
 *    Adds an element to the top of the stack.
 * 
 * 5. `int pop()`:
 *    Removes and returns the top element of the stack.
 *    Throws an error if the stack is empty.
 * 
 * 6. `int peek() const`:
 *    Returns the top element without removing it.
 *    Throws an error if the stack is empty.
 * 
 * 7. `Stack merge(const Stack& other) const`:
 *    Merges two stacks into a new stack. Retains the order of elements.
 * 
 * 8. `void reverse()`:
 *    Reverses the elements of the stack in place.
 * 
 * 9. `Stack copy() const`:
 *    Creates and returns a new stack that is a copy of the given stack.
 * 
 * 10. `void sort()`:
 *     Sorts the stack in ascending order.
 * 
 * 11. `Stack slice(int start, int end) const`:
 *     Creates and returns a new stack containing elements
 *     from index `start` to `end - 1` of the original stack.
 *     Throws an error if indices are invalid.
 * 
 **********************************************/

class Stack {
private:
    std::vector<int> data;

public:
    // Constructor
    Stack() {}

    // Check if the stack is empty
    bool isEmpty() const {
        return data.empty();
    }

    // Get the size of the stack
    int size() const {
        return data.size();
    }

    // Push an element onto the stack
    void push(int value) {
        data.push_back(value);
    }

    // Pop an element from the stack
    int pop() {
        if (isEmpty()) {
            throw std::runtime_error("Stack underflow error!");
        }
        int value = data.back();
        data.pop_back();
        return value;
    }

    // Peek the top element of the stack
    int peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty!");
        }
        return data.back();
    }

    // Merge with another stack
    Stack merge(const Stack& other) const {
        Stack mergedStack;
        mergedStack.data = data; // Add current stack elements
        mergedStack.data.insert(mergedStack.data.end(), other.data.begin(), other.data.end()); // Add other stack elements
        return mergedStack;
    }

    // Reverse the stack
    void reverse() {
        std::reverse(data.begin(), data.end());
    }

    // Copy the stack
    Stack copy() const {
        Stack copiedStack;
        copiedStack.data = data;
        return copiedStack;
    }

    // Sort the stack
    void sort() {
        std::sort(data.begin(), data.end());
    }

    // Slice the stack
    Stack slice(int start, int end) const {
        if (start < 0 || end > size() || start >= end) {
            throw std::runtime_error("Invalid slice indices!");
        }
        Stack slicedStack;
        slicedStack.data = std::vector<int>(data.begin() + start, data.begin() + end);
        return slicedStack;
    }
};

// Main function for testing
int main() {
    Stack stack1, stack2;

    // Push elements into stack1
    stack1.push(10);
    stack1.push(20);
    stack1.push(30);

    // Push elements into stack2
    stack2.push(40);
    stack2.push(50);
    stack2.push(60);

    // Merge stacks
    Stack mergedStack = stack1.merge(stack2);
    std::cout << "Merged stack: ";
    while (!mergedStack.isEmpty()) {
        std::cout << mergedStack.pop() << " ";
    }
    std::cout << std::endl;

    // Reverse stack1
    stack1.reverse();
    std::cout << "Reversed stack1: ";
    while (!stack1.isEmpty()) {
        std::cout << stack1.pop() << " ";
    }
    std::cout << std::endl;

    // Push elements into stack2 again
    stack2.push(70);
    stack2.push(80);

    // Copy stack2
    Stack copiedStack = stack2.copy();
    std::cout << "Copied stack2: ";
    while (!copiedStack.isEmpty()) {
        std::cout << copiedStack.pop() << " ";
    }
    std::cout << std::endl;

    // Sort stack2
    stack2.push(90);
    stack2.push(25);
    stack2.sort();
    std::cout << "Sorted stack2: ";
    while (!stack2.isEmpty()) {
        std::cout << stack2.pop() << " ";
    }
    std::cout << std::endl;

    return 0;
}