#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

/**********************************************
 * CATALOG OF FUNCTIONS AND CLASSES
 **********************************************
 * 
 * CLASS: Stack<T>
 * 
 * 1. `void push(const T& value)`
 *    - Adds an element `value` to the top of the stack.
 *    - Dynamically resizes the stack if needed.
 * 
 * 2. `void pop()`
 *    - Removes the top element from the stack.
 *    - Throws a `runtime_error` if the stack is empty.
 * 
 * 3. `T& top()`
 *    - Returns a reference to the top element of the stack.
 *    - Throws a `runtime_error` if the stack is empty.
 * 
 * 4. `bool isEmpty() const`
 *    - Checks if the stack is empty.
 *    - Returns `true` if empty, `false` otherwise.
 * 
 * 5. `int size() const`
 *    - Returns the number of elements in the stack.
 * 
 * 6. `void print() const`
 *    - Prints the elements of the stack from bottom to top.
 * 
 * 7. `const vector<T>& getData() const`
 *    - Returns a reference to the underlying data vector of the stack.
 *    - Useful for operations like merging stacks.
 * 
 **********************************************
 * FUNCTION: mergeInnerStacks
 * 
 * 1. `void mergeInnerStacks(Stack<Stack<T>>& stackOfStacks, int i, int j, int k)`
 *    - Merges two inner stacks at indices `i` and `j` into a new stack.
 *    - Inserts the merged stack at position `k` in the stack of stacks.
 *    - Dynamically adjusts the stack of stacks to accommodate the merged stack.
 *    - **Parameters**:
 *       - `stackOfStacks`: The stack of stacks containing the inner stacks.
 *       - `i`: The index of the first inner stack to merge.
 *       - `j`: The index of the second inner stack to merge.
 *       - `k`: The position to insert the merged stack.
 *    - **Error Handling**:
 *       - Throws a `runtime_error` if any of the indices are invalid.
 **********************************************/

// Template class for a Stack
template <typename T>
class Stack {
private:
    vector<T> data; // Vector to store stack elements

public:
    // Push an element onto the stack
    void push(const T& value) {
        data.push_back(value);
    }

    // Pop the top element from the stack
    void pop() {
        if (isEmpty())
            throw runtime_error("Stack underflow");
        data.pop_back();
    }

    // Get the top element of the stack
    T& top() {
        if (isEmpty())
            throw runtime_error("Stack is empty");
        return data.back();
    }

    // Check if the stack is empty
    bool isEmpty() const {
        return data.empty();
    }

    // Get the size of the stack
    int size() const {
        return data.size();
    }

    // Print the stack contents
    void print() const {
        for (const auto& elem : data)
            cout << elem << " ";
        cout << endl;
    }

    // Access the underlying data (needed for merging)
    const vector<T>& getData() const {
        return data;
    }
};

// Function to merge two inner stacks and insert the merged stack into a stack of stacks
template <typename T>
void mergeInnerStacks(Stack<Stack<T>>& stackOfStacks, int i, int j, int k) {
    if (i >= stackOfStacks.size() || j >= stackOfStacks.size() || k > stackOfStacks.size() || i == j)
        throw runtime_error("Invalid indices");

    Stack<T> mergedStack;

    Stack<T> stack1 = stackOfStacks.getData()[i];
    Stack<T> stack2 = stackOfStacks.getData()[j];

    for (const T& value : stack1.getData())
        mergedStack.push(value);

    for (const T& value : stack2.getData())
        mergedStack.push(value);

    auto& stacks = const_cast<vector<Stack<T>>&>(stackOfStacks.getData());
    if (i > j) swap(i, j); // Ensure proper order for deletion
    stacks.erase(stacks.begin() + j);
    stacks.erase(stacks.begin() + i);
    stacks.insert(stacks.begin() + k, mergedStack);
}

// Main function for testing
int main() {
    cout << "=== Testing Inner Stack Functions ===" << endl;

    // Create an inner stack
    Stack<int> innerStack;
    cout << "Inner stack created." << endl;

    // Push elements
    innerStack.push(10);
    innerStack.push(20);
    innerStack.push(30);
    cout << "Pushed elements onto the inner stack: 10, 20, 30." << endl;

    // Peek top element
    cout << "Top element of inner stack: " << innerStack.top() << endl;

    // Pop elements
    cout << "Popped element: " << innerStack.top() << endl;
    innerStack.pop();
    cout << "Popped element: " << innerStack.top() << endl;
    innerStack.pop();

    // Check if stack is empty
    cout << "Is inner stack empty? " << (innerStack.isEmpty() ? "Yes" : "No") << endl;

    cout << "\n=== Testing Outer Stack (Stack of Stacks) ===" << endl;

    // Create an outer stack
    Stack<Stack<int>> outerStack;
    cout << "Outer stack created." << endl;

    // Create inner stacks
    Stack<int> innerStack1, innerStack2;
    innerStack1.push(1);
    innerStack1.push(2);
    innerStack2.push(3);
    innerStack2.push(4);

    // Push inner stacks onto the outer stack
    outerStack.push(innerStack1);
    outerStack.push(innerStack2);
    cout << "Inner stacks pushed onto the outer stack." << endl;

    // Print outer stack
    cout << "Outer stack contents:" << endl;
    for (int i = 0; i < outerStack.size(); i++) {
        cout << "Stack " << i << ": ";
        outerStack.getData()[i].print();
    }

    // Peek the top inner stack
    cout << "Top inner stack (peek): ";
    outerStack.top().print();

    // Pop the top inner stack
    Stack<int> poppedStack = outerStack.top();
    outerStack.pop();
    cout << "Popped top inner stack. Contents of popped stack: ";
    poppedStack.print();

    // Check if the outer stack is empty
    cout << "Is outer stack empty? " << (outerStack.isEmpty() ? "Yes" : "No") << endl;

    cout << "\n=== Testing Merge Inner Stacks ===" << endl;

    // Push innerStack2 back and create another stack
    outerStack.push(innerStack2);
    Stack<int> innerStack3;
    innerStack3.push(5);
    innerStack3.push(6);
    outerStack.push(innerStack3);

    // Print before merging
    cout << "Outer stack before merging:" << endl;
    for (int i = 0; i < outerStack.size(); i++) {
        cout << "Stack " << i << ": ";
        outerStack.getData()[i].print();
    }

    // Merge two inner stacks
    mergeInnerStacks(outerStack, 0, 1, 1);

    // Print after merging
    cout << "Outer stack after merging inner stacks 0 and 1 into position 1:" << endl;
    for (int i = 0; i < outerStack.size(); i++) {
        cout << "Stack " << i << ": ";
        outerStack.getData()[i].print();
    }

    return 0;
}