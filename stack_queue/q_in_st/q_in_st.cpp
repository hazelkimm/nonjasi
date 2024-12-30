#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

/**********************************************
 * CATALOG OF FUNCTIONS AND CLASSES
 **********************************************

 * INNER QUEUE
 1. `Queue<T>()`
    - Constructor that initializes an empty queue.
 
 2. `void enqueue(const T& value)`
    - Adds an element `value` to the back of the queue.

 3. `T dequeue()`
    - Removes and returns the front element of the queue.
    - Throws a `runtime_error` if the queue is empty.

 4. `T front() const`
    - Returns the front element of the queue without removing it.
    - Throws a `runtime_error` if the queue is empty.

 5. `bool isEmpty() const`
    - Checks if the queue is empty.
    - Returns `true` if empty, otherwise `false`.

 6. `size_t size() const`
    - Returns the number of elements in the queue.

 7. `void print() const`
    - Prints the contents of the queue from front to back.

 8. `const vector<T>& getData() const`
    - Returns the underlying data of the queue.
    - Useful for operations like merging.

 9. `void reset()`
    - Resets the queue’s data to optimize storage after operations.

**********************************************

 * OUTER STACK (Stack of Queues)
 1. `StackOfQueues<T>()`
    - Constructor that initializes an empty stack of queues.

 2. `void push(const Queue<T>& queue)`
    - Pushes a queue onto the stack.

 3. `Queue<T> pop()`
    - Removes and returns the top queue from the stack.
    - Throws a `runtime_error` if the stack is empty.

 4. `Queue<T> top() const`
    - Returns the top queue from the stack without removing it.
    - Throws a `runtime_error` if the stack is empty.

 5. `bool isEmpty() const`
    - Checks if the stack is empty.
    - Returns `true` if empty, otherwise `false`.

 6. `size_t size() const`
    - Returns the number of queues in the stack.

 7. `void print() const`
    - Prints the contents of all queues in the stack.

**********************************************
 * MERGING QUEUES
 * 1. `void mergeInnerQueuesInStack(StackOfQueues<T>& stack, size_t i, size_t j, size_t k)`
 *    - Merges two inner queues at indices `i` and `j` in the stack into a new queue.
 *    - Inserts the merged queue at position `k` in the stack.
 *    - Deletes the original queues at indices `i` and `j`.
 *
 *    **Parameters**:
 *       - `stack`: The stack of queues containing the queues to merge.
 *       - `i`: Index of the first queue to merge.
 *       - `j`: Index of the second queue to merge.
 *       - `k`: Index where the merged queue will be inserted.
 *
 *    **Error Handling**:
 *       - Throws a `runtime_error` if:
 *          - `i`, `j`, or `k` are invalid indices.
 *          - `i == j`.
 *
 *    **Behavior**:
 *       - Combines elements of the `i-th` and `j-th` queues into a new merged queue.
 *       - Deletes the original queues at indices `i` and `j`.
 *       - Inserts the merged queue at position `k` in the stack.
 **********************************************/

// Template for Inner Queue
template <typename T>
class Queue {
private:
    vector<T> data;  // Vector to store queue elements
    size_t frontIdx; // Index of the front element
    size_t sizeVal;  // Current size of the queue

public:
    // Constructor
    Queue() : frontIdx(0), sizeVal(0) {}

    // Enqueue an element
    void enqueue(const T& value) {
        data.push_back(value);
        sizeVal++;
    }

    // Dequeue an element
    T dequeue() {
        if (isEmpty())
            throw runtime_error("Queue underflow");
        T value = data[frontIdx];
        frontIdx++;
        sizeVal--;
        return value;
    }

    // Peek the front element
    T front() const {
        if (isEmpty())
            throw runtime_error("Queue is empty");
        return data[frontIdx];
    }

    // Check if the queue is empty
    bool isEmpty() const {
        return sizeVal == 0;
    }

    // Get the size of the queue
    size_t size() const {
        return sizeVal;
    }

    // Print the queue
    void print() const {
        for (size_t i = frontIdx; i < data.size(); i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    // Access internal data for merging
    const vector<T>& getData() const {
        return data;
    }

    // Reset the queue for merging
    void reset() {
        vector<T> temp(data.begin() + frontIdx, data.end());
        data.swap(temp);
        frontIdx = 0;
    }
};

// Template for Outer Stack (Stack of Queues)
template <typename T>
class StackOfQueues {
private:
    vector<Queue<T>> stack;  // Vector of queues

public:
    // Push a queue onto the stack
    void push(const Queue<T>& queue) {
        stack.push_back(queue);
    }

    // Pop a queue from the stack
    Queue<T> pop() {
        if (isEmpty())
            throw runtime_error("Stack underflow");
        Queue<T> topQueue = stack.back();
        stack.pop_back();
        return topQueue;
    }

    // Peek the top queue without popping
    Queue<T> peek() const {
        if (isEmpty())
            throw runtime_error("Stack is empty");
        return stack.back();
    }

    // Check if the stack is empty
    bool isEmpty() const {
        return stack.empty();
    }

    // Get the size of the stack
    size_t size() const {
        return stack.size();
    }

    // Print the stack
    void print() const {
        for (const auto& queue : stack) {
            queue.print();
        }
    }

    // Access the stack data for merging
    vector<Queue<T>>& getStackData() {
        return stack;
    }
};

// Merge two queues in a stack
template <typename T>
void mergeInnerQueuesInStack(StackOfQueues<T>& stack, size_t i, size_t j, size_t k) {
    if (i >= stack.size() || j >= stack.size() || k > stack.size() || i == j)
        throw runtime_error("Invalid indices for merging");

    auto& stackData = stack.getStackData();

    // Create a new queue for the merged result
    Queue<T> mergedQueue;

    // Merge elements from the i-th queue
    stackData[i].reset();
    for (const auto& val : stackData[i].getData()) {
        mergedQueue.enqueue(val);
    }

    // Merge elements from the j-th queue
    stackData[j].reset();
    for (const auto& val : stackData[j].getData()) {
        mergedQueue.enqueue(val);
    }

    // Ensure indices are processed in correct order to avoid shifting issues
    size_t first = min(i, j);
    size_t second = max(i, j);

    // Erase the original queues
    stackData.erase(stackData.begin() + second);
    stackData.erase(stackData.begin() + first);

    // Insert the merged queue at position `k`
    stackData.insert(stackData.begin() + k, mergedQueue);
}

/**********************************************
 * MAIN FUNCTION FOR TESTING
 **********************************************/

int main() {
    cout << "=== Testing Merge Inner Queues in Stack ===" << endl;

    // Create a stack of queues
    StackOfQueues<int> stack;

    // Create and push queues onto the stack
    Queue<int> queue1;
    queue1.enqueue(1);
    queue1.enqueue(2);

    Queue<int> queue2;
    queue2.enqueue(3);
    queue2.enqueue(4);

    Queue<int> queue3;
    queue3.enqueue(5);
    queue3.enqueue(6);

    Queue<int> queue4;
    queue4.enqueue(7);
    queue4.enqueue(8);

    stack.push(queue1);
    stack.push(queue2);
    stack.push(queue3);
    stack.push(queue4);

    // Print the stack before merging
    cout << "Stack before merging:" << endl;
    stack.print();

    // Merge queue1 and queue2, insert at position 2, and remove original queues at positions 0 and 1
    mergeInnerQueuesInStack(stack, 0, 1, 2);

    // Print the stack after merging
    cout << "Stack after merging queues 0 and 1 into position 2:" << endl;
    stack.print();

    return 0;
}