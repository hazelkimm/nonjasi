#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

// Template for Inner Stack
template <typename T>
class Stack {
private:
    vector<T> data;

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
    T top() const {
        if (isEmpty())
            throw runtime_error("Stack is empty");
        return data.back();
    }

    // Check if the stack is empty
    bool isEmpty() const {
        return data.empty();
    }

    // Get the size of the stack
    size_t size() const {
        return data.size();
    }

    // Print the stack
    void print() const {
        for (const auto& val : data) {
            cout << val << " ";
        }
        cout << endl;
    }

    // Access internal data
    const vector<T>& getData() const {
        return data;
    }
};

// Template for Outer Queue (Queue of Stacks)
template <typename T>
class Queue {
private:
    vector<Stack<T>> data;

public:
    // Enqueue a stack into the queue
    void enqueue(const Stack<T>& stack) {
        data.push_back(stack);
    }

    // Dequeue a stack from the queue
    Stack<T> dequeue() {
        if (isEmpty())
            throw runtime_error("Queue underflow");
        Stack<T> frontStack = data.front();
        data.erase(data.begin());
        return frontStack;
    }

    // Peek at the front stack without dequeuing
    Stack<T> peek() const {
        if (isEmpty())
            throw runtime_error("Queue is empty");
        return data.front();
    }

    // Check if the queue is empty
    bool isEmpty() const {
        return data.empty();
    }

    // Get the size of the queue
    size_t size() const {
        return data.size();
    }

    // Access internal data for merging operations
    vector<Stack<T>>& getData() {
        return data;
    }

    // Print the queue
    void print() const {
        for (const auto& stack : data) {
            stack.print();
        }
    }
};

// Merge two stacks in a queue
template <typename T>
void mergeStacksInQueue(Queue<T>& queue, size_t i, size_t j, size_t k) {
    if (i >= queue.size() || j >= queue.size() || i == j || k > queue.size()) {
        throw runtime_error("Invalid indices for merging");
    }

    auto& stacks = queue.getData();
    Stack<T> mergedStack;

    // Add all elements from the i-th stack
    for (const auto& val : stacks[i].getData()) {
        mergedStack.push(val);
    }

    // Add all elements from the j-th stack
    for (const auto& val : stacks[j].getData()) {
        mergedStack.push(val);
    }

    // Remove the original stacks
    stacks.erase(stacks.begin() + max(i, j));
    stacks.erase(stacks.begin() + min(i, j));

    // Insert the merged stack at position k
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
    innerStack.pop();
    cout << "Popped element: 30" << endl;

    innerStack.pop();
    cout << "Popped element: 20" << endl;

    // Check if stack is empty
    cout << "Is inner stack empty? " << (innerStack.isEmpty() ? "Yes" : "No") << endl;

    cout << "\n=== Testing Outer Queue (Queue of Stacks) ===" << endl;

    // Create an outer queue
    Queue<int> queue;
    cout << "Outer queue created." << endl;

    // Create inner stacks
    Stack<int> stack1, stack2, stack3, stack4;
    stack1.push(1);
    stack1.push(2);

    stack2.push(3);
    stack2.push(4);

    stack3.push(5);
    stack3.push(6);

    stack4.push(7);
    stack4.push(8);

    // Enqueue inner stacks into the queue
    queue.enqueue(stack1);
    queue.enqueue(stack2);
    queue.enqueue(stack3);
    queue.enqueue(stack4);
    cout << "Inner stacks enqueued into the outer queue." << endl;

    // Print outer queue before merging
    cout << "Queue before merging:" << endl;
    queue.print();

    // Merge stack1 and stack2 into position 1
    mergeStacksInQueue(queue, 0, 1, 1);

    // Print outer queue after merging
    cout << "Queue after merging stacks 0 and 1 into position 1:" << endl;
    queue.print();

    return 0;
}